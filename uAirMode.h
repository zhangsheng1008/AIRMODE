//---------------------------------------------------------------------------

#ifndef uAirModeH
#define uAirModeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCGrids.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "uDM.h"
#include "uConfig.h"
#include "action.h"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfmAirMode : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TDBCtrlGrid *dcgMod;
	TLabel *Label1;
	TLabel *port;
	TLabel *baudrate;
	TDBEdit *DBEdit1;
	TDBComboBox *DBComboBox1;
	TDBComboBox *DBComboBox2;
	TDBCheckBox *passive;
	TDBCheckBox *dac;
	TDBNavigator *dbnvMod;
	TButton *btnRun;
	TLabel *Label2;
	TDBComboBox *DBComboBox3;
	TLabel *Label3;
	TMaskEdit *edtInterval;
	TButton *btnStop;
	TDBGrid *DBGrid1;
	TPanel *Panel1;
	TPanel *Panel2;
	TButton *Button1;
	TTimer *Timer1;
	TDataSource *dsDetail;
	TADOQuery *qryDetail;
	TDBGrid *DBGrid2;
	TCheckBox *cbRunMode;
	TButton *Button2;
	TTabSheet *TabSheet3;
	TDBCtrlGrid *dbcgEEProm;
	TDBMemo *DBMemo1;
	TDBMemo *DBMemo2;
	TDBText *DBText1;
	TButton *btnEEProm;
	TDBMemo *DBMemo3;
	TDBGrid *DBGrid3;
	TADOQuery *qryAnalyzer;
	TCheckBox *chkAnalyzer;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall btnStopClick(TObject *Sender);
	void __fastcall btnRunClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall btnEEPromClick(TObject *Sender);
private:	// User declarations
	int runId;
	int runMode;
	TSubThreadList subThreadList;
	bool inQuery;
	bool __fastcall readAnalyze() ;
	void __fastcall readModNo();
public:		// User declarations
	__fastcall TfmAirMode(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmAirMode *fmAirMode;
//---------------------------------------------------------------------------
#endif
