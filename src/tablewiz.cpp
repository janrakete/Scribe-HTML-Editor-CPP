//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "tablewiz.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTabellenAssistent *TabellenAssistent;
//---------------------------------------------------------------------------
__fastcall TTabellenAssistent::TTabellenAssistent(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTabellenAssistent::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_table_wiz.html", true);
}
//---------------------------------------------------------------------------
void __fastcall TTabellenAssistent::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TTabellenAssistent::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TTabellenAssistent::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);
}
//---------------------------------------------------------------------------
void __fastcall TTabellenAssistent::BitBtn1Click(TObject *Sender)
{
 String spaces = AnsiString::StringOfChar(' ', ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol);

 String tag;
 tag = "<table";

 if (CheckBox2->Checked)
 {
  if (ComboBox2->ItemIndex == 0)
   tag = tag + " width=\"" + String(UpDown2->Position) + "%" + "\"";
  else
   tag = tag + " width=\"" + String(UpDown2->Position) + "\"";
 }

 if (ComboBox3->ItemIndex == 1)
  tag = tag + " align=\"center\"";
 else if (ComboBox3->ItemIndex == 2)
  tag = tag + " align=\"right\"";

 if (Trim(Edit2->Text) != "")
  tag = tag + " background=\"" + Edit2->Text + "\"";
 if (ColorDialog1->Color != clWindow)
  tag = tag + " bgcolor=\"" + Hauptformular->ColorColorToXHTMLCode(ColorDialog1->Color) + "\"";

 if (CheckBox1->Checked)
  tag = tag + " border=\"" + String(UpDown4->Position) + "\"";
 if (CheckBox3->Checked)
  tag = tag + " cellspacing=\"" + String(UpDown5->Position) + "\"";
 if (CheckBox4->Checked)
  tag = tag + " cellpadding=\"" + String(UpDown6->Position) + "\"";

 //Cascading Style-Sheets - Anfang
 if (Trim(CssStyle->Text) != "")
  tag = tag + " style=\"" + CssStyle->Text + "\"";
 if (Trim(CssID->Text) != "")
  tag = tag + " id=\"" + CssID->Text + "\"";
 if (Trim(CssClass->Text) != "")
  tag = tag + " class=\"" + CssClass->Text + "\"";
 if (Trim(CssTitle->Text) != "")
  tag = tag + " title=\"" + CssTitle->Text + "\"";
 //Cascading Style-Sheets - Ende

 tag = tag + ">";
 Hauptformular->TagInsert(tag + "\r\n", "\r\n\r\n" + spaces + "</table>");

 int Zeile = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine;
 String temp_str;
 Zeile++;
 for (int i = 0; i < UpDown3->Position; i++)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(Zeile, spaces + " <tr>");
  for (int a = 0; a < UpDown1->Position; a++)
  {
   temp_str = StringGrid1->Cells[a][i];
   Zeile++;
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(Zeile, spaces + "  <td>" + temp_str + "</td>");
  }
  Zeile++;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(Zeile, spaces + " </tr>");
  Zeile = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine;
 }
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TTabellenAssistent::FormShow(TObject *Sender)
{
 Label1->Caption = Label1->Caption + ":";
 Label6->Caption = Label6->Caption + ":";
 ComboBox3->ItemIndex = 0;
 ComboBox2->ItemIndex = 0;
 Hauptformular->ColorAssignColorToButton(SpeedButton4, clWindow, ColorDialog1);
}
//---------------------------------------------------------------------------
void __fastcall TTabellenAssistent::CheckBox2Click(TObject *Sender)
{
 if (CheckBox2->Checked)
 {
  Edit6->Enabled = true;
  UpDown2->Enabled = true;
  ComboBox2->Enabled = true;
 }
 else
 {
  Edit6->Enabled = false;
  UpDown2->Enabled = false;
  ComboBox2->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TTabellenAssistent::SpeedButton2Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(6);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->graphicfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;
 OeffnenDialog->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 OeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OeffnenDialog->Execute())
  Edit2->Text = Hauptformular->DirectorySameAndRelative(OeffnenDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TTabellenAssistent::SpeedButton3Click(TObject *Sender)
{
 Edit2->Text = Hauptformular->ImageCatalogShow();        
}
//---------------------------------------------------------------------------

void __fastcall TTabellenAssistent::SpeedButton4Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog1);
 if (ColorDialog1->Execute())
 {
  Hauptformular->ColorButton(SpeedButton4, ColorDialog1->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog1);
 }
}
//---------------------------------------------------------------------------

void __fastcall TTabellenAssistent::CheckBox1Click(TObject *Sender)
{
 if (CheckBox1->Checked)
 {
  Edit3->Enabled = true;
  UpDown4->Enabled = true;
 }
 else
 {
  Edit3->Enabled = false;
  UpDown4->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TTabellenAssistent::CheckBox3Click(TObject *Sender)
{
 if (CheckBox3->Checked)
 {
  Edit4->Enabled = true;
  UpDown5->Enabled = true;
 }
 else
 {
  Edit4->Enabled = false;
  UpDown5->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TTabellenAssistent::CheckBox4Click(TObject *Sender)
{
 if (CheckBox4->Checked)
 {
  Edit5->Enabled = true;
  UpDown6->Enabled = true;
 }
 else
 {
  Edit5->Enabled = false;
  UpDown6->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TTabellenAssistent::Edit7Change(TObject *Sender)
{
 StringGrid1->RowCount = UpDown3->Position;
 StringGrid1->ColCount = UpDown1->Position;        
}
//---------------------------------------------------------------------------

void __fastcall TTabellenAssistent::Edit1Change(TObject *Sender)
{
 StringGrid1->RowCount = UpDown3->Position;
 StringGrid1->ColCount = UpDown1->Position;
}
//---------------------------------------------------------------------------

