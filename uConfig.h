//---------------------------------------------------------------------------

#ifndef uConfigH
#define uConfigH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uDM.h"
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfmSysConfig : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TPanel *Panel1;
	TDBNavigator *DBNavigator1;
private:	// User declarations
public:		// User declarations
	__fastcall TfmSysConfig(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSysConfig *fmSysConfig;
//---------------------------------------------------------------------------
#endif
