//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "proback.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Bffolder"
#pragma link "cabfiles"
#pragma resource "*.dfm"
TProjektBackup *ProjektBackup;
//---------------------------------------------------------------------------
__fastcall TProjektBackup::TProjektBackup(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TProjektBackup::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;        
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_project_backup.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::FormShow(TObject *Sender)
{
 StrLstDateien = new TStringList();
 ComboBox1->Items = Hauptformular->ProjekteAuswahl->Items;
 ComboBox1->Items->Delete(0);
 ComboBox2->ItemIndex = 0;
 Edit1->Text = Hauptformular->project_dir;

 String sel_profil = Hauptformular->ProjekteAuswahl->Items->Strings[Hauptformular->ProjekteAuswahl->ItemIndex];
 if (ComboBox1->Items->IndexOf(sel_profil) > -1)
  ComboBox1->ItemIndex = ComboBox1->Items->IndexOf(sel_profil);
 else
  ComboBox1->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::ComboBox2Change(TObject *Sender)
{
 if (ComboBox2->ItemIndex == 0)
 {
  Edit1->Enabled = true;
  SpeedButton1->Enabled = true;
  ComboBox1->Enabled = true;
  Edit2->Enabled = false;
  SpeedButton2->Enabled = false;
 }
 else
 {
  Edit1->Enabled = false;
  SpeedButton1->Enabled = false;
  ComboBox1->Enabled = false;
  Edit2->Enabled = true;
  SpeedButton2->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::SpeedButton1Click(TObject *Sender)
{
 Bffolder1->Caption = Hauptformular->SprachenWaehler->GetString(69);
 Bffolder1->Title = Hauptformular->SprachenWaehler->GetString(70);
 Bffolder1->SelectedDir = Edit1->Text;
 if (Bffolder1->Execute())
  Edit1->Text = Bffolder1->SelectedDir + "\\";
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::SpeedButton2Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(71);
 filter_temp = filter_temp + Hauptformular->BuildFilter("cab;");
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 Hauptformular->OeffnenDialog->Filter = filter_gesamt;

 Hauptformular->OeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);
 Hauptformular->OeffnenDialog->InitialDir = Hauptformular->project_dir;

 if (Hauptformular->OeffnenDialog->Execute())
  Edit2->Text = Hauptformular->OeffnenDialog->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::CABFile1OverWriteFile(TObject *Sender,
      AnsiString FileName, bool &Allow)
{
 Allow = true;          
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::CABFile1DecompressProgress(TObject *Sender,
      AnsiString FileName, int pos, int tot)
{
 ProgressBar1->Max = tot;
 ProgressBar1->Position = pos;        
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::CABFile1CompressProgress(TObject *Sender,
      int pos, int tot)
{
 ProgressBar1->Max = tot;
 ProgressBar1->Position = pos;        
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::BitBtn1Click(TObject *Sender)
{
 Screen->Cursor = crHourGlass;
 BitBtn1->Enabled = false;
 
 ProgressBar1->Position = 0;
 StrLstDateien->Clear();

 if (ComboBox2->ItemIndex == 0)
 {
  CABFile1->CABFile = Edit1->Text + ComboBox1->Items->Strings[ComboBox1->ItemIndex] + ".cab";
  Hauptformular->DirectoryFindSubs(Hauptformular->project_dir + ComboBox1->Items->Strings[ComboBox1->ItemIndex], Verzeichnisse);
  int items_count = Verzeichnisse->Items->Count;
  int items_count_2;
  String dateiname;

  for (int i = 0; i < items_count; i++)
  {
   TempDateilistBox->Directory = Verzeichnisse->Items->Strings[i];
   TempDateilistBox->Mask = "*.*";
   TempDateilistBox->Update();

   items_count_2 = TempDateilistBox->Items->Count;

   for (int a = 0; a < items_count_2; a++)
   {
    dateiname = TempDateilistBox->Items->Strings[a];
    dateiname = TempDateilistBox->Directory + "\\" + dateiname;
    StrLstDateien->Add(dateiname);
   }
  }

  CABFile1->CABFileContents->Clear();
  TCABFileEntry *CabItem;
  String comp_path;
  for (int i = 0; i < StrLstDateien->Count; i++)
  {
   CabItem = CABFile1->CABFileContents->Add();
   CabItem->Name = StrLstDateien->Strings[i];
   comp_path = ExtractFilePath(StrLstDateien->Strings[i]);
   comp_path = comp_path;
   comp_path = Hauptformular->ReplaceString(comp_path, Hauptformular->project_dir, "", false, false);
   CabItem->RelPath = comp_path;
  }
  if (CABFile1->Compress())
   1 == 1;
  else
   Application->MessageBox(Hauptformular->SprachenWaehler->GetStringEx(72, "Project backup - Compress").c_str(), "Scribe!",  MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);

  delete CabItem;
 }
 else
 {
  if (Trim(Edit2->Text) != "")
  {
   CABFile1->CABFile = Edit2->Text;
   CABFile1->GetContents();
   CABFile1->TargetPath = Hauptformular->project_dir;
   CABFile1->ExtractAll();

   String project_temp = Hauptformular->ProjekteAuswahl->Items->Strings[Hauptformular->ProjekteAuswahl->ItemIndex];
   Hauptformular->ProjectsLoad(project_temp);
   Hauptformular->ProjectsLoadFolders(project_temp);
   if (Hauptformular->ProjekteAuswahl->ItemIndex != 0)
   {
    (Hauptformular->ProjekteExplorer->Items->GetFirstNode())->Selected = true;
    Hauptformular->ProjekteExplorerChange(Sender, Hauptformular->ProjekteExplorer->Items->GetFirstNode());
   }
  }
 }
 BitBtn1->Enabled = true;
 Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TProjektBackup::Bffolder1SelectionChanged(TObject *Sender,
      AnsiString NewSel)
{
 Bffolder1->StatusText = NewSel;        
}
//---------------------------------------------------------------------------

