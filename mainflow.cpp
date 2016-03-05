//---------------------------------------------------------------------------


#pragma hdrstop

#include "mainflow.h"

//---------------------------------------------------------------------------


#pragma package(smart_init)


TStrings *Log;


using namespace std;

//---------------------------------------------------------------------------
void __fastcall TActionThread::executeAction(String actId)
{
	runStatus  = runStatus + ",executeAction";
	TADODataSet* actionDS = load("select * from action_list where id = " + actId);
	int operationId = actionDS->FieldByName("operation_id")->AsInteger;
	runStatus  = runStatus + ",saverunmode";
	BaseAction *action = createAction(operationId);
	if (action->component->code == "MODULE") {
	   action->component->port = "\\\\.\\COM" + actionDS->FieldByName("com_port")->AsString;
	}

	TStringList *commandpara = new TStringList;
	commandpara->CommaText = actionDS->FieldByName("command_para1")->AsString;
	action->operationPara = commandpara;
	for (int i = 2; i <= 6; i++) {
	  if (actionDS->FieldByName("command_para" + IntToStr(i))->AsString != "") {
		  action->operationPara->Add(actionDS->FieldByName("command_para" + IntToStr(i))->AsString);
	  }
	}
	action->runMode = runMode;

	action->execute();
	runStatus  = runStatus + ",execute";
	actionDS->Edit();
	actionDS->FieldByName("status")->AsInteger = 1;
	actionDS->FieldByName("run_time")->AsDateTime = Now();
	actionDS->FieldByName("thread_id")->AsString = UIntToStr(this->ThreadID);
	actionDS->FieldByName("command_desc")->AsString = action->GetExecuteDesc();
	if (Trim(action->component->code) != "CLOCK" && Trim(action->component->code) != "DATA_PROC") {
	   ComponentAction *pCompAction = dynamic_cast<ComponentAction *>(action);
	   actionDS->FieldByName("command")->AsString = pCompAction->command_str;
	   actionDS->FieldByName("result")->AsString = pCompAction->result_str;
	   for (int i = 0; i < 6; i++) {
		  actionDS->FieldByName("result_" + IntToStr(i + 1))->AsString = pCompAction->parseResult[i];
	   }
	}
	actionDS->Post();
	releaseDS(actionDS);
	delete action;

}
//---------------------------------------------------------------------------

String __fastcall TRunFlowThread::getOperaCom(int operId, String operPara)
{

}
//---------------------------------------------------------------------------
void __fastcall TActionThread::writeLog(int type, String log)
{
}
//---------------------------------------------------------------------------
void __fastcall TActionThread::logInfo(String log)
{
	writeLog(0, log);
}
//---------------------------------------------------------------------------
void __fastcall TActionThread::logError(String log)
{
	writeLog(1, log);
}
//---------------------------------------------------------------------------
void __fastcall TModuleThread::writeLog(int type, String log)
{


}
//---------------------------------------------------------------------------
void __fastcall TRunFlowThread::writeLog(int type, String log)
{


}

//---------------------------------------------------------------------------
void __fastcall TRunFlowThread::loadSysConfig(){

}

//---------------------------------------------------------------------------
void __fastcall TRunFlowThread::loadExperimentConfig(int expermentid){

}

//---------------------------------------------------------------------------
void __fastcall TRunFlowThread::genActionList(int groupId){


}
//---------------------------------------------------------------------------
void __fastcall TRunFlowThread::prepareGroupPara(int groupId){

}
//---------------------------------------------------------------------------
void __fastcall TRunFlowThread::initConfig(int experimentid){

}

//---------------------------------------------------------------------------
void __fastcall TRunFlowThread::Execute(){
	try
	{
		TADODataSet *expDS = load("select * from experiment where id =  " + IntToStr(runId));
		logInfo("Init Config Begin");
		initConfig(expDS->FieldByName("experiment_config_id")->AsInteger);
		logInfo("Init Config End");
		session["runid"] = IntToStr(runId);
		TStringList *flows = new TStringList;
		//if (expDS->FieldByName("flows")->AsString.Pos(",") > 0) {
		   flows->DelimitedText = expDS->FieldByName("flows")->AsString;
		//} else {
		//   flows->Add(expDS->FieldByName("flows")->AsString);
		//}

		releaseDS(expDS);
		logInfo("Prepare FLow Config Begin");
		runStatus = "Gen Action List";
		for (int i = 0; i < flows->Count  && Terminated == false; i++) {
			prepareGroupPara(StrToInt((*flows)[i]));
		}
		delete flows;
		logInfo("Prepare FLow Config End");
		logInfo("Execute command Begin");
		runStatus = "Running";
		run();
		logInfo("Execute command End");
	} catch (Sysutils::Exception &e){
		logError(e.Message);

	}

}
//---------------------------------------------------------------------------
__fastcall TRunFlowThread::TRunFlowThread(int id, int mode):TActionThread(mode)
{
	runId = id;
	FreeOnTerminate = true;
}


