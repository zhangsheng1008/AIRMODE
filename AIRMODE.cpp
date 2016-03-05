//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("uAirMode.cpp", fmAirMode);
USEFORM("uConfig.cpp", fmSysConfig);
USEFORM("uDM.cpp", dm); /* TDataModule: File Type */
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(Tdm), &dm);
		Application->CreateForm(__classid(TfmAirMode), &fmAirMode);
		Application->CreateForm(__classid(TfmSysConfig), &fmSysConfig);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
