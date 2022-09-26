//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "textfel.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTextfeld *Textfeld;
//---------------------------------------------------------------------------
__fastcall TTextfeld::TTextfeld(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTextfeld::CheckBox2Click(TObject *Sender)
{
 if (CheckBox2->Checked)
 {
  Edit1->Enabled = true;
  UpDown1->Enabled = true;
 }
 else
 {
  Edit1->Enabled = false;
  UpDown1->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TTextfeld::CheckBox3Click(TObject *Sender)
{
 if (CheckBox3->Checked)
 {
  Edit6->Enabled = true;
  UpDown2->Enabled = true;
 }
 else
 {
  Edit6->Enabled = false;
  UpDown2->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TTextfeld::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TTextfeld::FormShow(TObject *Sender)
{
 EventsTabSheet->TabVisible = Hauptformular->editor_events_tab;

 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  Edit4->Text = Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current);

  if ((Hauptformular->TagAttributeContainsStandalone("readonly", Hauptformular->tag_current)) || (AnsiLowerCase(Hauptformular->TagAttributeGetString("readonly=", Hauptformular->tag_current)) == "readonly"))
   CheckBox1->Checked = true;

  if (Hauptformular->TagAttributeContainsAttribute("rows=", Hauptformular->tag_current))
  {
   CheckBox2->Checked = true;
   UpDown1->Position = Hauptformular->TagAttributeGetNumeric("rows=", Hauptformular->tag_current);
  }

  if (Hauptformular->TagAttributeContainsAttribute("cols=", Hauptformular->tag_current))
  {
   CheckBox3->Checked = true;
   UpDown2->Position = Hauptformular->TagAttributeGetNumeric("cols=", Hauptformular->tag_current);
  }

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Edit2->Text = Hauptformular->TagAttributeGetString("onchange=", Hauptformular->tag_current);
  Edit5->Text = Hauptformular->TagAttributeGetString("onselect=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("textarea", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("name=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("rows=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("cols=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("readonly=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveStandalone("readonly", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onchange=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onselect=", Hauptformular->tag_current);
 }
}
//---------------------------------------------------------------------------

void __fastcall TTextfeld::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<textarea";

 if (Trim(Edit4->Text) != "")
  tag = tag + " name=\"" + Edit4->Text + "\"";

 if (CheckBox2->Checked)
  tag = tag + " rows=\"" + String(UpDown1->Position) + "\"";

 if (CheckBox3->Checked)
  tag = tag + " cols=\"" + String(UpDown2->Position) + "\"";

 if (CheckBox1->Checked)
 {
  if (Hauptformular->editor_xhtml_mode)
   tag = tag + " readonly=\"readonly\"";
  else
   tag = tag + " readonly";
 }

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

 //JavaScript-Ereignisse - Anfang
 if (Trim(Edit2->Text) != "")
  tag = tag + " onChange=\"" + Edit2->Text + "\"";
 if (Trim(Edit5->Text) != "")
  tag = tag + " onSelect=\"" + Edit5->Text + "\"";
 //JavaScript-Ereignisse - Ende

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
  Hauptformular->TagInsert(tag, "</textarea>");
 }
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TTextfeld::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TTextfeld::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_textarea.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TTextfeld::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);       
}
//---------------------------------------------------------------------------

