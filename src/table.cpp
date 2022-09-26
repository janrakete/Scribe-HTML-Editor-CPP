//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "table.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTabelle *Tabelle;
//---------------------------------------------------------------------------
__fastcall TTabelle::TTabelle(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTabelle::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);        
}
//---------------------------------------------------------------------------
void __fastcall TTabelle::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_table.html", true);        
}
//---------------------------------------------------------------------------
void __fastcall TTabelle::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------
void __fastcall TTabelle::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TTabelle::FormShow(TObject *Sender)
{
 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  if (Hauptformular->TagAttributeContainsAttribute("width=", Hauptformular->tag_current))
  {
   CheckBox2->Checked = true;
   if (Hauptformular->TagAttributeContainsPercent("width=", Hauptformular->tag_current))
   {
    ComboBox2->ItemIndex = 0;
    UpDown2->Position = Hauptformular->TagAttributeGetPercent("width=", Hauptformular->tag_current);
   }
   else
   {
    ComboBox2->ItemIndex = 1;
    UpDown2->Position = Hauptformular->TagAttributeGetNumeric("width=", Hauptformular->tag_current);
   }
  }
  else
   ComboBox2->ItemIndex = 0;

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("align=", Hauptformular->tag_current)) == "center")
   ComboBox3->ItemIndex = 1;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("align=", Hauptformular->tag_current)) == "right")
   ComboBox3->ItemIndex = 2;
  else
   ComboBox3->ItemIndex = 0;

  Edit2->Text = Hauptformular->TagAttributeGetString("background=", Hauptformular->tag_current);

  if (Hauptformular->TagAttributeContainsAttribute("bgcolor=", Hauptformular->tag_current))
   Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->TagAttributeGetColor("bgcolor=", Hauptformular->tag_current), ColorDialog1);
  else
   Hauptformular->ColorAssignColorToButton(SpeedButton4, clWindow, ColorDialog1);


  if (Hauptformular->TagAttributeContainsAttribute("border=", Hauptformular->tag_current))
  {
   CheckBox1->Checked = true;
   UpDown4->Position = Hauptformular->TagAttributeGetNumeric("border=", Hauptformular->tag_current);
  }
  if (Hauptformular->TagAttributeContainsAttribute("cellspacing=", Hauptformular->tag_current))
  {
   CheckBox3->Checked = true;
   UpDown5->Position = Hauptformular->TagAttributeGetNumeric("cellspacing=", Hauptformular->tag_current);
  }
  if (Hauptformular->TagAttributeContainsAttribute("cellpadding=", Hauptformular->tag_current))
  {
   CheckBox4->Checked = true;
   UpDown6->Position = Hauptformular->TagAttributeGetNumeric("cellpadding=", Hauptformular->tag_current);
  }

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("table", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("width=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("align=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("border=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("background=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("bgcolor=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("cellpadding=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("cellspacing=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
 }
 else
 {
  ComboBox3->ItemIndex = 0;
  ComboBox2->ItemIndex = 0;
  Hauptformular->ColorAssignColorToButton(SpeedButton4, clWindow, ColorDialog1);
 }
}
//---------------------------------------------------------------------------
void __fastcall TTabelle::CheckBox2Click(TObject *Sender)
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
void __fastcall TTabelle::SpeedButton2Click(TObject *Sender)
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
void __fastcall TTabelle::SpeedButton3Click(TObject *Sender)
{
 Edit2->Text = Hauptformular->ImageCatalogShow();          
}
//---------------------------------------------------------------------------
void __fastcall TTabelle::SpeedButton4Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog1);
 if (ColorDialog1->Execute())
 {
  Hauptformular->ColorButton(SpeedButton4, ColorDialog1->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog1);
 }
}
//---------------------------------------------------------------------------
void __fastcall TTabelle::CheckBox1Click(TObject *Sender)
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
void __fastcall TTabelle::CheckBox3Click(TObject *Sender)
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
void __fastcall TTabelle::CheckBox4Click(TObject *Sender)
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
void __fastcall TTabelle::BitBtn1Click(TObject *Sender)
{
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

 if (Hauptformular->tag_currently_editing)
 {
  tag = tag + Hauptformular->tag_current.SubString(0, Hauptformular->tag_current.Length());
  tag = TrimRight(tag);
  tag = tag + ">";
  Hauptformular->TagInsert(tag, "");
 }
 else
 {
  tag = tag + ">";
  Hauptformular->TagInsert(tag + "\r\n", "\r\n</table>");
 }
 Close();
}
//---------------------------------------------------------------------------
