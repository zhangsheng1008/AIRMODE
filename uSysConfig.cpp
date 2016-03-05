//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uSysConfig.h"
#include "uDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmSysConfig *fmSysConfig;
//---------------------------------------------------------------------------
__fastcall TfmSysConfig::TfmSysConfig(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmSysConfig::Button1Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfmSysConfig::FormClose(TObject *Sender, TCloseAction &Action)
{
	this->Free();
	fmSysConfig = NULL;
}
//---------------------------------------------------------------------------

