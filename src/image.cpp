//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "image.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGrafik *Grafik;
//---------------------------------------------------------------------------
__fastcall TGrafik::TGrafik(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGrafik::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_img.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TGrafik::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);        
}
//---------------------------------------------------------------------------

void __fastcall TGrafik::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;        
}
//---------------------------------------------------------------------------

void __fastcall TGrafik::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }        
}
//---------------------------------------------------------------------------

void __fastcall TGrafik::CheckBox1Click(TObject *Sender)
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

void __fastcall TGrafik::CheckBox2Click(TObject *Sender)
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


void __fastcall TGrafik::SpeedButton2Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(6);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->graphicfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;
 OeffnenDialog->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 OeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OeffnenDialog->Execute())
 {
  Edit1->Text = Hauptformular->DirectorySameAndRelative(OeffnenDialog->FileName);
  Image1->Picture->LoadFromFile(OeffnenDialog->FileName);

  if (Image1->Picture->Width < 153)
   Image1->Left = 75 - (Image1->Picture->Width / 2);
  else
   Image1->Left = 0;
  if (Image1->Picture->Height < 181)
   Image1->Top = 89 - (Image1->Picture->Height / 2);
  else
   Image1->Top = 0;
  UpDown1->Position = Image1->Height;
  UpDown2->Position = Image1->Width;
  ComboBox1->ItemIndex = 1;
  ComboBox2->ItemIndex = 1;
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafik::SpeedButton3Click(TObject *Sender)
{
 Edit1->Text = Hauptformular->ImageCatalogShow();

 if (Trim(Edit1->Text) != "")
 {
  String pfad_vorher = GetCurrentDir();
  SetCurrentDir (ExtractFilePath(Hauptformular->ActiveMDIChild->Caption));

  Image1->Picture->LoadFromFile(Edit1->Text);

  if (Image1->Picture->Width < 153)
   Image1->Left = 75 - (Image1->Picture->Width / 2);
  else
   Image1->Left = 0;
  if (Image1->Picture->Height < 181)
   Image1->Top = 89 - (Image1->Picture->Height / 2);
  else
   Image1->Top = 0;
  UpDown1->Position = Image1->Height;
  UpDown2->Position = Image1->Width;
  ComboBox1->ItemIndex = 1;
  ComboBox2->ItemIndex = 1;

  SetCurrentDir (pfad_vorher);
 }
}
//---------------------------------------------------------------------------
void __fastcall TGrafik::BitBtn4Click(TObject *Sender)
{
 String pfad_vorher = GetCurrentDir();
 SetCurrentDir (ExtractFilePath(Hauptformular->ActiveMDIChild->Caption));
 Image1->Picture->LoadFromFile(Edit1->Text);
 UpDown1->Position = Image1->Height;
 UpDown2->Position = Image1->Width;
 ComboBox1->ItemIndex = 1;
 ComboBox2->ItemIndex = 1;
 SetCurrentDir (pfad_vorher);
}
//---------------------------------------------------------------------------

void __fastcall TGrafik::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<img";

 tag = tag + " src=\"" + Edit1->Text + "\"";
 tag = tag + " alt=\"" + Edit4->Text + "\"";

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

 //JavaScript-Ereignisse - Anfang
 if (Trim(Edit2->Text) != "")
  tag = tag + " onAbort=\"" + Edit2->Text + "\"";
 if (Trim(Edit3->Text) != "")
  tag = tag + " onError=\"" + Edit3->Text + "\"";
 //JavaScript-Ereignisse - Ende

 if (Hauptformular->tag_currently_editing)
  tag = tag + Hauptformular->tag_current.SubString(0, Hauptformular->tag_current.Length());

 tag = Hauptformular->XHTMLBracketAdd(tag);
 tag = tag + ">";
 Hauptformular->TagInsert(tag, "");
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TGrafik::FormShow(TObject *Sender)
{
 EventsTabSheet->TabVisible = Hauptformular->editor_events_tab;

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

  if (Hauptformular->TagAttributeContainsAttribute("src=", Hauptformular->tag_current))
  {
   Edit1->Text = Hauptformular->TagAttributeGetString("src=", Hauptformular->tag_current);
   String pfad_vorher = GetCurrentDir();
   SetCurrentDir (ExtractFilePath(Hauptformular->ActiveMDIChild->Caption));
   try
   {
    Image1->Picture->LoadFromFile(Edit1->Text);
    if (Image1->Picture->Width < 153)
     Image1->Left = 75 - (Image1->Picture->Width / 2);
    else
     Image1->Left = 0;
    if (Image1->Picture->Height < 181)
     Image1->Top = 89 - (Image1->Picture->Height / 2);
    else
     Image1->Top = 0;
   }
   catch (...)
   {
    1 == 1;
   }
   SetCurrentDir (pfad_vorher);
  }

  Edit4->Text = Hauptformular->TagAttributeGetString("alt=", Hauptformular->tag_current);

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);
  Edit2->Text = Hauptformular->TagAttributeGetString("onabort=", Hauptformular->tag_current);
  Edit3->Text = Hauptformular->TagAttributeGetString("onerror=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("img", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("src=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("alt=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("height=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("width=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("border=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("align=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onabort=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onerror=", Hauptformular->tag_current);
 }
 else
 {
  ComboBox1->ItemIndex = 0;
  ComboBox2->ItemIndex = 0;
  ComboBox3->ItemIndex = 0;
 }
}
//---------------------------------------------------------------------------

