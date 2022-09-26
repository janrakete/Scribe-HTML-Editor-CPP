//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "xhtmlcon.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TXHTMLKonverter *XHTMLKonverter;
//---------------------------------------------------------------------------
__fastcall TXHTMLKonverter::TXHTMLKonverter(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TXHTMLKonverter::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TXHTMLKonverter::BitBtn2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------
void __fastcall TXHTMLKonverter::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_xhtml_converter.html", true);
}
//---------------------------------------------------------------------------
void __fastcall TXHTMLKonverter::BitBtn1Click(TObject *Sender)
{
 TForm *aktuelles_mdi;
 aktuelles_mdi = Hauptformular->ActiveMDIChild;

 Screen->Cursor = crHourGlass;
 BitBtn1->Enabled = false;
 ProgressBar1->Position = 0;

 if (ComboBox4->ItemIndex == 0)
 {
  int button;
  button = Application->MessageBox(Hauptformular->SprachenWaehler->GetString(20).c_str(), "Scribe!", MB_ICONQUESTION + MB_YESNO + MB_DEFBUTTON1);
  ProgressBar1->Max = Hauptformular->MDIChildCount;
  String dateiname;
  int mdis_count = Hauptformular->MDIChildCount;

  for (int i = 0; i < mdis_count; i++)
  {
   Hauptformular->TempMemo->Lines->Clear();
   Hauptformular->MDIChildren[i]->BringToFront();
   dateiname = Hauptformular->ActiveMDIChild->Caption;
   Hauptformular->TempMemo->Lines = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines;
   Button1Click(Sender);
   Button2Click(Sender);
   Button3Click(Sender);
   Button4Click(Sender);
   Button5Click(Sender);
   Button6Click(Sender);
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines = Hauptformular->TempMemo->Lines;
   if (button == IDYES)
    Hauptformular->FileSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, dateiname, false);
   ProgressBar1->StepBy(1);
   ProgressBar1->Position = ProgressBar1->Max;
  }
 }
 else
 {
  Application->MessageBox(Hauptformular->SprachenWaehler->GetString(81).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);

  if ((ComboBox4->ItemIndex == 2) || ((ComboBox4->ItemIndex == 1) && (CheckBox5->Checked)))
  {
   if (ComboBox4->ItemIndex == 1)
    Hauptformular->DirectoryFindSubs(Hauptformular->fileexplorer_dir, Verzeichnisse);
   else
    Hauptformular->DirectoryFindSubs(Hauptformular->project_dir + Hauptformular->ProjekteAuswahl->Items->Strings[Hauptformular->ProjekteAuswahl->ItemIndex] + "\\",Verzeichnisse);
  }
  else
   Verzeichnisse->Items->Add(Hauptformular->fileexplorer_dir);

  int items_count = Verzeichnisse->Items->Count;
  int items_count_2;
  String dateiname;
  ProgressBar1->Max = items_count;

  for (int i = 0; i < items_count; i++)
  {
   Dateien->Mask = Edit2->Text;
   Dateien->Directory = Verzeichnisse->Items->Strings[i];
   items_count_2 = Dateien->Items->Count;

   for (int a = 0; a < items_count_2; a++)
   {
    dateiname = Dateien->Items->Strings[a];
    dateiname = Dateien->Directory + "\\" + dateiname;
    Hauptformular->TempMemo->Lines->LoadFromFile(dateiname);
    Button1Click(Sender);
    Button2Click(Sender);
    Button3Click(Sender);
    Button4Click(Sender);
    Button5Click(Sender);
    Button6Click(Sender);
    Hauptformular->FileSave(Hauptformular->TempMemo, dateiname, false);
   }
   ProgressBar1->StepBy(1);
  }
 }

 ProgressBar1->Position = ProgressBar1->Max;
 BitBtn1->Enabled = true;
 Screen->Cursor = crDefault;

 aktuelles_mdi->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TXHTMLKonverter::FormShow(TObject *Sender)
{
 ComboBox4->ItemIndex = 0;
 Edit2->Enabled = false;
 CheckBox5->Enabled = false;
 ComboBox1->ItemIndex = 0;
 ComboBox3->ItemIndex = 0;

 if (Trim(Edit2->Text) == "")
 {
  String filter_part = "";
  filter_part = "*." + Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all;
  filter_part = filter_part.SubString(0, filter_part.Length() - 1);
  Edit2->Text = Hauptformular->ReplaceString(filter_part, ";", ";*.", true, true);
 }
}
//---------------------------------------------------------------------------
void __fastcall TXHTMLKonverter::ComboBox4Change(TObject *Sender)
{
 if (ComboBox4->ItemIndex == 1)
 {
  Edit2->Enabled = true;
  CheckBox5->Enabled = true;
 }
 else if (ComboBox4->ItemIndex == 2)
 {
  Edit2->Enabled = true;
  CheckBox5->Enabled = false;
 }
 else
 {
  Edit2->Enabled = false;
  CheckBox5->Enabled = false;
 }

 if (ComboBox4->ItemIndex == 2 && Hauptformular->ProjekteAuswahl->ItemIndex == 0)
 {
  Application->MessageBox(Hauptformular->SprachenWaehler->GetString(17).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONWARNING);
  ComboBox4->ItemIndex = 0;
 }
}
//---------------------------------------------------------------------------

