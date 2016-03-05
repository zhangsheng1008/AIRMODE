//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uConfig.h"
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
