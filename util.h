//---------------------------------------------------------------------------

#ifndef utilH
#define utilH
#include <vcl.h>
#include <Forms.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <StdCtrls.hpp>
#include <iostream.h>
#include <ADODB.hpp>
#include "uDM.h"
//---------------------------------------------------------------------------

typedef struct {
	int addr_485;
	int addr_iic[20];
}  Mod;

typedef struct{
	int pageNum;
	int checkState;
	Mod mod[60];
} ModGroup;



const String REG_LEFT_SYMBOL = "{";
const String REG_RIGHT_SYMBOL = "}";
String _fastcall paraProcess(String src, String para[]);
TStringList* _fastcall regexMap(String src, String regex);
void _fastcall setFormComponentCaption(TForm *form, String prefix, String content);
unsigned char* convertHexCommand(String cmd, unsigned int *len);
String convertHexResult(unsigned char* buf, int len);
unsigned char* flowHexPara(float flow);
float convertFlowValue(unsigned char* buf);
String __fastcall sensibilityPara(String c);
TComponent* __fastcall getComponentByName(TForm* form, String name);
void _fastcall queryDS(TADODataSet *ds, String sql);
String __fastcall analyzePPM(unsigned char *result, int groupNum, int resultSize);
HANDLE __fastcall openPort(String portNum, int baudRate);
void __fastcall writePort(HANDLE hCom, unsigned char *command, unsigned int len);
void __fastcall readPort(HANDLE hCom, unsigned char *result, unsigned int &result_size);
#endif
