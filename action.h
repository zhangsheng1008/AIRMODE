//---------------------------------------------------------------------------

#ifndef actionH
#define actionH

#include <Classes.hpp>
#include <vcl.h>
#include "uDM.h"
#include "util.h"
#include <vector>
//---------------------------------------------------------------------------
const int DS_MAX_NUM = 20;

const int RESULT_SUCC = 0;
const int ERR_OPEN_PORT = 1;
const int ERR_SET_PORT = 2;
const int ERR_READ_PORT = 3;
const int ERR_WRITE_PORT = 4;

const int TEST_MODE = 1;
const int NORMAL_MODE = 0;

using namespace std;
class TModuleThread : public TThread
{
	private:
		int runMode;
		int portNum;
		int runId;
		int ivl;
		DCB dcb;
		HANDLE hCom;
		TStringList *sendCmdList;
		TStringList *recieveCmdList;
		TStringList *idList;
		TADODataSet *threadDataSetPool[DS_MAX_NUM];
		TADOConnection *dbCon[DS_MAX_NUM];
		TADODataSet* __fastcall load(String sql);
		virtual void __fastcall releaseDS(TADODataSet *ds);
		void __fastcall send();
		int __fastcall recieve();
		void __fastcall buildCommand();
		virtual __fastcall int openComPort();
		void __fastcall saveResult(String id, String command,  unsigned char* result, DWORD);
	protected:
	public:
		__fastcall TModuleThread(int runid, int port, int interval, int mode);
		virtual void __fastcall Execute();
		virtual __fastcall ~TModuleThread();
};

typedef TModuleThread* PThread;
typedef vector<PThread> TSubThreadList;




#endif
