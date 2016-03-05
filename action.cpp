//---------------------------------------------------------------------------


#pragma hdrstop

#include "action.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall TModuleThread::TModuleThread(int runid, int port, int interval, int mode):TThread(true)
{
	runMode = mode;
	portNum = port;
	runId = runid;
	ivl = interval;
	for (int i = 0; i < DS_MAX_NUM; i++) {
		TADODataSet *ds = new TADODataSet(NULL);
		dbCon[i] = new TADOConnection(NULL);
		dbCon[i]->ConnectionString = dm->dbConn->ConnectionString;
		dbCon[i]->LoginPrompt = false;
		dbCon[i]->Connected = true;
		ds->Connection = dbCon[i];
		ds->Tag = 0;
		threadDataSetPool[i] = ds;
	}
	sendCmdList = new TStringList();
	recieveCmdList = new TStringList();
	idList = new TStringList();
}
//---------------------------------------------------------------------------
void __fastcall TModuleThread::Execute()
{
	if (openComPort() != RESULT_SUCC) {
		ShowMessage("open port error");
	} else {
		buildCommand();
		while(Terminated == false){
			send();
			recieve();
		}
	}
}
//---------------------------------------------------------------------------
__fastcall TModuleThread::~TModuleThread()
{
	for (int i = 0; i < DS_MAX_NUM; i++) {

		delete threadDataSetPool[i];
		delete dbCon[i];
	}
	delete sendCmdList;
	delete recieveCmdList;
	delete idList;
	CloseHandle(hCom);
}
//---------------------------------------------------------------------------

 void __fastcall TModuleThread::releaseDS(TADODataSet *ds)
{
	ds->Close();
	ds->Tag = 0;
}
//---------------------------------------------------------------------------
TADODataSet* __fastcall TModuleThread::load(String sql)
{

	try{
		for (int i = 0; i < DS_MAX_NUM; i++) {
			if (threadDataSetPool[i]->Tag == 0) {
					threadDataSetPool[i]->Tag = 1;
					if (threadDataSetPool[i]->Active == false) {
						threadDataSetPool[i]->CommandText = sql;
						threadDataSetPool[i]->Open();
						threadDataSetPool[i]->First();
						return threadDataSetPool[i];
					}
			}
		}
		throw new Sysutils::Exception("non idle ds can use");
	} catch (Sysutils::Exception &e){
	} catch (...){

	}


}
//---------------------------------------------------------------------------
void __fastcall TModuleThread::buildCommand()
{
	TADODataSet *modDS = load("select * from module_config where port = " + IntToStr(portNum));
	while (modDS->Eof == false){
		String addrPara = modDS->FieldByName("addr")->AsString;

		TADODataSet *baudParaConfig = load("select value_2 from sys_config where code = 'baudrate_para' and value_1 = '" + modDS->FieldByName("command_baud_rate")->AsString + "'");
		String baudPara =  baudParaConfig->FieldByName("value_2")->AsString;
		releaseDS(baudParaConfig);
		String commandCode = "CMD_";
		if (modDS->FieldByName("passive")->AsBoolean == true)
		   commandCode = commandCode + "ACTIVE";
		else
		   commandCode = commandCode + "PASSIVE";

		if (modDS->FieldByName("dac")->AsBoolean == true)
		   commandCode = commandCode + "_DAC";

		TADODataSet *commandConfig = load("select * from sys_config where code = '" + commandCode + "'");
		String sendCmd = commandConfig->FieldByName("value_1")->AsString;
		String recieveCmd = commandConfig->FieldByName("value_2")->AsString;
		releaseDS(commandConfig);

		String  para1[2] = {addrPara, baudPara};
		String  para2[1] = {addrPara};
		sendCmd = paraProcess(sendCmd, para1);
		recieveCmd = paraProcess(recieveCmd, para2);
		sendCmdList->Add(paraProcess(sendCmd, para1));
		recieveCmdList->Add(paraProcess(recieveCmd, para2));
        idList->Add(modDS->FieldByName("id")->AsString);
      	modDS->Next();
	}
	releaseDS(modDS);

}
//---------------------------------------------------------------------------
void __fastcall TModuleThread::send()
{

	for (int i = 0; i < sendCmdList->Count; i++) {
		Sleep(1000* ivl);
		if (runMode == TEST_MODE) {
			continue;
		}
		unsigned int len;
		unsigned char* command = convertHexCommand((*sendCmdList)[i], &len);
		DWORD lpNumberOfBytesWritten;
		PurgeComm(hCom,PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
		WriteFile(hCom, command, len, &lpNumberOfBytesWritten, NULL);

	}

}
//---------------------------------------------------------------------------
int __fastcall TModuleThread::recieve()
{

	for (int i = 0; i < recieveCmdList->Count; i++) {
		DWORD result_size ;
		unsigned char result[4096];
		if (runMode != TEST_MODE) {
			unsigned int len;
			unsigned char* command = convertHexCommand((*recieveCmdList)[i], &len);
			DWORD lpNumberOfBytesWritten;
			PurgeComm(hCom,PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
			WriteFile(hCom, command, len, &lpNumberOfBytesWritten, NULL);
			DWORD lpErr ,lpNumberOfBytesRead;
			COMSTAT comStat;
			ClearCommError(hCom,  &lpErr, &comStat);
			if (comStat.cbInQue > 4096 || comStat.cbInQue == 0) {
				PurgeComm(hCom,PURGE_RXCLEAR);
				return ERR_READ_PORT;
			}
			result_size = comStat.cbInQue;
			ReadFile(hCom, result, comStat.cbInQue, &lpNumberOfBytesRead, NULL);
		}
		saveResult((*idList)[i], "W:" + (*sendCmdList)[i] + "  R:" + (*recieveCmdList)[i], &result[0], result_size);

	}
	return RESULT_SUCC;
}
//---------------------------------------------------------------------------
int __fastcall TModuleThread::openComPort(){
	if (runMode == TEST_MODE) {
		return RESULT_SUCC;
	}
	String port = "\\\\.\\COM" + IntToStr(portNum);
	hCom = CreateFile(port.t_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
	if (hCom == INVALID_HANDLE_VALUE) {
		return ERR_OPEN_PORT;
	}

	GetCommState(hCom, &dcb);
	dcb.ByteSize=8;
	dcb.Parity=NOPARITY;
	dcb.StopBits=ONESTOPBIT;
	if (SetCommState(hCom, &dcb) == false){
		CloseHandle(hCom);
		return ERR_SET_PORT;

	}
	return RESULT_SUCC;
}
//---------------------------------------------------------------------------
void __fastcall TModuleThread::saveResult(String id, String command, unsigned char* result, DWORD result_size)
{
	TADODataSet *modDS = load("select * from module_config where id = " + id);
	TADODataSet *execDtl = load("select * from exec_detail where 1=2");
	execDtl->Append();
	execDtl->FieldByName("addr")->AsString = modDS->FieldByName("addr")->AsString;
	execDtl->FieldByName("passive")->AsString = modDS->FieldByName("passive")->AsString;
	execDtl->FieldByName("dac")->AsString = modDS->FieldByName("dac")->AsString;
	execDtl->FieldByName("baud_para")->AsString = modDS->FieldByName("command_baud_rate")->AsString;
	execDtl->FieldByName("log_id")->AsInteger = runId;
	execDtl->FieldByName("command")->AsString = command;
	if (runMode != TEST_MODE) {
		execDtl->FieldByName("result_info")->AsString = convertHexResult(result, result_size);
		int groupNum = 3;
		if (execDtl->FieldByName("dac")->AsBoolean == true) groupNum = 2;
	}
    execDtl->Post();
	releaseDS(modDS);
	releaseDS(execDtl);
}
