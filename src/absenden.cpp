//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "absenden.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAbsendenZuruecksetzen *AbsendenZuruecksetzen;
//---------------------------------------------------------------------------
__fastcall TAbsendenZuruecksetzen::TAbsendenZuruecksetzen(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAbsendenZuruecksetzen::ComboBox1Change(TObject *Sender)
{
 if (ComboBox1->ItemIndex == 1)
 {
  CheckBox1->Checked = false;
  Edit3->Enabled = true;
  Edit3->Color = clWindow;
  CheckBox1->Enabled = false;
 }
 else
 {
  CheckBox1->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TAbsendenZuruecksetzen::CheckBox1Click(TObject *Sender)
{
 if (CheckBox1->Checked)
 {
  Edit4->Enabled = true;
  Edit4->Color = clWindow;
  SpeedButton2->Enabled = true;
  SpeedButton3->Enabled = true;
  Edit3->Enabled = false;
  Edit3->Color = clBtnFace;
  Label1->Font->Style = Label1->Font->Style >> fsBold;
  Label9->Font->Style = Label9->Font->Style << fsBold;
 }
 else
 {
  Edit4->Enabled = false;
  Edit4->Color = clBtnFace;
  SpeedButton2->Enabled = false;
  SpeedButton3->Enabled = false;
  Edit3->Enabled = true;
  Edit3->Color = clWindow;
  Label1->Font->Style = Label1->Font->Style << fsBold;
  Label9->Font->Style = Label9->Font->Style >> fsBold;
 }
}
//---------------------------------------------------------------------------

void __fastcall TAbsendenZuruecksetzen::SpeedButton2Click(TObject *Sender)
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
  Edit4->Text = Hauptformular->DirectorySameAndRelative(OeffnenDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TAbsendenZuruecksetzen::SpeedButton3Click(TObject *Sender)
{
 Edit4->Text = Hauptformular->ImageCatalogShow();         
}
//---------------------------------------------------------------------------

void __fastcall TAbsendenZuruecksetzen::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);       
}
//---------------------------------------------------------------------------

void __fastcall TAbsendenZuruecksetzen::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TAbsendenZuruecksetzen::FormShow(TObject *Sender)
{
 EventsTabSheet->TabVisible = Hauptformular->editor_events_tab;

 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current)) == "submit")
   ComboBox1->ItemIndex = 0;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current)) == "reset")
  {
   ComboBox1->ItemIndex = 1;
   CheckBox1->Enabled = false;
  }
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current)) == "image")
  {
   ComboBox1->ItemIndex = 0;
   CheckBox1->Checked = true;
   CheckBox1Click(Sender);
  }
  else
   ComboBox1->ItemIndex = 0;

  Edit3->Text = Hauptformular->TagAttributeGetString("value=", Hauptformular->tag_current);
  Edit4->Text = Hauptformular->TagAttributeGetString("src=", Hauptformular->tag_current);

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);
  Edit2->Text = Hauptformular->TagAttributeGetString("onclick=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("input", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("type=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("src=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("value=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onclick=", Hauptformular->tag_current);
 }
 else
  ComboBox1->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TAbsendenZuruecksetzen::BitBtn1Click(TObject *Sender)
{
 String tag;

 if ((ComboBox1->ItemIndex == 0) && (!CheckBox1->Checked))
  tag = "<input type=\"submit\"";
 else if (ComboBox1->ItemIndex == 1)
  tag = "<input type=\"reset\"";
 else
  tag = "<input type=\"image\"";

 if ((Trim(Edit3->Text) != "") && (!CheckBox1->Checked))
  tag = tag + " value=\"" + Edit3->Text + "\"";

 if ((CheckBox1->Checked) && (Trim(Edit4->Text) != ""))
  tag = tag + " src=\"" + Edit4->Text + "\"";

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
 Hauptformular->TagInsert(tag, "");
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TAbsendenZuruecksetzen::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TAbsendenZuruecksetzen::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_input_submit.html", true);     
}
//---------------------------------------------------------------------------

