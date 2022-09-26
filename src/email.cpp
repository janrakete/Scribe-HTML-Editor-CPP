//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "email.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEmailVerweis *EmailVerweis;
//---------------------------------------------------------------------------
__fastcall TEmailVerweis::TEmailVerweis(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEmailVerweis::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------
void __fastcall TEmailVerweis::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;        
}
//---------------------------------------------------------------------------
void __fastcall TEmailVerweis::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_ahref.html", true);        
}
//---------------------------------------------------------------------------
void __fastcall TEmailVerweis::SpeedButton1Click(TObject *Sender)
{
CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);
}
//---------------------------------------------------------------------------
void __fastcall TEmailVerweis::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<a";

 tag = tag + " href=\"MailTo:" + Edit1->Text + "\"";

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
 {
  tag = tag + Hauptformular->tag_current.SubString(0, Hauptformular->tag_current.Length());
  tag = TrimRight(tag);
  tag = tag + ">";
  Hauptformular->TagInsert(tag, "");
 }
 else
 {
  tag = tag + ">";
  if (CheckBox1->Checked)
   tag = tag + Edit1->Text;
  Hauptformular->TagInsert(tag, "</a>");
 }
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TEmailVerweis::FormShow(TObject *Sender)
{
 EventsTabSheet->TabVisible = Hauptformular->editor_events_tab;

 if (Hauptformular->tag_currently_editing)
 {
  CheckBox1->Enabled = false;
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  Edit1->Text = Hauptformular->ReplaceString(Hauptformular->TagAttributeGetString("href=", Hauptformular->tag_current), "MAILTO:", "", false, true);

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);
  Edit2->Text = Hauptformular->TagAttributeGetString("onclick=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("a", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("href=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onclick=", Hauptformular->tag_current);
 }
}
//---------------------------------------------------------------------------

