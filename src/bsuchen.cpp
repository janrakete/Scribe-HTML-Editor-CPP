//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "bsuchen.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBrowserSuchen *BrowserSuchen;

//---------------------------
// Eigene Funktionen - Anfang
//---------------------------
void __fastcall TBrowserSuchen::BrowserSearch(String path, String pattern, String pattern2, String pattern3)
{
 //--------------------
 // Sucht nach Browsern
 //--------------------
 TSearchRec searchrec;
 TSearchRec searchrec2;
 TSearchRec searchrec3;

 int result;
 int result2;
 int result3;

 result = FindFirst(path + pattern, faAnyFile - faDirectory - faVolumeID, searchrec);
 result2 = FindFirst(path + pattern2, faAnyFile - faDirectory - faVolumeID, searchrec2);
 result3 = FindFirst(path + pattern3, faAnyFile - faDirectory - faVolumeID, searchrec3);

 while (result == 0 || result2 == 0 || result3 == 0)
 {
  if (result == 0)
   List->Items->Add(path + searchrec.Name);
  if (result2 == 0)
   List->Items->Add(path + searchrec2.Name);
  if (result3 == 0)
   List->Items->Add(path + searchrec3.Name);
  Label2->Caption = MinimizeName(path, Canvas, Label2->Width);
  Label2->Update();
  result = FindNext(searchrec);
  result2 = FindNext(searchrec2);
  result3 = FindNext(searchrec3);
 }
 FindClose(searchrec);
 FindClose(searchrec2);
 FindClose(searchrec3);

 result = FindFirst(path + "*.*", faDirectory, searchrec);
 while (result == 0)
 {
  if ((searchrec.Name != ".") && (searchrec.Name != ".."))
  {
   BrowserSearch(path + searchrec.Name + "\\", pattern, pattern2, pattern3);
   Label2->Caption = MinimizeName(path, Canvas, Label2->Width);
   Label2->Update();
  }
  result = FindNext(searchrec);
 }
 FindClose(searchrec);
}
//-------------------------
// Eigene Funktionen - Ende
//-------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TBrowserSuchen::TBrowserSuchen(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBrowserSuchen::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 try
 {
  Hauptformular->browser_path_1 = Pfad->Items->Strings[0];
  Hauptformular->browser_desc_1 = Titel->Items->Strings[0];
  Hauptformular->browser_path_2 = Pfad->Items->Strings[1];
  Hauptformular->browser_desc_2 = Titel->Items->Strings[1];
  Hauptformular->browser_path_3 = Pfad->Items->Strings[2];
  Hauptformular->browser_desc_3 = Titel->Items->Strings[2];
 }
 catch (...)
 {
  1 == 1;
 }
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TBrowserSuchen::BitBtn2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TBrowserSuchen::FormShow(TObject *Sender)
{
 Caption = Label3->Caption;
 TOSVersionInfo* os = new TOSVersionInfo;
 GetVersionEx(os);
 if (os->dwPlatformId == VER_PLATFORM_WIN32_NT)
 {
  delete os;
  int button = Application->MessageBox(Hauptformular->SprachenWaehler->GetString(82).c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON2 + MB_ICONWARNING);
  if (button == IDNO)
   BitBtn1->Enabled = false;
 }
 delete os;
}
//---------------------------------------------------------------------------

void __fastcall TBrowserSuchen::BitBtn1Click(TObject *Sender)
{
 Screen->Cursor = crHourGlass;
 BitBtn1->Enabled = false;
 BitBtn2->Enabled = false;

 Application->ProcessMessages();

 if (DirectoryExists("C:\\Programme"))
  BrowserSearch("C:\\Programme\\", "iexplo*.exe", "netsc*.exe", "opera*.exe");
 else if (DirectoryExists("C:\\Program Files"))
  BrowserSearch("C:\\Program Files\\", "iexplo*.exe", "netsc*.exe", "opera*.exe");
 else
  BrowserSearch("C:\\", "iexplo*.exe", "netsc*.exe", "opera*.exe");

 String temp;
 for (int i = 0; i < List->Items->Count; i++)
 {
  temp = List->Items->Strings[i];
  if (AnsiPos("iexplore", AnsiLowerCase(temp)))
  {
   Titel->Items->Add("Microsoft Internet Explorer");
   Pfad->Items->Add(temp);
   break;
  }
 }

 for (int i = 0; i < List->Items->Count; i++)
 {
  temp = List->Items->Strings[i];
  if (AnsiPos("netsc", AnsiLowerCase(temp)))
  {
   Titel->Items->Add("Netscape Navigator");
   Pfad->Items->Add(temp);
   break;
  }
 }

 for (int i = 0; i < List->Items->Count; i++)
 {
  temp = List->Items->Strings[i];
  if (AnsiPos("opera", AnsiLowerCase(temp)))
  {
   Titel->Items->Add("Opera");
   Pfad->Items->Add(temp);
   break;
  }
 }
 Screen->Cursor = crDefault;
 Close();
}
//---------------------------------------------------------------------------

