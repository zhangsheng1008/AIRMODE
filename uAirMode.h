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
	TPanel *Panel1;
	TPanel *Panel2;
	TButton *Button1;
	TTimer *Timer1;
	TDataSource *dsDetail;
	TADOQuery *qryDetail;
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
	TWideStringField *qryDetailaddr;
	TWideStringField *qryDetailpassive;
	TWideStringField *qryDetaildac;
	TWideStringField *qryDetailbaud_para;
	TWideStringField *qryDetailport;
	TWideStringField *qryDetailvalue_type;
	TIntegerField *qryDetailv10;
	TIntegerField *qryDetailv11;
	TIntegerField *qryDetailv12;
	TIntegerField *qryDetailv13;
	TIntegerField *qryDetailv14;
	TIntegerField *qryDetailv15;
	TIntegerField *qryDetailv16;
	TIntegerField *qryDetailv17;
	TIntegerField *qryDetailv18;
	TIntegerField *qryDetailv19;
	TIntegerField *qryDetailv20;
	TIntegerField *qryDetailv21;
	TIntegerField *qryDetailv22;
	TIntegerField *qryDetailv23;
	TIntegerField *qryDetailv24;
	TIntegerField *qryDetailv25;
	TIntegerField *qryDetailv26;
	TIntegerField *qryDetailv27;
	TIntegerField *qryDetailv28;
	TIntegerField *qryDetailv29;
	TCheckBox *chkPress;
	TCheckBox *chkTemp;
	TButton *btnExport;
	TDBEdit *DBEdit2;
	TLabel *Label6;
	TTabControl *tabResult;
	TDBGrid *DBGrid2;
	TDataSource *dsAnalyzer;
	TTimer *Timer2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall btnStopClick(TObject *Sender);
	void __fastcall btnRunClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall btnEEPromClick(TObject *Sender);
	void __fastcall tabResultChange(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
private:	// User declarations
	int runId;
	int runMode;
	TSubThreadList subThreadList;
	bool inQuery;
	bool inQuery2;
	float analyzerData;
	bool __fastcall readOtherInfo() ;
	void __fastcall readModNo();
public:		// User declarations
	__fastcall TfmAirMode(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmAirMode *fmAirMode;
//---------------------------------------------------------------------------
#endif
