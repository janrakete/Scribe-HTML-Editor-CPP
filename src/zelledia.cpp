//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "zelledia.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TZelle *Zelle;
//---------------------------------------------------------------------------
__fastcall TZelle::TZelle(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TZelle::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<td";

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

 if (CheckBox3->Checked)
  tag = tag + " bgcolor=\"" + Hauptformular->ColorColorToXHTMLCode(ColorDialog1->Color) + "\"";

 if (ComboBox3->ItemIndex == 1)
  tag = tag + " align=\"center\"";
 else if (ComboBox3->ItemIndex == 2)
  tag = tag + " align=\"right\"";

 if (ComboBox4->ItemIndex == 0)
  tag = tag + " valign=\"top\"";
 else if (ComboBox4->ItemIndex == 2)
  tag = tag + " valign=\"bottom\"";

 if (CheckBox4->Checked)
 {
  if (Hauptformular->editor_xhtml_mode)
   tag = tag + " nowrap=\"nowrap\"";
  else
   tag = tag + " nowrap";
 }

 if (CheckBox5->Checked)
  tag = tag + " rowspan=\"" + UpDown3->Position + "\"";
 if (CheckBox6->Checked)
  tag = tag + " colspan=\"" + UpDown4->Position + "\"";

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
  Hauptformular->TagInsert(tag, "</td>");
 }
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TZelle::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TZelle::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_td.html", true);      
}
//---------------------------------------------------------------------------

void __fastcall TZelle::CheckBox3Click(TObject *Sender)
{
 if (CheckBox3->Checked)
  SpeedButton4->Enabled = true;
 else
  SpeedButton4->Enabled = false;        
}
//---------------------------------------------------------------------------

void __fastcall TZelle::SpeedButton4Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog1);
 if (ColorDialog1->Execute())
 {
  Hauptformular->ColorButton(SpeedButton4, ColorDialog1->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog1);
 }
}
//---------------------------------------------------------------------------

void __fastcall TZelle::CheckBox1Click(TObject *Sender)
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

void __fastcall TZelle::CheckBox2Click(TObject *Sender)
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

void __fastcall TZelle::CheckBox5Click(TObject *Sender)
{
 if (CheckBox5->Checked)
 {
  Edit7->Enabled = true;
  UpDown3->Enabled = true;
 }
 else
 {
  Edit7->Enabled = false;
  UpDown3->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TZelle::CheckBox6Click(TObject *Sender)
{
 if (CheckBox6->Checked)
 {
  Edit1->Enabled = true;
  UpDown4->Enabled = true;
 }
 else
 {
  Edit1->Enabled = false;
  UpDown4->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TZelle::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);
}
//---------------------------------------------------------------------------

void __fastcall TZelle::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TZelle::FormShow(TObject *Sender)
{
 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

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

  if (Hauptformular->TagAttributeContainsAttribute("bgcolor=", Hauptformular->tag_current))
  {
   Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->TagAttributeGetColor("bgcolor=", Hauptformular->tag_current), ColorDialog1);
   CheckBox3->Checked = true;
  }
  else
   Hauptformular->ColorAssignColorToButton(SpeedButton4, clBlack, ColorDialog1);

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("align=", Hauptformular->tag_current)) == "center")
   ComboBox3->ItemIndex = 1;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("align=", Hauptformular->tag_current)) == "right")
   ComboBox3->ItemIndex = 2;
  else
   ComboBox3->ItemIndex = 0;

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("valign=", Hauptformular->tag_current)) == "top")
   ComboBox4->ItemIndex = 0;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("valign=", Hauptformular->tag_current)) == "bottom")
   ComboBox4->ItemIndex = 2;
  else
   ComboBox4->ItemIndex = 1;

  if ((Hauptformular->TagAttributeContainsStandalone("nowrap", Hauptformular->tag_current)) || (AnsiLowerCase(Hauptformular->TagAttributeGetString("nowrap=", Hauptformular->tag_current)) == "nowrap"))
   CheckBox4->Checked = true;

  if (Hauptformular->TagAttributeContainsAttribute("rowspan=", Hauptformular->tag_current))
  {
   UpDown3->Position = Hauptformular->TagAttributeGetNumeric("rowspan=", Hauptformular->tag_current);
   CheckBox5->Checked = true;
  }
  if (Hauptformular->TagAttributeContainsAttribute("colspan=", Hauptformular->tag_current))
  {
   UpDown4->Position = Hauptformular->TagAttributeGetNumeric("colspan=", Hauptformular->tag_current);
   CheckBox6->Checked = true;
  }

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("td", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("height=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("width=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("bgcolor=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("valign=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("align=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("colspan=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("rowspan=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("nowrap=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveStandalone("nowrap", Hauptformular->tag_current);
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
  ComboBox4->ItemIndex = 1;
  Hauptformular->ColorAssignColorToButton(SpeedButton4, clBlack, ColorDialog1);
 }
}
//---------------------------------------------------------------------------

