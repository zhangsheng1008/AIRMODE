//---------------------------------------------------------------------------

#ifndef uDMH
#define uDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <memory>
//---------------------------------------------------------------------------


class Tdm : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *dbConn;
	TDataSource *dsAirModeMod;
	TADOTable *tbAirModeMod;
	TADOTable *tbSysConfig;
	TDataSource *dsSysConfig;
	TADOTable *execLog;
	TDataSource *dsLog;
	TADOTable *tbEEProm;
	TADOTable *tbAnalyzer;
	TDataSource *dsEEProm;
	TDataSource *dsAnalyzer;
	TADOCommand *CmdEEPromClear;
	void __fastcall DataModuleCreate(TObject *Sender);
private:	// User declarations
	TADODataSet* dsPool[50];
public:		// User declarations
	__fastcall Tdm(TComponent* Owner);
	TADODataSet* __fastcall query(String sql);
	TADODataSet* __fastcall queryDS(String sql);
};
//---------------------------------------------------------------------------
extern PACKAGE Tdm *dm;
//---------------------------------------------------------------------------
#endif