void __fastcall TXHTMLKonverter::ComboBox1Change(TObject *Sender)
{
 if (ComboBox1->ItemIndex == 0)
  ComboBox2->Text = "iso-8859-1";
 else
  ComboBox2->Text = "UTF-8";
}
//---------------------------------------------------------------------------

void __fastcall TXHTMLKonverter::Button1Click(TObject *Sender)
{
 String edit_text;
 int zahl_1;
 char buchstabe_1;

 Hauptformular->TempMemo->SelectAll();
 edit_text = Hauptformular->TempMemo->SelText;

 for (int i = 0; i < SonderzeichenCodesIntern->Items->Count; i++)
 {
  zahl_1 = SonderzeichenCodesIntern->Items->Strings[i].ToInt();
  buchstabe_1 = (char)zahl_1;
  edit_text = Hauptformular->ReplaceString(edit_text, String(buchstabe_1), SonderzeichenNamesIntern->Items->Strings[i], true, false);
 }

 Hauptformular->TempMemo->SelText = edit_text;
 Hauptformular->TempMemo->SelStart = 0;
}
//---------------------------------------------------------------------------

void __fastcall TXHTMLKonverter::Button2Click(TObject *Sender)
{
 bool kompatibel;
 int klammer_auf_pos = 0;
 int klammer_zu_pos = 0;
 bool comment = false;
 String comment_part;
 String tag_string;
 String edit_text;
 String last_char;

 if (CheckBox2->Checked)
  kompatibel = true;
 else
  kompatibel = false;

 Hauptformular->TempMemo->SelectAll();
 edit_text = Hauptformular->TempMemo->SelText;

 while (AnsiPos("<", edit_text) && AnsiPos(">", edit_text) && (AnsiPos("<", edit_text) < AnsiPos(">", edit_text)))
 {
  klammer_auf_pos = AnsiPos ("<", edit_text);
  comment_part = edit_text.SubString(klammer_auf_pos, 4);
  if (comment_part == "<!--")
   comment = true;
  else
   comment = false;

  if (comment)
  {
   klammer_zu_pos = AnsiPos("-->", edit_text);
   klammer_zu_pos += 2;
  }
  else
   klammer_zu_pos = AnsiPos (">", edit_text);

  tag_string = edit_text.SubString(klammer_auf_pos, (klammer_zu_pos + 1) - klammer_auf_pos);

  //if (!AnsiPos("\n", tag_string) && !AnsiPos("\r", tag_string))
  //{
   if (comment)
   {
    edit_text = edit_text.Delete(klammer_auf_pos, (klammer_zu_pos + 1) - klammer_auf_pos);
    tag_string = Hauptformular->ReplaceString(tag_string, "<", "±¥", true, false);
    tag_string = Hauptformular->ReplaceString(tag_string, ">", "¥±", true, false);
    edit_text = edit_text.Insert(tag_string, klammer_auf_pos);
   }
   else
   {
    edit_text = edit_text.Delete(klammer_auf_pos, (klammer_zu_pos + 1) - klammer_auf_pos);
    tag_string = Hauptformular->TagNormalize(tag_string, true);
    last_char = tag_string.SubString(tag_string.Length() - 1, 1);
    if (last_char != "/")
    {
     for (int b = 0; b < TagsMitSlash->Items->Count; b++)
     {
      if (AnsiPos(TagsMitSlash->Items->Strings[b], AnsiLowerCase(tag_string)))
      {
       if (kompatibel)
        tag_string = tag_string.Insert(" /", tag_string.Length());
       else
        tag_string = tag_string.Insert("/", tag_string.Length());
      }
     }
    }

    for (int t = 0; t < StandAlones->Items->Count; t++)
    {
     if (Hauptformular->TagAttributeContainsStandalone(StandAlones->Items->Strings[t], tag_string))
     {
      tag_string = Hauptformular->TagAttributeRemoveAttribute(StandAlones->Items->Strings[t] + "=", tag_string);
      tag_string = Hauptformular->TagAttributeRemoveStandalone(StandAlones->Items->Strings[t], tag_string);

      String last_part = tag_string.SubString(tag_string.Length() - 1, 1);
      if (last_part == "/")
      {
       last_part = tag_string.SubString(tag_string.Length() - 2, 1);
       if (last_part == " ")
        tag_string.Insert(" " + StandAlones->Items->Strings[t] + "=\"" + StandAlones->Items->Strings[t] + "\"", tag_string.Length() - 2);
       else
        tag_string.Insert(" " + StandAlones->Items->Strings[t] + "=\"" + StandAlones->Items->Strings[t] + "\"", tag_string.Length() - 1);
      }
      else
       tag_string.Insert(" " + StandAlones->Items->Strings[t] + "=\"" + StandAlones->Items->Strings[t] + "\"", tag_string.Length());
     }
    }

    if (AnsiPos("<img", AnsiLowerCase(tag_string)))
    {
     if (!AnsiPos("alt=\"", AnsiLowerCase(tag_string)))
     {
      String last_part = tag_string.SubString(tag_string.Length() - 1, 1);
      if (last_part == "/")
      {
       last_part = tag_string.SubString(tag_string.Length() - 2, 1);
       if (last_part == " ")
        tag_string.Insert(" alt=\"\"", tag_string.Length() - 2);
       else
        tag_string.Insert(" alt=\"\"", tag_string.Length() - 1);
      }
      else
       tag_string.Insert(" alt=\"\"", tag_string.Length());
     }
    }

    for (int r = 0; r < WerteKlein->Items->Count; r++)
     tag_string = Hauptformular->ReplaceString(tag_string, WerteKlein->Items->Strings[r], WerteKlein->Items->Strings[r], true, true);

    tag_string = tag_string.SubString(2, tag_string.Length());
    tag_string = tag_string.SubString(1, tag_string.Length() - 1);
    tag_string = "±¥" + tag_string + "¥±";
    edit_text = edit_text.Insert(tag_string, klammer_auf_pos);
   }
  //}
  //else
  //{
  // edit_text = edit_text.Delete(klammer_auf_pos, (klammer_zu_pos + 1) - klammer_auf_pos);
  // tag_string = Hauptformular->ReplaceString(tag_string, "<", "±¥", true, false);
  // tag_string = Hauptformular->ReplaceString(tag_string, ">", "¥±", true, false);
  // edit_text = edit_text.Insert(tag_string, klammer_auf_pos);
  //}*/
 }
 edit_text = Hauptformular->ReplaceString(edit_text, "±¥", "<", true, false);
 edit_text = Hauptformular->ReplaceString(edit_text, "¥±", ">", true, false);
 Hauptformular->TempMemo->SelectAll();
 Hauptformular->TempMemo->SelText = edit_text;
 Hauptformular->TempMemo->SelStart = 0;
}
//---------------------------------------------------------------------------

