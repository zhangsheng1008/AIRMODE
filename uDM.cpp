//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tdm *dm;
//---------------------------------------------------------------------------
__fastcall Tdm::Tdm(TComponent* Owner)
	: TDataModule(Owner)
{
	for (int i = 0; i < 50; i++) {
		TADODataSet *ds = new TADODataSet(this);
		ds->Connection = this->dbConn;
		dsPool[i] = ds;
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
TADODataSet* __fastcall  Tdm::queryDS(String sql)
{
	TADODataSet *ds = new TADODataSet(NULL);
	ds->Connection = this->dbConn;
	ds->CommandText = sql;
	ds->Open();
	ds->First();
	return ds;

}
//---------------------------------------------------------------------------

TADODataSet* __fastcall  Tdm::query(String sql)
{
	for (int i = 0; i < 50; i++) {
		if (dsPool[i]->Active == false) {
				dsPool[i]->CommandText = sql;
				dsPool[i]->Open();
				dsPool[i]->First();
				return dsPool[i];
		}
	}
	return query(sql);

}

//---------------------------------------------------------------------------

void __fastcall Tdm::DataModuleCreate(TObject *Sender)
{
	char hostName[300];
	unsigned long len = 300;
	if (GetComputerName(hostName, &len) == false){
	   ShowMessage("Get SYS Name Error");
	   return;
	}

	//this->dbConn->ConnectionString = "Provider=SQLNCLI11.1;Integrated Security=SSPI;Persist Security Info=False;User ID=\"\";Initial Catalog=airmode;Data Source=ZSLABTOP-PC\\SQLEXPRESS;Initial File Name=\"\";Server SPN=\"\"";
	this->dbConn->ConnectionString = "Provider=SQLNCLI11.1;Integrated Security=SSPI;Persist Security Info=False;User ID=\"\";Initial Catalog=airmode;Data Source=" + String(hostName) + "\\SQLEXPRESS;Initial File Name=\"\";Server SPN=\"\"";
	this->dbConn->Connected = true;

	tbAirModeMod->Active = true;
	tbSysConfig->Active = true;
	execLog->Active = true;
	tbEEProm->Active = true;
	tbAnalyzer->Active = true;
}
//---------------------------------------------------------------------------


