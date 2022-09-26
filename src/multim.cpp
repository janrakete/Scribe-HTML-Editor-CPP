//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "multim.h"
#include "hilfed.h"
#include "child.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMultimedia *Multimedia;
//---------------------------------------------------------------------------
__fastcall TMultimedia::TMultimedia(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMultimedia::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TMultimedia::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TMultimedia::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_object.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TMultimedia::FormShow(TObject *Sender)
{
 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  if (Hauptformular->TagAttributeContainsAttribute("border=", Hauptformular->tag_current))
   UpDown3->Position = Hauptformular->TagAttributeGetNumeric("border=", Hauptformular->tag_current);

  if (Hauptformular->TagAttributeContainsAttribute("height=", Hauptformular->tag_current))
  {
   CheckBox1->Checked = true;
   if (Hauptformular->TagAttributeContainsPercent("height=", Hauptformular->tag_current))
   {
    ComboBox1->ItemIndex = 0;
    UpDown1->Position = Hauptformular->TagAttributeGetPercent("height=", Hauptformular->tag_current);
   }
   else
   {
    ComboBox1->ItemIndex = 1;
    UpDown1->Position = Hauptformular->TagAttributeGetNumeric("height=", Hauptformular->tag_current);
   }
  }
  else
   ComboBox1->ItemIndex = 0;

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

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("align=", Hauptformular->tag_current)) == "top")
   ComboBox3->ItemIndex = 1;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("align=", Hauptformular->tag_current)) == "middle")
   ComboBox3->ItemIndex = 2;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("align=", Hauptformular->tag_current)) == "bottom")
   ComboBox3->ItemIndex = 3;
  else
   ComboBox3->ItemIndex = 0;

  Edit1->Text = Hauptformular->TagAttributeGetString("data=", Hauptformular->tag_current);
  Edit2->Text = Hauptformular->TagAttributeGetString("standby=", Hauptformular->tag_current);
  ComboBox4->Text = Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current);

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("object", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("data=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("standby=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("height=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("width=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("border=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("align=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("type=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
 }
 else
 {
  ComboBox1->ItemIndex = 0;
  ComboBox2->ItemIndex = 0;
  ComboBox3->ItemIndex = 0;
 }
}
//---------------------------------------------------------------------------

void __fastcall TMultimedia::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<object";

 tag = tag + " data=\"" + Edit1->Text + "\"";

 if (Trim(Edit2->Text) != "")
  tag = tag + " standby=\"" + Edit2->Text + "\"";

 if (Trim(ComboBox4->Text) != "")
  tag = tag + " type=\"" + ComboBox4->Text + "\"";

 if (CheckBox1->Checked)
 {
  if (ComboBox1->ItemIndex == 0)
   tag = tag + " height=\"" + String(UpDown1->Position) + "%" + "\"";
  else
   tag = tag + " height=\"" + String(UpDown1->Position) + "\"";
 }

 if (CheckBox2->Checked)
 {
  if (ComboBox2->ItemIndex == 0)
   tag = tag + " width=\"" + String(UpDown2->Position) + "%" + "\"";
  else
   tag = tag + " width=\"" + String(UpDown2->Position) + "\"";
 }

 if (UpDown3->Position != 2)
  tag = tag + " border=\"" + String(UpDown3->Position) + "\"";

 if (ComboBox3->ItemIndex == 1)
  tag = tag + " align=\"top\"";
 else if (ComboBox3->ItemIndex == 2)
  tag = tag + " align=\"middle\"";
 else if (ComboBox3->ItemIndex == 3)
  tag = tag + " align=\"bottom\"";

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
  Hauptformular->TagInsert(tag, "</object>");
 }
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TMultimedia::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);        
}
//---------------------------------------------------------------------------

void __fastcall TMultimedia::SpeedButton2Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;
 OeffnenDialog->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 OeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OeffnenDialog->Execute())
  Edit1->Text = Hauptformular->DirectorySameAndRelative(OeffnenDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TMultimedia::CheckBox1Click(TObject *Sender)
{
 if (CheckBox1->Checked)
 {
  Edit5->Enabled = true;
  UpDown1->Enabled = true;
  ComboBox1->Enabled = true;
 }
 else
 {
  Edit5->Enabled = false;
  UpDown1->Enabled = false;
  ComboBox1->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TMultimedia::CheckBox2Click(TObject *Sender)
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

