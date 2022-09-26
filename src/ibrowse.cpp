//---------------------------------------------------------------------------
#include <vcl.h>
#include <mshtml.h>
#pragma hdrstop

#include "ibrowse.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInternerBrowser *InternerBrowser;
//---------------------------------------------------------------------------
__fastcall TInternerBrowser::TInternerBrowser(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInternerBrowser::ToolButton5Click(TObject *Sender)
{
 Hauptformular->msie_previewbrowser->GoBack();
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::ToolButton6Click(TObject *Sender)
{
 Hauptformular->msie_previewbrowser->GoForward();
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::N640x4801Click(TObject *Sender)
{
 Width = 640;
 Height = 480;
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::N800x6001Click(TObject *Sender)
{
 Width = 800;
 Height = 600;
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::N1024x7681Click(TObject *Sender)
{
 Width = 1024;
 Height = 768;
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::ToolButton1Click(TObject *Sender)
{
 String datei = Ursprung->Caption;
 wchar_t temp[400];
 StringToWideChar(datei, temp, 400);
 Hauptformular->msie_previewbrowser->Navigate(temp);
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::N320x2401Click(TObject *Sender)
{
 Width = 320;
 Height = 240;
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::ToolButton9Click(TObject *Sender)
{
 Hauptformular->msie_previewbrowser->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::ToolButton3Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(5);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(7);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->cssfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(21);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->javascriptfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;

 if (Hauptformular->MDIChildCount)
  OeffnenDialog->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 else
 {
  if (Hauptformular->VerwControl->ActivePage == Hauptformular->VerwTab1)
   OeffnenDialog->InitialDir = Hauptformular->fileexplorer_dir;
  else
   OeffnenDialog->InitialDir = Hauptformular->projectexplorer_dir;
 }

 OeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);
 if (OeffnenDialog->Execute())
 {
  String datei_start = OeffnenDialog->FileName;
  datei_start = Hauptformular->ReplaceString(datei_start, "\\", "/", true, true);
  datei_start = "file:///" + datei_start;
  String datei = datei_start;
  wchar_t temp[400];
  StringToWideChar(datei, temp, 400);
  Hauptformular->msie_previewbrowser->Navigate(temp);
 }
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::FormDeactivate(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------


void __fastcall TInternerBrowser::Edit1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 if (Key == VK_RETURN)
 {
  String datei = Edit1->Text;
  wchar_t temp[400];
  StringToWideChar(datei, temp, 400);
  Hauptformular->msie_previewbrowser->Navigate(temp);
  Key = NULL;
 }
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->msie_previewbrowser->Stop();
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::ToolButton11Click(TObject *Sender)
{
 if (Hauptformular->msie_previewbrowser->Busy)
  return;

 IHTMLDocument2 *HTMLDocument = NULL;
 IPersistFile *PersistFile = NULL;
 if (Hauptformular->msie_previewbrowser->Document && SUCCEEDED(Hauptformular->msie_previewbrowser->Document->QueryInterface(IID_IHTMLDocument2, (LPVOID*)&HTMLDocument)))
 {
  if (SUCCEEDED(HTMLDocument->QueryInterface(IID_IPersistFile, (LPVOID*)&PersistFile)))
  {
   PersistFile->Save(WideString(Hauptformular->program_dir + "~temp.html"), true);
   PersistFile->Release();
  }
  HTMLDocument->Release();
  //----------------------
  String url = StatusBar1->Panels->Items[1]->Text;
  if (AnsiPos("?", url))
   url = url.SubString(0, AnsiPos("?", url) - 1);
  url = Hauptformular->ReplaceString(url, "%20", " ", true, true);

 if (AnsiPos("http://", AnsiLowerCase(url)))
 {
  url = Hauptformular->ReplaceString(url, "/", "\\", true, true);
  url = Hauptformular->ReplaceString(url, "http:\\\\", "ftp://", false, true);
 }
 else if (AnsiPos("file:///", AnsiLowerCase(url)))
 {
  url = Hauptformular->ReplaceString(url, "file:///", "", false, true);
  url = Hauptformular->ReplaceString(url, "/", "\\", true, true);
 }

 bool schon_vorhanden = false;
 int mdis_count = Hauptformular->MDIChildCount;

 for (int i = 0; i < mdis_count; i++)
 {
  if (AnsiLowerCase(Hauptformular->MDIChildren[i]->Caption) == AnsiLowerCase(url))
  {
   schon_vorhanden = true;
   Hauptformular->MDIChildren[i]->BringToFront();
  }
 }

 if (!schon_vorhanden)
  Hauptformular->CreateChildForm("", "", Hauptformular->program_dir + "~temp.html");
 else
  Close();
 }
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::FormResize(TObject *Sender)
{
 Edit1->Width = Width;        
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::Action1Execute(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TInternerBrowser::Action2Execute(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

