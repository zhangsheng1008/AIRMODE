//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uComponentConfig.h"
#include "uDM.h"
#include "action.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmComponentConfig *fmComponentConfig;
//---------------------------------------------------------------------------
__fastcall TfmComponentConfig::TfmComponentConfig(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


Component* __fastcall loadCompConfig(){

}

Operation* __fastcall loadOperation(){

}





void __fastcall TfmComponentConfig::Button1Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------


void __fastcall TfmComponentConfig::FormClose(TObject *Sender, TCloseAction &Action)

{
	this->Free();
	fmComponentConfig = NULL;
}
//---------------------------------------------------------------------------

