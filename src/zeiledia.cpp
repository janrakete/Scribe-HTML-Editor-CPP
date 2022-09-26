//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "zeiledia.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TZeile *Zeile;
//---------------------------------------------------------------------------
__fastcall TZeile::TZeile(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TZeile::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_tr.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TZeile::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TZeile::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<tr";

 if (ComboBox3->ItemIndex == 1)
  tag = tag + " align=\"center\"";
 else if (ComboBox3->ItemIndex == 2)
  tag = tag + " align=\"right\"";

 if (ComboBox1->ItemIndex == 0)
  tag = tag + " valign=\"top\"";
 else if (ComboBox1->ItemIndex == 2)
  tag = tag + " valign=\"bottom\"";

 if (CheckBox3->Checked)
  tag = tag + " bgcolor=\"" + Hauptformular->ColorColorToXHTMLCode(ColorDialog1->Color) + "\"";

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
  Hauptformular->TagInsert(tag + "\r\n", "\r\n</tr>");
 }
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TZeile::SpeedButton4Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog1);
 if (ColorDialog1->Execute())
 {
  Hauptformular->ColorButton(SpeedButton4, ColorDialog1->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog1);
 }
}
//---------------------------------------------------------------------------

void __fastcall TZeile::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TZeile::FormShow(TObject *Sender)
{
 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("align=", Hauptformular->tag_current)) == "center")
   ComboBox3->ItemIndex = 1;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("align=", Hauptformular->tag_current)) == "right")
   ComboBox3->ItemIndex = 2;
  else
   ComboBox3->ItemIndex = 0;

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("valign=", Hauptformular->tag_current)) == "top")
   ComboBox1->ItemIndex = 0;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("valign=", Hauptformular->tag_current)) == "bottom")
   ComboBox1->ItemIndex = 2;
  else
   ComboBox1->ItemIndex = 1;

  if (Hauptformular->TagAttributeContainsAttribute("bgcolor=", Hauptformular->tag_current))
  {
   Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->TagAttributeGetColor("bgcolor=", Hauptformular->tag_current), ColorDialog1);
   CheckBox3->Checked = true;
  }
  else
   Hauptformular->ColorAssignColorToButton(SpeedButton4, clBlack, ColorDialog1);

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("tr", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("valign=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("align=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("bgcolor=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
 }
 else
 {
  ComboBox3->ItemIndex = 0;
  ComboBox1->ItemIndex = 1;
  Hauptformular->ColorAssignColorToButton(SpeedButton4, clBlack, ColorDialog1);
 }
}
//---------------------------------------------------------------------------

void __fastcall TZeile::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);
}
//---------------------------------------------------------------------------

void __fastcall TZeile::CheckBox3Click(TObject *Sender)
{
 if (CheckBox3->Checked)
  SpeedButton4->Enabled = true;
 else
  SpeedButton4->Enabled = false;
}
//---------------------------------------------------------------------------

