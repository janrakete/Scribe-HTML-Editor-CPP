//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "verstfe.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVerstecktesFeld *VerstecktesFeld;
//---------------------------------------------------------------------------
__fastcall TVerstecktesFeld::TVerstecktesFeld(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TVerstecktesFeld::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TVerstecktesFeld::FormShow(TObject *Sender)
{
 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  Edit1->Text = Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current);
  Edit3->Text = Hauptformular->TagAttributeGetString("value=", Hauptformular->tag_current);

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("input", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("type=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("name=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("value=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
 }
}
//---------------------------------------------------------------------------

void __fastcall TVerstecktesFeld::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<input type=\"hidden\"";

 if (Trim(Edit3->Text) != "")
  tag = tag + " value=\"" + Edit3->Text + "\"";

 if (Trim(Edit1->Text) != "")
  tag = tag + " name=\"" + Edit1->Text + "\"";

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
  tag = tag + Hauptformular->tag_current.SubString(0, Hauptformular->tag_current.Length());

 tag = Hauptformular->XHTMLBracketAdd(tag);
 tag = tag + ">";
 Hauptformular->TagInsert(tag, "");
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TVerstecktesFeld::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }        
}
//---------------------------------------------------------------------------

void __fastcall TVerstecktesFeld::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_input_hidden.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TVerstecktesFeld::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);        
}
//---------------------------------------------------------------------------

