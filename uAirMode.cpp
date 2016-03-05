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
	dbnvMod->Enabled = true;
	dcgMod->Enabled = true;
	btnRun->Enabled = true;
	btnStop->Enabled = false;
	qryDetail->Active = false;
	inQuery = false;
	Timer1->Enabled = false;
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

	TStringList *ports = new TStringList();
	dm->tbAirModeMod->First();
	while(dm->tbAirModeMod->Eof == false){
		String port = dm->tbAirModeMod->FieldByName("port")->AsString;
		if (ports->IndexOf(port) == -1) ports->Add(port);
        dm->tbAirModeMod->Next();
	}

	dm->execLog->Append();
	dm->execLog->FieldByName("execute_time")->AsDateTime = Now();
	dm->execLog->Post() ;
	runId = dm->execLog->FieldByName("id")->AsInteger;
	int runMode = 0;
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
	inQuery = false;
	Timer1->Enabled = true;
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