//---------------------------------------------------------------------------
bool __fastcall TRunFlowThread::waitForSubThread(){
   for (TSubThreadList::iterator pr = subThreadList.begin(); pr != subThreadList.end(); pr++) {
		(*pr)->WaitFor();
   }
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TRunFlowThread::clearSubThread(){
   for (TSubThreadList::iterator pr = subThreadList.begin(); pr != subThreadList.end(); pr++) {
		delete (*pr);
   }
	subThreadList.clear();

}
//---------------------------------------------------------------------------

void __fastcall TRunFlowThread::TerminateSubThread(){
   for (TSubThreadList::iterator pr = subThreadList.begin(); pr != subThreadList.end(); pr++) {
		 (*pr)->Terminate();
   }

}

//---------------------------------------------------------------------------
void __fastcall TRunFlowThread::run(){
	Config subThreadAct;
	TADODataSet *actionList = load("select t1.id, t2.component_code, t1.com_port from action_list t1, v_com_oper t2 where t1.operation_id = t2.id and t1.status = 0 and t1.run_id =  " + IntToStr(runId)  + " order by t1.id asc");
	TStringList *actIds = new TStringList();
	TStringList *comps = new TStringList();
	TStringList *ports = new TStringList();
	actionList->First();
	while (actionList->Eof == false) {
	   actIds->Add(IntToStr(actionList->FieldByName("id")->AsInteger));
	   comps->Add(actionList->FieldByName("component_code")->AsString);
	   ports->Add(actionList->FieldByName("com_port")->AsString);
	   actionList->Next();
	}
	releaseDS(actionList);
	int i = 0;
	while (i < actIds->Count && Terminated == false) {
		if ((*comps)[i] == "MODULE") {
			if (subThreadAct[(*ports)[i]] == NULL) {
			   TStringList *ids = new TStringList();
			   subThreadAct[(*ports)[i]] = ids;
			}
			subThreadAct[(*ports)[i]]->Add((*actIds)[i]);
			i++;
			if (i == actIds->Count || (*comps)[i] != "MODULE") {
				for (Config::iterator subAct = subThreadAct.begin(); subAct != subThreadAct.end(); subAct++){
					PThread subThread = new TModuleThread(runMode, subAct->second);
					subThread->Start();
					subThreadList.push_back(subThread);
				}
				if (Terminated == false){
				   waitForSubThread();
				}

				clearSubThread();
				subThreadAct.clear();
			}
		} else {
			executeAction((*actIds)[i]);
			i++;
		}
	}

	delete actIds;
	delete comps;
	delete ports;
}

//---------------------------------------------------------------------------
__fastcall TRunFlowThread::~TRunFlowThread()
{
	for (Config::iterator cit = cfg.begin(); cit != cfg.end(); ++cit){
		if (cit->first != "C_DATA" && cit->first != "T" && cit->first != "C_VALVE") {
			delete cit->second;
		}
	}
	clearSubThread();
}
//---------------------------------------------------------------------------
__fastcall TModuleThread::TModuleThread(int mode, TStringList *actionList):TActionThread(mode){
	actIds = actionList;

}

//---------------------------------------------------------------------------

__fastcall TActionThread::~TActionThread(){
	logInfo(" ds released");
	for (int i = 0; i < DS_MAX_NUM; i++) {

		delete threadDataSetPool[i];
		delete dbCon[i];
	}
}
//---------------------------------------------------------------------------
__fastcall TActionThread::TActionThread(int mode):TThread(true)
{
	runMode = mode;
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
}
//---------------------------------------------------------------------------

 void __fastcall TActionThread::releaseDS(TADODataSet *ds)
{
	ds->Close();
	ds->Tag = 0;
}
//---------------------------------------------------------------------------
TADODataSet* __fastcall TActionThread::load(String sql)
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
		logError(" loadds error " + sql + " \n errormsg" + e.Message);
	} catch (...){
		logError(" loadds error.");
	}


}

//---------------------------------------------------------------------------
__fastcall TModuleThread::~TModuleThread()
{
	if (actIds != NULL) {
	   delete actIds;
	}
}
//---------------------------------------------------------------------------
void __fastcall TModuleThread::Execute(){
	int i = 0;
	if (actIds != NULL) {


		while (i < actIds->Count && Terminated == false) {
		  try{
		        actionId = StrToInt((*actIds)[i]);
				runStatus = (*actIds)[i];
				executeAction((*actIds)[i]);
				actionId = StrToInt((*actIds)[i]);
		  }catch (EListError &e){
				logError(e.Message);

		  } catch (Sysutils::Exception &e){
			logError(" action execute error " + e.Message);
		  }catch(...) {
			logError(runStatus);
		  }
		  i++ ;
	   }

   }
}
//---------------------------------------------------------------------------





BaseAction * __fastcall  TActionThread::createAction(int operationId){
	runStatus = runStatus + ",CreateAction";
	TADODataSet *compDS= load("select * from v_com_oper where id = " + IntToStr(operationId));
    BaseAction *action;
	if (compDS->RecordCount == 1) {
		String componentCode =  Trim(compDS->FieldByName("component_code")->AsString);
		action = createActionByComp(componentCode);
		runStatus = runStatus + ",createActionByComp";
		if (action != NULL) {
			action->Init(compDS);

			runStatus = runStatus + ",Init";
		}

	}
	releaseDS(compDS);
	return action;
}

