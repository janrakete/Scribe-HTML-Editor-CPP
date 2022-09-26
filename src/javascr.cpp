//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "javascr.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TJavaScriptVorlagen *JavaScriptVorlagen;
//---------------------------------------------------------------------------
__fastcall TJavaScriptVorlagen::TJavaScriptVorlagen(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TJavaScriptVorlagen::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_javascript.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;        
}
//---------------------------------------------------------------------------


void __fastcall TJavaScriptVorlagen::SpeedButton2Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(6);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->graphicfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 HighlightOeffnenDialog->Filter = filter_gesamt;
 HighlightOeffnenDialog->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 HighlightOeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (HighlightOeffnenDialog->Execute())
  Edit1->Text = Hauptformular->DirectorySameAndRelative(HighlightOeffnenDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::SpeedButton4Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(6);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->graphicfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 HighlightOeffnenDialog->Filter = filter_gesamt;
 HighlightOeffnenDialog->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 HighlightOeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (HighlightOeffnenDialog->Execute())
  Edit2->Text = Hauptformular->DirectorySameAndRelative(HighlightOeffnenDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::SpeedButton3Click(TObject *Sender)
{
 Edit1->Text = Hauptformular->ImageCatalogShow();        
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::SpeedButton1Click(TObject *Sender)
{
 Edit2->Text = Hauptformular->ImageCatalogShow();        
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::SpeedButton5Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(5);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(6);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->graphicfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 HighlightOeffnenDialog2->Filter = filter_gesamt;
 HighlightOeffnenDialog2->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 HighlightOeffnenDialog2->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (HighlightOeffnenDialog2->Execute())
  Edit3->Text = Hauptformular->DirectorySameAndRelative(HighlightOeffnenDialog2->FileName);
}
//---------------------------------------------------------------------------


void __fastcall TJavaScriptVorlagen::Lschen1Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::PopupMenu2Popup(TObject *Sender)
{
 if (ListView1->Selected)
  Entfernen1->Enabled = true;
 else
  Entfernen1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::Entfernen1Click(TObject *Sender)
{
 ListView1->Selected->Delete();
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::BitBtn4Click(TObject *Sender)
{
 TListItem *ListItem;
 ListItem = ListView1->Items->Add();
 ListItem->Caption = Edit1->Text;
 ListItem->SubItems->Add(Edit2->Text);
 ListItem->SubItems->Add(Edit3->Text);
 ListItem->ImageIndex = 56;
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::SpeedButton6Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(5);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(6);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->graphicfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 HighlightOeffnenDialog2->Filter = filter_gesamt;
 HighlightOeffnenDialog2->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 HighlightOeffnenDialog2->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (HighlightOeffnenDialog2->Execute())
  Edit6->Text = Hauptformular->DirectorySameAndRelative(HighlightOeffnenDialog2->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::BitBtn5Click(TObject *Sender)
{
 TListItem *ListItem;
 ListItem = ListView2->Items->Add();
 ListItem->Caption = Edit7->Text;
 ListItem->SubItems->Add(Edit6->Text);
 ListItem->ImageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::MenuItem1Click(TObject *Sender)
{
 ListView2->Selected->Delete();
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::PopupMenu1Popup(TObject *Sender)
{
 if (ListView2->Selected)
  MenuItem1->Enabled = true;
 else
  MenuItem1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TJavaScriptVorlagen::BitBtn1Click(TObject *Sender)
{
 String temp_str_1, temp_str_2;
 int zeile = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine;
 int temp_pos = 0;

 if (PageControl1->ActivePage == TabSheet1)
 {
  if (Hauptformular->editor_xhtml_mode)
  {
   for (int i = 0; i < ListView1->Items->Count; i++)
    temp_str_2 = temp_str_2 + "<a href=\"" + ListView1->Items->Item[i]->SubItems->Strings[1] + "\" onMouseover=\"image_" + String(i) + ".src='" + ListView1->Items->Item[i]->SubItems->Strings[0] + "';\" onMouseout=\"image_" + String(i) + ".src='" + ListView1->Items->Item[i]->Caption + "';\"><img name=\"image_" + String(i) + "\" src=\"" + ListView1->Items->Item[i]->Caption + "\" border=\"0\" />" + "</a><br />\r\n";
  }
  else
  {
   for (int i = 0; i < ListView1->Items->Count; i++)
    temp_str_2 = temp_str_2 + "<a href=\"" + ListView1->Items->Item[i]->SubItems->Strings[1] + "\" onMouseover=\"image_" + String(i) + ".src='" + ListView1->Items->Item[i]->SubItems->Strings[0] + "';\" onMouseout=\"image_" + String(i) + ".src='" + ListView1->Items->Item[i]->Caption + "';\"><img name=\"image_" + String(i) + "\" src=\"" + ListView1->Items->Item[i]->Caption + "\" border=\"0\">" + "</a><br>\r\n";
  }

  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(zeile, temp_str_2);
 }
 else if (PageControl1->ActivePage == TabSheet2)
 {
  temp_str_2 = "<form name=\"select_box\">\r\n<select name=\"select_entries\" size=\"1\" onChange=\"select_target();\">\r\n";
  temp_str_2 = temp_str_2 + " <option value=\"\">" + Edit4->Text + "</option>\r\n";
  temp_str_2 = temp_str_2 + " <option value=\"\">" + "--------------" + "</option>\r\n";
  for (int i = 0; i < ListView2->Items->Count; i++)
   temp_str_2 = temp_str_2 + " <option value=\"" + ListView2->Items->Item[i]->SubItems->Strings[0] + "\">" + ListView2->Items->Item[i]->Caption + "</option>\r\n";

  temp_str_2 = temp_str_2 + "</select>\r\n</form>";
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(zeile, temp_str_2);

  temp_str_1 = " <script type=\"text/javascript\">\r\n <!--\r\n ";
  if (Trim(ComboBox1->Text) == "")
   temp_str_1 = temp_str_1 + " function select_target()\r\n  {\r\n   s_index = document.select_box.select_entries.selectedIndex;\r\n   s_text = document.select_box.select_entries.options[s_index].value;\r\n   if (s_text != \"\")\r\n    document.location.href = s_text;\r\n  }\r\n //-->\r\n";
  else
   temp_str_1 = temp_str_1 + " function select_target()\r\n  {\r\n   s_index = document.select_box.select_entries.selectedIndex;\r\n   s_text = document.select_box.select_entries.options[s_index].value;\r\n   if (s_text != \"\")\r\n    parent." + ComboBox1->Text + ".location.href = s_text;\r\n  }\r\n //-->\r\n";
  temp_str_1 = temp_str_1 + " </script>";

  if (Hauptformular->tag_automatic_position)
  {
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
   if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt("</HEAD>", true, false, false, false))
   {
    temp_pos = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(temp_pos, temp_str_1);
   }
   else
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(zeile, temp_str_1);
  }
  else
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(zeile, temp_str_1);
 }
 else if (PageControl1->ActivePage == TabSheet3)
 {
  if (Hauptformular->editor_xhtml_mode)
   temp_str_2 = "<form name=\"ticker_box\">\r\n <input type=\"text\" name=\"ticker_textbox\" size=\"50\" />\r\n";
  else
   temp_str_2 = "<form name=\"ticker_box\">\r\n <input type=\"text\" name=\"ticker_textbox\" size=\"50\">\r\n";
  temp_str_2 = temp_str_2 + "</form>";

  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(zeile, temp_str_2);
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt("<BODY", true, false, false, false))
   Hauptformular->TagAppendAttribute(" onLoad=\"ticker_scroll();\"");
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;

  temp_str_1 = " <script type=\"text/javascript\">\r\n <!--\r\n ";
  temp_str_1 = temp_str_1  + " var TickerID = Object;\r\n  var Ticker_Text = new Object();\r\n  var Ticker_Speed = " + String(UpDown1->Position) + ";\r\n  var Ticker_Pause = " + String(UpDown2->Position) + ";\r\n  var Ticker_Position = 0; Ticker_Count = 1; Ticker_TextMax = 3;\r\n  \r\n  Ticker_Text[1] = \"" + Edit5->Text + "\";\r\n  Ticker_Text[2] = \"" + Edit8->Text + "\";\r\n  Ticker_Text[3] = \"" + Edit9->Text + "\";\r\n  \r\n  function ticker_scroll()\r\n  {\r\n   document.ticker_box.ticker_textbox.value = Ticker_Text[Ticker_Count].substring(0, Ticker_Position);\r\n   if (Ticker_Position ++== Ticker_Text[Ticker_Count].length)\r\n   {\r\n    Ticker_Position = 0;\r\n    TickerID = setTimeout(\"ticker_scroll()\", Ticker_Pause);\r\n    Ticker_Count++;\r\n    if (Ticker_Count == Ticker_TextMax + 1)\r\n     Ticker_Count = 1;\r\n   }\r\n   else\r\n    TickerID = setTimeout(\"ticker_scroll()\", Ticker_Speed);\r\n  }\r\n //-->\r\n";
  temp_str_1 = temp_str_1 + " </script>";

  if (Hauptformular->tag_automatic_position)
  {
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
   if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt("</HEAD>", true, false, false, false))
   {
    temp_pos = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(temp_pos, temp_str_1);
   }
   else
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(zeile, temp_str_1);
  }
  else
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(zeile, temp_str_1);
 }
 else if (PageControl1->ActivePage == TabSheet4)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;

  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt("<BODY", true, false, false, false))
   Hauptformular->TagAppendAttribute(" onLoad=\"scrolltext();\"");
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;

  temp_str_1 = " <script type=\"text/javascript\">\r\n <!--\r\n ";
  temp_str_1 = temp_str_1 + " var BannerID = Object;\r\n  var Text = new Object();\r\n  var Speed = " + UpDown4->Position + ";\r\n  var Position = 0;\r\n  var Length = 120;\r\n  \r\n  Text[1] = \"" + Edit12->Text + "\";\r\n  Text[2] = \"" + Edit13->Text + "\";\r\n  Text[3] = \"" + Edit14->Text + "\";\r\n  \r\n  var Msg = Message(3);\r\n  \r\n  function Message(Count)\r\n  {\r\n   Msg = Spacer(Length, \" \");\r\n   for (var i = 1; i <= Count; i++)\r\n    Msg += Text[i] + \"" +  AnsiString::StringOfChar(' ', UpDown3->Position) + "\";\r\n   Msg += Spacer(Length, \" \");\r\n   return Msg;\r\n  }\r\n  \r\n  function Spacer(Len, Asc)\r\n  {\r\n   var Space = \"\";\r\n   if (Asc > \" \")\r\n   {\r\n    for (i = 1; i <= Len/2; i++)\r\n     Space += \" \";\r\n    for (i = Len/2; i <= Len/2 + 3; i++)\r\n     Space += Asc + \" \";\r\n    for (i = Len/2; i <= Len; i++)\r\n     Space += \" \";\r\n   }\r\n   else\r\n   {\r\n    for (i = 1; i <= Len; i++)\r\n     Space += \" \";\r\n   }\r\n   return Space;\r\n  }\r\n";
  temp_str_1 = temp_str_1 + "    \r\n  function scrolltext()\r\n  {\r\n   window.status = Msg.substring(Position, Position + Length);\r\n   if (Position ++== Msg.length - Length)\r\n    Position = 0;\r\n   BannerID = setTimeout(\"scrolltext()\", Speed);\r\n  }\r\n //-->\r\n";
  temp_str_1 = temp_str_1 + " </script>";

  if (Hauptformular->tag_automatic_position)
  {
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
   if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt("</HEAD>", true, false, false, false))
   {
    temp_pos = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(temp_pos, temp_str_1);
   }
   else
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(zeile, temp_str_1);
  }
  else
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(zeile, temp_str_1);
 }

 if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt("<BODY", true, false, false, false))
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
 }
 Close();
}
//---------------------------------------------------------------------------

