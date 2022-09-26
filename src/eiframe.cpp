//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "eiframe.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEinzelnerFrame *EinzelnerFrame;
//---------------------------------------------------------------------------
__fastcall TEinzelnerFrame::TEinzelnerFrame(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEinzelnerFrame::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;        
}
//---------------------------------------------------------------------------

void __fastcall TEinzelnerFrame::FormShow(TObject *Sender)
{
 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  Source1->Text = Hauptformular->TagAttributeGetString("src=", Hauptformular->tag_current);
  Name1->Text = Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current);

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("scrolling=", Hauptformular->tag_current)) == "yes")
   ComboScrollbalken1->ItemIndex = 1;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("scrolling=", Hauptformular->tag_current)) == "no")
   ComboScrollbalken1->ItemIndex = 2;
  else
   ComboScrollbalken1->ItemIndex = 0;

  if ((Hauptformular->TagAttributeContainsStandalone("noresize", Hauptformular->tag_current)) || (AnsiLowerCase(Hauptformular->TagAttributeGetString("noresize=", Hauptformular->tag_current)) == "noresize"))
   CheckUnveraenderbar1->Checked = true;

  if (Hauptformular->TagAttributeContainsAttribute("frameborder=", Hauptformular->tag_current))
  {
   CheckRand1->Checked = true;
   Rand1->Position = Hauptformular->TagAttributeGetNumeric("frameborder=", Hauptformular->tag_current);
  }
  if (Hauptformular->TagAttributeContainsAttribute("marginwidth=", Hauptformular->tag_current))
  {
   CheckAbstandLinks1->Checked = true;
   LinksRechts1->Position = Hauptformular->TagAttributeGetNumeric("marginwidth=", Hauptformular->tag_current);
  }
  if (Hauptformular->TagAttributeContainsAttribute("marginheight=", Hauptformular->tag_current))
  {
   CheckAbstandOben1->Checked = true;
   ObenUnten1->Position = Hauptformular->TagAttributeGetNumeric("marginheight=", Hauptformular->tag_current);
  }

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("frame", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("src=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("name=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("scrolling=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("noresize=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveStandalone("noresize", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("frameborder=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("marginwidth=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("marginheight=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
 }
 else
  ComboScrollbalken1->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TEinzelnerFrame::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);    
}
//---------------------------------------------------------------------------

void __fastcall TEinzelnerFrame::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_frame.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TEinzelnerFrame::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TEinzelnerFrame::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<frame";

 tag = tag + " src=\"" + Source1->Text + "\"";

 if (Trim(Name1->Text) != "")
  tag = tag + " name=\"" + Name1->Text + "\"";
 if (ComboScrollbalken1->ItemIndex == 1)
  tag = tag + " scrolling=\"yes\"";
 else if (ComboScrollbalken1->ItemIndex == 2)
  tag = tag + " scrolling=\"no\"";
 if (CheckUnveraenderbar1->Checked)
 {
  if (Hauptformular->editor_xhtml_mode)
   tag = tag + " noresize=\"noresize\"";
  else
   tag = tag + " noresize";
 }
 if (CheckAbstandLinks1->Checked)
  tag = tag + " marginwidth=\"" + String(LinksRechts1->Position) + "\"";
 if (CheckAbstandOben1->Checked)
  tag = tag + " marginheight=\"" + String(ObenUnten1->Position) + "\"";
 if (CheckRand1->Checked)
  tag = tag + " frameborder=\"" + String(Rand1->Position) + "\"";

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

void __fastcall TEinzelnerFrame::CheckRand1Click(TObject *Sender)
{
 if (CheckRand1->Checked)
 {
  Edit3->Enabled = true;
  Rand1->Enabled = true;
 }
 else
 {
  Edit3->Enabled = false;
  Rand1->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEinzelnerFrame::CheckAbstandLinks1Click(TObject *Sender)
{
 if (CheckAbstandLinks1->Checked)
 {
  Edit1->Enabled = true;
  LinksRechts1->Enabled = true;
 }
 else
 {
  Edit1->Enabled = false;
  LinksRechts1->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEinzelnerFrame::CheckAbstandOben1Click(TObject *Sender)
{
 if (CheckAbstandOben1->Checked)
 {
  Edit2->Enabled = true;
  ObenUnten1->Enabled = true;
 }
 else
 {
  Edit2->Enabled = false;
  ObenUnten1->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEinzelnerFrame::SpeedButton7Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(5);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;
 OeffnenDialog->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 OeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OeffnenDialog->Execute())
  Source1->Text = Hauptformular->DirectorySameAndRelative(OeffnenDialog->FileName);
}
//---------------------------------------------------------------------------