void __fastcall TXHTMLKonverter::Button3Click(TObject *Sender)
{
 if (Hauptformular->TempMemo->FindTxt("<title", true, false, false, false))
 {
  int start;
  int ende;
  int ende_zeile;
  String temp_sel;

  start = Hauptformular->TempMemo->SelStart + Hauptformular->TempMemo->SelLength;
  Hauptformular->TempMemo->FindTxt("</title>", true, false, false, false);
  ende = Hauptformular->TempMemo->SelStart;
  ende_zeile = Hauptformular->TempMemo->SelLine;
  Hauptformular->TempMemo->SelStart = start;
  Hauptformular->TempMemo->SelLength = ende - start;
  temp_sel = Hauptformular->TempMemo->SelText;
  Hauptformular->TempMemo->SelText = "";
  if (Trim(Hauptformular->TempMemo->Lines->Strings[ende_zeile]) == "")
   Hauptformular->TempMemo->Lines->Delete(ende_zeile);
  Hauptformular->TempMemo->SelStart = 0;

  if (Hauptformular->TempMemo->FindTxt("<head", true, false, false, false))
  {
   Hauptformular->TempMemo->FindTxt(">", true, false, false, false);
   Hauptformular->TempMemo->Lines->Insert(Hauptformular->TempMemo->SelLine + 1, " " + temp_sel);
  }
 }

 Hauptformular->TempMemo->SelStart = 0;
}
//---------------------------------------------------------------------------

