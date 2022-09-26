//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "frameass.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrameAssistent *FrameAssistent;
//---------------------------------------------------------------------------
__fastcall TFrameAssistent::TFrameAssistent(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrameAssistent::SpeedButton3Click(TObject *Sender)
{
 TabSheet3->TabVisible = true;
 TabSheet4->TabVisible = true;
 TabSheet5->TabVisible = false;

 Mass1->Position = 30;
 Mass2->Position = 70;
 ComboMass1->ItemIndex = 0;
 ComboMass2->ItemIndex = 0;
 LabelMass1->Caption = Width->Caption;
 LabelMass2->Caption = Width->Caption;

 Image1->Picture = UrImage1->Picture;
 Image2->Picture = UrImage1->Picture;
 Image3->Picture = UrImage1->Picture;
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::SpeedButton4Click(TObject *Sender)
{
 TabSheet3->TabVisible = true;
 TabSheet4->TabVisible = true;
 TabSheet5->TabVisible = false;

 Mass1->Position = 30;
 Mass2->Position = 70;
 ComboMass1->ItemIndex = 0;
 ComboMass2->ItemIndex = 0;
 LabelMass1->Caption = Height->Caption;
 LabelMass2->Caption = Height->Caption;

 Image1->Picture = UrImage2->Picture;
 Image2->Picture = UrImage2->Picture;
 Image3->Picture = UrImage2->Picture;

 PageControl1->ActivePage = TabSheet3;
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::SpeedButton5Click(TObject *Sender)
{
 TabSheet3->TabVisible = true;
 TabSheet4->TabVisible = true;
 TabSheet5->TabVisible = true;

 Mass1->Position = 30;
 Mass2->Position = 30;
 Mass3->Position = 70;
 ComboMass1->ItemIndex = 0;
 ComboMass2->ItemIndex = 0;
 ComboMass3->ItemIndex = 0;
 LabelMass1->Caption = Height->Caption;
 LabelMass2->Caption = Width->Caption;
 LabelMass3->Caption = Width->Caption;

 Image1->Picture = UrImage3->Picture;
 Image2->Picture = UrImage3->Picture;
 Image3->Picture = UrImage3->Picture;

 PageControl1->ActivePage = TabSheet3;
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::SpeedButton6Click(TObject *Sender)
{
 TabSheet3->TabVisible = true;
 TabSheet4->TabVisible = true;
 TabSheet5->TabVisible = true;

 Mass1->Position = 30;
 Mass2->Position = 30;
 Mass3->Position = 70;
 ComboMass1->ItemIndex = 0;
 ComboMass2->ItemIndex = 0;
 ComboMass3->ItemIndex = 0;
 LabelMass1->Caption = Width->Caption;
 LabelMass2->Caption = Height->Caption;
 LabelMass3->Caption = Height->Caption;

 Image1->Picture = UrImage4->Picture;
 Image2->Picture = UrImage4->Picture;
 Image3->Picture = UrImage4->Picture;

 PageControl1->ActivePage = TabSheet3;
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::SpeedButton7Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(5);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog1->Filter = filter_gesamt;
 OeffnenDialog1->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 OeffnenDialog1->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OeffnenDialog1->Execute())
  Source1->Text = Hauptformular->DirectorySameAndRelative(OeffnenDialog1->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::ComboMass1Change(TObject *Sender)
{
 if (ComboMass1->ItemIndex == 2)
 {
  Edit5->Enabled = false;
  Mass1->Enabled = false;
 }
 else
 {
  Edit5->Enabled = true;
  Mass1->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_frame_wiz.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::BitBtn2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;        
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::BitBtn1Click(TObject *Sender)
{
 String tag, percent, temp_str;
 tag = "<frameset";

 if (SpeedButton3->Down)
 {
  //Frame_1
  if (ComboMass1->ItemIndex == 0)
   temp_str = String(Mass1->Position) + "%";
  else if (ComboMass1->ItemIndex == 2)
   temp_str = "*";
  else
   temp_str = Mass1->Position;
  tag = tag + " cols=\"" + temp_str + ",";
  if (ComboMass2->ItemIndex == 0)
   temp_str = String(Mass2->Position) + "%";
  else if (ComboMass2->ItemIndex == 2)
   temp_str = "*";
  else
   temp_str = Mass2->Position;
  tag = tag + temp_str + "\"";

  if (Trim(CssStyle->Text) != "")
   tag = tag + " style=\"" + CssStyle->Text + "\"";
  if (Trim(CssID->Text) != "")
   tag = tag + " id=\"" + CssID->Text + "\"";
  if (Trim(CssClass->Text) != "")
   tag = tag + " class=\"" + CssClass->Text + "\"";
  if (Trim(CssTitle->Text) != "")
   tag = tag + " title=\"" + CssTitle->Text + "\"";
  tag = tag + ">";

  tag = tag + "\r\n" + " <frame src=\"" + Source1->Text + "\"";
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
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";

  tag = tag + "\r\n" + " <frame src=\"" + Source2->Text + "\"";
  if (Trim(Name2->Text) != "")
   tag = tag + " name=\"" + Name2->Text + "\"";
  if (ComboScrollbalken2->ItemIndex == 1)
   tag = tag + " scrolling=\"yes\"";
  else if (ComboScrollbalken2->ItemIndex == 2)
   tag = tag + " scrolling=\"no\"";
  if (CheckUnveraenderbar2->Checked)
  {
   if (Hauptformular->editor_xhtml_mode)
    tag = tag + " noresize=\"noresize\"";
   else
    tag = tag + " noresize";
  }
  if (CheckAbstandLinks2->Checked)
   tag = tag + " marginwidth=\"" + String(LinksRechts2->Position) + "\"";
  if (CheckAbstandOben2->Checked)
   tag = tag + " marginheight=\"" + String(ObenUnten2->Position) + "\"";
  if (CheckRand2->Checked)
   tag = tag + " frameborder=\"" + String(Rand2->Position) + "\"";
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";
 }
 else  if (SpeedButton4->Down)
 {
  //Frame_2
  if (ComboMass1->ItemIndex == 0)
   temp_str = String(Mass1->Position) + "%";
  else if (ComboMass1->ItemIndex == 2)
   temp_str = "*";
  else
   temp_str = Mass1->Position;
  tag = tag + " rows=\"" + temp_str + ",";
  if (ComboMass2->ItemIndex == 0)
   temp_str = String(Mass2->Position) + "%";
  else if (ComboMass2->ItemIndex == 2)
   temp_str = "*";
  else
   temp_str = Mass2->Position;
  tag = tag + temp_str + "\"";

  if (Trim(CssStyle->Text) != "")
   tag = tag + " style=\"" + CssStyle->Text + "\"";
  if (Trim(CssID->Text) != "")
   tag = tag + " id=\"" + CssID->Text + "\"";
  if (Trim(CssClass->Text) != "")
   tag = tag + " class=\"" + CssClass->Text + "\"";
  if (Trim(CssTitle->Text) != "")
   tag = tag + " title=\"" + CssTitle->Text + "\"";
  tag = tag + ">";

  tag = tag + "\r\n" + " <frame src=\"" + Source1->Text + "\"";
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
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";

  tag = tag + "\r\n" + " <frame src=\"" + Source2->Text + "\"";
  if (Trim(Name2->Text) != "")
   tag = tag + " name=\"" + Name2->Text + "\"";
  if (ComboScrollbalken2->ItemIndex == 1)
   tag = tag + " scrolling=\"yes\"";
  else if (ComboScrollbalken2->ItemIndex == 2)
   tag = tag + " scrolling=\"no\"";
  if (CheckUnveraenderbar2->Checked)
  {
   if (Hauptformular->editor_xhtml_mode)
    tag = tag + " noresize=\"noresize\"";
   else
    tag = tag + " noresize";
  }
  if (CheckAbstandLinks2->Checked)
   tag = tag + " marginwidth=\"" + String(LinksRechts2->Position) + "\"";
  if (CheckAbstandOben2->Checked)
   tag = tag + " marginheight=\"" + String(ObenUnten2->Position) + "\"";
  if (CheckRand2->Checked)
   tag = tag + " frameborder=\"" + String(Rand2->Position) + "\"";
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";
 }
 else if (SpeedButton5->Down)
 {
  //Frame_3
  if (ComboMass1->ItemIndex == 0)
   temp_str = String(Mass1->Position) + "%";
  else if (ComboMass1->ItemIndex == 2)
   temp_str = "*";
  else
   temp_str = Mass1->Position;
  tag = tag + " rows=\"" + temp_str + ",*\"";

  if (Trim(CssStyle->Text) != "")
   tag = tag + " style=\"" + CssStyle->Text + "\"";
  if (Trim(CssID->Text) != "")
   tag = tag + " id=\"" + CssID->Text + "\"";
  if (Trim(CssClass->Text) != "")
   tag = tag + " class=\"" + CssClass->Text + "\"";
  if (Trim(CssTitle->Text) != "")
   tag = tag + " title=\"" + CssTitle->Text + "\"";
  tag = tag + ">";

  tag = tag + "\r\n" + " <frame src=\"" + Source1->Text + "\"";
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
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";

  tag = tag + "\r\n  <frameset";

  if (ComboMass2->ItemIndex == 0)
   temp_str = String(Mass2->Position) + "%";
  else if (ComboMass2->ItemIndex == 2)
   temp_str = "*";
  else
   temp_str = Mass2->Position;
  tag = tag + " cols=\"" + temp_str + ",";
  if (ComboMass3->ItemIndex == 0)
   temp_str = String(Mass3->Position) + "%";
  else if (ComboMass3->ItemIndex == 2)
   temp_str = "*";
  else
   temp_str = Mass3->Position;
  tag = tag + temp_str + "\"";

  if (Trim(CssStyle->Text) != "")
   tag = tag + " style=\"" + CssStyle->Text + "\"";
  if (Trim(CssID->Text) != "")
   tag = tag + " id=\"" + CssID->Text + "\"";
  if (Trim(CssClass->Text) != "")
   tag = tag + " class=\"" + CssClass->Text + "\"";
  if (Trim(CssTitle->Text) != "")
   tag = tag + " title=\"" + CssTitle->Text + "\"";
  tag = tag + ">";

  tag = tag + "\r\n" + "   <frame src=\"" + Source2->Text + "\"";
  if (Trim(Name2->Text) != "")
   tag = tag + " name=\"" + Name2->Text + "\"";
  if (ComboScrollbalken2->ItemIndex == 1)
   tag = tag + " scrolling=\"yes\"";
  else if (ComboScrollbalken2->ItemIndex == 2)
   tag = tag + " scrolling=\"no\"";
  if (CheckUnveraenderbar2->Checked)
  {
   if (Hauptformular->editor_xhtml_mode)
    tag = tag + " noresize=\"noresize\"";
   else
    tag = tag + " noresize";
  }
  if (CheckAbstandLinks2->Checked)
   tag = tag + " marginwidth=\"" + String(LinksRechts2->Position) + "\"";
  if (CheckAbstandOben2->Checked)
   tag = tag + " marginheight=\"" + String(ObenUnten2->Position) + "\"";
  if (CheckRand2->Checked)
   tag = tag + " frameborder=\"" + String(Rand2->Position) + "\"";
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";

  tag = tag + "\r\n" + "   <frame src=\"" + Source3->Text + "\"";
  if (Trim(Name3->Text) != "")
   tag = tag + " name=\"" + Name3->Text + "\"";
  if (ComboScrollbalken3->ItemIndex == 1)
   tag = tag + " scrolling=\"yes\"";
  else if (ComboScrollbalken3->ItemIndex == 2)
   tag = tag + " scrolling=\"no\"";
  if (CheckUnveraenderbar3->Checked)
  {
   if (Hauptformular->editor_xhtml_mode)
    tag = tag + " noresize=\"noresize\"";
   else
    tag = tag + " noresize";
  }
  if (CheckAbstandLinks3->Checked)
   tag = tag + " marginwidth=\"" + String(LinksRechts3->Position) + "\"";
  if (CheckAbstandOben3->Checked)
   tag = tag + " marginheight=\"" + String(ObenUnten3->Position) + "\"";
  if (CheckRand3->Checked)
   tag = tag + " frameborder=\"" + String(Rand3->Position) + "\"";
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";
  tag = tag + "\r\n  </frameset>";
 }
 else if (SpeedButton6->Down)
 {
  //Frame_4
  if (ComboMass1->ItemIndex == 0)
   temp_str = String(Mass1->Position) + "%";
  else if (ComboMass1->ItemIndex == 2)
   temp_str = "*";
  else
   temp_str = Mass1->Position;
  tag = tag + " cols=\"" + temp_str + ",*\"";

  if (Trim(CssStyle->Text) != "")
   tag = tag + " style=\"" + CssStyle->Text + "\"";
  if (Trim(CssID->Text) != "")
   tag = tag + " id=\"" + CssID->Text + "\"";
  if (Trim(CssClass->Text) != "")
   tag = tag + " class=\"" + CssClass->Text + "\"";
  if (Trim(CssTitle->Text) != "")
   tag = tag + " title=\"" + CssTitle->Text + "\"";
  tag = tag + ">";

  tag = tag + "\r\n" + " <frame src=\"" + Source1->Text + "\"";
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
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";

  tag = tag + "\r\n  <frameset";

  if (ComboMass2->ItemIndex == 0)
   temp_str = String(Mass2->Position) + "%";
  else if (ComboMass2->ItemIndex == 2)
   temp_str = "*";
  else
   temp_str = Mass2->Position;
  tag = tag + " rows=\"" + temp_str + ",";
  if (ComboMass3->ItemIndex == 0)
   temp_str = String(Mass3->Position) + "%";
  else if (ComboMass3->ItemIndex == 2)
   temp_str = "*";
  else
   temp_str = Mass3->Position;
  tag = tag + temp_str + "\"";

  if (Trim(CssStyle->Text) != "")
   tag = tag + " style=\"" + CssStyle->Text + "\"";
  if (Trim(CssID->Text) != "")
   tag = tag + " id=\"" + CssID->Text + "\"";
  if (Trim(CssClass->Text) != "")
   tag = tag + " class=\"" + CssClass->Text + "\"";
  if (Trim(CssTitle->Text) != "")
   tag = tag + " title=\"" + CssTitle->Text + "\"";
  tag = tag + ">";

  tag = tag + "\r\n" + "   <frame src=\"" + Source2->Text + "\"";
  if (Trim(Name2->Text) != "")
   tag = tag + " name=\"" + Name2->Text + "\"";
  if (ComboScrollbalken2->ItemIndex == 1)
   tag = tag + " scrolling=\"yes\"";
  else if (ComboScrollbalken2->ItemIndex == 2)
   tag = tag + " scrolling=\"no\"";
  if (CheckUnveraenderbar2->Checked)
  {
   if (Hauptformular->editor_xhtml_mode)
    tag = tag + " noresize=\"noresize\"";
   else
    tag = tag + " noresize";
  }
  if (CheckAbstandLinks2->Checked)
   tag = tag + " marginwidth=\"" + String(LinksRechts2->Position) + "\"";
  if (CheckAbstandOben2->Checked)
   tag = tag + " marginheight=\"" + String(ObenUnten2->Position) + "\"";
  if (CheckRand2->Checked)
   tag = tag + " frameborder=\"" + String(Rand2->Position) + "\"";
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";

  tag = tag + "\r\n" + "   <frame src=\"" + Source3->Text + "\"";
  if (Trim(Name3->Text) != "")
   tag = tag + " name=\"" + Name3->Text + "\"";
  if (ComboScrollbalken3->ItemIndex == 1)
   tag = tag + " scrolling=\"yes\"";
  else if (ComboScrollbalken3->ItemIndex == 2)
   tag = tag + " scrolling=\"no\"";
  if (CheckUnveraenderbar3->Checked)
  {
   if (Hauptformular->editor_xhtml_mode)
    tag = tag + " noresize=\"noresize\"";
   else
    tag = tag + " noresize";
  }
  if (CheckAbstandLinks3->Checked)
   tag = tag + " marginwidth=\"" + String(LinksRechts3->Position) + "\"";
  if (CheckAbstandOben3->Checked)
   tag = tag + " marginheight=\"" + String(ObenUnten3->Position) + "\"";
  if (CheckRand3->Checked)
   tag = tag + " frameborder=\"" + String(Rand3->Position) + "\"";
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";
  tag = tag + "\r\n  </frameset>";
 }
 tag = tag + "\r\n</frameset>";
 Hauptformular->TagInsertAndFindPosition(tag + "\r\n", "", "<body", "");
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::CheckAbstandLinks1Click(TObject *Sender)
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

void __fastcall TFrameAssistent::CheckAbstandOben1Click(TObject *Sender)
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

void __fastcall TFrameAssistent::CheckRand1Click(TObject *Sender)
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

void __fastcall TFrameAssistent::SpeedButton2Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(5);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog2->Filter = filter_gesamt;
 OeffnenDialog2->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 OeffnenDialog2->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OeffnenDialog2->Execute())
  Source2->Text = Hauptformular->DirectorySameAndRelative(OeffnenDialog2->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::SpeedButton8Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(5);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog3->Filter = filter_gesamt;
 OeffnenDialog3->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 OeffnenDialog3->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OeffnenDialog3->Execute())
  Source3->Text = Hauptformular->DirectorySameAndRelative(OeffnenDialog3->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::ComboMass2Change(TObject *Sender)
{
 if (ComboMass2->ItemIndex == 2)
 {
  Edit7->Enabled = false;
  Mass2->Enabled = false;
 }
 else
 {
  Edit7->Enabled = true;
  Mass2->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::ComboMass3Change(TObject *Sender)
{
 if (ComboMass3->ItemIndex == 2)
 {
  Edit13->Enabled = false;
  Mass3->Enabled = false;
 }
 else
 {
  Edit13->Enabled = true;
  Mass3->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::CheckAbstandLinks2Click(TObject *Sender)
{
 if (CheckAbstandLinks2->Checked)
 {
  Edit8->Enabled = true;
  LinksRechts2->Enabled = true;
 }
 else
 {
  Edit8->Enabled = false;
  LinksRechts2->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::CheckAbstandLinks3Click(TObject *Sender)
{
 if (CheckAbstandLinks3->Checked)
 {
  Edit14->Enabled = true;
  LinksRechts3->Enabled = true;
 }
 else
 {
  Edit14->Enabled = false;
  LinksRechts3->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::CheckAbstandOben2Click(TObject *Sender)
{
 if (CheckAbstandOben2->Checked)
 {
  Edit9->Enabled = true;
  ObenUnten2->Enabled = true;
 }
 else
 {
  Edit9->Enabled = false;
  ObenUnten2->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::CheckAbstandOben3Click(TObject *Sender)
{
 if (CheckAbstandOben3->Checked)
 {
  Edit15->Enabled = true;
  ObenUnten3->Enabled = true;
 }
 else
 {
  Edit15->Enabled = false;
  ObenUnten3->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::CheckRand2Click(TObject *Sender)
{
 if (CheckRand2->Checked)
 {
  Edit10->Enabled = true;
  Rand2->Enabled = true;
 }
 else
 {
  Edit10->Enabled = false;
  Rand2->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::CheckRand3Click(TObject *Sender)
{
 if (CheckRand3->Checked)
 {
  Edit16->Enabled = true;
  Rand3->Enabled = true;
 }
 else
 {
  Edit16->Enabled = false;
  Rand3->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::FormShow(TObject *Sender)
{
 SpeedButton3Click(Sender);
 ComboScrollbalken1->ItemIndex = 0;
 ComboScrollbalken2->ItemIndex = 0;
 ComboScrollbalken3->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFrameAssistent::PageControl1Change(TObject *Sender)
{
 TabSheet2->ImageIndex = 61;        
}
//---------------------------------------------------------------------------

