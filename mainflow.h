//---------------------------------------------------------------------------

#ifndef mainflowH
#define mainflowH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <vcl.h>
#include <map>
#include "action.h"
#include "uDM.h"
#include "util.h"
using namespace std;
typedef map<String, TStringList*> Config;
typedef pair<String, TStringList*> ConfigItem;
typedef map<String, String> StrMap;
const int DS_MAX_NUM = 20;

class TActionThread : public TThread
{
	private:
		BaseAction * __fastcall  createAction(int operationId);

		TADODataSet *threadDataSetPool[DS_MAX_NUM];
		TADOConnection *dbCon[DS_MAX_NUM];

	protected:
		int runMode;
		virtual void __fastcall writeLog(int type, String log);
		virtual void __fastcall executeAction(String actId);
		TADODataSet* __fastcall load(String sql);
		virtual void __fastcall releaseDS(TADODataSet *ds);
		virtual __fastcall TActionThread(int mode);
		virtual __fastcall ~TActionThread();
		virtual void __fastcall logInfo(String log);
		virtual void __fastcall logError(String log);
	public:
		String runStatus;
};

class TModuleThread : public TActionThread
{
	private:
		TStringList *actIds;
		int actionId;

		virtual void __fastcall writeLog(int type, String log);
	protected:
	public:
		__fastcall TModuleThread(int mode, TStringList *actionList);
		virtual void __fastcall Execute();
		virtual __fastcall ~TModuleThread();
};

typedef TModuleThread* PThread;
typedef vector<PThread> TSubThreadList;


class TRunFlowThread : public TActionThread
{
	private:
		StrMap session;
		StrMap modAddr;
		Config cfg;
		int runId;
		int experimentId;
		TSubThreadList subThreadList;
		void __fastcall loadSysConfig();
		void __fastcall loadExperimentConfig(int expermentid);
		void __fastcall genActionList(int groupId);
		void __fastcall prepareGroupPara(int groupId);
		void __fastcall initConfig(int experimentid);
		bool __fastcall waitForSubThread();
		void __fastcall clearSubThread();
		void __fastcall run() ;
		virtual void __fastcall writeLog(int type, String log);
		String __fastcall getOperaCom(int operId, String operPara) ;
	public:
		__fastcall TRunFlowThread(int id, int mode);
		virtual void __fastcall TerminateSubThread();
		void __fastcall Execute();
		virtual __fastcall ~TRunFlowThread();
};




void processTest(String groupCode, TStrings* log);
#endif

