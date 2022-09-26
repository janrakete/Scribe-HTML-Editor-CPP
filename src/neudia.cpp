//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "neudia.h"
#include "main.h"
#include "hilfed.h"
#include "seitenass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNeu *Neu;
//---------------------------------------------------------------------------
__fastcall TNeu::TNeu(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TNeu::FormClose(TObject *Sender, TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TNeu::BitBtn2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TNeu::FormShow(TObject *Sender)
{
 TListItem *ListItem3;

 ListItem3 = Assistenten->Items->Add();
 ListItem3->Caption = Hauptformular->ReplaceString(Label1->Caption, "...", "", true, true);
 ListItem3->ImageIndex = 4;
 //---------------------------------------------------------------------------
 Hauptformular->TempDateilistBox->Directory = Hauptformular->program_dir + "Storage!\\Templates";
 Hauptformular->TempDateilistBox->Mask = "*.sct";
 Hauptformular->TempDateilistBox->Update();

 TListItem *ListItem;

 if (Hauptformular->TempDateilistBox->Items->IndexOf("Standard.sct") > -1)
 {
  ListItem = Vorlagen->Items->Add();
  ListItem->Caption = "Standard";
  ListItem->ImageIndex = 0;
  Hauptformular->TempDateilistBox->Items->Delete(Hauptformular->TempDateilistBox->Items->IndexOf("Standard.sct"));
 }

 for (int i = 0; i < Hauptformular->TempDateilistBox->Items->Count; i++)
 {
  ListItem = Vorlagen->Items->Add();
  ListItem->Caption = Hauptformular->ReplaceString(Hauptformular->TempDateilistBox->Items->Strings[i], ".sct", "", false, true);
  ListItem->ImageIndex = 0;
 }
 //---------------------------------------------------------------------------
 Hauptformular->TempDateilistBox->Directory = Hauptformular->program_dir + "Storage!\\Wizards";
 Hauptformular->TempDateilistBox->Mask = "*.dll";
 Hauptformular->TempDateilistBox->Update();

 TListItem  *ListItem2;
 randomize();
 for (int i = 0; i < Hauptformular->TempDateilistBox->Items->Count; i++)
 {
  ListItem2 = Assistenten->Items->Add();
  ListItem2->Caption = Hauptformular->ReplaceString(Hauptformular->TempDateilistBox->Items->Strings[i], ".dll", "", false, true);
  ListItem2->ImageIndex = random(3) + 1;
 }
}
//---------------------------------------------------------------------------


void __fastcall TNeu::PopupMenu1Popup(TObject *Sender)
{
 if ((Vorlagen->Selected) && (Vorlagen->Selected->Caption != "Standard"))
  Lschen1->Enabled = true;
 else
  Lschen1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TNeu::PopupMenu2Popup(TObject *Sender)
{
 if ((Assistenten->Selected) && (Assistenten->Selected->Caption != Hauptformular->ReplaceString(Label1->Caption, "...", "", true, true)))
  Lschen2->Enabled = true;
 else
  Lschen2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TNeu::Lschen1Click(TObject *Sender)
{
 String complete_file;
 complete_file = Hauptformular->program_dir + "Storage!\\Templates\\";
 complete_file = complete_file + Vorlagen->Selected->Caption + ".sct";

 if (Hauptformular->FileDeleteOnlyOne(complete_file, true))
 {
  Vorlagen->Selected->Delete();
  Hauptformular->standard_template = "Standard";
 }
}
//---------------------------------------------------------------------------

void __fastcall TNeu::Lschen2Click(TObject *Sender)
{
 String complete_file;
 complete_file = Hauptformular->program_dir + "Storage!\\Wizards\\";
 complete_file = complete_file + Assistenten->Selected->Caption + ".dll";

 if (Hauptformular->FileDeleteOnlyOne(complete_file, true))
  Assistenten->Selected->Delete();
}
//---------------------------------------------------------------------------

void __fastcall TNeu::BitBtn1Click(TObject *Sender)
{
 if (PageControl1->ActivePage == TabSheet1)
 {
  if (Vorlagen->Selected)
  {
   Hauptformular->CreateChildForm(Vorlagen->Selected->Caption, "", "");
   Close();
  }
 }
 else
 {
  if ((Assistenten->Selected) && (Assistenten->Selected->Caption == Hauptformular->ReplaceString(Label1->Caption, "...", "", true, true)))
  {
   Visible = false;
   TSeitenAssistent* SeitenAssistent = new TSeitenAssistent(Application);
   Hauptformular->SprachenWaehler->SetFormLanguage(SeitenAssistent);
   SeitenAssistent->ShowModal();
   Close();
  }
  else
  {
   Visible = false;
   Hauptformular->ScribePluginEngine(Hauptformular->program_dir + "Storage!\\Wizards\\" + Assistenten->Selected->Caption + ".dll");
   Close();
  }
 }
}
//---------------------------------------------------------------------------



void __fastcall TNeu::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_new.html", true);
}
//---------------------------------------------------------------------------

