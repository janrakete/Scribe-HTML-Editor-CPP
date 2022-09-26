//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "grapview.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGrafikBetrachter *GrafikBetrachter;

//---------------------------
// Eigene Funktionen - Anfang
//---------------------------
void __fastcall TGrafikBetrachter::ShowImage(String sel_file)
{
 //------------------------------
 // Zeigt Grafik im Betrachter an
 //------------------------------
 Image1->Picture->LoadFromFile(sel_file);

 if (Image1->Picture->Width < 211)
  Image1->Left = 104 - (Image1->Picture->Width / 2);
 else
  Image1->Left = 0;
 if (Image1->Picture->Height < 211)
  Image1->Top = 104 - (Image1->Picture->Height / 2);
 else
  Image1->Top = 0;

 Height->Caption = String(Image1->Picture->Height) + " " + Hauptformular->SprachenWaehler->GetString(11);
 Width->Caption = String(Image1->Picture->Width) + " " + Hauptformular->SprachenWaehler->GetString(11);
 if (AnsiPos("~temp.", sel_file)) // Für DirektFTP
  Filename->Caption = Hauptformular->DirektFTPListe->ItemFocused->Caption;
 else
  Filename->Caption = ExtractFileName(sel_file);

 int file_size = Hauptformular->FileGetSize(sel_file);
 int file_size_kb = 0;

 if (file_size < 1025)
  file_size_kb = 1;
 else
  file_size_kb = file_size / 1024;
 Size->Caption = String(file_size_kb) + " KB (" + String(file_size) + " " + Hauptformular->SprachenWaehler->GetString(10) + ")";
 AktuelleDatei->Caption = sel_file;
}
//-------------------------
// Eigene Funktionen - Ende
//-------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TGrafikBetrachter::TGrafikBetrachter(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TGrafikBetrachter::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->graphics_viewer_file = "";
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TGrafikBetrachter::BitBtn1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TGrafikBetrachter::FormShow(TObject *Sender)
{
 if (Trim(Hauptformular->standard_graphic_tool) == "")
  BitBtn4->Visible = false;

 if (Trim(Hauptformular->graphics_viewer_file) != "")
 {
  BitBtn3->Visible = false;
  BitBtn2->Visible = false;
  ShowImage(Hauptformular->graphics_viewer_file);
 }
 else
 {
  if (Hauptformular->VerwControl->ActivePage == Hauptformular->VerwTab1)
   ShowImage(Hauptformular->fileexplorer_dir + Hauptformular->DateimanagerListe->ItemFocused->Caption);
  else
   ShowImage(Hauptformular->projectexplorer_dir + Hauptformular->ProjekteListe->ItemFocused->Caption);
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikBetrachter::BitBtn4Click(TObject *Sender)
{
 Hauptformular->FileExecute(Hauptformular->standard_graphic_tool, AktuelleDatei->Caption);
}
//---------------------------------------------------------------------------

void __fastcall TGrafikBetrachter::BitBtn2Click(TObject *Sender)
{
 String gew_datei;
 Image1->Picture = NULL;

 if (Hauptformular->VerwControl->ActivePage == Hauptformular->VerwTab1)
 {
  do
  {
   if (Hauptformular->DateimanagerListe->ItemFocused->Index < Hauptformular->DateimanagerListe->Items->Count - 1)
   {
    gew_datei = Hauptformular->DateimanagerListe->Items->Item[Hauptformular->DateimanagerListe->ItemFocused->Index + 1]->Caption;
    Hauptformular->DateimanagerListe->Items->Item[Hauptformular->DateimanagerListe->ItemFocused->Index + 1]->Focused = true;
   }
   else
   {
    gew_datei = Hauptformular->DateimanagerListe->Items->Item[0]->Caption;
    Hauptformular->DateimanagerListe->Items->Item[0]->Focused = true;
   }
   gew_datei = Hauptformular->fileexplorer_dir + gew_datei;
  }
  while (!Hauptformular->GraphicFile(gew_datei));
 }
 else
 {
  do
  {
   if (Hauptformular->ProjekteListe->ItemFocused->Index < Hauptformular->ProjekteListe->Items->Count - 1)
   {
    gew_datei = Hauptformular->ProjekteListe->Items->Item[Hauptformular->ProjekteListe->ItemFocused->Index + 1]->Caption;
    Hauptformular->ProjekteListe->Items->Item[Hauptformular->ProjekteListe->ItemFocused->Index + 1]->Focused = true;
   }
   else
   {
    gew_datei = Hauptformular->ProjekteListe->Items->Item[0]->Caption;
    Hauptformular->ProjekteListe->Items->Item[0]->Focused = true;
   }
   gew_datei = Hauptformular->projectexplorer_dir + gew_datei;
  }
  while (!Hauptformular->GraphicFile(gew_datei));
 }
 ShowImage(gew_datei);
}
//---------------------------------------------------------------------------

void __fastcall TGrafikBetrachter::BitBtn3Click(TObject *Sender)
{
 String gew_datei;
 Image1->Picture = NULL;

 if (Hauptformular->VerwControl->ActivePage == Hauptformular->VerwTab1)
 {
  do
  {
   if (Hauptformular->DateimanagerListe->ItemFocused->Index > 0)
   {
    gew_datei = Hauptformular->DateimanagerListe->Items->Item[Hauptformular->DateimanagerListe->ItemFocused->Index - 1]->Caption;
    Hauptformular->DateimanagerListe->Items->Item[Hauptformular->DateimanagerListe->ItemFocused->Index - 1]->Focused = true;
   }
   else
   {
    gew_datei = Hauptformular->DateimanagerListe->Items->Item[Hauptformular->DateimanagerListe->Items->Count - 1]->Caption;
    Hauptformular->DateimanagerListe->Items->Item[Hauptformular->DateimanagerListe->Items->Count - 1]->Focused = true;
   }
   gew_datei = Hauptformular->fileexplorer_dir + gew_datei;
  }
  while (!Hauptformular->GraphicFile(gew_datei));
 }
 else
 {
  do
  {
   if (Hauptformular->ProjekteListe->ItemFocused->Index > 0)
   {
    gew_datei = Hauptformular->ProjekteListe->Items->Item[Hauptformular->ProjekteListe->ItemFocused->Index - 1]->Caption;
    Hauptformular->ProjekteListe->Items->Item[Hauptformular->ProjekteListe->ItemFocused->Index - 1]->Focused = true;
   }
   else
   {
    gew_datei = Hauptformular->ProjekteListe->Items->Item[Hauptformular->ProjekteListe->Items->Count - 1]->Caption;
    Hauptformular->ProjekteListe->Items->Item[Hauptformular->ProjekteListe->Items->Count - 1]->Focused = true;
   }
   gew_datei = Hauptformular->projectexplorer_dir + gew_datei;
  }
  while (!Hauptformular->GraphicFile(gew_datei));
 }
 ShowImage(gew_datei);
}
//---------------------------------------------------------------------------

