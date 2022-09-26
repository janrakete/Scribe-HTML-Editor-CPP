//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "neuproj.h"
#include "main.h"
#include "hilfed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNeuesProjekt *NeuesProjekt;
//---------------------------------------------------------------------------
__fastcall TNeuesProjekt::TNeuesProjekt(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TNeuesProjekt::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TNeuesProjekt::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TNeuesProjekt::CheckBox1Click(TObject *Sender)
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

void __fastcall TNeuesProjekt::CheckBox2Click(TObject *Sender)
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

void __fastcall TNeuesProjekt::CheckBox3Click(TObject *Sender)
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

void __fastcall TNeuesProjekt::BitBtn1Click(TObject *Sender)
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
   Close();
   if (Hauptformular->ProjectsLoad(projekt_name))
    (Hauptformular->ProjekteExplorer->Items->GetFirstNode())->Selected = true;
  }
  else
   Application->MessageBox(Hauptformular->SprachenWaehler->GetString(3).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);
 }
}
//---------------------------------------------------------------------------

void __fastcall TNeuesProjekt::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_new_project.html", true);
}
//---------------------------------------------------------------------------

