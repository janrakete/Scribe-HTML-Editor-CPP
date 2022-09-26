//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "formula.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormular *Formular;
//---------------------------------------------------------------------------
__fastcall TFormular::TFormular(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormular::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TFormular::FormShow(TObject *Sender)
{
 EventsTabSheet->TabVisible = Hauptformular->editor_events_tab;

 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  Edit3->Text = Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current);
  ComboBox1->Text = Hauptformular->TagAttributeGetString("target=", Hauptformular->tag_current);

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("method=", Hauptformular->tag_current)) == "post")
   ComboBox2->ItemIndex = 1;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("method=", Hauptformular->tag_current)) == "get")
   ComboBox2->ItemIndex = 2;
  else
   ComboBox2->ItemIndex = 0;

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("enctype=", Hauptformular->tag_current)) == "text/plain")
   CheckBox1->Checked = true;

  if (Hauptformular->TagAttributeContainsAttribute("action=", Hauptformular->tag_current) && AnsiPos("mailto:", AnsiLowerCase(Hauptformular->TagAttributeGetString("action=", Hauptformular->tag_current))))
  {
   Edit1->Text = Hauptformular->ReplaceString(Hauptformular->TagAttributeGetString("action=", Hauptformular->tag_current), "mailto:", "", true, true);
   ComboBox3->ItemIndex = 1;
   ComboBox3Change(Sender);
  }
  else if (Hauptformular->TagAttributeContainsAttribute("action=", Hauptformular->tag_current))
  {
   Edit1->Text = Hauptformular->TagAttributeGetString("action=", Hauptformular->tag_current);
   ComboBox3->ItemIndex = 2;
   ComboBox3Change(Sender);
  }
  else
  {
   ComboBox3->ItemIndex = 0;
   ComboBox3Change(Sender);
  }

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Edit2->Text = Hauptformular->TagAttributeGetString("onsubmit=", Hauptformular->tag_current);
  Edit5->Text = Hauptformular->TagAttributeGetString("onreset=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("form", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("name=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("action=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("target=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("method=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("enctype=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onsubmit=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onreset=", Hauptformular->tag_current);
 }
 else
 {
  ComboBox3->ItemIndex = 0;
  ComboBox2->ItemIndex = 0;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFormular::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<form";

 if (Trim(Edit3->Text) != "")
  tag = tag + " name=\"" + Edit3->Text + "\"";

 if (ComboBox3->ItemIndex == 1)
  tag = tag + " action=\"MailTo:" + Edit1->Text + "\"";
 else if (ComboBox3->ItemIndex == 2)
  tag = tag + " action=\"" + Edit1->Text + "\"";

 if (ComboBox2->ItemIndex == 1)
  tag = tag + " method=\"post\"";
 else if (ComboBox2->ItemIndex == 2)
  tag = tag + " method=\"get\"";

 if (CheckBox1->Checked)
  tag = tag + " enctype=\"text/plain\"";

 if (Trim(ComboBox1->Text) != "")
  tag = tag + " target=\"" + ComboBox1->Text + "\"";

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
  tag = tag + " onSubmit=\"" + Edit2->Text + "\"";
 if (Trim(Edit5->Text) != "")
  tag = tag + " onReset=\"" + Edit5->Text + "\"";
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
  Hauptformular->TagInsert(tag, "\r\n</form>");
 }
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormular::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TFormular::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_form.html", true);       
}
//---------------------------------------------------------------------------

void __fastcall TFormular::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);        
}
//---------------------------------------------------------------------------

void __fastcall TFormular::ComboBox3Change(TObject *Sender)
{
 if (ComboBox3->ItemIndex == 1)
 {
  CheckBox1->Enabled = true;
 }
 else
 {
  CheckBox1->Enabled = false;
  CheckBox1->Checked = false;
 }
}
//---------------------------------------------------------------------------

