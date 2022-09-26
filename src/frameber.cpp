//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "frameber.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrameBereich *FrameBereich;
//---------------------------------------------------------------------------
__fastcall TFrameBereich::TFrameBereich(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrameBereich::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TFrameBereich::FormShow(TObject *Sender)
{
 EventsTabSheet->TabVisible = Hauptformular->editor_events_tab;

 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);


  if (Hauptformular->TagAttributeContainsAttribute("cols=", Hauptformular->tag_current))
  {
   ComboBox1->ItemIndex = 0;
   Edit1->Text = Hauptformular->TagAttributeGetString("cols=", Hauptformular->tag_current);
  }
  else if (Hauptformular->TagAttributeContainsAttribute("rows=", Hauptformular->tag_current))
  {
   ComboBox1->ItemIndex = 1;
   Edit1->Text = Hauptformular->TagAttributeGetString("rows=", Hauptformular->tag_current);
  }
  else
   ComboBox1->ItemIndex = 0;

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Edit2->Text = Hauptformular->TagAttributeGetString("onload=", Hauptformular->tag_current);
  Edit3->Text = Hauptformular->TagAttributeGetString("onunload=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("frameset", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("cols=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("rows=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onload=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onunload=", Hauptformular->tag_current);
 }
 else
  ComboBox1->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFrameBereich::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);
}
//---------------------------------------------------------------------------

void __fastcall TFrameBereich::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_frameset.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TFrameBereich::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrameBereich::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<frameset";


 if (ComboBox1->ItemIndex == 0)
  tag = tag + " cols=\"" + Edit1->Text + "\"";
 else
  tag = tag + " rows=\"" + Edit1->Text + "\"";

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
  tag = tag + " onLoad=\"" + Edit2->Text + "\"";
 if (Trim(Edit3->Text) != "")
  tag = tag + " onUnload=\"" + Edit3->Text + "\"";
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
  Hauptformular->TagInsert(tag + "\r\n", "\r\n</frameset>");
 }
 Close();
}
//---------------------------------------------------------------------------

