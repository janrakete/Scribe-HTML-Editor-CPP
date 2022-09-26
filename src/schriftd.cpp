//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "schriftd.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSchrift *Schrift;
//---------------------------------------------------------------------------
__fastcall TSchrift::TSchrift(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSchrift::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TSchrift::FormShow(TObject *Sender)
{
 int items_count = Screen->Fonts->Count;
 for (int i = 0; i < items_count; i++)
  ListBox1->Items->Add(Screen->Fonts->Strings[i]);

 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  Edit1->Text = Hauptformular->TagAttributeGetString("face=", Hauptformular->tag_current);

  if (Hauptformular->TagAttributeContainsAttribute("size=", Hauptformular->tag_current))
   UpDown3->Position = Hauptformular->TagAttributeGetNumeric("size=", Hauptformular->tag_current);

  if (Hauptformular->TagAttributeContainsAttribute("color=", Hauptformular->tag_current))
   Hauptformular->ColorAssignColorToButton(SpeedButton2, Hauptformular->TagAttributeGetColor("color=", Hauptformular->tag_current), ColorDialog1);
  else
   Hauptformular->ColorAssignColorToButton(SpeedButton2, clBlack, ColorDialog1);

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("font", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("color=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("face=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("size=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
 }
 else
  Hauptformular->ColorAssignColorToButton(SpeedButton2, clBlack, ColorDialog1);
}
//---------------------------------------------------------------------------

void __fastcall TSchrift::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TSchrift::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_font.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TSchrift::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);        
}
//---------------------------------------------------------------------------

void __fastcall TSchrift::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<font";

 if (Trim(Edit1->Text) != "")
  tag = tag + " face=\"" + Edit1->Text + "\"";
 if (UpDown3->Position != 3)
  tag = tag + " size=\"" + String(UpDown3->Position) + "\"";
 if (ColorDialog1->Color != clBlack)
  tag = tag + " color=\"" + Hauptformular->ColorColorToXHTMLCode(ColorDialog1->Color) + "\"";

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
  Hauptformular->TagInsert(tag, "</font>");
 }
 Close();
}
//---------------------------------------------------------------------------


void __fastcall TSchrift::SpeedButton3Click(TObject *Sender)
{
 if (ListBox1->ItemIndex != -1)
 {
  String font;
  int items_count = ListBox1->Items->Count;

  for (int i = 0; i < items_count; i++)
  {
   if (ListBox1->Selected[i])
    font = font + ListBox1->Items->Strings[i] + ",";
  }
  font = Edit1->Text + "," + font;

  String firstchar = font.SubString(0, 1);
  if (firstchar == ",")
   font = font.SubString(2, font.Length());
  String lastchar = font.AnsiLastChar();
  if (lastchar == ",")
   font = font.SubString(0, font.Length() - 1);

  Edit1->Text = font;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSchrift::ListBox1Click(TObject *Sender)
{
 SpeedButton3->Enabled = ListBox1->SelCount;
}
//---------------------------------------------------------------------------

void __fastcall TSchrift::SpeedButton2Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog1);
 if (ColorDialog1->Execute())
 {
  Hauptformular->ColorButton(SpeedButton2, ColorDialog1->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog1);
 }
}
//---------------------------------------------------------------------------

