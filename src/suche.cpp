//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "suche.h"
#include "main.h"
#include "child.h"
#include "hilfed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSuchen *Suchen;
//---------------------------------------------------------------------------
__fastcall TSuchen::TSuchen(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSuchen::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TSuchen::FormShow(TObject *Sender)
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

 ProgressBar1->Position = 0;
 ListView1->Items->Clear();
 ListBox1->Clear();
 ListBox2->Clear();
 Verzeichnisse->Clear();

 TabSheet2->TabVisible = false;
 PageControl1->ActivePage = TabSheet1;
 if (Hauptformular->MDIChildCount)
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength != 0)
   SuchenMemo->Text = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;
 }
 SuchenMemo->SelectAll();
}
//---------------------------------------------------------------------------


void __fastcall TSuchen::BitBtn1Click(TObject *Sender)
{
 Screen->Cursor = crHourGlass;

 if (Trim(SuchenMemo->Text) != "")
 {
  ProgressBar1->Position = 0;
  ListView1->Items->Clear();
  ListBox1->Clear();
  ListBox2->Clear();
  Verzeichnisse->Clear();
  TabSheet2->TabVisible = true;
  PageControl1->ActivePage = TabSheet2;

  bool MatchCase;

  if (CheckBox3->Checked)
   MatchCase = true;
  else
   MatchCase = false;

  if (ComboBox4->ItemIndex == 0)
  {
   int button;
   if (CheckBox1->Checked)
    button = Application->MessageBox(Hauptformular->SprachenWaehler->GetString(20).c_str(), "Scribe!", MB_ICONQUESTION + MB_YESNO + MB_DEFBUTTON1);
   ProgressBar1->Max = Hauptformular->MDIChildCount;
   String dateiname;
   TListItem *ListItem;
   String gesamter_text;
   String suchtext = SuchenMemo->Text;
   String ersetzentext = ErsetzenMemo->Text;
   String dummy_string;
   int such_pos;
   int mdis_count = Hauptformular->MDIChildCount;

   dummy_string = AnsiString::StringOfChar('#', suchtext.Length());

   for (int i = 0; i < mdis_count; i++)
   {
    Hauptformular->MDIChildren[i]->BringToFront();
    dateiname = Hauptformular->ActiveMDIChild->Caption;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
    gesamter_text = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Text;

    if (!MatchCase)
     gesamter_text = AnsiLowerCase(gesamter_text);
    if (!MatchCase)
     suchtext = AnsiLowerCase(suchtext);

    while (AnsiPos(suchtext, gesamter_text))
    {
     such_pos = AnsiPos(suchtext, gesamter_text);
     ListItem = ListView1->Items->Add();
     ListItem->Caption = ExtractFileName(dateiname);
     ListItem->ImageIndex = Hauptformular->FileCalculateIcon(dateiname);
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = such_pos - 1;
     ListItem->SubItems->Add(String(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelPar + 1) + ":" + String(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol + 1));
     ListBox1->Items->Add(dateiname);
     ListBox2->Items->Add((such_pos - 1));
     ListView1->Update();
     gesamter_text = gesamter_text.Delete(such_pos, suchtext.Length());
     gesamter_text = gesamter_text.Insert(dummy_string, such_pos);
    }
    if (CheckBox1->Checked)
    {
     if (MatchCase)
      ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Text = StringReplace(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Text, suchtext, ersetzentext, TReplaceFlags() << rfReplaceAll);
     else
      ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Text = StringReplace(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Text, suchtext, ersetzentext, TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
    }
    if (button == IDYES)
     Hauptformular->FileSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, dateiname, false);
    ProgressBar1->StepBy(1);
   }
   ProgressBar1->Position = ProgressBar1->Max;
  }

  else
  {
   if ((ComboBox4->ItemIndex == 2) || ((ComboBox4->ItemIndex == 1) && (CheckBox5->Checked)))
   {
    if (ComboBox4->ItemIndex == 1)
     Hauptformular->DirectoryFindSubs(Hauptformular->fileexplorer_dir,Verzeichnisse);
    else
     Hauptformular->DirectoryFindSubs(Hauptformular->project_dir + Hauptformular->ProjekteAuswahl->Items->Strings[Hauptformular->ProjekteAuswahl->ItemIndex] + "\\",Verzeichnisse);
   }
   else
    Verzeichnisse->Items->Add(Hauptformular->fileexplorer_dir);

   int items_count = Verzeichnisse->Items->Count;
   ProgressBar1->Max = items_count;
   int items_count_2;
   String dateiname;
   TListItem *ListItem;
   String gesamter_text;
   String suchtext = SuchenMemo->Text;
   String ersetzentext = ErsetzenMemo->Text;
   String dummy_string;
   int such_pos;

   dummy_string = AnsiString::StringOfChar('#', suchtext.Length());

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
     gesamter_text = Hauptformular->TempMemo->Lines->Text;

     if (!MatchCase)
      gesamter_text = AnsiLowerCase(gesamter_text);
     if (!MatchCase)
      suchtext = AnsiLowerCase(suchtext);

     while (AnsiPos(suchtext, gesamter_text))
     {
      such_pos = AnsiPos(suchtext, gesamter_text);
      ListItem = ListView1->Items->Add();
      ListItem->Caption = ExtractFileName(dateiname);
      ListItem->ImageIndex = Hauptformular->FileCalculateIcon(dateiname);
      Hauptformular->TempMemo->SelStart = such_pos - 1;
      ListItem->SubItems->Add(String(Hauptformular->TempMemo->SelPar + 1) + ":" + String(Hauptformular->TempMemo->SelCol + 1));
      ListBox1->Items->Add(dateiname);
      ListBox2->Items->Add((such_pos - 1));
      ListView1->Update();
      gesamter_text = gesamter_text.Delete(such_pos, suchtext.Length());
      gesamter_text = gesamter_text.Insert(dummy_string, such_pos);
     }
     if (CheckBox1->Checked)
     {
      if (MatchCase)
       Hauptformular->TempMemo->Lines->Text = StringReplace(Hauptformular->TempMemo->Lines->Text, suchtext, ersetzentext, TReplaceFlags() << rfReplaceAll);
      else
       Hauptformular->TempMemo->Lines->Text = StringReplace(Hauptformular->TempMemo->Lines->Text, suchtext, ersetzentext, TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
     }
     if (CheckBox1->Checked)
      Hauptformular->FileSave(Hauptformular->TempMemo, dateiname, false);
    }
    ProgressBar1->StepBy(1);
   }
  }
 }
 else
  Application->MessageBox(Hauptformular->SprachenWaehler->GetString(15).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);

 Screen->Cursor = crDefault;
}

