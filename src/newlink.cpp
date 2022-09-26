//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "newlink.h"
#include "main.h"
#include "hilfed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNeueVerknuepfung *NeueVerknuepfung;
//---------------------------------------------------------------------------
__fastcall TNeueVerknuepfung::TNeueVerknuepfung(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TNeueVerknuepfung::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TNeueVerknuepfung::BitBtn2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TNeueVerknuepfung::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_new_link.html", true);        
}
//---------------------------------------------------------------------------
void __fastcall TNeueVerknuepfung::FormShow(TObject *Sender)
{
 Anwendungen->Selected = Anwendungen->Items->Item[0];
 AnwendungenClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNeueVerknuepfung::SpeedButton1Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(58);
 filter_temp = filter_temp + " (*.exe,*.bat,*.com)|*.exe;*.bat;*.com";
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OpenDialog1->Filter = filter_gesamt;
 OpenDialog1->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OpenDialog1->Execute())
 {
  Edit2->Text = OpenDialog1->FileName;
  Edit1->Text = ExtractFileName(OpenDialog1->FileName);
 }
}
//---------------------------------------------------------------------------

void __fastcall TNeueVerknuepfung::AnwendungenClick(TObject *Sender)
{
 if (Anwendungen->Selected)
 {
  if (Anwendungen->Selected->Index == 0)
  {
   Edit1->Text = Hauptformular->quickstart_desc_1;
   Edit2->Text = Hauptformular->quickstart_path_1;
   Edit3->Text = Hauptformular->quickstart_para_1;
  }
  else if (Anwendungen->Selected->Index == 1)
  {
   Edit1->Text = Hauptformular->quickstart_desc_2;
   Edit2->Text = Hauptformular->quickstart_path_2;
   Edit3->Text = Hauptformular->quickstart_para_2;
  }
  else if (Anwendungen->Selected->Index == 2)
  {
   Edit1->Text = Hauptformular->quickstart_desc_3;
   Edit2->Text = Hauptformular->quickstart_path_3;
   Edit3->Text = Hauptformular->quickstart_para_3;
  }
  else if (Anwendungen->Selected->Index == 3)
  {
   Edit1->Text = Hauptformular->quickstart_desc_4;
   Edit2->Text = Hauptformular->quickstart_path_4;
   Edit3->Text = Hauptformular->quickstart_para_4;
  }
  else if (Anwendungen->Selected->Index == 4)
  {
   Edit1->Text = Hauptformular->quickstart_desc_5;
   Edit2->Text = Hauptformular->quickstart_path_5;
   Edit3->Text = Hauptformular->quickstart_para_5;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TNeueVerknuepfung::BitBtn1Click(TObject *Sender)
{
 if (!Anwendungen->Selected)
  Anwendungen->Selected = Anwendungen->ItemFocused;

 if (Anwendungen->Selected->Index == 0)
 {
  Hauptformular->quickstart_desc_1 = Edit1->Text;
  Hauptformular->quickstart_path_1 = Edit2->Text;
  Hauptformular->quickstart_para_1 = Edit3->Text;
 }
 else if (Anwendungen->Selected->Index == 1)
 {
  Hauptformular->quickstart_desc_2 = Edit1->Text;
  Hauptformular->quickstart_path_2 = Edit2->Text;
  Hauptformular->quickstart_para_2 = Edit3->Text;
 }
 else if (Anwendungen->Selected->Index == 2)
 {
  Hauptformular->quickstart_desc_3 = Edit1->Text;
  Hauptformular->quickstart_path_3 = Edit2->Text;
  Hauptformular->quickstart_para_3 = Edit3->Text;
 }
 else if (Anwendungen->Selected->Index == 3)
 {
  Hauptformular->quickstart_desc_4 = Edit1->Text;
  Hauptformular->quickstart_path_4 = Edit2->Text;
  Hauptformular->quickstart_para_4 = Edit3->Text;
 }
 else if (Anwendungen->Selected->Index == 4)
 {
  Hauptformular->quickstart_desc_5 = Edit1->Text;
  Hauptformular->quickstart_path_5 = Edit2->Text;
  Hauptformular->quickstart_para_5 = Edit3->Text;
 }
}
//---------------------------------------------------------------------------

