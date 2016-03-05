//---------------------------------------------------------------------------

#ifndef uSysConfigH
#define uSysConfigH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfmSysConfig : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TDBGrid *DBGrid2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TfmSysConfig(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSysConfig *fmSysConfig;
//---------------------------------------------------------------------------
#endif
