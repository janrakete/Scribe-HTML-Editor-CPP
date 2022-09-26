//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "include.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TIncludeDatei *IncludeDatei;
//---------------------------------------------------------------------------
__fastcall TIncludeDatei::TIncludeDatei(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TIncludeDatei::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TIncludeDatei::BitBtn2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TIncludeDatei::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_include_file.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TIncludeDatei::FormShow(TObject *Sender)
{
 Hauptformular->DirectoryFindSubs(Hauptformular->includes_dir, Verzeichnisse);

 int items_count = Verzeichnisse->Items->Count;
 int items_count_2;
 String dateiname;
 TListItem *ListItem;

 for (int i = 0; i < items_count; i++)
 {
  Hauptformular->TempDateilistBox->Directory = Verzeichnisse->Items->Strings[i];
  Hauptformular->TempDateilistBox->Mask = "*.inc";
  Hauptformular->TempDateilistBox->Update();

  items_count_2 = Hauptformular->TempDateilistBox->Items->Count;

  for (int a = 0; a < items_count_2; a++)
  {
   dateiname = Hauptformular->TempDateilistBox->Items->Strings[a];
   dateiname = Hauptformular->TempDateilistBox->Directory + "\\" + dateiname;
   dateiname = Hauptformular->ReplaceString(dateiname, Hauptformular->includes_dir, "", true, true);
   ListItem = ListView1->Items->Add();
   ListItem->Caption = dateiname;
   ListItem->ImageIndex = 73;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TIncludeDatei::ListView1Click(TObject *Sender)
{
 ToolButton4->Enabled = ListView1->Selected;
 ToolButton5->Enabled = ListView1->Selected;
 BitBtn1->Enabled = ListView1->Selected;
}
//---------------------------------------------------------------------------

void __fastcall TIncludeDatei::ToolButton4Click(TObject *Sender)
{
 if (ListView1->Selected)
 {
  Hauptformular->CreateChildForm("", Hauptformular->includes_dir + ListView1->Selected->Caption, "");
  Close();
 }
}
//---------------------------------------------------------------------------


void __fastcall TIncludeDatei::ToolButton5Click(TObject *Sender)
{
 if (ListView1->Selected)
 {
  int remove_button = Application->MessageBox(Hauptformular->SprachenWaehler->GetStringEx(68, ExtractFileName(ListView1->Selected->Caption)).c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON2 + MB_ICONQUESTION);

  if (remove_button == IDYES)
  {
   String complete_file = Hauptformular->includes_dir + ListView1->Selected->Caption;
   if (Hauptformular->FileDeleteOnlyOne(complete_file, true))
   {
    ListView1->Selected->Delete();
    ListView1Click (Sender);
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TIncludeDatei::BitBtn1Click(TObject *Sender)
{
 if (ListView1->Selected)
 {
  Hauptformular->TempMemo->Lines->Clear();
  Hauptformular->TempMemo->Lines->LoadFromFile(Hauptformular->includes_dir + ListView1->Selected->Caption);
  Hauptformular->TempMemo->SelectAll();
  String tag = "<!--INC:\"" + ListView1->Selected->Caption + "\"-->";
  tag = tag + Hauptformular->TempMemo->SelText;
  String end_tag = "<!--/INC:\"" + ListView1->Selected->Caption + "\"-->";
  Hauptformular->TagInsert(tag, end_tag);
  Close();
 }
}
//---------------------------------------------------------------------------