void __fastcall TXHTMLKonverter::Button4Click(TObject *Sender)
{
 if (CheckBox1->Checked)
 {
  while (Hauptformular->TempMemo->FindTxt("<li", true, false, false, false))
  {
   if (!AnsiPos("</li>", AnsiLowerCase(Hauptformular->TempMemo->Lines->Strings[Hauptformular->TempMemo->SelLine])) && !AnsiPos("<link", AnsiLowerCase(Hauptformular->TempMemo->Lines->Strings[Hauptformular->TempMemo->SelLine])))
    Hauptformular->TempMemo->Lines->Strings[Hauptformular->TempMemo->SelLine] = Hauptformular->TempMemo->Lines->Strings[Hauptformular->TempMemo->SelLine] + "</li>";
  }

  Hauptformular->TempMemo->SelStart = 0;

  while (Hauptformular->TempMemo->FindTxt("<option", true, false, false, false))
  {
   if (!AnsiPos("</option>", AnsiLowerCase(Hauptformular->TempMemo->Lines->Strings[Hauptformular->TempMemo->SelLine])))
    Hauptformular->TempMemo->Lines->Strings[Hauptformular->TempMemo->SelLine] = Hauptformular->TempMemo->Lines->Strings[Hauptformular->TempMemo->SelLine] + "</option>";
  }
 }

 Hauptformular->TempMemo->SelStart = 0;
}
//---------------------------------------------------------------------------

void __fastcall TXHTMLKonverter::Button5Click(TObject *Sender)
{
 String zeichensatz = ComboBox2->Text;
 String sprache;
 if (ComboBox1->ItemIndex == 0)
  sprache = "de";
 else
  sprache = "en";

 if (!Hauptformular->TempMemo->FindTxt("<?xml", true, false, false, false))
  Hauptformular->TempMemo->Lines->Insert(0, "<?xml version=\"1.0\" encoding=\"" + zeichensatz + "\"?>");

 Hauptformular->TempMemo->SelStart = 0;

 if (Hauptformular->TempMemo->FindTxt("<html", true, false, false, false))
 {
  int start;
  int ende;
  start = Hauptformular->TempMemo->SelStart + Hauptformular->TempMemo->SelLength;
  Hauptformular->TempMemo->FindTxt(">", true, false, false, false);
  ende = Hauptformular->TempMemo->SelStart;
  Hauptformular->TempMemo->SelStart = start;
  Hauptformular->TempMemo->SelLength = ende - start;
  if (!AnsiPos("xmlns", AnsiLowerCase(Hauptformular->TempMemo->SelText)))
  {
   Hauptformular->TempMemo->SelStart = ende - 1;
   Hauptformular->TempMemo->SelText = " xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"" + sprache + "\" lang=\"" + sprache + "\"";
  }
 }

 Hauptformular->TempMemo->SelStart = 0;
}
//---------------------------------------------------------------------------

void __fastcall TXHTMLKonverter::Button6Click(TObject *Sender)
{
 String DTD;

 if (ComboBox3->ItemIndex == 0)
  DTD = "PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\"";
 else if (ComboBox3->ItemIndex == 1)
  DTD = "PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"";
 else
  DTD = "PUBLIC \"-//W3C//DTD XHTML 1.0 Frameset//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-frame-set.dtd\"";

 if (Hauptformular->TempMemo->FindTxt("<!Doctype", true, false, false, false))
 {
  int start;
  int ende;
  int ende_zeile;
  start = Hauptformular->TempMemo->SelStart + Hauptformular->TempMemo->SelLength;
  Hauptformular->TempMemo->FindTxt(">", true, false, false, false);
  ende = Hauptformular->TempMemo->SelStart;
  ende_zeile = Hauptformular->TempMemo->SelLine;
  Hauptformular->TempMemo->SelStart = start;
  Hauptformular->TempMemo->SelLength = ende - start;
  Hauptformular->TempMemo->SelText = "";
  if (Trim(Hauptformular->TempMemo->Lines->Strings[ende_zeile]) == "")
   Hauptformular->TempMemo->Lines->Delete(ende_zeile);
 }
 Hauptformular->TempMemo->Lines->Insert(1, "<!DOCTYPE html " + DTD + ">");
 Hauptformular->TempMemo->SelStart = 0;
}
//---------------------------------------------------------------------------

