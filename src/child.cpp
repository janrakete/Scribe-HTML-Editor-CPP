//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "child.h"
#include "main.h"
#include "hyper.h"
#include "ankerdia.h"
#include "email.h"
#include "image.h"
#include "trennli.h"
#include "multim.h"
#include "meta.h"
#include "schriftd.h"
#include "schnellf.h"
#include "para.h"
#include "abschni.h"
#include "listedia.h"
#include "seitprop.h"
#include "tablewiz.h"
#include "table.h"
#include "zeiledia.h"
#include "caption.h"
#include "kopfzell.h"
#include "zelledia.h"
#include "buttonta.h"
#include "auswahle.h"
#include "checkb.h"
#include "radio.h"
#include "verstfe.h"
#include "eingabe.h"
#include "password.h"
#include "textfel.h"
#include "absenden.h"
#include "auswahl.h"
#include "formula.h"
#include "frameber.h"
#include "eiframe.h"
#include "iframe.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Plusmemo"
#pragma link "PlusGutter"
#pragma resource "*.dfm"
TKindFormular *KindFormular;
//---------------------------------------------------------------------------
__fastcall TKindFormular::TKindFormular(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TKindFormular::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 int title_index = Hauptformular->MDIKinderTitel->Items->IndexOf(Caption);
 Hauptformular->MDIKinderTitel->Items->Delete(title_index);
 Hauptformular->FensterLeiste->Tabs->Delete(title_index);

 if (Hauptformular->FensterLeiste->Tabs->Count)
 {
  if (title_index != 0)
   title_index = title_index - 1;
  else
   title_index = title_index;
  Hauptformular->FensterLeiste->TabIndex =  title_index;

  String mdi_title = Hauptformular->MDIKinderTitel->Items->Strings[Hauptformular->FensterLeiste->TabIndex];
  int mdis_count = Hauptformular->MDIChildCount;
  for (int i = 0; i < mdis_count; i++)
  {
   if (Hauptformular->MDIChildren[i]->Caption == mdi_title)
   {
    Hauptformular->MDIChildren[i]->Show();
    break;
   }
  }
 }
 Hauptformular->ButtonsDisable();
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TKindFormular::SpeedButton1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TKindFormular::TextfeldMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 ::SetFocus(Textfeld->Handle);        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::FormShow(TObject *Sender)
{
 Hauptformular->ButtonsEnable();
 Textfeld->TabStops = Hauptformular->textarea_tabstops;
 Textfeld->WordWrap = Hauptformular->textarea_wordwrap;
 Zeilennummern->Visible = Hauptformular->textarea_linenumbers;
 Zeilennummern->PlusMemo = Textfeld;
 Textfeld->Color = Hauptformular->editor_background_color;
 Textfeld->Font->Name = Hauptformular->editor_font_face;
 Textfeld->Font->Size = Hauptformular->editor_font_size;
 Textfeld->Separators = Hauptformular->editor_word_delimiters;
 Textfeld->ReApplyKeywords();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::FormActivate(TObject *Sender)
{
 int title_index = Hauptformular->MDIKinderTitel->Items->IndexOf(Caption);
 Hauptformular->FensterLeiste->TabIndex = title_index;
 Title->Caption = Hauptformular->SearchXHTMLTitle(Textfeld->Lines);
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Seiteschlieen1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::TextfeldChange(TObject *Sender)
{
 if (Textfeld->SelLength != 0)
 {
  Hauptformular->ToolButton12->Enabled = true;
  Hauptformular->ToolButton13->Enabled = true;
 }
 else
 {
  Hauptformular->ToolButton12->Enabled = false;
  Hauptformular->ToolButton13->Enabled = false;
 }

 Hauptformular->ToolButton15->Enabled = Textfeld->CanUndo;
 Hauptformular->ToolButton16->Enabled = Textfeld->CanRedo;

 String zeile, spalte;
 zeile = Textfeld->SelPar + 1;
 spalte = Textfeld->SelCol + 1;
 zeile = zeile + ":" + spalte;
 Hauptformular->StatusLeiste->Panels->Items[1]->Text = zeile;
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
 if (Textfeld->Modified)
  CanClose = Hauptformular->FileAskSave(Textfeld, Caption);
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::TextfeldKeyPress(TObject *Sender, char &Key)
{
 if (Hauptformular->textarea_convert_special_chars)
 {
  int zeichen_ascii = Key;
  if (zeichen_ascii < 0)
   zeichen_ascii = zeichen_ascii + 256;
  if (zeichen_ascii > 160 || zeichen_ascii == 128)
  {
   if (Hauptformular->use_ascii_code)
    Textfeld->SelText = "&#" + String(zeichen_ascii) + ";";
   else
   {
    if (Hauptformular->SonderzeichenCodes->Items->IndexOf(zeichen_ascii) > -1)
     Textfeld->SelText = Hauptformular->SonderzeichenNames->Items->Strings[Hauptformular->SonderzeichenCodes->Items->IndexOf(zeichen_ascii)];
   }
   Key = NULL;
  }
 }

 if (Hauptformular->tag_auto_complete)
 {
  int key_ascii = Key;
  if (key_ascii < 0)
   key_ascii = key_ascii + 256;
  if (key_ascii == 62)
  {
   Hauptformular->TempMemo->Lines->Clear();
   String tag;
   String line;
   line = Textfeld->Lines->Strings[Textfeld->SelLine];
   line = line.SubString(0, Textfeld->SelCol);
   Hauptformular->TempMemo->Lines->Add(line);
   Hauptformular->TempMemo->SelStart = 0;
   if (Hauptformular->TempMemo->FindTxt("<", true, true, false, false))
   {
    while (Hauptformular->TempMemo->FindTxt("<", true, true, false, false));
    line = line.SubString(Hauptformular->TempMemo->SelCol, (Textfeld->SelCol - Hauptformular->TempMemo->SelCol)+ 1);
    if (!AnsiPos(">", line))
    {
     if (AnsiPos(" ", line))
      tag = line.SubString(2, AnsiPos(" ", line) - 2);
     else
      tag = line.SubString(2, line.Length());
    }
    else
     tag = "";
   }
   else
    tag = "";

   if (Trim(tag) != "")
   {
    if (Hauptformular->AutoComplete->Items->IndexOf(tag) > -1)
    {
     Textfeld->SelText = "</" + tag + ">";
     Textfeld->SelStart = Textfeld->SelStart - ("</" + tag + ">").Length();
    }
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::TextfeldDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
 if (Source == Hauptformular->DateimanagerListe || Source == Hauptformular->ProjekteListe || Source == Hauptformular->DirektFTPListe)
  Accept = true;
 else
  Accept = false;
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::TextfeldDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
 if (Source == Hauptformular->DateimanagerListe || Source == Hauptformular->ProjekteListe || Source == Hauptformular->DirektFTPListe)
 {
  String file;
  String file_complete;

  if (Source == Hauptformular->DateimanagerListe)
  {
   file = Hauptformular->fileexplorer_dir + Hauptformular->DateimanagerListe->ItemFocused->Caption;
   file_complete = file;
   file = Hauptformular->DirectorySameAndRelative(file);
  }
  else if (Source == Hauptformular->ProjekteListe)
  {
   file = Hauptformular->projectexplorer_dir + Hauptformular->ProjekteListe->ItemFocused->Caption;
   file_complete = file;
   file = Hauptformular->DirectorySameAndRelative(file);
  }
  else if (Source == Hauptformular->DirektFTPListe)
  {
   if (Hauptformular->directftp_current_profile == FTPProfil->Caption)
   {
    String file_1;
    String file_2;
    String all;

    file_1 = Caption;
    file_2 = Hauptformular->directftp_current_dir + Hauptformular->DirektFTPListe->ItemFocused->Caption;
    file_1 = file_1.SubString(AnsiPos("\\", file_1), file_1.Length());
    file_2 = file_2.SubString(AnsiPos("\\", file_2), file_2.Length());
    file_1 = "C:" + file_1;
    file_2 = "C:" + file_2;
    file_1 = ExtractFilePath(file_1);
    file_2 = ExtractFilePath(file_2);
    all = ExtractRelativePath(file_1, file_2) + Hauptformular->DirektFTPListe->ItemFocused->Caption;
    file = Hauptformular->ReplaceString(all, "\\", "/", true, true);
   }
   else
   {
    file = Hauptformular->DirectFTPURLDecompatible(Hauptformular->directftp_current_dir + Hauptformular->DirektFTPListe->ItemFocused->Caption);
    file = Hauptformular->ReplaceString(file, "ftp://", "http://", true, true);
   }
  }

  if (Hauptformular->CSSFile(file))
  {
   String tag;
   if (Hauptformular->editor_xhtml_mode)
    tag = " <link rel=\"stylesheet\" type=\"text/css\" href=\"" + file + "\" />";
   else
    tag = " <link rel=\"stylesheet\" type=\"text/css\" href=\"" + file + "\">";
   Hauptformular->TagInsertAndFindPosition(tag, "", "</head>", "");
  }
  else if (Hauptformular->JavaScriptFile(file))
  {
   String tag;
   tag = " <script type=\"text/javascript\" src=\"" + file + "\">\r\n </script>";
   Hauptformular->TagInsertAndFindPosition(tag, "", "</head>", "");
  }
  else if (Hauptformular->GraphicFile(file))
  {
   try
   {
    Hauptformular->TempGrafik->Picture->LoadFromFile(file_complete);
    int height = Hauptformular->TempGrafik->Picture->Height;
    int width = Hauptformular->TempGrafik->Picture->Width;
    String tag;
    if (Hauptformular->editor_xhtml_mode)
     tag = "<img src=\"" + file + "\" alt=\"\" height=\"" + String(height) + "\" width=\"" + String(width) + "\" border=\"0\" />";
    else
     tag = "<img src=\"" + file + "\" alt=\"\" height=\"" + String(height) + "\" width=\"" + String(width) + "\" border=\"0\">";
    Hauptformular->TagInsert(tag, "");
   }
   catch (...)
   {
    String tag;
    if (Hauptformular->editor_xhtml_mode)
     tag = "<img src=\"" + file + "\" alt=\"\" border=\"0\" />";
    else
     tag = "<img src=\"" + file + "\" alt=\"\" border=\"0\">";
    Hauptformular->TagInsert(tag, "");
   }
  }
  else if (Hauptformular->MultimediaFile(file))
  {
   String tag;
   tag = "<object data=\"" + file + "\">";
   Hauptformular->TagInsert(tag, "</object>");
  }
  else
  {
   String tag;
   tag = "<a href=\"" + file + "\">";
   Hauptformular->TagInsert(tag, "</a>");
  }
 }
 ::SetFocus(Textfeld->Handle);
 Textfeld->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::TextfeldKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onAbort1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onAbort=\"\"");
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onBlur1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onBlur=\"\"");
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onChange1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onChange=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onClick1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onClick=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onDblClick1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onDblClick=\"\"");
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onError1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onError=\"\"");
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onFocus1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onFocus=\"\"");
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onKeydown1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onKeydown=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onKeypress1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onKeypress=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onKeyup1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onKeyup=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onLoad1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onLoad=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onMousedown1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onMousedown=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onMousemove1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onMousemove=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onMouseout1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onMouseout=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onMouseover1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onMouseover=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onMouseup1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onMouseup=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onReset1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onReset=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onSelect1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onSelect=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onSubmit1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onSubmit=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::onUnload1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" onUnload=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::TextfeldMenuPopup(TObject *Sender)
{
 Einfgen1->Enabled = Clipboard()->HasFormat(CF_TEXT);

 if (Textfeld->SelLength != 0)
 {
  Ausschneiden1->Enabled = true;
  Kopieren1->Enabled = true;
  Lschen1->Enabled = true;
  Markierung1->Enabled = true;
 }
 else
 {
  Ausschneiden1->Enabled = false;
  Kopieren1->Enabled = false;
  Lschen1->Enabled = false;
  Markierung1->Enabled = false;
 }

 if (Hauptformular->TagInIt())
 {
  Tagentfernen1->Enabled = true;
  StyleSheets1->Enabled = true;
  JavaScriptEreignisse1->Enabled = true;
  Stichwort1->Enabled = true;
 }
 else
 {
  Tagentfernen1->Enabled = false;
  StyleSheets1->Enabled = false;
  JavaScriptEreignisse1->Enabled = false;
  Stichwort1->Enabled = false;
 }

 if (Hauptformular->TagInIt())
 {
  String tag = Hauptformular->TagCurrent();
  String caption;

  if (AnsiPos("<IFRAME", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->EingebettetesFrame1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 127;
  }
  else if (AnsiPos("<FRAMESET", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->FrameBereich1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 129;
  }
  else if (AnsiPos("<FRAME", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Frame1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 130;
  }
  else if (AnsiPos("<FORM", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Formular2->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 114;
  }
  else if (AnsiPos("<SELECT", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Auswahlliste1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 122;
  }
  else if (AnsiPos("<INPUT", AnsiUpperCase(tag)) && AnsiPos("TYPE=SUBMIT", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->AbsendenundZurcksetzenbutton1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 117;
  }
  else if (AnsiPos("<INPUT", AnsiUpperCase(tag)) && AnsiPos("TYPE=RESET", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->AbsendenundZurcksetzenbutton1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 117;
  }
  else if (AnsiPos("<INPUT", AnsiUpperCase(tag)) && AnsiPos("TYPE=IMAGE", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->AbsendenundZurcksetzenbutton1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 117;
  }
  else if (AnsiPos("<TEXTAREA", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Textfeld1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 116;
  }
  else if (AnsiPos("<INPUT", AnsiUpperCase(tag)) && AnsiPos("TYPE=PASSWORD", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Passwortfeld1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 118;
  }
  else if (AnsiPos("<INPUT", AnsiUpperCase(tag)) && AnsiPos("TYPE=TEXT", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Eingabefeld1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 115;
  }
  else if (AnsiPos("<INPUT", AnsiUpperCase(tag)) && AnsiPos("TYPE=HIDDEN", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->VerstecktesFeld1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 119;
  }
  else if (AnsiPos("<INPUT", AnsiUpperCase(tag)) && AnsiPos("TYPE=RADIO", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Radiobutton1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 121;
  }
  else if (AnsiPos("<INPUT", AnsiUpperCase(tag)) && AnsiPos("TYPE=CHECKBOX", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Checkbox1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 120;
  }
  else if (AnsiPos("<OPTION", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Auswahleintrag1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 123;
  }
  else if (AnsiPos("<INPUT", AnsiUpperCase(tag)) && AnsiPos("TYPE=BUTTON", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Button1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 124;
  }
  else if (AnsiPos("<TD", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Zelle1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 99;
  }
  else if (AnsiPos("<TH", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Kopfzelle1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 98;
  }
  else if (AnsiPos("<CAPTION", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->berUnterschrift1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 100;
  }
  else if (AnsiPos("<TR", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Zeile1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 97;
  }
  else if (AnsiPos("<TABLE", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Tabelle2->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 96;
  }
  else if (AnsiPos("<BODY", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Seiteneigenschaften1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 71;
  }
  else if (AnsiPos("<OL", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Liste1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 67;
  }
  else if (AnsiPos("<UL", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Liste1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 67;
  }
  else if (AnsiPos("<DIV", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Abschnitt1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 81;
  }
  else if (AnsiPos("<P", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Paragraph1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 69;
  }
  else if (AnsiPos("<SPAN", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Schnellformatierung1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 80;
  }
  else if (AnsiPos("<FONT", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Schrift1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 79;
  }
  else if (AnsiPos("<META", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Metatag1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 64;
  }
  else if (AnsiPos("<OBJECT", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->MultimediaObjekt1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 62;
  }
  else if (AnsiPos("<HR", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Trennlinie1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 66;
  }
  else if (AnsiPos("<IMG", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Grafik1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 56;
  }
  else if (AnsiPos("<A", AnsiUpperCase(tag)) && AnsiPos("NAME=", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Anker1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 63;
  }
  else if (AnsiPos("<A", AnsiUpperCase(tag)) && AnsiPos("MAILTO:", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->eMailVerweis1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 65;
  }
  else if (AnsiPos("<A", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->Hyperlink1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 55;
  }
  else if (AnsiPos("<LINK", AnsiUpperCase(tag)) && AnsiPos("STYLESHEET", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->ExterneStyleSheetDatei1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 108;
  }
  else if (AnsiPos("<STYLE", AnsiUpperCase(tag)))
  {
   caption = Hauptformular->ReplaceString(Hauptformular->StyleSheetZuweisungen1->Caption, "&", "", false, true);
   caption = Hauptformular->ReplaceString(caption, "...", "", false, true);
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetStringEx(67, caption);
   Tagbearbeiten1->Enabled = true;
   Tagbearbeiten1->ImageIndex = 61;
  }
  else
  {
   Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetString(66);
   Tagbearbeiten1->Enabled = false;
   Tagbearbeiten1->ImageIndex = -1;
  }
 }
 else
 {
  Tagbearbeiten1->Caption = Hauptformular->SprachenWaehler->GetString(66);
  Tagbearbeiten1->Enabled = false;
  Tagbearbeiten1->ImageIndex = -1;
 }
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::AlsKommentar1Click(TObject *Sender)
{
 Hauptformular->TagInsert("<!--", "//-->");
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::InGrossbuchstaben1Click(TObject *Sender)
{
 Textfeld->SelText = AnsiUpperCase(Textfeld->SelText);
 Textfeld->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::InKleinbuchstaben1Click(TObject *Sender)
{
 Textfeld->SelText = AnsiLowerCase(Textfeld->SelText);
 Textfeld->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Class1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" class=\"\"");        
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::ID1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" id=\"\"");
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Title1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" title=\"\"");
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Ausschneiden1Click(TObject *Sender)
{
 Textfeld->CutToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Kopieren1Click(TObject *Sender)
{
 Textfeld->CopyToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Einfgen1Click(TObject *Sender)
{
 Textfeld->PasteFromClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Lschen1Click(TObject *Sender)
{
 Textfeld->ClearSelection();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Tagentfernen1Click(TObject *Sender)
{
 String tag_str = Hauptformular->TagCurrent();
 String tag_str_2 = Hauptformular->TagCurrent();

 if (AnsiPos("/", tag_str.SubString(0, 2)))
 {
  tag_str = Hauptformular->ReplaceString(tag_str, "/", "", true, true);
  tag_str = tag_str.SubString(0, tag_str.Length() - 1);
  if (Textfeld->FindTxt(tag_str, false, false, false, false))
  {
   int temp1 = Textfeld->SelStart;
   Textfeld->FindTxt(">", true, false, false, false);
   int temp2 = Textfeld->SelStart;
   Textfeld->SelStart = temp1;
   Textfeld->SelLength = temp2 - temp1;
   Textfeld->SelText = "";
   Textfeld->FindTxt(tag_str_2, true, false, false, false);
   Textfeld->SelText = "";
  }
  Textfeld->SetFocus();
 }
 else
 {
  Textfeld->FindTxt("<", false, false, false, false);
  int temp1 = Textfeld->SelStart;
  Textfeld->FindTxt(">", true, false, false, false);
  int temp2 = Textfeld->SelStart;
  Textfeld->SelStart = temp1;
  Textfeld->SelLength = temp2 - temp1;
  Textfeld->SelText = "";
  if (AnsiPos(" ", tag_str))
  {
   tag_str = tag_str.SubString(0, (AnsiPos(" ", tag_str)) - 1);
   tag_str = tag_str + ">";
  }
  tag_str = tag_str.Insert("/", 2);
  if (Textfeld->FindTxt(tag_str, true, false, false, false))
   Textfeld->SelText = "";
  Textfeld->SelStart = temp1;
  Textfeld->SetFocus();
 }
 Textfeld->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Zeilenumbrcheanhngen1Click(TObject *Sender)
{
 String line_break;
 if (Hauptformular->editor_xhtml_mode)
  line_break = "<br />";
 else
  line_break = "<br>";

 Hauptformular->TempMemo->Lines->Clear();
 Hauptformular->TempMemo->SelText = Textfeld->SelText;
 int items_count = Hauptformular->TempMemo->Lines->Count;
 for (int i = 0; i < items_count; i++)
  Hauptformular->TempMemo->Lines->Strings[i] = Hauptformular->TempMemo->Lines->Strings[i] + line_break;
 Hauptformular->TempMemo->SelectAll();
 Textfeld->SelText = Hauptformular->TempMemo->SelText;
 Textfeld->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TKindFormular::InListeumwandeln1Click(TObject *Sender)
{
 Hauptformular->TempMemo->Lines->Clear();
 Hauptformular->TempMemo->SelText = Textfeld->SelText;
 int items_count = Hauptformular->TempMemo->Lines->Count;
 for (int i = 0; i < items_count; i++)
  Hauptformular->TempMemo->Lines->Strings[i] = "<li>" + Hauptformular->TempMemo->Lines->Strings[i] + "</li>";
 Hauptformular->TempMemo->Lines->Add("</ol>");
 Hauptformular->TempMemo->Lines->Insert(0, "<ol>");
 Hauptformular->TempMemo->SelectAll();
 Textfeld->SelText = Hauptformular->TempMemo->SelText;
 Textfeld->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::AlleTagsentfernen1Click(TObject *Sender)
{
 Hauptformular->TempMemo->Lines->Clear();
 Hauptformular->TempMemo->SelText = Textfeld->SelText;
 Hauptformular->TempMemo->SelStart = 0;
 bool abort = false;
 int temp1 = 0;
 int temp2 = 0;

 do
 {
  if (Hauptformular->TempMemo->FindTxt("<", true, false, false, false))
  {
   temp1 = Hauptformular->TempMemo->SelStart - 1;
   if (Hauptformular->TempMemo->FindTxt(">", true, false, false, false))
   {
    temp2 = Hauptformular->TempMemo->SelStart;
    Hauptformular->TempMemo->SelStart = temp1;
    Hauptformular->TempMemo->SelLength = temp2 - temp1;
    Hauptformular->TempMemo->SelText = "";
   }
   else
    abort = true;
  }
  else
   abort = true;
 }
 while (!abort);
 Hauptformular->TempMemo->SelectAll();
 Textfeld->SelText = Hauptformular->TempMemo->SelText;
 Textfeld->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::InTabelleumwandeln1Click(TObject *Sender)
{
 String eingabe = ";";
 if (InputQuery(Hauptformular->ReplaceString(InTabelleumwandeln1->Caption, "&", "", false, true), Hauptformular->SprachenWaehler->GetString(65), eingabe))
 {
  Hauptformular->TempMemo2->Lines->Clear();
  Hauptformular->TempMemo2->Lines->Add("<table>");
  char *teil;
  String tempstr;
  Hauptformular->TempMemo->Lines->Clear();
  Hauptformular->TempMemo->SelText = Textfeld->SelText;
  int items_count = Hauptformular->TempMemo->Lines->Count;
  for (int i = 0; i < items_count; i++)
  {
   Hauptformular->TempMemo2->Lines->Add(" <tr>");
   tempstr = Hauptformular->TempMemo->Lines->Strings[i];
   teil = strtok(tempstr.c_str(), eingabe.c_str());
   if (teil)
    Hauptformular->TempMemo2->Lines->Add("  <td>" + String(teil) + "</td>");
   do
   {
    teil = strtok(NULL, eingabe.c_str());
    if (teil)
     Hauptformular->TempMemo2->Lines->Add("  <td>" + String(teil) + "</td>");
   }
   while (teil);
   Hauptformular->TempMemo2->Lines->Add(" </tr>");
  }
  Hauptformular->TempMemo2->Lines->Add("</table>");
  Hauptformular->TempMemo2->SelectAll();
  Hauptformular->TempMemo2->SelLength = Hauptformular->TempMemo2->SelLength  - 2;
  Textfeld->SelText = Hauptformular->TempMemo2->SelText;
 }
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Style1Click(TObject *Sender)
{
 Hauptformular->TagAppendAttribute(" style=\"" + Hauptformular->CSSEditorEditStyle("") + "\"");
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Tagbearbeiten1Click(TObject *Sender)
{
 Hauptformular->tag_current = Hauptformular->TagCurrent();
 Textfeld->SelStart = Hauptformular->tag_sel_position;
 Textfeld->SelLength = Hauptformular->tag_current.Length();

 if (AnsiPos("<IFRAME", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TEingebettetesFrame* EingebettetesFrame = new TEingebettetesFrame(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(EingebettetesFrame);
  EingebettetesFrame->Caption = Hauptformular->ReplaceString(Hauptformular->EingebettetesFrame1->Caption, "&", "", false, true);
  EingebettetesFrame->ShowModal();
 }
 else if (AnsiPos("<FRAMESET", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TFrameBereich* FrameBereich = new TFrameBereich(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(FrameBereich);
  FrameBereich->Caption = Hauptformular->ReplaceString(Hauptformular->FrameBereich1->Caption, "&", "", false, true);
  FrameBereich->ShowModal();
 }
 else if (AnsiPos("<FRAME", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TEinzelnerFrame* EinzelnerFrame = new TEinzelnerFrame(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(EinzelnerFrame);
  EinzelnerFrame->Caption = Hauptformular->ReplaceString(Hauptformular->Frame1->Caption, "&", "", false, true);
  EinzelnerFrame->ShowModal();
 }
 else if (AnsiPos("<FORM", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TFormular* Formular = new TFormular(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Formular);
  Formular->Caption = Hauptformular->ReplaceString(Hauptformular->Formular2->Caption, "&", "", false, true);
  Formular->ShowModal();
 }
 else if (AnsiPos("<SELECT", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TAuswahlliste* Auswahlliste = new TAuswahlliste(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Auswahlliste);
  Auswahlliste->Caption = Hauptformular->ReplaceString(Hauptformular->Auswahlliste1->Caption, "&", "", false, true);
  Auswahlliste->ShowModal();
 }
 else if (AnsiPos("<INPUT", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("TYPE=SUBMIT", AnsiUpperCase(Hauptformular->QuotesDelete(Hauptformular->tag_current))))
 {
  Hauptformular->tag_currently_editing = true;
  TAbsendenZuruecksetzen* AbsendenZuruecksetzen = new TAbsendenZuruecksetzen(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(AbsendenZuruecksetzen);
  AbsendenZuruecksetzen->Caption = Hauptformular->ReplaceString(Hauptformular->AbsendenundZurcksetzenbutton1->Caption, "&", "", false, true);
  AbsendenZuruecksetzen->ShowModal();
 }
 else if (AnsiPos("<INPUT", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("TYPE=RESET", AnsiUpperCase(Hauptformular->QuotesDelete(Hauptformular->tag_current))))
 {
  Hauptformular->tag_currently_editing = true;
  TAbsendenZuruecksetzen* AbsendenZuruecksetzen = new TAbsendenZuruecksetzen(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(AbsendenZuruecksetzen);
  AbsendenZuruecksetzen->Caption = Hauptformular->ReplaceString(Hauptformular->AbsendenundZurcksetzenbutton1->Caption, "&", "", false, true);
  AbsendenZuruecksetzen->ShowModal();
 }
 else if (AnsiPos("<INPUT", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("TYPE=IMAGE", AnsiUpperCase(Hauptformular->QuotesDelete(Hauptformular->tag_current))))
 {
  Hauptformular->tag_currently_editing = true;
  TAbsendenZuruecksetzen* AbsendenZuruecksetzen = new TAbsendenZuruecksetzen(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(AbsendenZuruecksetzen);
  AbsendenZuruecksetzen->Caption = Hauptformular->ReplaceString(Hauptformular->AbsendenundZurcksetzenbutton1->Caption, "&", "", false, true);
  AbsendenZuruecksetzen->ShowModal();
 }
 else if (AnsiPos("<TEXTAREA", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TTextfeld* Textfeld = new TTextfeld(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Textfeld);
  Textfeld->Caption = Hauptformular->ReplaceString(Hauptformular->Textfeld1->Caption, "&", "", false, true);
  Textfeld->ShowModal();
 }
 else if (AnsiPos("<INPUT", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("TYPE=PASSWORD", AnsiUpperCase(Hauptformular->QuotesDelete(Hauptformular->tag_current))))
 {
  Hauptformular->tag_currently_editing = true;
  TPasswortfeld* Passwortfeld = new TPasswortfeld(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Passwortfeld);
  Passwortfeld->Caption = Hauptformular->ReplaceString(Hauptformular->Passwortfeld1->Caption, "&", "", false, true);
  Passwortfeld->ShowModal();
 }
 else if (AnsiPos("<INPUT", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("TYPE=TEXT", AnsiUpperCase(Hauptformular->QuotesDelete(Hauptformular->tag_current))))
 {
  Hauptformular->tag_currently_editing = true;
  TEingabefeld* Eingabefeld = new TEingabefeld(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Eingabefeld);
  Eingabefeld->Caption = Hauptformular->ReplaceString(Hauptformular->Eingabefeld1->Caption, "&", "", false, true);
  Eingabefeld->ShowModal();
 }
 else if (AnsiPos("<INPUT", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("TYPE=HIDDEN", AnsiUpperCase(Hauptformular->QuotesDelete(Hauptformular->tag_current))))
 {
  Hauptformular->tag_currently_editing = true;
  TVerstecktesFeld* VerstecktesFeld = new TVerstecktesFeld(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(VerstecktesFeld);
  VerstecktesFeld->Caption = Hauptformular->ReplaceString(Hauptformular->VerstecktesFeld1->Caption, "&", "", false, true);
  VerstecktesFeld->ShowModal();
 }
 else if (AnsiPos("<INPUT", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("TYPE=RADIO", AnsiUpperCase(Hauptformular->QuotesDelete(Hauptformular->tag_current))))
 {
  Hauptformular->tag_currently_editing = true;
  TRadiobutton* Radiobutton = new TRadiobutton(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Radiobutton);
  Radiobutton->Caption = Hauptformular->ReplaceString(Hauptformular->Radiobutton1->Caption, "&", "", false, true);
  Radiobutton->ShowModal();
 }
 else if (AnsiPos("<INPUT", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("TYPE=CHECKBOX", AnsiUpperCase(Hauptformular->QuotesDelete(Hauptformular->tag_current))))
 {
  Hauptformular->tag_currently_editing = true;
  TCheckboxTag* CheckboxTag = new TCheckboxTag(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(CheckboxTag);
  CheckboxTag->Caption = Hauptformular->ReplaceString(Hauptformular->Checkbox1->Caption, "&", "", false, true);
  CheckboxTag->ShowModal();
 }
 else if (AnsiPos("<OPTION", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TAuswahleintrag* Auswahleintrag = new TAuswahleintrag(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Auswahleintrag);
  Auswahleintrag->Caption = Hauptformular->ReplaceString(Hauptformular->Auswahleintrag1->Caption, "&", "", false, true);
  Auswahleintrag->ShowModal();
 }
 else if (AnsiPos("<INPUT", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("TYPE=BUTTON", AnsiUpperCase(Hauptformular->QuotesDelete(Hauptformular->tag_current))))
 {
  Hauptformular->tag_currently_editing = true;
  TButtonTag* ButtonTag = new TButtonTag(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(ButtonTag);
  ButtonTag->Caption = Hauptformular->ReplaceString(Hauptformular->Button1->Caption, "&", "", false, true);
  ButtonTag->ShowModal();
 }
 else if (AnsiPos("<TD", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TZelle* Zelle = new TZelle(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Zelle);
  Zelle->Caption = Hauptformular->ReplaceString(Hauptformular->Zelle1->Caption, "&", "", false, true);
  Zelle->ShowModal();
 }
 else if (AnsiPos("<TH", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TKopfzelle* Kopfzelle = new TKopfzelle(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Kopfzelle);
  Kopfzelle->Caption = Hauptformular->ReplaceString(Hauptformular->Kopfzelle1->Caption, "&", "", false, true);
  Kopfzelle->ShowModal();
 }
 else if (AnsiPos("<CAPTION", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TUeberUnterschrift* UeberUnterschrift = new TUeberUnterschrift(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(UeberUnterschrift);
  UeberUnterschrift->Caption = Hauptformular->ReplaceString(Hauptformular->berUnterschrift1->Caption, "&", "", false, true);
  UeberUnterschrift->ShowModal();
 }
 else if (AnsiPos("<TR", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TZeile* Zeile = new TZeile(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Zeile);
  Zeile->Caption = Hauptformular->ReplaceString(Hauptformular->Zeile1->Caption, "&", "", false, true);
  Zeile->ShowModal();
 }
 else if (AnsiPos("<TABLE", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TTabelle* Tabelle = new TTabelle(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Tabelle);
  Tabelle->Caption = Hauptformular->ReplaceString(Hauptformular->Tabelle2->Caption, "&", "", false, true);
  Tabelle->ShowModal();
 }
 else if (AnsiPos("<BODY", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TSeiteneigen* Seiteneigen = new TSeiteneigen(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Seiteneigen);
  Seiteneigen->Caption = Hauptformular->ReplaceString(Hauptformular->Seiteneigenschaften1->Caption, "&", "", false, true);
  Seiteneigen->ShowModal();
 }
 else if (AnsiPos("<OL", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TListe* Liste = new TListe(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Liste);
  Liste->Caption = Hauptformular->ReplaceString(Hauptformular->Liste1->Caption, "&", "", false, true);
  Liste->ShowModal();
 }
 else if (AnsiPos("<UL", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TListe* Liste = new TListe(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Liste);
  Liste->Caption = Hauptformular->ReplaceString(Hauptformular->Liste1->Caption, "&", "", false, true);
  Liste->ShowModal();
 }
 else if (AnsiPos("<DIV", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TAbschnitt* Abschnitt = new TAbschnitt(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Abschnitt);
  Abschnitt->Caption = Hauptformular->ReplaceString(Hauptformular->Abschnitt1->Caption, "&", "", false, true);
  Abschnitt->ShowModal();
 }
 else if (AnsiPos("<P", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TParagraph* Paragraph = new TParagraph(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Paragraph);
  Paragraph->Caption = Hauptformular->ReplaceString(Hauptformular->Paragraph1->Caption, "&", "", false, true);
  Paragraph->ShowModal();
 }
 else if (AnsiPos("<SPAN", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TSchnellformat* Schnellformat = new TSchnellformat(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Schnellformat);
  Schnellformat->Caption = Hauptformular->ReplaceString(Hauptformular->Schnellformatierung1->Caption, "&", "", false, true);
  Schnellformat->ShowModal();
 }
 else if (AnsiPos("<FONT", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TSchrift* Schrift = new TSchrift(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Schrift);
  Schrift->Caption = Hauptformular->ReplaceString(Hauptformular->Schrift1->Caption, "&", "", false, true);
  Schrift->ShowModal();
 }
 else if (AnsiPos("<META", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TMetatag* Metatag = new TMetatag(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Metatag);
  Metatag->Caption = Hauptformular->ReplaceString(Hauptformular->Metatag1->Caption, "&", "", false, true);
  Metatag->ShowModal();
 }
 else if (AnsiPos("<OBJECT", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TMultimedia* Multimedia = new TMultimedia(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Multimedia);
  Multimedia->Caption = Hauptformular->ReplaceString(Hauptformular->MultimediaObjekt1->Caption, "&", "", false, true);
  Multimedia->ShowModal();
 }
 else if (AnsiPos("<HR", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TTrennlinie* Trennlinie = new TTrennlinie(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Trennlinie);
  Trennlinie->Caption = Hauptformular->ReplaceString(Hauptformular->Trennlinie1->Caption, "&", "", false, true);
  Trennlinie->ShowModal();
 }
 else if (AnsiPos("<IMG", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TGrafik* Grafik = new TGrafik(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Grafik);
  Grafik->Caption = Hauptformular->ReplaceString(Hauptformular->Grafik1->Caption, "&", "", false, true);
  Grafik->ShowModal();
 }
 else if (AnsiPos("<A", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("NAME=", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TAnker* Anker = new TAnker(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Anker);
  Anker->Caption = Hauptformular->ReplaceString(Hauptformular->Anker1->Caption, "&", "", false, true);
  Anker->ShowModal();
 }
 else if (AnsiPos("<A", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("MAILTO:", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  TEmailVerweis* EmailVerweis = new TEmailVerweis(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(EmailVerweis);
  EmailVerweis->Caption = Hauptformular->ReplaceString(Hauptformular->eMailVerweis1->Caption, "&", "", false, true);
  EmailVerweis->ShowModal();
 }
 else if (AnsiPos("<A", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Hauptformular->tag_currently_editing = true;
  THyperlink* Hyperlink = new THyperlink(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Hyperlink);
  Hyperlink->Caption = Hauptformular->ReplaceString(Hauptformular->Hyperlink1->Caption, "&", "", false, true);
  Hyperlink->ShowModal();
 }
 else if (AnsiPos("<LINK", AnsiUpperCase(Hauptformular->tag_current)) && AnsiPos("STYLESHEET", AnsiUpperCase(Hauptformular->tag_current)))
 {
  String file;
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);
  file = Hauptformular->TagAttributeGetString("href=", Hauptformular->tag_current);
  String pfad_vorher = GetCurrentDir();
  SetCurrentDir (ExtractFilePath(Caption));
  file = ExpandFileName(file);
  Hauptformular->CSSEditorFileOpen(file);
  SetCurrentDir (pfad_vorher);
  Hauptformular->tag_current = "";
 }
 else if (AnsiPos("<STYLE", AnsiUpperCase(Hauptformular->tag_current)))
 {
  Textfeld->FindTxt(">", true, false, false, false);
  int StyleStart = Textfeld->SelStart;
  if (Textfeld->FindTxt("</Style>", true, false, false, false))
  {
   int StyleEnd = Textfeld->SelStart;
   String style_text;
   Textfeld->SelStart = StyleStart;
   Textfeld->SelLength = StyleEnd - StyleStart - 8;
   style_text = Textfeld->SelText;
   style_text = Hauptformular->ReplaceString(style_text, "\r\n<!--", "", true, true);
   style_text = Hauptformular->ReplaceString(style_text, "<!--\r\n", "", true, true);
   style_text = Hauptformular->ReplaceString(style_text, "<!--", "", true, true);
   style_text = Hauptformular->ReplaceString(style_text, "//-->", "", true, true);
   style_text = Hauptformular->ReplaceString(style_text, "-->", "", true, true);
   style_text = Hauptformular->CSSEditorEditStyleBlock(style_text);
   style_text = "\r\n<!--" + style_text + "//-->\r\n";
   Textfeld->SelText = style_text;
   Textfeld->SetFocus();
   Hauptformular->tag_current = "";
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Stichwort1Click(TObject *Sender)
{
 String tag = Hauptformular->TagCurrent();
 tag = AnsiUpperCase(tag);

 if (AnsiPos("<HR", tag))
  Hauptformular->HelpKeywordShow("tag_hr.html");
 else if (AnsiPos("<OBJECT", tag))
  Hauptformular->HelpKeywordShow("tag_object.html");
 else if (AnsiPos("<FONT", tag))
  Hauptformular->HelpKeywordShow("tag_font.html");
 else if (AnsiPos("<ADRESS", tag))
  Hauptformular->HelpKeywordShow("tag_formats.html#adress");
 else if (AnsiPos("<HTML", tag))
  Hauptformular->HelpKeywordShow("tag_structure.html#html");
 else if (AnsiPos("<HEAD", tag))
  Hauptformular->HelpKeywordShow("tag_structure.html#head");
 else if (AnsiPos("<TITLE", tag))
  Hauptformular->HelpKeywordShow("tag_structure.html#title");
 else if (AnsiPos("<BR", tag))
  Hauptformular->HelpKeywordShow("tag_br.html");
 else if (AnsiPos("<IMG", tag))
  Hauptformular->HelpKeywordShow("tag_img.html");
 else if (AnsiPos("<BODY", tag))
  Hauptformular->HelpKeywordShow("tag_body.html");
 else if (AnsiPos("<OL", tag))
  Hauptformular->HelpKeywordShow("tag_ol_ul.html");
 else if (AnsiPos("<UL", tag))
  Hauptformular->HelpKeywordShow("tag_ol_ul.html");
 else if (AnsiPos("<PRE", tag))
  Hauptformular->HelpKeywordShow("tag_formats.html#pre");
 else if (AnsiPos("<P", tag))
  Hauptformular->HelpKeywordShow("tag_p.html");
 else if (AnsiPos("<DIV", tag))
  Hauptformular->HelpKeywordShow("tag_div.html");
 else if (AnsiPos("<FORM", tag))
  Hauptformular->HelpKeywordShow("tag_form.html");
 else if (AnsiPos("<TEXTAREA", tag))
  Hauptformular->HelpKeywordShow("tag_textarea.html");
 else if (AnsiPos("<SELECT", tag))
  Hauptformular->HelpKeywordShow("tag_select.html");
 else if (AnsiPos("<OPTION", tag))
  Hauptformular->HelpKeywordShow("tag_option.html");
 else if (AnsiPos("<INPUT", tag) && AnsiPos("TYPE=TEXT", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  Hauptformular->HelpKeywordShow("tag_input_text.html");
 else if (AnsiPos("<INPUT", tag) && AnsiPos("TYPE=PASSWORD", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  Hauptformular->HelpKeywordShow("tag_input_password.html");
 else if (AnsiPos("<INPUT", tag) && AnsiPos("TYPE=HIDDEN", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  Hauptformular->HelpKeywordShow("tag_input_hidden.html");
 else if (AnsiPos("<INPUT", tag) && AnsiPos("TYPE=CHECKBOX", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  Hauptformular->HelpKeywordShow("tag_input_checkbox.html");
 else if (AnsiPos("<INPUT", tag) && AnsiPos("TYPE=RADIO", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  Hauptformular->HelpKeywordShow("tag_input_radio.html");
 else if (AnsiPos("<INPUT", tag) && AnsiPos("TYPE=BUTTON", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  Hauptformular->HelpKeywordShow("tag_input_button.html");
 else if (AnsiPos("<INPUT", tag) && AnsiPos("TYPE=SUBMIT", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  Hauptformular->HelpKeywordShow("tag_input_submit.html");
 else if (AnsiPos("<INPUT", tag) && AnsiPos("TYPE=IMAGE", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  Hauptformular->HelpKeywordShow("tag_input_submit.html");
 else if (AnsiPos("<INPUT", tag) && AnsiPos("TYPE=RESET", AnsiUpperCase(Hauptformular->QuotesDelete(tag))))
  Hauptformular->HelpKeywordShow("tag_input_submit.html");
 else if (AnsiPos("<A", tag) && AnsiPos("MAILTO:", tag))
  Hauptformular->HelpKeywordShow("tag_ahref.html");
 else if (AnsiPos("<A", tag) && AnsiPos("NAME=", tag))
  Hauptformular->HelpKeywordShow("tag_aname.html");
 else if (AnsiPos("<A", tag))
  Hauptformular->HelpKeywordShow("tag_ahref.html");
 else if (AnsiPos("<FRAMESET", tag))
  Hauptformular->HelpKeywordShow("tag_frameset.html");
 else if (AnsiPos("<FRAME", tag))
  Hauptformular->HelpKeywordShow("tag_frame.html");
 else if (AnsiPos("<TD", tag))
  Hauptformular->HelpKeywordShow("tag_td.html");
 else if (AnsiPos("<TH", tag))
  Hauptformular->HelpKeywordShow("tag_th.html");
 else if (AnsiPos("<TR", tag))
  Hauptformular->HelpKeywordShow("tag_tr.html");
 else if (AnsiPos("<IFRAME", tag))
  Hauptformular->HelpKeywordShow("tag_iframe.html");
 else if (AnsiPos("<TABLE", tag))
  Hauptformular->HelpKeywordShow("tag_table.html");
 else if (AnsiPos("<CAPTION", tag))
  Hauptformular->HelpKeywordShow("tag_caption.html");
 else if (AnsiPos("<META", tag))
  Hauptformular->HelpKeywordShow("tag_meta.html");
 else if (AnsiPos("<DD", tag))
  Hauptformular->HelpKeywordShow("tag_dd.html");
 else if (AnsiPos("<DL", tag))
  Hauptformular->HelpKeywordShow("tag_dl.html");
 else if (AnsiPos("<DT", tag))
  Hauptformular->HelpKeywordShow("tag_dt.html");
 else if (AnsiPos("<H1", tag))
  Hauptformular->HelpKeywordShow("tag_h16.html");
 else if (AnsiPos("<H2", tag))
  Hauptformular->HelpKeywordShow("tag_h16.html");
 else if (AnsiPos("<H3", tag))
  Hauptformular->HelpKeywordShow("tag_h16.html");
 else if (AnsiPos("<H4", tag))
  Hauptformular->HelpKeywordShow("tag_h16.html");
 else if (AnsiPos("<H5", tag))
  Hauptformular->HelpKeywordShow("tag_h16.html");
 else if (AnsiPos("<H6", tag))
  Hauptformular->HelpKeywordShow("tag_h16.html");
 else if (AnsiPos("<LI", tag))
  Hauptformular->HelpKeywordShow("tag_li.html");
 else if (AnsiPos("<BIG", tag))
  Hauptformular->HelpKeywordShow("tag_formats.html#big");
 else if (AnsiPos("<BLOCKQUOTE", tag))
  Hauptformular->HelpKeywordShow("tag_formats.html#blockquote");
 else if (AnsiPos("<B", tag))
  Hauptformular->HelpKeywordShow("tag_formats.html#b");
 else if (AnsiPos("<I", tag))
  Hauptformular->HelpKeywordShow("tag_formats.html#i");
 else if (AnsiPos("<EM", tag))
  Hauptformular->HelpKeywordShow("tag_formats.html#em");
 else if (AnsiPos("<SUP", tag))
  Hauptformular->HelpKeywordShow("tag_formats.html#sup");
 else if (AnsiPos("<SUB", tag))
  Hauptformular->HelpKeywordShow("tag_formats.html#sub");
 else if (AnsiPos("<SMALL", tag))
  Hauptformular->HelpKeywordShow("tag_formats.html#small");
 else if (AnsiPos("<SPAN", tag))
  Hauptformular->HelpKeywordShow("tag_span.html");
 else
  Hauptformular->HelpKeywordShow("tag_unknown.html");
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::Sonderzeichenumwandeln1Click(
      TObject *Sender)
{
 int zahl_1;
 char buchstabe_1;
 String edit_text = Textfeld->SelText;

 for (int i = 0; i < Hauptformular->SonderzeichenCodesLite->Items->Count; i++)
 {
  zahl_1 = Hauptformular->SonderzeichenCodesLite->Items->Strings[i].ToInt();
  buchstabe_1 = (char)zahl_1;
  edit_text = Hauptformular->ReplaceString(edit_text, String(buchstabe_1), Hauptformular->SonderzeichenNamesLite->Items->Strings[i], true, false);
 }
 Textfeld->SelText = edit_text;
}
//---------------------------------------------------------------------------

void __fastcall TKindFormular::FormResize(TObject *Sender)
{
// Hauptformular->Caption = WindowState;

/* Hauptformular->StatusLeiste->Panels->Items[0]->Text = Hauptformular->StatusLeiste->Panels->Items[0]->Text + "x";
  if (WindowState == 0)
  SpeedButton1->Visible = true;
 else
  SpeedButton1->Visible = false;*/
}
//---------------------------------------------------------------------------

