//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "cssedit.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Plusmemo"
#pragma link "ExtHilit"
#pragma link "PMSupport"
#pragma resource "*.dfm"
TStyleSheetEditor *StyleSheetEditor;
//---------------------------------------------------------------------------
__fastcall TStyleSheetEditor::TStyleSheetEditor(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::ToolButton11Click(TObject *Sender)
{
 Hauptformular->HelpShow(NULL, "dialog_stylesheet_editor.html", false);        
}
//---------------------------------------------------------------------------


void __fastcall TStyleSheetEditor::Splitter1CanResize(TObject *Sender,
      int &NewSize, bool &Accept)
{
 Accept = false;
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::Neu1Click(TObject *Sender)
{
 if (Stylefeld->Modified)
 {
  int save_button = Application->MessageBox(Hauptformular->SprachenWaehler->GetStringEx(31, StatusBar1->Panels->Items[1]->Text).c_str(), "Scribe!", MB_YESNOCANCEL + MB_DEFBUTTON1 + MB_ICONQUESTION);
  if (save_button == IDNO)
  {
   Stylefeld->Lines->Clear();
   Stylefeld->Modified = false;
   if (Hauptformular->VerwControl->ActivePage == Hauptformular->VerwTab1)
    StatusBar1->Panels->Items[1]->Text = Hauptformular->fileexplorer_dir  + "Layout.css";
   else
    StatusBar1->Panels->Items[1]->Text = Hauptformular->projectexplorer_dir + "Layout.css";
  }
  else if (save_button == IDYES)
  {
   Hauptformular->FileSave(Stylefeld, StatusBar1->Panels->Items[1]->Text, true);
   Stylefeld->Lines->Clear();
   Stylefeld->Modified = false;
   if (Hauptformular->VerwControl->ActivePage == Hauptformular->VerwTab1)
     StatusBar1->Panels->Items[1]->Text = Hauptformular->fileexplorer_dir  + "Layout.css";
   else
    StatusBar1->Panels->Items[1]->Text = Hauptformular->projectexplorer_dir + "Layout.css";
  }
 }
 else
 {
  Stylefeld->Lines->Clear();
  Stylefeld->Modified = false;
  if (Hauptformular->VerwControl->ActivePage == Hauptformular->VerwTab1)
   StatusBar1->Panels->Items[1]->Text = Hauptformular->fileexplorer_dir  + "Layout.css";
  else
   StatusBar1->Panels->Items[1]->Text = Hauptformular->projectexplorer_dir + "Layout.css";
 }
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::ffnen1Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(7);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->cssfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;
 OeffnenDialog->InitialDir = ExtractFilePath(StatusBar1->Panels->Items[1]->Text);
 OeffnenDialog->FileName = ExtractFileName(StatusBar1->Panels->Items[1]->Text);
 OeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OeffnenDialog->Execute())
 {
  Stylefeld->Lines->LoadFromFile(OeffnenDialog->FileName);
  StatusBar1->Panels->Items[1]->Text = OeffnenDialog->FileName;
  Stylefeld->Modified = false;
 }
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Speichern1Click(TObject *Sender)
{
 Hauptformular->FileSave(Stylefeld, StatusBar1->Panels->Items[1]->Text, true);
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Speichernunter1Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(7);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->cssfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 SpeichernunterDialog->Filter = filter_gesamt;
 SpeichernunterDialog->Title = Hauptformular->ReplaceString(Hauptformular->Speichernunter1->Caption, "&", "", false, true);

 SpeichernunterDialog->InitialDir = ExtractFilePath(StatusBar1->Panels->Items[1]->Text);
 SpeichernunterDialog->FileName = ExtractFileName(StatusBar1->Panels->Items[1]->Text);

 if (SpeichernunterDialog->Execute())
 {
  Hauptformular->FileSave(Stylefeld, SpeichernunterDialog->FileName, true);
  StatusBar1->Panels->Items[1]->Text = SpeichernunterDialog->FileName;
 }
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Beenden1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::StyleS1Click(TObject *Sender)
{
 if (Hauptformular->css_edit_editstyle)
 {
  String style;
  Stylefeld->HideSelection = true;
  Stylefeld->SelectAll();
  style = Stylefeld->SelText;
  style = Hauptformular->ReplaceString(style, "\r\n", "  ", true, true);
  style = Hauptformular->ReplaceString(style, "{", "", true, true);
  style = Hauptformular->ReplaceString(style, "}", "", true, true);

  int pos_1;
  bool found = false;

  String teil_1;
  do
  {
   style = Hauptformular->ReplaceString(style, "  ", " ", true, true);
   pos_1 = AnsiPos("  ", style);
   if (pos_1 == 0)
    found = true;
  }
  while (!found);

  style = TrimLeft(style);
  style = TrimRight(style);
  if (style.SubString(style.Length(), 1) != ";")
   style = style + ";";
  Hauptformular->css_editstyle = style;
 }
 else if (Hauptformular->css_edit_editstyleblock)
 {
  String style;
  Stylefeld->HideSelection = true;
  Stylefeld->SelectAll();
  style = Stylefeld->SelText;
  String temp_carr = "";
  for (int i = 0; i < carriage - 1; i++)
   temp_carr = temp_carr + " ";
  style = TrimRight(style);
  Hauptformular->css_editstyleblock = temp_carr + style + temp_carr;
 }
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Abbrechen1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Rckgngig1Click(TObject *Sender)
{
 Stylefeld->Undo();
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Widerrufen1Click(TObject *Sender)
{
 Stylefeld->Redo();
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Ausschneiden1Click(TObject *Sender)
{
 Stylefeld->CutToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Kopieren1Click(TObject *Sender)
{
 Stylefeld->CopyToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Einfgen1Click(TObject *Sender)
{
 if (Clipboard()->HasFormat(CF_TEXT))
  Stylefeld->PasteFromClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Lschen1Click(TObject *Sender)
{
 Stylefeld->ClearSelection();
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::Allesmarkieren1Click(TObject *Sender)
{
 Stylefeld->SelectAll();
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::AlsKommentar1Click(TObject *Sender)
{
 Stylefeld->SelText = "/*" + Stylefeld->SelText + "*/";
}
//---------------------------------------------------------------------------
void __fastcall TStyleSheetEditor::BitBtn1Click(TObject *Sender)
{
 String temp_str;
 if (ComboBox5->Visible == true)
  temp_str = ComboBox5->Text;

 if (Stylefeld->SelLength == 0)
  Stylefeld->SelText = ComboBox3->Text + ":" + ComboBox4->Text + temp_str + ";";
 else
  Stylefeld->SelText = ComboBox3->Text + ":" + ComboBox4->Text + temp_str;
 Stylefeld->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::SpeedButton4Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog1);
 if (ColorDialog1->Execute())
 {
  Hauptformular->ColorButton(SpeedButton4, ColorDialog1->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog1);
  ComboBox4->Text = Hauptformular->ColorColorToXHTMLCode(ColorDialog1->Color);
  if (Stylefeld->SelLength != 0)
   BitBtn1Click(Sender);
 }
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::StylefeldMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 ::SetFocus(Stylefeld->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::PopupMenu1Popup(TObject *Sender)
{
 Einfgen2->Enabled = Clipboard()->HasFormat(CF_TEXT);

 if (Stylefeld->SelLength != 0)
 {
  Ausschneiden2->Enabled = true;
  Kopieren2->Enabled = true;
  Lschen2->Enabled = true;
 }
 else
 {
  Ausschneiden2->Enabled = false;
  Kopieren2->Enabled = false;
  Lschen2->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::BearbeitenMenuPopup(TObject *Sender)
{
 Rckgngig1->Enabled = Stylefeld->CanUndo;
 Widerrufen1->Enabled = Stylefeld->CanRedo;
 Einfgen1->Enabled = Clipboard()->HasFormat(CF_TEXT);

 if (Stylefeld->SelLength != 0)
 {
  Ausschneiden1->Enabled = true;
  Kopieren1->Enabled = true;
  Lschen1->Enabled = true;
 }
 else
 {
  Ausschneiden1->Enabled = false;
  Kopieren1->Enabled = false;
  Lschen1->Enabled = false;
 }

 Allesmarkieren1->Enabled = Stylefeld->Lines->Count;
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::FormShow(TObject *Sender)
{
 StyleMenu->TrackButton = tbLeftButton;
 BearbeitenMenu->TrackButton = tbLeftButton;

 TIniFile* Einstellungen = new TIniFile(Hauptformular->program_dir + "Storage!\\settings.ini");

 Left = Einstellungen->ReadInteger("Positions", "StyleSheetEditorXPos", 20);
 Top = Einstellungen->ReadInteger("Positions", "StyleSheetEditorYPos", 20);
 Height = Einstellungen->ReadInteger("Positions", "StyleSheetEditorHeight", 440);
 Width = Einstellungen->ReadInteger("Positions", "StyleSheetEditorWidth", 600);

 delete Einstellungen;

 Label1->Caption = Hauptformular->SprachenWaehler->GetString(80);

 Stylefeld->Font->Name = Hauptformular->editor_font_face;
 Stylefeld->Font->Size = Hauptformular->editor_font_size;

 TWordOptions Worter;
 TExtFontStyles Styles;
 TFontStyles FontStyles;

 StylefeldHighlighter->StartStopKeys->Clear();
 StylefeldHighlighter->Keywords->Clear();

 if (Hauptformular->syntax_bold_css_attrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_css_attrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 StylefeldHighlighter->StartStopKeys->AddExStartStopKey("{", "}", Worter, Styles, 1, 0, 0, crDefault, clWindow, Hauptformular->syntax_color_css_attrs, false);

 if (Hauptformular->syntax_bold_css_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_css_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 StylefeldHighlighter->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 2, 0, 1, crDefault, clWindow, Hauptformular->syntax_color_css_comments, false);

 if (Hauptformular->syntax_bold_css_chars)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_css_chars)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 StylefeldHighlighter->Keywords->AddExtKeyWord("{", TWordOptions(), Styles, 3, 1, 1, crDefault, clWindow, Hauptformular->syntax_color_css_chars);
 StylefeldHighlighter->Keywords->AddExtKeyWord("}", TWordOptions(), Styles, 4, 1, 1, crDefault, clWindow, Hauptformular->syntax_color_css_chars);
 StylefeldHighlighter->Keywords->AddExtKeyWord(";", TWordOptions(), Styles, 5, 1, 1, crDefault, clWindow, Hauptformular->syntax_color_css_chars);
 StylefeldHighlighter->Keywords->AddExtKeyWord(":", TWordOptions(), Styles, 6, 1, 1, crDefault, clWindow, Hauptformular->syntax_color_css_chars);

 if (Hauptformular->syntax_bold_css_strings)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_css_strings)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 StylefeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 7, 1, 2, crDefault, clWindow, Hauptformular->syntax_color_css_strings, true);

 if (Hauptformular->syntax_bold_css_tags)
  FontStyles << fsBold;
 else
  FontStyles >> fsBold;
 if (Hauptformular->syntax_italic_css_tags)
  FontStyles << fsItalic;
 else
  FontStyles >> fsItalic;
 Stylefeld->Font->Style = FontStyles;
 Stylefeld->Font->Color = Hauptformular->syntax_color_css_tags;

 ComboBox2->ItemIndex = 0;
 carriage = 0;

 int zeile = -1;
 String code;
 char *teil;
 int spalte = 0;
 int zaehler = 0;
 StringGrid1->RowCount = TempMemo->Lines->Count;

 for (int i = 0; i < TempMemo->Lines->Count; i++)
 {
  zeile++;
  zaehler = 0;
  spalte = 1;
  code = TempMemo->Lines->Strings[i];
  teil = strtok(code.c_str(), ",");
  if (teil)
   StringGrid1->Cells[spalte][zeile] = String(teil);
  spalte++;
  teil = strtok(NULL, ";");
  if (teil)
   StringGrid1->Cells[spalte][zeile] = String(teil);
  spalte++;
  do
  {
   teil = strtok(NULL, ",");
   if (teil)
    StringGrid1->Cells[spalte][zeile] = String(teil);
   spalte++;
   zaehler++;
  }
  while (teil);
  StringGrid1->Cells[0][i] = String(zaehler-1);
 }

 ComboBox3->Items->Clear();
 ComboBox2Change(Sender);

 if (Hauptformular->css_edit_editstyle)
 {
  String style;

  Neu1->Visible = false;
  N1->Visible = false;
  ffnen1->Visible = false;
  N2->Visible = false;
  Speichern1->Visible = false;
  Speichernunter1->Visible = false;
  N6->Visible = false;
  Beenden1->Visible = false;
  N9->Visible = false;
  AlsKommentar1->Visible = false;
  N4->Visible = false;
  AlsKommentar2->Visible = false;
  StyleS1->Visible = true;
  N3->Visible = true;
  Abbrechen1->Visible = true;
  ToolBar1->Visible = false;
  ToolBar3->Visible = true;
  ComboBox1->Enabled = false;
  ToolButton16->Enabled = false;
  ToolButton13->Enabled = false;

  if (Trim(Hauptformular->css_editstyle) != "")
  {
   style = Hauptformular->css_editstyle;
   style = TrimLeft(style);
   style = TrimRight(style);
   if (style.SubString(style.Length(), 1) != ";")
    style = style + ";";
   style = Hauptformular->ReplaceString(style, ";   ", ";", true, true);
   style = Hauptformular->ReplaceString(style, ";  ", ";", true, true);
   style = Hauptformular->ReplaceString(style, "; ", ";", true, true);
   style = Hauptformular->ReplaceString(style, ";", ";\r\n ", true, true);
   style = TrimRight(style);
   Stylefeld->Lines->Add("{\r\n " + style + "\r\n}");
  }
  else
   Stylefeld->Lines->Add("{\r\n \r\n}");
  Stylefeld->SelStart = 4;
 }
 else if (Hauptformular->css_edit_editstyleblock)
 {
  String style;

  Neu1->Visible = false;
  N1->Visible = false;
  ffnen1->Visible = false;
  N2->Visible = false;
  Speichern1->Visible = false;
  Speichernunter1->Visible = false;
  N6->Visible = false;
  Beenden1->Visible = false;
  StyleS1->Visible = true;
  N3->Visible = true;
  Abbrechen1->Visible = true;
  ToolBar1->Visible = false;
  ToolBar3->Visible = true;

  style = Hauptformular->css_editstyleblock;
  style = Hauptformular->ReplaceString(style, "<!--", "", true, true);
  style = Hauptformular->ReplaceString(style, "//-->", "", true, true);
  style = Hauptformular->ReplaceString(style, "-->", "", true, true);
  Stylefeld->SelText = style;

  for (int i = 0; i < Stylefeld->Lines->Count; i++)
  {
   if (Trim(Stylefeld->Lines->Strings[i]) == "")
   {
    Stylefeld->Lines->Delete(i);
    Stylefeld->Lines->Strings[i] = TrimLeft(Stylefeld->Lines->Strings[i]);
   }
  }
  if (Stylefeld->Lines->Strings[0] == "")
   Stylefeld->Lines->Delete(0);
  carriage = Stylefeld->Lines->Strings[0].Length() - Trim(Stylefeld->Lines->Strings[0]).Length();
 }
 else if (Trim(Hauptformular->css_openfile) != "")
 {
  StatusBar1->Panels->Items[1]->Text = Hauptformular->css_openfile;
  Stylefeld->Lines->LoadFromFile(Hauptformular->css_openfile);
  Stylefeld->Modified = false;
 }
 else
 {
  if (Hauptformular->VerwControl->ActivePage == Hauptformular->VerwTab1)
   StatusBar1->Panels->Items[1]->Text = Hauptformular->fileexplorer_dir  + "Layout.css";
  else
   StatusBar1->Panels->Items[1]->Text = Hauptformular->projectexplorer_dir + "Layout.css";
 }
 Stylefeld->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 TIniFile* Einstellungen = new TIniFile(Hauptformular->program_dir + "Storage!\\settings.ini");

 Einstellungen->WriteInteger("Positions", "StyleSheetEditorXPos", Left);
 Einstellungen->WriteInteger("Positions", "StyleSheetEditorYPos", Top);
 Einstellungen->WriteInteger("Positions", "StyleSheetEditorHeight", Height);
 Einstellungen->WriteInteger("Positions", "StyleSheetEditorWidth", Width);

 delete Einstellungen;

 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::ToolButton13Click(TObject *Sender)
{
 int pos = Stylefeld->SelStart;
 Stylefeld->SelText = ComboBox1->Text + " {  }";
 Stylefeld->SelStart = pos + ComboBox1->Text.Length() + 3;
 Stylefeld->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::ToolButton16Click(TObject *Sender)
{
 Stylefeld->Lines->Add(ComboBox1->Text + " {  }");
 Stylefeld->SelStart = Stylefeld->GetTextLen() - 4;
 Stylefeld->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::ComboBox2Change(TObject *Sender)
{
 ComboBox3->Items->Clear();

 if (ComboBox2->ItemIndex == 0)
 {
  MinZ = 0;
  MaxZ = TempMemo->Lines->Count - 1;
 }
 else if (ComboBox2->ItemIndex == 1)
 {
  MinZ = 0;
  MaxZ = 11;
 }
 else if (ComboBox2->ItemIndex == 2)
 {
  MinZ = 12;
  MaxZ = 16;
 }
 else if (ComboBox2->ItemIndex == 3)
 {
  MinZ = 17;
  MaxZ = 19;
 }
 else if (ComboBox2->ItemIndex == 4)
 {
  MinZ = 20;
  MaxZ = 31;
 }
 else if (ComboBox2->ItemIndex == 5)
 {
  MinZ = 32;
  MaxZ = 37;
 }
 else if (ComboBox2->ItemIndex == 6)
 {
  MinZ = 38;
  MaxZ = 42;
 }
 else if (ComboBox2->ItemIndex == 7)
 {
  MinZ = 43;
  MaxZ = 47;
 }
 else if (ComboBox2->ItemIndex == 8)
 {
  MinZ = 48;
  MaxZ = 51;
 }
 else if (ComboBox2->ItemIndex == 9)
 {
  MinZ = 52;
  MaxZ = 57;
 }

 for (int i = MinZ; i < MaxZ + 1; i++)
  ComboBox3->Items->Add(StringGrid1->Cells[2][i]);

 ComboBox3->ItemIndex = 0;
 ComboBox3Change(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TStyleSheetEditor::StylefeldChange(TObject *Sender)
{
 if (Stylefeld->SelLength != 0)
 {
  ToolButton7->Enabled = true;
  ToolButton8->Enabled = true;
  ToolButton20->Enabled = true;
  ToolButton21->Enabled = true;
 }
 else
 {
  ToolButton7->Enabled = false;
  ToolButton8->Enabled = false;
  ToolButton20->Enabled = false;
  ToolButton21->Enabled = false;
 }

 ToolButton10->Enabled = Stylefeld->CanUndo;
 ToolButton12->Enabled = Stylefeld->CanRedo;
 ToolButton23->Enabled = Stylefeld->CanUndo;
 ToolButton24->Enabled = Stylefeld->CanRedo;

 String zeile, spalte;
 zeile = Stylefeld->SelPar + 1;
 spalte = Stylefeld->SelCol + 1;
 zeile = zeile + ":" + spalte;
 StatusBar1->Panels->Items[0]->Text = zeile;
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
 if ((!Hauptformular->css_edit_editstyle) && (!Hauptformular->css_edit_editstyleblock))
 {
  if (Stylefeld->Modified)
   CanClose = Hauptformular->FileAskSave(Stylefeld, StatusBar1->Panels->Items[1]->Text);
 }
}
//---------------------------------------------------------------------------


void __fastcall TStyleSheetEditor::StylefeldClick(TObject *Sender)
{
 String zeile;
 int ursprung_selstart = Stylefeld->SelStart;
 int ursprung_sellength = Stylefeld->SelLength;
 int selstart = Stylefeld->SelStart;
 int Found1 = 0;
 int Found2 = 0;

 if (Stylefeld->FindTxt("{", false, true, false, false))
 {
  Found1 = Stylefeld->SelStart;
  if (Stylefeld->FindTxt("}", true, true, false, false))
  {
   Found2 = Stylefeld->SelStart;
   Stylefeld->SelStart = Found1;
   Stylefeld->SelLength = Found2 - Found1;
   zeile = Stylefeld->SelText;
   zeile = Hauptformular->ReplaceString(zeile, "\r\n", "  ", true, true);
  }
 }

 bool ausstieg = false;
 int part_pos = 0;
 int ursprung = Found1;
 ursprung = selstart - Found1;
 Stylefeld->SelStart = selstart;
 int left_part_int = 0;
 int right_part_int = 0;
 String definition;
 String part;
 String right_part = zeile.SubString(ursprung + 1, zeile.Length());
 String left_part = zeile.SubString(0, ursprung);
 String temp_str;

 if ((Trim(left_part) != "") && (Trim(right_part) != ""))
 {
  while (!ausstieg)
  {
   part = right_part.SubString(part_pos, 1);
   if ((part == "}") || (part == ";"))
   {
    right_part = right_part.SubString(0, part_pos);
    ausstieg = true;
   }
   else if (part == "{")
   {
    right_part = "";
    ausstieg = true;
   }
   else if (part_pos == right_part.Length())
   {
    right_part = "";
    ausstieg = true;
   }
   else
    part_pos++;
  }

  ausstieg = false;
  part = "";
  part_pos = ursprung;

  while (!ausstieg)
  {
   part = left_part.SubString(part_pos, 1);
   if ((part == "{") || (part == ";"))
   {
    left_part = left_part.SubString(part_pos, left_part.Length() - part_pos + 1);
    ausstieg = true;
   }
   else if (part == "}")
   {
    left_part = "";
    ausstieg = true;
   }
   else if (part_pos == 0)
   {
    left_part = "";
    ausstieg = true;
   }
   else
    part_pos--;
  }

  left_part = StringReplace(left_part, "{", "", TReplaceFlags() << rfReplaceAll);
  left_part = StringReplace(left_part, "}", "", TReplaceFlags() << rfReplaceAll);
  left_part = StringReplace(left_part, ";", "", TReplaceFlags() << rfReplaceAll);
  left_part = TrimLeft(left_part);
  right_part = StringReplace(right_part, "{", "", TReplaceFlags() << rfReplaceAll);
  right_part = StringReplace(right_part, "}", "", TReplaceFlags() << rfReplaceAll);
  right_part = StringReplace(right_part, ";", "", TReplaceFlags() << rfReplaceAll);
  right_part = TrimRight(right_part);
  right_part_int = right_part.Length();
  left_part_int = left_part.Length();

  if ((Trim(left_part) != "") && (Trim(right_part) != ""))
  {
   zeile = left_part + right_part;
   left_part = zeile.SubString(0, AnsiPos(":", zeile) - 1);
   left_part = TrimLeft(left_part);
   left_part = TrimRight(left_part);
   right_part = zeile.SubString(AnsiPos(":", zeile) + 1, zeile.Length());
   right_part = TrimLeft(right_part);
   right_part = TrimRight(right_part);
   Stylefeld->SelStart = selstart - left_part_int;
   Stylefeld->SelLength = (selstart + right_part_int) - (selstart - left_part_int);

   ComboBox2->ItemIndex = 0;
   ComboBox2Change(Sender);
   ComboBox3->Text = left_part;

   TempMemo->SelStart = 0;
   if (TempMemo->FindTxt(ComboBox3->Text, true, false, false, false))
   {
    if (SpeedButton4->Visible)
     SpeedButton4->Visible = false;
    if (ComboBox5->Visible)
     ComboBox5->Visible = false;

    ComboBox4->Text = "";
    ComboBox4->Items->Clear();
    Label1->Caption = StringGrid1->Cells[1][TempMemo->SelLine];

    int tempint = (StringGrid1->Cells[0][TempMemo->SelLine]).ToInt();
    tempint +=3;
    for (int i = 3; i < tempint; i++)
    {
     temp_str = StringGrid1->Cells[i][TempMemo->SelLine];
     if (temp_str == "#AllFonts")
     {
      for (int a = 0; a < Screen->Fonts->Count; a++)
       ComboBox4->Items->Add(Screen->Fonts->Strings[a]);
     }
     else if (temp_str == "#AllColors")
     {
      ComboBox4->Items->Add("Black");
      ComboBox4->Items->Add("Maroon");
      ComboBox4->Items->Add("Green");
      ComboBox4->Items->Add("Olive");
      ComboBox4->Items->Add("Navy");
      ComboBox4->Items->Add("Purple");
      ComboBox4->Items->Add("Teal");
      ComboBox4->Items->Add("Gray");
      ComboBox4->Items->Add("Silver");
      ComboBox4->Items->Add("Red");
      ComboBox4->Items->Add("Lime");
      ComboBox4->Items->Add("Yellow");
      ComboBox4->Items->Add("Blue");
      ComboBox4->Items->Add("Fuchsia");
      ComboBox4->Items->Add("Aqua");
      ComboBox4->Items->Add("White");
     }
     else if (temp_str == "#AllMasse")
     {
      if (!ComboBox5->Visible)
       ComboBox5->Visible = true;
     }
     else if (temp_str == "#AllExtColors")
     {
      ComboBox4->Items->Add("activeborder");
      ComboBox4->Items->Add("activecaption");
      ComboBox4->Items->Add("appworkspace");
      ComboBox4->Items->Add("background");
      ComboBox4->Items->Add("buttonface");
      ComboBox4->Items->Add("buttonhighlight");
      ComboBox4->Items->Add("buttontext");
      ComboBox4->Items->Add("captiontext");
      ComboBox4->Items->Add("greytext");
      ComboBox4->Items->Add("highlight");
      ComboBox4->Items->Add("highlighttext");
      ComboBox4->Items->Add("inactiveborder");
      ComboBox4->Items->Add("inactivecaption");
      ComboBox4->Items->Add("infobackground");
      ComboBox4->Items->Add("infotext");
      ComboBox4->Items->Add("menu");
      ComboBox4->Items->Add("menutext");
      ComboBox4->Items->Add("scrollbar");
      ComboBox4->Items->Add("threeddarkshadow");
      ComboBox4->Items->Add("threedface");
      ComboBox4->Items->Add("threedhighlight");
      ComboBox4->Items->Add("threedlightshadow");
      ComboBox4->Items->Add("threedshadow");
      ComboBox4->Items->Add("window");
      ComboBox4->Items->Add("windowframe");
      ComboBox4->Items->Add("windowtext");
     }
     else if (temp_str == "#ColorDialog")
     {
      Hauptformular->ColorAssignColorToButton(SpeedButton4, clBlack, ColorDialog1);
      if (!SpeedButton4->Visible)
       SpeedButton4->Visible = true;
     }
     else
      ComboBox4->Items->Add(temp_str);
    }
   }
   else
   {
    Label1->Caption = "[...]";
    ComboBox4->Items->Clear();
   }

   definition = right_part;

   if (definition.SubString(definition.Length() - 1, 2) == "pt")
   {
    ComboBox5->Text = "pt";
    definition = Hauptformular->ReplaceString(definition, "pt", "", true, true);
   }
   else if (definition.SubString(definition.Length() - 1, 2) == "pc")
   {
    ComboBox5->Text = "pc";
    definition = Hauptformular->ReplaceString(definition, "pc", "", true, true);
   }
   else if (definition.SubString(definition.Length() - 1, 2) == "in")
   {
    ComboBox5->Text = "in";
    definition = Hauptformular->ReplaceString(definition, "in", "", true, true);
   }
   else if (definition.SubString(definition.Length() - 1, 2) == "mm")
   {
    ComboBox5->Text = "mm";
    definition = Hauptformular->ReplaceString(definition, "mm", "", true, true);
   }
   else if (definition.SubString(definition.Length() - 1, 2) == "cm")
   {
    ComboBox5->Text = "cm";
    definition = Hauptformular->ReplaceString(definition, "cm", "", true, true);
   }
   else if (definition.SubString(definition.Length() - 1, 2) == "em")
   {
    ComboBox5->Text = "em";
    definition = Hauptformular->ReplaceString(definition, "em", "", true, true);
   }
   else if (definition.SubString(definition.Length() - 1, 2) == "ex")
   {
    ComboBox5->Text = "ex";
    definition = Hauptformular->ReplaceString(definition, "ex", "", true, true);
   }
   else if (definition.SubString(definition.Length() - 1, 2) == "px")
   {
    ComboBox5->Text = "px";
    definition = Hauptformular->ReplaceString(definition, "px", "", true, true);
   }
   else if (definition.SubString(definition.Length(), 1) == "%")
   {
    ComboBox5->Text = "%";
    definition = Hauptformular->ReplaceString(definition, "%", "", true, true);
   }
   else if (AnsiPos("#", definition))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor(definition), ColorDialog1);

   else if (AnsiPos("black", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("black"), ColorDialog1);
   else if (AnsiPos("maroon", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("maroon"), ColorDialog1);
   else if (AnsiPos("green", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("green"), ColorDialog1);
   else if (AnsiPos("olive", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("olive"), ColorDialog1);
   else if (AnsiPos("navy", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("navy"), ColorDialog1);
   else if (AnsiPos("purple", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("purple"), ColorDialog1);
   else if (AnsiPos("teal", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("teal"), ColorDialog1);
   else if (AnsiPos("gray", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("gray"), ColorDialog1);
   else if (AnsiPos("silver", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("silver"), ColorDialog1);
   else if (AnsiPos("red", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("red"), ColorDialog1);
   else if (AnsiPos("lime", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("lime"), ColorDialog1);
   else if (AnsiPos("yellow", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("yellow"), ColorDialog1);
   else if (AnsiPos("blue", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("blue"), ColorDialog1);
   else if (AnsiPos("fuchsia", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("fuchsia"), ColorDialog1);
   else if (AnsiPos("aqua", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("aqua"), ColorDialog1);
   else if (AnsiPos("white", AnsiLowerCase(definition)))
    Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->ColorXHTMLCodeToColor("white"), ColorDialog1);
   else
    ComboBox5->Text = "";
   ComboBox4->Text = definition;
  }
  else
  {
   Label1->Caption = Hauptformular->SprachenWaehler->GetString(80);
   Stylefeld->SelStart = ursprung_selstart;
   Stylefeld->SelLength = ursprung_sellength;
  }
 }
 else
 {
  Label1->Caption = Hauptformular->SprachenWaehler->GetString(80);
  Stylefeld->SelStart = ursprung_selstart;
  Stylefeld->SelLength = ursprung_sellength;
 }
 StylefeldChange(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TStyleSheetEditor::ComboBox5Click(TObject *Sender)
{
 if (Stylefeld->SelLength != 0)
  BitBtn1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::ComboBox3Click(TObject *Sender)
{
 if (Stylefeld->SelLength != 0)
  BitBtn1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::ComboBox4Click(TObject *Sender)
{
 if (Stylefeld->SelLength != 0)
  BitBtn1Click(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TStyleSheetEditor::ComboBox3Change(TObject *Sender)
{
 try
 {
  SpeedButton4->Visible = false;
  ComboBox5->Visible = false;
  String temp_str;
  int temp_int;
  ComboBox4->Text = "";
  ComboBox4->Items->Clear();

  if (Hauptformular->editor_language == 0)
   Label1->Caption = StringGrid1->Cells[1][ComboBox3->ItemIndex + MinZ];
  else
  {
   String definition = ComboBox3->Text;
   String first_letter = ComboBox3->Text.SubString(0, 1);
   definition = ComboBox3->Text.SubString(2, ComboBox3->Text.Length());
   definition = Hauptformular->ReplaceString(definition, "-", " ", true, true);
   Label1->Caption = AnsiUpperCase(first_letter) + definition;
  }

  temp_int = (StringGrid1->Cells[0][ComboBox3->ItemIndex + MinZ]).ToInt();
  temp_int +=3;
  for (int i = 3; i < temp_int; i++)
  {
   temp_str = StringGrid1->Cells[i][ComboBox3->ItemIndex + MinZ];
   if (temp_str == "#AllFonts")
   {
    for (int a = 0; a < Screen->Fonts->Count; a++)
     ComboBox4->Items->Add(Screen->Fonts->Strings[a]);
   }
   else if (temp_str == "#AllColors")
   {
    ComboBox4->Items->Add("Black");
    ComboBox4->Items->Add("Maroon");
    ComboBox4->Items->Add("Green");
    ComboBox4->Items->Add("Olive");
    ComboBox4->Items->Add("Navy");
    ComboBox4->Items->Add("Purple");
    ComboBox4->Items->Add("Teal");
    ComboBox4->Items->Add("Gray");
    ComboBox4->Items->Add("Silver");
    ComboBox4->Items->Add("Red");
    ComboBox4->Items->Add("Lime");
    ComboBox4->Items->Add("Yellow");
    ComboBox4->Items->Add("Blue");
    ComboBox4->Items->Add("Fuchsia");
    ComboBox4->Items->Add("Aqua");
    ComboBox4->Items->Add("White");
   }
   else if (temp_str == "#AllMasse")
    ComboBox5->Visible = true;
   else if (temp_str == "#AllExtColors")
   {
    ComboBox4->Items->Add("activeborder");
    ComboBox4->Items->Add("activecaption");
    ComboBox4->Items->Add("appworkspace");
    ComboBox4->Items->Add("background");
    ComboBox4->Items->Add("buttonface");
    ComboBox4->Items->Add("buttonhighlight");
    ComboBox4->Items->Add("buttontext");
    ComboBox4->Items->Add("captiontext");
    ComboBox4->Items->Add("greytext");
    ComboBox4->Items->Add("highlight");
    ComboBox4->Items->Add("highlighttext");
    ComboBox4->Items->Add("inactiveborder");
    ComboBox4->Items->Add("inactivecaption");
    ComboBox4->Items->Add("infobackground");
    ComboBox4->Items->Add("infotext");
    ComboBox4->Items->Add("menu");
    ComboBox4->Items->Add("menutext");
    ComboBox4->Items->Add("scrollbar");
    ComboBox4->Items->Add("threeddarkshadow");
    ComboBox4->Items->Add("threedface");
    ComboBox4->Items->Add("threedhighlight");
    ComboBox4->Items->Add("threedlightshadow");
    ComboBox4->Items->Add("threedshadow");
    ComboBox4->Items->Add("window");
    ComboBox4->Items->Add("windowframe");
    ComboBox4->Items->Add("windowtext");
   }
   else if (temp_str == "#ColorDialog")
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton4, clBlack, ColorDialog1);
    SpeedButton4->Visible = true;
   }
   else
    ComboBox4->Items->Add(temp_str);
  }
  ComboBox4->ItemIndex = 0;
 }
 catch (...)
 {
  1 == 1;
 }
}
//---------------------------------------------------------------------------


void __fastcall TStyleSheetEditor::ComboBox4KeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
 if (Key == 13)
  BitBtn1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::ComboBox5KeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
 if (Key == 13)
  BitBtn1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TStyleSheetEditor::ComboBox3KeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
 if (Key == 13)
  BitBtn1Click(Sender);
}
//---------------------------------------------------------------------------

