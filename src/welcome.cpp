//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "welcome.h"
#include "bsuchen.h"
#include "main.h"
#include "seitenass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWillkommen *Willkommen;
//---------------------------------------------------------------------------
__fastcall TWillkommen::TWillkommen(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TWillkommen::CheckBox1Click(TObject *Sender)
{
 if (CheckBox1->Checked)
 {
  Edit2->Color = clWindow;
  Edit2->Enabled = true;
 }
 else
 {
  Edit2->Color = clBtnFace;
  Edit2->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TWillkommen::CheckBox2Click(TObject *Sender)
{
 if (CheckBox2->Checked)
 {
  Edit3->Color = clWindow;
  Edit3->Enabled = true;
 }
 else
 {
  Edit3->Color = clBtnFace;
  Edit3->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TWillkommen::CheckBox3Click(TObject *Sender)
{
 if (CheckBox3->Checked)
 {
  Edit4->Color = clWindow;
  Edit4->Enabled = true;
 }
 else
 {
  Edit4->Color = clBtnFace;
  Edit4->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TWillkommen::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "first_help.html", false);
}
//---------------------------------------------------------------------------

void __fastcall TWillkommen::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TWillkommen::BitBtn2Click(TObject *Sender)
{
 Hauptformular->VerwControl->ActivePage = Hauptformular->VerwTab1;
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TWillkommen::BitBtn1Click(TObject *Sender)
{
 String projekt_name = Edit1->Text;
 String projekt_ordner1 = Edit2->Text;
 String projekt_ordner2 = Edit3->Text;
 String projekt_ordner3 = Edit4->Text;

 if (Trim(Edit1->Text) == "")
  Application->MessageBox(Hauptformular->SprachenWaehler->GetString(2).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONWARNING);
 else
 {
  if (CreateDir(Hauptformular->project_dir + projekt_name))
  {
   if (CheckBox1->Checked)
    CreateDir (Hauptformular->project_dir + projekt_name + "\\" + projekt_ordner1);
   if (CheckBox2->Checked)
    CreateDir (Hauptformular->project_dir + projekt_name + "\\" + projekt_ordner2);
   if (CheckBox3->Checked)
    CreateDir (Hauptformular->project_dir + projekt_name + "\\" + projekt_ordner3);
   Visible = false;
   Close();
   if (Hauptformular->ProjectsLoad(projekt_name))
    (Hauptformular->ProjekteExplorer->Items->GetFirstNode())->Selected = true;
   Hauptformular->ProjekteAuswahlChange(Sender);
   Hauptformular->VerwControl->ActivePage = Hauptformular->VerwTab2;

   TSeitenAssistent* SeitenAssistent = new TSeitenAssistent(Application);
   Hauptformular->SprachenWaehler->SetFormLanguage(SeitenAssistent);
   SeitenAssistent->ShowModal();
  }
  else
   Application->MessageBox(Hauptformular->SprachenWaehler->GetString(3).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);
 }
}
//---------------------------------------------------------------------------

void __fastcall TWillkommen::FormShow(TObject *Sender)
{
 TBrowserSuchen* BrowserSuchen = new TBrowserSuchen(Application);
 Hauptformular->SprachenWaehler->SetFormLanguage(BrowserSuchen);
 BrowserSuchen->ShowModal();
}
//---------------------------------------------------------------------------

