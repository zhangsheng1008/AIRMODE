//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAirMode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmAirMode *fmAirMode;
//---------------------------------------------------------------------------
__fastcall TfmAirMode::TfmAirMode(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------





void __fastcall TfmAirMode::Button1Click(TObject *Sender)
{
	fmSysConfig->ShowModal() ;
}
//---------------------------------------------------------------------------


void __fastcall TfmAirMode::btnStopClick(TObject *Sender)
{
   for (TSubThreadList::iterator pr = subThreadList.begin(); pr != subThreadList.end(); pr++) {
		 (*pr)->Terminate();
   }

    subThreadList.clear();

	dbnvMod->Enabled = true;
	dcgMod->Enabled = true;
	btnRun->Enabled = true;
	btnStop->Enabled = false;
	qryDetail->Active = false;
	inQuery = false;
	Timer1->Enabled = false;
	inQuery2 = false;
	Timer2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfmAirMode::btnRunClick(TObject *Sender)
{
	if (dm->tbAirModeMod->State == dsEdit || dm->tbAirModeMod->State == dsInsert) {
		dm->tbAirModeMod->Post();
	}
	dbnvMod->Enabled = false;
	dcgMod->Enabled = false;
	btnRun->Enabled = false;
	btnStop->Enabled = true;

    dm->cmdClearAnalyzerData->Execute();

	TStringList *ports = new TStringList();
	tabResult->Tabs->Clear() ;
	dm->tbAirModeMod->First();
	while(dm->tbAirModeMod->Eof == false){
		String port = dm->tbAirModeMod->FieldByName("port")->AsString;
		if (ports->IndexOf(port) == -1) ports->Add(port);
		dm->tbAirModeMod->Next();
		tabResult->Tabs->Append(port + "," + dm->tbAirModeMod->FieldByName("addr")->AsString);
	}


	dm->execLog->Append();
	dm->execLog->FieldByName("execute_time")->AsDateTime = Now();
	dm->execLog->Post() ;
	runId = dm->execLog->FieldByName("id")->AsInteger;
	runMode = 0;
	if (cbRunMode->Checked == true) {
        runMode = 1;
	}

	for (int i = 0 ; i < ports->Count; i++) {
		PThread subThread = new TModuleThread(runId, StrToInt((*ports)[i]), StrToInt(Trim(edtInterval->Text)), runMode);
		subThread->Start();
		subThreadList.push_back(subThread);
	}
	delete ports;
	qryDetail->Parameters->ParamByName("logid")->Value = runId;
	qryDetail->Active = true;
	tabResultChange(this->tabResult);
	inQuery = false;
	inQuery2 = false;
	Timer1->Enabled = true;
	Timer2->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TfmAirMode::Timer1Timer(TObject *Sender)
{
	if (inQuery == false) {
		inQuery = true;
		qryDetail->Requery() ;
		qryDetail->Last() ;

		inQuery = false;
	}

}
//---------------------------------------------------------------------------

void __fastcall TfmAirMode::Button2Click(TObject *Sender)
{
	unsigned int i;
	unsigned char *res = convertHexCommand("0F 14 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 08 C4 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F 14 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 EC", &i);
	ShowMessage(analyzePPM(res, 2, i));
}
//---------------------------------------------------------------------------


bool __fastcall TfmAirMode::readOtherInfo()
{
	int tryTimes = 5;
	int iTimes = 0;
	unsigned int result_size = 0;
	unsigned char result[4096];
	String command;
	String resTpl;
	HANDLE hCom;
	String result_str;
	String port;
	String baud_rate;
	TADODataSet *otherDataDS = dm->query("select * from analyzer_data");
	otherDataDS->Append();

	if (chkAnalyzer->Checked){
		TADODataSet *ds = dm->query("select * from sys_config where code = 'ANALYZER'");
		port = ds->FieldByName("value_1")->AsString;
		baud_rate =  ds->FieldByName("value_2")->AsString;
		ds->Close();

		ds = dm->query("select * from sys_config where code = 'ANALYZER_RES_TPL'");
		resTpl = ds->FieldByName("value_1")->AsString;
		ds->Close();

		hCom = openPort(port, StrToInt(baud_rate));

		while(result_size == 0 && iTimes < tryTimes){
			readPort(hCom, result, result_size);
			iTimes++;
			Sleep(500);
		}
		for (unsigned int i = 0;i < result_size && result_size <= 4096; i++) {
		   result_str = result_str + (char)(result[i]);
		}
		TStrings *s = regexMap(result_str, resTpl);
		CloseHandle(hCom);
		otherDataDS->FieldByName("analyzer_return_info")->AsString = result_str;
		otherDataDS->FieldByName("analyzer_data")->AsString = Trim(s->Text);
		analyzerData = StrToFloat(otherDataDS->FieldByName("analyzer_data")->AsString);
		delete s;
	}

	if (chkPress->Checked){
		TADODataSet *ds = dm->query("select * from sys_config where code = 'PRESSURE'");
		port = ds->FieldByName("value_1")->AsString;
		baud_rate =  ds->FieldByName("value_2")->AsString;
		ds->Close();

		ds = dm->query("select * from sys_config where code = 'PRESSURE_CMD'");
		command = ds->FieldByName("value_1")->AsString;
		resTpl = ds->FieldByName("value_2")->AsString;
		ds->Close();
		unsigned int pressCmdLen;
		unsigned char *pressCmd = convertHexCommand(command, &pressCmdLen);
		result_size = 0;
		tryTimes = 0;
		for (int i = 0; i < result_size; i++) {
           result[i] = 0;
		}
		while(result_size == 0 && iTimes < tryTimes){
			sendCmdToComPort(port, StrToInt(baud_rate), pressCmd, pressCmdLen, result, result_size);
			iTimes++;
		}

		for (unsigned int i = 0;i < result_size && result_size <= 4096; i++) {
		   result_str = result_str + (char)(result[i]);
		}
		TStrings *pressRes = regexMap(result_str, resTpl);

		otherDataDS->FieldByName("pressure_return_info")->AsString = result_str;
		otherDataDS->FieldByName("pressure_data")->AsString = pressRes->Text;
		delete pressRes;
	}

	if (chkTemp->Checked){
		TADODataSet *ds = dm->query("select * from sys_config where code = 'TEMP'");
		port = ds->FieldByName("value_1")->AsString;
		baud_rate =  ds->FieldByName("value_2")->AsString;
		ds->Close();

		result_size = 0;
		tryTimes = 0;
		for (int i = 0; i < result_size; i++) {
           result[i] = 0;
		}
		while(result_size == 0 && iTimes < tryTimes){
			sendCmdToComPort(port, StrToInt(baud_rate), NULL, 0, result, result_size);
			iTimes++;
			Sleep(500);
		}
		if (result_size > 0) {
			for (unsigned int i = 0;i < result_size && result_size <= 4096; i++) {
			   result_str = result_str + (char)(result[i]);
			}
			TStrings *pressRes = regexMap(result_str, resTpl);
			otherDataDS->FieldByName("temp_return_info")->AsString = result_str;
			otherDataDS->FieldByName("temp_data")->AsString = Trim(pressRes->Text);
			otherDataDS->FieldByName("humi_data")->AsString = Trim(pressRes->Text);
			delete pressRes;
		}

	}

	otherDataDS->Post();
	otherDataDS->Close();
	if (qryAnalyzer->Active == false) qryAnalyzer->Open();
	qryAnalyzer->Requery() ;
	return true;
}


void __fastcall TfmAirMode::btnEEPromClick(TObject *Sender)
{
	runMode = 0;
	if (cbRunMode->Checked == true) {
        runMode = 1;
	}
	dm->cmdClearEEProm->Execute();
	String commandPara[3];
	dbcgEEProm->Refresh();
	TADODataSet *modConfig = dm->query("select * from module_config ");
	TADODataSet *cmdConfig = dm->query("select * from sys_config where code = 'EEPROM'");
	String sendCommandTpl = cmdConfig->FieldByName("value_1")->AsString;
	String recCommandTpl = cmdConfig->FieldByName("value_2")->AsString;

	cmdConfig->Close();
	modConfig->First();
	TADODataSet *ds = dm->query("select * from sys_config where code = 'EEPROM_TPL'");
	String resTpl = ds->FieldByName("value_1")->AsString;
	ds->Close();


	while(modConfig->Eof == false){
		String addr = modConfig->FieldByName("addr")->AsString;
		String port =modConfig->FieldByName("port")->AsString;
		String baudRate = modConfig->FieldByName("baud_rate")->AsString;
		HANDLE hCom;
		if (runMode == 0) {
		  hCom = openPort(port, StrToInt(baudRate));
		  if (hCom == NULL) {
             return; 
		  }
		}


		commandPara[0] = addr;
		TADODataSet *baudDS = dm->query("select * from sys_config where code = 'baudrate_para' and value_1 = '" + modConfig->FieldByName("command_baud_rate")->AsString + "'");
		commandPara[2] = baudDS->FieldByName("value_2")->AsString;
		baudDS->Close();
		for (int i = 10; i < 30; i++) {
			String iicAddr = "0" + IntToStr(i);
			commandPara[1] = RightStr(AnsiString(iicAddr), 2);
			String sendCommand = paraProcess(sendCommandTpl, commandPara);
			String recCommand = paraProcess(recCommandTpl, commandPara);
			String result_str;
            String res = "";

			if (runMode == 0) {
				unsigned int len;
				unsigned char* command = convertHexCommand(sendCommand, &len);
				writePort(hCom, command, len);
				delete command;
				Sleep(StrToInt(edtInterval->Text) * 1000);

				command = convertHexCommand(recCommand, &len);
				writePort(hCom, command, len);
				delete command;
				Sleep(StrToInt(edtInterval->Text) * 1000);

				unsigned char result[4096];
				unsigned int result_size;
				readPort(hCom, result, result_size);
				for (unsigned int i = 0;i < result_size && result_size <= 4096; i++) {
				   result_str = result_str + (char)(result[i]);
				}
				TStrings *s = regexMap(result_str, resTpl);
				for (int c = 0; c < s->Count; c++) {
				   res = res + (*s)[c] + "  ";
				}
			}
			dm->tbEEProm->Append();
			dm->tbEEProm->FieldByName("addr")->AsString = commandPara[0] + "," + commandPara[1];
			dm->tbEEProm->FieldByName("command")->AsString = "W: " + sendCommand + "  R:" + recCommand;
			dm->tbEEProm->FieldByName("result")->AsString = res;
			dm->tbEEProm->FieldByName("return_info")->AsString = result_str;
			dm->tbEEProm->Post();
            dbcgEEProm->Refresh();
		}
		if (runMode == 0 && hCom != NULL) CloseHandle(hCom);
		modConfig->Next();
	}
	modConfig->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfmAirMode::readModNo()
{
	runMode = 0;
	if (cbRunMode->Checked == true) {
        runMode = 1;
	}
	String commandPara[2];
	TADODataSet *modConfig = dm->query("select * from module_config ");
	TADODataSet *cmdConfig = dm->query("select * from sys_config where code = 'READ_MODNO'");
	String sendCommandTpl = cmdConfig->FieldByName("value_1")->AsString;
	String resTpl = cmdConfig->FieldByName("value_2")->AsString;

	cmdConfig->Close();
	modConfig->First();

	while(modConfig->Eof == false){
		String addr = modConfig->FieldByName("addr")->AsString;
		String port = modConfig->FieldByName("port")->AsString;
		String baudRate = modConfig->FieldByName("baud_rate")->AsString;
		HANDLE hCom;
		if (runMode == 0) {
          hCom = openPort(port, StrToInt(baudRate));
		}

		commandPara[0] = addr;

		for (int i = 10; i < 30; i++) {
			String iicAddr = "0" + IntToStr(i);
			commandPara[1] = RightStr(AnsiString(iicAddr), 2);
			String sendCommand = paraProcess(sendCommandTpl, commandPara);
			String result_str;
            String res = "";

			if (runMode == 0) {
				unsigned int len;
				unsigned char* command = convertHexCommand(sendCommand, &len);
				writePort(hCom, command, len);
				delete command;
				Sleep(StrToInt(edtInterval->Text) * 1000);


				unsigned char result[4096];
				unsigned int result_size;
				readPort(hCom, result, result_size);
				for (unsigned int i = 0;i < result_size && result_size <= 4096; i++) {
				   result_str = result_str + (char)(result[i]);
				}
				TStrings *s = regexMap(result_str, resTpl);
				for (int c = 0; c < s->Count; c++) {
				   res = res + (*s)[c] + "  ";
				}
			}
			dm->tbModNo->Append();
			dm->tbModNo->FieldByName("addr")->AsString = commandPara[0] + "," + commandPara[1];
			dm->tbModNo->FieldByName("log_id")->AsInteger = runId;
			dm->tbModNo->FieldByName("mod_no")->AsString = res;
			dm->tbModNo->FieldByName("command")->AsString = sendCommand;
			dm->tbModNo->FieldByName("return_info")->AsString = result_str;
			dm->tbModNo->Post();
		}
		if (runMode == 0 && hCom != NULL) CloseHandle(hCom);
		modConfig->Next();
	}
	modConfig->Close();



}



void __fastcall TfmAirMode::tabResultChange(TObject *Sender)
{
	if (tabResult->TabIndex >= 0){
		TStringList *s = new TStringList();
		s->DelimitedText = (*(tabResult->Tabs))[tabResult->TabIndex];
		qryDetail->Filter = "port=" + (*s)[0] + " and addr=" + (*s)[1];
		delete s;
		qryDetail->Filtered = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmAirMode::Timer2Timer(TObject *Sender)
{
	if (inQuery2 == false) {
		if (chkAnalyzer->Checked || chkTemp->Checked || chkPress->Checked) readOtherInfo();
		inQuery2 = true;
	}
}
//---------------------------------------------------------------------------


