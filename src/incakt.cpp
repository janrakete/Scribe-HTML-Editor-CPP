//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "incakt.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TIncludesAktualisieren *IncludesAktualisieren;
//---------------------------------------------------------------------------
__fastcall TIncludesAktualisieren::TIncludesAktualisieren(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TIncludesAktualisieren::BitBtn2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TIncludesAktualisieren::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TIncludesAktualisieren::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_update_includes.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TIncludesAktualisieren::BitBtn1Click(TObject *Sender)
{
 TForm *aktuelles_mdi;
 aktuelles_mdi = Hauptformular->ActiveMDIChild;

 Screen->Cursor = crHourGlass;
 BitBtn1->Enabled = false;
 ProgressBar1->Position = 0;

 int include_sel_start = 0;
 int include_sel_end = 0;
 String include_file = "";


 if (ComboBox4->ItemIndex == 0)
 {
  int button;
  button = Application->MessageBox(Hauptformular->SprachenWaehler->GetString(20).c_str(), "Scribe!", MB_ICONQUESTION + MB_YESNO + MB_DEFBUTTON1);
  ProgressBar1->Max = Hauptformular->MDIChildCount;
  String dateiname;
  int mdis_count = Hauptformular->MDIChildCount;

  for (int i = 0; i < mdis_count; i++)
  {
   Hauptformular->TempMemo->Lines->Clear();
   Hauptformular->MDIChildren[i]->BringToFront();
   dateiname = Hauptformular->ActiveMDIChild->Caption;
   Hauptformular->TempMemo->Lines = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines;
   Hauptformular->TempMemo->SelStart = 0;

   while (Hauptformular->TempMemo->FindTxt("<!--INC:\"", true, false, false, false))
   {
    include_sel_start = Hauptformular->TempMemo->SelStart;
    Hauptformular->TempMemo->FindTxt("-->", true, false, false, false);
    include_sel_end = Hauptformular->TempMemo->SelStart;
    Hauptformular->TempMemo->SelStart = include_sel_start;
    Hauptformular->TempMemo->SelLength = include_sel_end - include_sel_start - 4;
    include_file = Hauptformular->TempMemo->SelText;
    Hauptformular->TempMemo3->Lines->Clear();
    Hauptformular->TempMemo3->Lines->LoadFromFile(Hauptformular->includes_dir + include_file);
    Hauptformular->TempMemo3->SelectAll();
    Hauptformular->TempMemo->SelStart = include_sel_end;
    Hauptformular->TempMemo->FindTxt("<!--/INC:\"" + include_file + "\"-->", true, false, false, false);
    Hauptformular->TempMemo->SelStart = Hauptformular->TempMemo->SelStart + Hauptformular->TempMemo->SelLength;
    include_sel_start = Hauptformular->TempMemo->SelStart;
    Hauptformular->TempMemo->SelStart = include_sel_end;
    Hauptformular->TempMemo->SelLength = include_sel_start - include_sel_end;
    Hauptformular->TempMemo->SelText = Hauptformular->TempMemo3->SelText;
   }

   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines = Hauptformular->TempMemo->Lines;
   if (button == IDYES)
    Hauptformular->FileSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, dateiname, false);
   ProgressBar1->StepBy(1);
   ProgressBar1->Position = ProgressBar1->Max;
  }
 }
 else
 {
  Application->MessageBox(Hauptformular->SprachenWaehler->GetString(81).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);

  if ((ComboBox4->ItemIndex == 2) || ((ComboBox4->ItemIndex == 1) && (CheckBox5->Checked)))
  {
   if (ComboBox4->ItemIndex == 1)
    Hauptformular->DirectoryFindSubs(Hauptformular->fileexplorer_dir, Verzeichnisse);
   else
    Hauptformular->DirectoryFindSubs(Hauptformular->project_dir + Hauptformular->ProjekteAuswahl->Items->Strings[Hauptformular->ProjekteAuswahl->ItemIndex] + "\\",Verzeichnisse);
  }
  else
   Verzeichnisse->Items->Add(Hauptformular->fileexplorer_dir);

  int items_count = Verzeichnisse->Items->Count;
  int items_count_2;
  String dateiname;
  ProgressBar1->Max = items_count;

  for (int i = 0; i < items_count; i++)
  {
   Dateien->Mask = Edit2->Text;
   Dateien->Directory = Verzeichnisse->Items->Strings[i];
   items_count_2 = Dateien->Items->Count;

   for (int a = 0; a < items_count_2; a++)
   {
    dateiname = Dateien->Items->Strings[a];
    dateiname = Dateien->Directory + "\\" + dateiname;
    Hauptformular->TempMemo->Lines->LoadFromFile(dateiname);

    while (Hauptformular->TempMemo->FindTxt("<!--INC:\"", true, false, false, false))
    {
     include_sel_start = Hauptformular->TempMemo->SelStart;
     Hauptformular->TempMemo->FindTxt("-->", true, false, false, false);
     include_sel_end = Hauptformular->TempMemo->SelStart;
     Hauptformular->TempMemo->SelStart = include_sel_start;
     Hauptformular->TempMemo->SelLength = include_sel_end - include_sel_start - 4;
     include_file = Hauptformular->TempMemo->SelText;
     Hauptformular->TempMemo3->Lines->Clear();
     Hauptformular->TempMemo3->Lines->LoadFromFile(Hauptformular->includes_dir + include_file);
     Hauptformular->TempMemo3->SelectAll();
     Hauptformular->TempMemo->SelStart = include_sel_end;
     Hauptformular->TempMemo->FindTxt("<!--/INC:\"" + include_file + "\"-->", true, false, false, false);
     Hauptformular->TempMemo->SelStart = Hauptformular->TempMemo->SelStart + Hauptformular->TempMemo->SelLength;
     include_sel_start = Hauptformular->TempMemo->SelStart;
     Hauptformular->TempMemo->SelStart = include_sel_end;
     Hauptformular->TempMemo->SelLength = include_sel_start - include_sel_end;
     Hauptformular->TempMemo->SelText = Hauptformular->TempMemo3->SelText;
    }
    Hauptformular->FileSave(Hauptformular->TempMemo, dateiname, false);
   }
   ProgressBar1->StepBy(1);
  }
 }

 ProgressBar1->Position = ProgressBar1->Max;
 BitBtn1->Enabled = true;
 Screen->Cursor = crDefault;

 aktuelles_mdi->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TIncludesAktualisieren::FormShow(TObject *Sender)
{
 ComboBox4->ItemIndex = 0;
 Edit2->Enabled = false;
 CheckBox5->Enabled = false;

 if (Trim(Edit2->Text) == "")
 {
  String filter_part = "";
  filter_part = "*." + Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all;
  filter_part = filter_part.SubString(0, filter_part.Length() - 1);
  Edit2->Text = Hauptformular->ReplaceString(filter_part, ";", ";*.", true, true);
 }
}
//---------------------------------------------------------------------------

void __fastcall TIncludesAktualisieren::ComboBox4Change(TObject *Sender)
{
 if (ComboBox4->ItemIndex == 1)
 {
  Edit2->Enabled = true;
  CheckBox5->Enabled = true;
 }
 else if (ComboBox4->ItemIndex == 2)
 {
  Edit2->Enabled = true;
  CheckBox5->Enabled = false;
 }
 else
 {
  Edit2->Enabled = false;
  CheckBox5->Enabled = false;
 }

 if (ComboBox4->ItemIndex == 2 && Hauptformular->ProjekteAuswahl->ItemIndex == 0)
 {
  Application->MessageBox(Hauptformular->SprachenWaehler->GetString(17).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONWARNING);
  ComboBox4->ItemIndex = 0;
 }
}
//---------------------------------------------------------------------------