//---------------------------------------------------------------------------
void __fastcall TSuchen::ComboBox4Change(TObject *Sender)
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

void __fastcall TSuchen::PageControl1Change(TObject *Sender)
{
 if (TabSheet2->TabVisible)
  TabSheet2->TabVisible = false;
}
//---------------------------------------------------------------------------

void __fastcall TSuchen::ListView1DblClick(TObject *Sender)
{
 if (ListView1->Selected)
 {
  String gewdatei = ListBox1->Items->Strings[ListView1->Selected->Index];
  int pos = ListBox2->Items->Strings[ListView1->Selected->Index].ToInt();
  Hauptformular->CreateChildForm("", gewdatei, "");

  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = pos;
  if (CheckBox1->Checked)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = ErsetzenMemo->Text.Length();
  else
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = SuchenMemo->Text.Length();
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
 }
}
//---------------------------------------------------------------------------

void __fastcall TSuchen::CheckBox1Click(TObject *Sender)
{
 if (CheckBox1->Checked)
 {
  ErsetzenMemo->Color = clWindow;
  ErsetzenMemo->Enabled = true;
 }
 else
 {
  ErsetzenMemo->Color = clBtnFace;
  ErsetzenMemo->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSuchen::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_extended_search.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TSuchen::FormClose(TObject *Sender, TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
}
//---------------------------------------------------------------------------

