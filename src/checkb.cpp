//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "checkb.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCheckboxTag *CheckboxTag;
//---------------------------------------------------------------------------
__fastcall TCheckboxTag::TCheckboxTag(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCheckboxTag::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TCheckboxTag::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_input_checkbox.html", true);
}
//---------------------------------------------------------------------------
void __fastcall TCheckboxTag::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------
void __fastcall TCheckboxTag::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<input type=\"checkbox\"";

 if (Trim(Edit1->Text) != "")
  tag = tag + " value=\"" + Edit1->Text + "\"";

 if (Trim(Edit3->Text) != "")
  tag = tag + " name=\"" + Edit3->Text + "\"";

 if (CheckBox1->Checked)
 {
  if (Hauptformular->editor_xhtml_mode)
   tag = tag + " checked=\"checked\"";
  else
   tag = tag + " checked";
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
  tag = tag + " onClick=\"" + Edit2->Text + "\"";
 //JavaScript-Ereignisse - Ende

 if (Hauptformular->tag_currently_editing)
  tag = tag + Hauptformular->tag_current.SubString(0, Hauptformular->tag_current.Length());

 tag = Hauptformular->XHTMLBracketAdd(tag);
 tag = tag + ">";
 Hauptformular->TagInsert(tag + Edit4->Text, "");
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TCheckboxTag::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);      
}
//---------------------------------------------------------------------------
void __fastcall TCheckboxTag::FormShow(TObject *Sender)
{
 EventsTabSheet->TabVisible = Hauptformular->editor_events_tab;

 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  Edit4->Color = clBtnFace;
  Edit4->Enabled = false;

  Edit3->Text = Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current);
  Edit1->Text = Hauptformular->TagAttributeGetString("value=", Hauptformular->tag_current);

  if ((Hauptformular->TagAttributeContainsStandalone("checked", Hauptformular->tag_current)) || (AnsiLowerCase(Hauptformular->TagAttributeGetString("checked=", Hauptformular->tag_current)) == "checked"))
   CheckBox1->Checked = true;

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);
  Edit2->Text = Hauptformular->TagAttributeGetString("onclick=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("input", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("type=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("name=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("value=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("checked=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveStandalone("checked", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onclick=", Hauptformular->tag_current);
 }
}
//---------------------------------------------------------------------------
