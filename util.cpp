//---------------------------------------------------------------------------


#pragma hdrstop

#include "util.h"
#include "boost/regex.hpp"
#include <Forms.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <StdCtrls.hpp>
#include <sstream>
#include <iostream>
//---------------------------------------------------------------------------

#pragma package(smart_init)
using namespace std;

const char* HEX_REGEX = "([0-9a-fA-F]{2}?)";
const char* COMMMAND_TEMPLATE_REGEX = "(\\{\\d\\.\\d\\})|(\\{\\d\\})";




String _fastcall paraProcess(String src, String para[]){
	boost::regex reg(COMMMAND_TEMPLATE_REGEX);
	int i = 1;
	boost::smatch m;
	String strRep;
	String result = src;
	std::string s = src.t_str();
	std::string::const_iterator it = s.begin();
	std::string::const_iterator end = s.end();
	String reg_last;
	while(boost::regex_search(it, end, m, reg)){
	  int k,j;
	  String paraDes;
	  if (m[1].matched) {
		 paraDes = (m[0].str()).c_str();
		 j = StrToInt(paraDes[2]) - 1;
		 k = StrToInt(paraDes[4]);
		 result = StringReplace(result, paraDes, para[j][k], TReplaceFlags(rfReplaceAll));
	  } else {
		 paraDes = (m[2].str()).c_str();
		 j = StrToInt(paraDes[2]) - 1;
		 strRep = para[j];
		 result = StringReplace(result, paraDes, para[j], TReplaceFlags(rfReplaceAll));
	  }
	  it = m[0].second;
	  i++;
	}

	return result;


}

TStringList* _fastcall regexMap(String src, String regex){
	TStringList *res = new TStringList();
	if (regex == "" || src == "") {
    	return res;
	}
	boost::regex reg(regex.t_str());
	boost::smatch m;
	std::string s = src.t_str();
	std::string::const_iterator it = s.begin();
	std::string::const_iterator end = s.end();
	boost::match_flag_type flags = boost::match_not_dot_newline;
	while(boost::regex_search(it, end, m, reg, flags)){
		for (unsigned int i = 0; i < m.size(); i++) {
			if (m[i+1].matched)
				res->Append(m[i+1].str().c_str());

		}
		it = m[0].second;
	}
	return res;

}

void _fastcall setFormComponentCaption(TForm *form, String prefix, String content){
	String name;
	int idx;
	TStringList *s = new TStringList();
	s->Delimiter = ',';
	s->DelimitedText = content;
	for (int i= 0; i < form->ComponentCount - 1; i++) {
		if(GetPropInfo(form->Components[i], "Name")){
			name = GetStrProp(form->Components[i], "Name");
			if(name.SubString(0, prefix.Length()) == prefix){
            	idx = StrToInt(name.SubString(prefix.Length() + 1, name.Length()));
				if(GetPropInfo(form->Components[i], "Text"))
					SetStrProp(form->Components[i], "Text", (*s)[idx-1]);
				if(GetPropInfo(form->Components[i], "Caption"))
					SetStrProp(form->Components[i], "Caption", (*s)[idx-1]);
		}
	 }
   }

}


TComponent* __fastcall getComponentByName(TForm* form, String name){
	String compName;
	for (int i= 0; i < form->ComponentCount - 1; i++) {
		if(GetPropInfo(form->Components[i], "Name")){
			compName = GetStrProp(form->Components[i], "Name");
			if (compName == name) {
				return  form->Components[i];
			}

	 }
   }
   return NULL;
}

int convertStrToHex(string str){
	std::stringstream ss;
	unsigned int x;
	ss << std::hex <<str;
	ss >> x;
	return x;
}


unsigned char* convertHexCommand(String cmd, unsigned int* len){
	boost::regex reg(HEX_REGEX);
	boost::smatch m;
	std::string s = cmd.t_str();
	std::string::const_iterator it = s.begin();
	std::string::const_iterator end = s.end();
	*len = 0;
	while(boost::regex_search(it, end, m, reg)){
	  it = m[0].second;
	  *len = *len + 1 ;
	}
	it = s.begin();
	int vLen = *len;
	unsigned char *c = new unsigned char[vLen];
	int i = 0;
	while(boost::regex_search(it, end, m, reg)){
	  if (m[1].matched)
		 c[i] = (convertStrToHex(m[1].str()));
	  it = m[0].second;
	  i++;
	}
	return c;
}

String convertHexResult(unsigned char* buf, int len){
	String res;
	for (int i = 0; i < len; i++) {
	   res = res + IntToHex(buf[i], 2);
	}
	return res;
}


unsigned char* flowHexPara(float flow){
   long InitFlow = 16384;
   long FlowPara = 32768;
   long flowValue = FlowPara * flow / 100 + InitFlow;
   unsigned char *c = new unsigned char[2];
   c[0] = flowValue%(16*16);
   c[1] = flowValue/(16*16);
   return c;
}

float convertFlowValue(unsigned char* buf){
   float InitFlow = 16384;
   float FlowPara = 32768;
   float value = buf[1] * (16*16) + buf[0];
   float result = ((value - InitFlow) / FlowPara) * 100;
   return result;
}

String __fastcall sensibilityPara(String c){
	if (c == "0") {
	   return "57313636" ;
	};

	while (c.Length() < 3)
		c = "0" + c;

	String cmd_part1 = "573230303{1.1}3{1.2}3{1.3}";
	String cmd_part2 = "3{1.1}3{1.2}";

	String para[1] = {c};
	cmd_part1 = paraProcess(cmd_part1.t_str(), para);

	int j, k;
	String t;
	for (int i = 0; i < 7; i++) {
	   t = cmd_part1.SubString(i*2 + 1, 2);
	   j =  convertStrToHex(t.t_str());
	   if (i == 0) {
			k = j;
	   } else {
            k = j ^ k;
	   }
	}
	para[0] = IntToHex(k, 2);
	cmd_part2 =  paraProcess(cmd_part2.t_str(), para);
    return cmd_part1 + cmd_part2;
}

void _fastcall queryDS(TADODataSet *ds, String sql){
	ds->Connection = dm->dbConn;
	ds->CommandText = sql;
	if (ds->Active == true) {
		ds->ClearFields();
		ds->Close();
	}

	ds->Open();
	ds->First();
}

String __fastcall analyzePPM(unsigned char *result, int groupNum, int resultSize){
	for (int i = 0; i < resultSize; i=i+groupNum) {

	}
}
