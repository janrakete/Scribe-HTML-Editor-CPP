//---------------------------------------------------------------------------
// Scribe! 2.2
// © Copyright 2000-2003 by Jan Uhlenbrok
// Auf den Stücken 4 - 32699 Extertal
//
// Codename: "Der beste Web-Editor der Welt"
//
//---------------------------------------------------------------------------
// Neu: PHP
//      - Passende Klammer finden
//      - Fenster - Menü
//      - Hintergrundfarbe
//      - FTP-Passwort verschlüsselt
//
//---------------------------------------------------------------------------
// Fehler: Todo - Liste
//         <Button> Tag
//---------------------------------------------------------------------------
#include <vcl.h>
#include <shellapi.h>
#include <registry.hpp>
#include <dos.h>
#include <math.h>
#pragma hdrstop

#include "main.h"
#include "addluni.h"
#include "child.h"
#include "openinet.h"
#include "neudia.h"
#include "neuproj.h"
#include "info.h"
#include "grapview.h"
#include "suche.h"
#include "hilfed.h"
#include "ibrowse.h"
#include "ftpprofi.h"
#include "newlink.h"
#include "tipoday.h"
#include "plugin.h"
#include "button.h"
#include "hyper.h"
#include "ankerdia.h"
#include "email.h"
#include "image.h"
#include "trennli.h"
#include "multim.h"
#include "meta.h"
#include "include.h"
#include "schriftd.h"
#include "schnellf.h"
#include "para.h"
#include "abschni.h"
#include "listedia.h"
#include "proback.h"
#include "seitprop.h"
#include "grafkata.h"
#include "thumbs.h"
#include "tablewiz.h"
#include "table.h"
#include "zeiledia.h"
#include "caption.h"
#include "kopfzell.h"
#include "zelledia.h"
#include "cssedit.h"
#include "xhtmlcon.h"
#include "incakt.h"
#include "lcheck.h"
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
#include "frameass.h"
#include "fastta.h"
#include "frameber.h"
#include "eiframe.h"
#include "iframe.h"
#include "welcome.h"
#include "download.h"
#include "options.h"
#include "javascr.h"
#include "ftpprops.h"
#include "ftppass.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Plusmemo"
#pragma link "LsFileExplorer28"
#pragma link "ExtHilit"
#pragma link "HTTPGet"
#pragma link "pmprint"
#pragma link "SHDocVw_OCX"
#pragma link "FtpListView"
#pragma link "Ftp"
#pragma link "FTPSock"
#pragma link "EnPngGr"
#pragma link "PMSupport"
#pragma resource "*.dfm"
#pragma resource "others.res"
THauptformular *Hauptformular;

// Neue Cursor-Variable setzen
const int crPipette  = 23;

//---------------------------------------------------------------------------
// Eigene Funktionen - Anfang
//---------------------------------------------------------------------------
String __fastcall THauptformular::ParseString (String uebergabe, String divider, int part)
{
 //-----------------------------------------
 // Liefert einen bestimmten Textteil zurück
 //-----------------------------------------
 char* teil;
 teil = strtok(uebergabe.c_str(), divider.c_str());
 if (part == 0)
  return (String(teil));
 else
 {
  for (int i = 0; i < part; i++)
  {
   teil = strtok(NULL, divider.c_str());
  }
  return (teil);
 }
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::AddLangPrepareSystem()
{
 //------------------------------------------------
 // Trifft Vorbereitungen für das AddLang! - System
 //------------------------------------------------
 TempDateilistBox->Directory = program_dir + "Storage!\\AddLang!";
 TempDateilistBox->Mask = "*.ini";
 TempDateilistBox->Update();
 if (TempDateilistBox->Items->Count != 0)
 {
  //------------------------------------
  // Erstellt die AddLang! - Popup-Menüs
  //------------------------------------
  TPopupMenu* AddLangPopup;
  TMenuItem* AddLangMenuItem;
  String current_menu_caption;
  for (int a = 0; a < TempDateilistBox->Items->Count; a++)
  {
   AddLangPopup = new TPopupMenu(this);
   AddLangPopup->Name = "AddLangPopup" + String(a);
   AddLangPopup->OnPopup = AddLangCreateMenu;
   current_menu_caption = ReplaceString(TempDateilistBox->Items->Strings[a], ".ini", "", true, true);
   AddLangMenuItem = NewItem(current_menu_caption, NULL, false, false, NULL, NULL, "addlangtempmenuitem" + current_menu_caption + "0");
   AddLangPopup->Items->Add(AddLangMenuItem);
   AddLangMenuItem->Visible = false;
  }
  //------------------------------------
  // Erstellt die AddLang! - Menübuttons
  //------------------------------------
  TToolButton* AddLangButton;
  for (int i = 0; i < TempDateilistBox->Items->Count; i++)
  {
   AddLangButton = new TToolButton(this);
   AddLangButton->Parent = MenuLeiste;
   AddLangButton->Left = ToolButton9->Left + ToolButton9->Width;
   AddLangButton->Caption = ReplaceString(TempDateilistBox->Items->Strings[i], ".ini", "", true, true);
   AddLangButton->Name = "AddLangButton" + String(i);
   AddLangButton->AutoSize = true;
   AddLangButton->Grouped = true;
   AddLangButton->Enabled = false;
   AddLangButton->DropdownMenu = dynamic_cast<TPopupMenu*>(FindComponent("AddLangPopup" + String(i))); //Noch unsicher
  }
  //----------------------------------------
  // Schreibt sonstige Infos in eine ListBox
  // Struktur: Dateiname|Beschreibung|Vorlage|Standard-Endung|Endungen|Hilfe-Datei
  //----------------------------------------
  TIniFile* Ini_Datei;
  String file_name;
  String description;
  String temp_late;
  String standard_ext;
  String extensions;
  String helpfile;

  for (int b = 0; b < TempDateilistBox->Items->Count; b++)
  {
   Ini_Datei = new TIniFile(program_dir + "Storage!\\AddLang!\\" + TempDateilistBox->Items->Strings[b]);
   file_name = TempDateilistBox->Items->Strings[b];
   description = Ini_Datei->ReadString("Other stuff", "Description", "(none)");
   temp_late = Ini_Datei->ReadString("Other stuff", "Template", "(none)");
   temp_late = ReplaceString(temp_late, ".sct", "", true, true);
   standard_ext = Ini_Datei->ReadString("Other stuff", "StandardExtension", "(none)");
   extensions = Ini_Datei->ReadString("Other stuff", "Extensions", "(none)");
   helpfile = Ini_Datei->ReadString("Other stuff", "HelpFile", "(none)");
   AddLangStuff->Items->Add(file_name + "|" + description + "|" + temp_late + "|" + standard_ext + "|" + extensions + "|" + helpfile);
  }
  delete Ini_Datei;

  //----------------------------------
  // Globalen Variablen Werte zuweisen
  //----------------------------------
  addlang_langs_count = TempDateilistBox->Items->Count;
  addlang_extensions_all = "";
  for (int i = 0; i < addlang_langs_count; i++)
   addlang_extensions_all = addlang_extensions_all + ParseString(AddLangStuff->Items->Strings[i], "|", 4);
 }
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::AddLangCreateMenu(TObject *Sender)
{
 //------------------------------
 // Erstellt die AddLang! - Menüs
 //------------------------------
 if (dynamic_cast<TPopupMenu*>(Sender)->Items->Count == 1)
 {
  TMenuItem* AddLangMenuItem;
  String current_menu_caption = dynamic_cast<TPopupMenu*>(Sender)->Items->Items[0]->Caption;
  String menuitem;
  TIniFile* Menueintraege_Datei = new TIniFile(program_dir + "Storage!\\AddLang!\\" + current_menu_caption + ".ini");
  TStringList* Menueintraege = new TStringList();

  Menueintraege_Datei->ReadSection("Menu items", Menueintraege);
  for (int i = 0; i < Menueintraege->Count; i++)
  {
   menuitem = Menueintraege->Strings[i];
   AddLangMenuItem = NewItem(menuitem, NULL, false, true, AddLangMenuClick, NULL, "addlangtempmenuitem" + current_menu_caption + String(i + 1));
   dynamic_cast<TPopupMenu*>(Sender)->Items->Add(AddLangMenuItem);
  }
  delete Menueintraege;
  delete Menueintraege_Datei;
 }
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::AddLangMenuClick(TObject *Sender)
{
 //----------------------------------------
 // Reagiert auf Klick's im AddLang! - Menü
 //----------------------------------------
 addlang_current_tag = dynamic_cast<TMenuItem*>(Sender)->Caption;
 addlang_current_tag = addlang_current_tag + "|";
 addlang_current_tag = addlang_current_tag + dynamic_cast<TMenuItem*>(Sender)->GetParentMenu()->Items->Items[0]->Caption;
 if (Trim(addlang_current_tag) != "")
 {
  TAddLangUniDialog* AddLangUniDialog = new TAddLangUniDialog(Application);
  SprachenWaehler->SetFormLanguage(AddLangUniDialog);
  AddLangUniDialog->ShowModal();
  delete AddLangUniDialog;
 }
 addlang_current_tag = "";
}
//---------------------------------------------------------------------------
TForm* __fastcall THauptformular::CreateChildForm(String vorlagen_datei, String datei_oeffnen, String http_datei)
{
 //----------------------------
 // Erstellt die Childformulare
 //----------------------------
 bool schon_vorhanden = false;
 String datei_name_1 = fileexplorer_dir + documents_name + (file_counter + 1) + documents_extension;
 String datei_name_2 = datei_oeffnen;
 String datei_name_3 = projectexplorer_dir + documents_name + (file_counter + 1) + documents_extension;
 String datei_name_4 = directftp_current_dir + documents_name + (file_counter + 1) + documents_extension;

 int mdis_count = MDIChildCount;

 for (int i = 0; i < mdis_count; i++)
 {
  if (AnsiLowerCase(MDIChildren[i]->Caption) == AnsiLowerCase(datei_name_1))
  {
   schon_vorhanden = true;
   MDIChildren[i]->BringToFront();
   break;
  }
  else if (AnsiLowerCase(MDIChildren[i]->Caption) == AnsiLowerCase(datei_name_2))
  {
   schon_vorhanden = true;
   MDIChildren[i]->BringToFront();
   break;
  }
  else if (AnsiLowerCase(MDIChildren[i]->Caption) == AnsiLowerCase(datei_name_3))
  {
   schon_vorhanden = true;
   MDIChildren[i]->BringToFront();
   break;
  }
  else if (AnsiLowerCase(MDIChildren[i]->Caption) == AnsiLowerCase(datei_name_4))
  {
   schon_vorhanden = true;
   MDIChildren[i]->BringToFront();
   break;
  }
 }

 if (!schon_vorhanden)
 {
  LockWindowUpdate(Application->MainForm->ClientHandle);
  TKindFormular* KindFormular = new TKindFormular(Application);
  SprachenWaehler->SetFormLanguage(KindFormular);
  LockWindowUpdate(NULL);
  if (Trim(vorlagen_datei) != "")
  {
   if (vorlagen_datei != "[leer]")
   {
    file_counter++;
    if (VerwControl->ActivePage == VerwTab1)
     KindFormular->Caption = fileexplorer_dir + documents_name + file_counter + documents_extension;
    else if (VerwControl->ActivePage == VerwTab3)
    {
     KindFormular->Caption = directftp_current_dir + documents_name + file_counter + documents_extension;
     KindFormular->FTPProfil->Caption = directftp_current_profile;
    }
    else
     KindFormular->Caption = projectexplorer_dir + documents_name + file_counter + documents_extension;
    try
    {
     KindFormular->Textfeld->Lines->LoadFromFile(program_dir + "Storage!\\Templates\\" + vorlagen_datei + ".sct");
    }
    catch (...)
    {
     KindFormular->Textfeld->Lines->LoadFromFile(program_dir + "Storage!\\Templates\\Standard.sct");
     standard_template = "Standard";
    }
    KindFormular->Textfeld->SetFocus();
    if (KindFormular->Textfeld->FindTxt("#Cursor", true, true, false, false))
     KindFormular->Textfeld->SelText = "";
    KindFormular->Textfeld->ScrollInView();
    KindFormular->Textfeld->Modified = false;
    KindFormular->Textfeld->ClearUndo();
   }
   else
   {
    file_counter++;
    if (VerwControl->ActivePage == VerwTab1)
     KindFormular->Caption = fileexplorer_dir + documents_name + file_counter + documents_extension;
    else
     KindFormular->Caption = projectexplorer_dir + documents_name + file_counter + documents_extension;
    KindFormular->Textfeld->SetFocus();
    KindFormular->Textfeld->Modified = false;
    KindFormular->Textfeld->ClearUndo();
   }
  }
  else if (Trim(datei_oeffnen) != "")
  {
   KindFormular->Caption = datei_oeffnen;
   KindFormular->Textfeld->Lines->LoadFromFile(datei_oeffnen);
   KindFormular->Textfeld->SetFocus();
   KindFormular->Textfeld->Modified = false;
   KindFormular->Textfeld->ClearUndo();
  }
  else
  {
   if (FileGetSize(program_dir + "~temp.html") > 0)
   {
    file_counter++;
    if (VerwControl->ActivePage == VerwTab1)
     KindFormular->Caption = fileexplorer_dir + documents_name + file_counter + documents_extension;
    else
     KindFormular->Caption = projectexplorer_dir + documents_name + file_counter + documents_extension;
    KindFormular->Textfeld->Lines->LoadFromFile(program_dir + "~temp.html");
    KindFormular->Textfeld->SetFocus();
    KindFormular->Textfeld->Modified = false;
    KindFormular->Textfeld->ClearUndo();
   }
   else
   {
    delete KindFormular;
    return (NULL);
   }
  }
  FensterLeiste->Tabs->Add(ExtractFileName(KindFormular->Caption));
  MDIKinderTitel->Items->Add(KindFormular->Caption);
  FensterLeiste->TabIndex =  FensterLeiste->Tabs->Count - 1;
  KindFormular->Title->Caption = SearchXHTMLTitle(KindFormular->Textfeld->Lines);
  return (KindFormular);
 }
 else
  return (NULL);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::FileFillList(TLsFilelistView28 *FillListSource, TListView *FillListTarget)
{
 //------------------
 // Füllt Dateilisten
 //------------------
 TListItem *ListItem;
 FillListTarget->Items->Clear();
 String datei_name;
 String datei_groesse;
 String datei_typ;
 String datei_date;
 int item_count = FillListSource->Items->Count;

 for (int i = 0; i < item_count; i++)
 {
  datei_name = FillListSource->Items->Item[i]->Caption;
  datei_groesse = FillListSource->Items->Item[i]->SubItems->Strings[0];
  datei_typ = FillListSource->Items->Item[i]->SubItems->Strings[1];
  datei_date = FillListSource->Items->Item[i]->SubItems->Strings[2];
  ListItem = FillListTarget->Items->Add();
  ListItem->Caption = datei_name;
  ListItem->SubItems->Add(datei_groesse);
  ListItem->SubItems->Add(datei_typ);
  ListItem->SubItems->Add(datei_date);
  ListItem->ImageIndex = FileCalculateIcon(datei_name);
 }
 StatusLeiste->Panels->Items[2]->Text = String(FillListSource->Items->Count) + " " + SprachenWaehler->GetString(28);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::SearchXHTMLTitle(TStrings *HTMLTitleDatei)
{
 //--------------------------------------
 // Sucht den Titel eines HTML-Dokumentes
 //--------------------------------------
 if (textarea_read_xhtml_title)
 {
  TempMemo->Lines->Clear();
  TempMemo->Lines = HTMLTitleDatei;

  if (TempMemo->FindTxt("<title>", true, false, false, false))
  {
   int Found1 = TempMemo->SelStart;
   if (TempMemo->FindTxt("</title>", true, false, false, false))
   {
    int Found2 = TempMemo->SelStart;
    TempMemo->SelStart = Found1;
    TempMemo->SelLength = Found2 - (Found1 + 8);
    return (TempMemo->SelText);
   }
   else
    return ("");
  }
  else
   return ("");
 }
 else
  return ("");
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::ReplaceString(String zeichenkette, String was, String durch_was, bool all, bool ignore_case)
{
 //---------------------------------------
 // Kapselt nur die StringReplace-Funktion
 //---------------------------------------
 if (all)
 {
  if (ignore_case)
   return (StringReplace(zeichenkette, was, durch_was, TReplaceFlags() << rfReplaceAll << rfIgnoreCase));
  else
   return (StringReplace(zeichenkette, was, durch_was, TReplaceFlags() << rfReplaceAll));
 }
 else
 {
  if (ignore_case)
   return (StringReplace(zeichenkette, was, durch_was, TReplaceFlags() << rfIgnoreCase));
  else
   return (StringReplace(zeichenkette, was, durch_was, TReplaceFlags()));
 }
}
//---------------------------------------------------------------------------
TStrings* __fastcall THauptformular::HistoryRead(String section)
{
 //----------------------
 // Liest History-Enträge
 //----------------------
 TStrings* Liste = new TStringList();
 TIniFile* HisFile = new TIniFile(program_dir + "Storage!\\history.ini");
 HisFile->ReadSection(section, Liste);
 delete HisFile;
 return (Liste);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::HistoryWrite(String section, TStrings* HistoryItems)
{
 //-------------------------
 // Schreibt History-Enträge
 //-------------------------
 TIniFile* HisFile = new TIniFile(program_dir + "Storage!\\history.ini");
 HisFile->EraseSection(section);
 for (int i = 0; i < max_history_entries; i++)
  HisFile->WriteString(section, HistoryItems->Strings[i], HistoryItems->Strings[i]);
 delete HisFile;
}
//---------------------------------------------------------------------------
int __fastcall THauptformular::FileGetSize(String file_name)
{
 //--------------------------------
 // Ermittelt die Größe einer Datei
 //--------------------------------
 TSearchRec SearchRec;
 if (FindFirst(ExpandFileName(file_name), faAnyFile, SearchRec) == 0)
 {
  FindClose(SearchRec);
  return SearchRec.Size;
 }
 else
 {
  FindClose(SearchRec);
  return -1;
 }
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::FTPFile(String file_name)
{
 //------------------------------
 // Ist das hier eine FTP-Datei ?
 //------------------------------
 if (AnsiPos("ftp://", AnsiLowerCase(file_name)))
  return (true);
 else
  return (false);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::DocumentFile(String file_name)
{
 //----------------------------------
 // Ist das hier ein XHTML-Dokument ?
 //----------------------------------
 String temp_str;
 temp_str = ExtractFileExt(file_name);
 temp_str = temp_str + ";";
 temp_str = temp_str.SubString(2, (temp_str.Length() - 1));
 if (AnsiPos (AnsiLowerCase(temp_str), AnsiLowerCase(docfile_extensions)))
  return (true);
 else
  return (false);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::CSSFile(String file_name)
{
 //------------------------------
 // Ist das hier eine CSS-Datei ?
 //------------------------------
 String temp_str;
 temp_str = ExtractFileExt(file_name);
 temp_str = temp_str + ";";
 temp_str = temp_str.SubString(2, (temp_str.Length() - 1));
 if (AnsiPos (AnsiLowerCase(temp_str), AnsiLowerCase(cssfile_extensions)))
  return (true);
 else
  return (false);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::JavaScriptFile(String file_name)
{
 //-------------------------------------
 // Ist das hier eine JavaScript-Datei ?
 //-------------------------------------
 String temp_str;
 temp_str = ExtractFileExt(file_name);
 temp_str = temp_str + ";";
 temp_str = temp_str.SubString(2, (temp_str.Length() - 1));
 if (AnsiPos (AnsiLowerCase(temp_str), AnsiLowerCase(javascriptfile_extensions)))
  return (true);
 else
  return (false);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::GraphicFile(String file_name)
{
 //---------------------------------
 // Ist das hier eine Grafik-Datei ?
 //---------------------------------
 String temp_str;
 temp_str = ExtractFileExt(file_name);
 temp_str = temp_str + ";";
 temp_str = temp_str.SubString(2, (temp_str.Length() - 1));
 if (AnsiPos (AnsiLowerCase(temp_str), AnsiLowerCase(graphicfile_extensions)))
  return (true);
 else
  return (false);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::MultimediaFile(String file_name)
{
 //-------------------------------------
 // Ist das hier eine Multimedia-Datei ?
 //-------------------------------------
 String temp_str;
 temp_str = ExtractFileExt(file_name);
 temp_str = temp_str + ";";
 temp_str = temp_str.SubString(2, (temp_str.Length() - 1));
 if (AnsiPos (AnsiLowerCase(temp_str), AnsiLowerCase(multimediafile_extensions)))
  return (true);
 else
  return (false);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::AddLangFile(String file_name)
{
 //-----------------------------------
 // Ist das hier eine AddLang!-Datei ?
 //-----------------------------------
 String temp_str;
 temp_str = ExtractFileExt(file_name);
 temp_str = temp_str + ";";
 temp_str = temp_str.SubString(2, (temp_str.Length() - 1));
 if (AnsiPos (AnsiLowerCase(temp_str), AnsiLowerCase(addlang_extensions_all)))
  return (true);
 else
  return (false);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::ScribePluginEngine(String file_name)
{
 //----------------------------
 // Die Scribe! - Plugin-Engine
 //----------------------------
 HINSTANCE plugin = LoadLibrary(file_name.c_str());
 typedef int (__stdcall  *pluginInterfaceVersionType)();
 pluginInterfaceVersionType pluginInterfaceVersiontyp;
 pluginInterfaceVersiontyp = (pluginInterfaceVersionType)GetProcAddress(plugin, "pluginInterfaceVersion");
 int pversion = (pluginInterfaceVersiontyp)();

 if (pversion == 1)
 {
  // Nur wegen Kompatibilität zu Phase 5
  String text_aus_dem_editor = "";
  int plugin_rueckgabe = 0;
  int text_laenge = 0;
  int sel_start = 0;
  int sel_length = 0;

  if (MDIChildCount)
  {
   text_laenge = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextLen();
   sel_start = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
   sel_length = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength;
   text_aus_dem_editor = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(0, text_laenge);
   if (sel_length < 0)
   {
    sel_start = sel_start + sel_length;
    sel_length = sel_length * (-1);
   }
  }

  typedef PChar (__stdcall *pluginStartType)(PChar, int, int);
  pluginStartType pluginStarttyp;
  pluginStarttyp = (pluginStartType)GetProcAddress(plugin, "pluginStart");
  text_aus_dem_editor = (pluginStarttyp)(text_aus_dem_editor.c_str(), sel_start, sel_length);

  typedef int (__stdcall *pluginRueckgabeType)();
  pluginRueckgabeType pluginRueckgabetyp;
  pluginRueckgabetyp = (pluginRueckgabeType)GetProcAddress(plugin, "pluginRueckgabetyp");
  plugin_rueckgabe = (pluginRueckgabetyp)();

  if (MDIChildCount)
  {
   if (plugin_rueckgabe == 1)
   {
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = text_aus_dem_editor;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
   }
   else if (plugin_rueckgabe == 2)
   {
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelectAll();
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = text_aus_dem_editor;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
   }
  }
 }
 else if (pversion == 2)
 {
  String text_aus_dem_editor = "";
  int plugin_rueckgabe = 0;
  int text_laenge = 0;
  int sel_start = 0;
  int sel_length = 0;
  int frage_rueckgabe = 0;

  if (MDIChildCount)
  {
   text_laenge = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextLen();
   sel_start = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
   sel_length = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength;
   text_aus_dem_editor = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(0, text_laenge);
   if (sel_length < 0)
   {
    sel_start = sel_start + sel_length;
    sel_length = sel_length * (-1);
   }
  }

  typedef int (__stdcall *pluginFrageType)();
  pluginFrageType pluginFragetyp;
  pluginFragetyp = (pluginFrageType)GetProcAddress(plugin, "pluginFrage");
  frage_rueckgabe = (pluginFragetyp)();

  typedef (__stdcall *pluginAntwortType)(PChar, int, int);
  pluginAntwortType pluginAntworttyp;
  pluginAntworttyp = (pluginAntwortType)GetProcAddress(plugin, "pluginAntwort");

  while (frage_rueckgabe != 0)
  {
   switch (frage_rueckgabe)
   {
    case 1:
    {
     (pluginAntworttyp)("Scribe!", 0, 0);
     break;
    }
    case 2:
    {
     (pluginAntworttyp)(program_version.c_str(), 0, 0);
     break;
    }
    case 3:
    {
     if (editor_language == 0)
      (pluginAntworttyp)("", 2, 0);
     else if (editor_language == 1)
      (pluginAntworttyp)("", 1, 0);
     break;
    }
    case 4:
    {
     (pluginAntworttyp)((program_dir + "Storage!\\Plugins\\").c_str(), 0, 0);
     break;
    }
    case 5:
    {
     String temp_projekt_dir;
     temp_projekt_dir = project_dir;
     if (ProjekteAuswahl->ItemIndex != 0)
      temp_projekt_dir = temp_projekt_dir + ProjekteAuswahl->Items->Strings[ProjekteAuswahl->ItemIndex] + "\\";
     else
      temp_projekt_dir = "";
     (pluginAntworttyp)(temp_projekt_dir.c_str(), 0, 0);
     break;
    }
    case 6:
    {
     (pluginAntworttyp)(fileexplorer_dir.c_str(), 0, 0);
     break;
    }
    case 7:
    {
     if (MDIChildCount)
      (pluginAntworttyp)((ActiveMDIChild->Caption).c_str(), 0, 0);
     else
      (pluginAntworttyp)("", 0, 0);
     break;
    }
    case 8:
    {
     if (MDIChildCount)
     {
      String all_children;
      int mdis_count = MDIChildCount;
      for (int i = 0; i < mdis_count; i++)
       all_children = all_children + MDIChildren[i]->Caption + "|";
      all_children = all_children.SubString(0, (all_children.Length() - 1));
      (pluginAntworttyp)(all_children.c_str(), 0, 0);
     }
     else
      (pluginAntworttyp)("", 0, 0);
     break;
    }
    case 9:
    {
     //Zuletzt geöffnete Dateien noch reinbringen
     (pluginAntworttyp)("", 0, -1);
     break;
    }
    case 10:
    {
     (pluginAntworttyp)(standard_xhtml_documentation.c_str(), 0, 0);
     break;
    }
    case 11:
    {
     (pluginAntworttyp)(browser_desc_1.c_str(), 0, 0);
     break;
    }
    case 12:
    {
     (pluginAntworttyp)(browser_desc_2.c_str(), 0, 0);
     break;
    }
    case 13:
    {
     (pluginAntworttyp)(browser_path_1.c_str(), 0, 0);
     break;
    }
    case 14:
    {
     (pluginAntworttyp)(browser_path_2.c_str(), 0, 0);
     break;
    }
    case 255:
    {
     (pluginAntworttyp)(0, 201, 0);
     break;
    }
    default:
    {
     (pluginAntworttyp)("", 0, -1);
     break;
    }
   }
   frage_rueckgabe = (pluginFragetyp)();
  }

  typedef PChar (__stdcall *pluginStartType)(PChar, int, int);
  pluginStartType pluginStarttyp;
  pluginStarttyp = (pluginStartType)GetProcAddress(plugin, "pluginStart");
  text_aus_dem_editor = (pluginStarttyp)(text_aus_dem_editor.c_str(), sel_start, sel_length);

  typedef int (__stdcall *pluginRueckgabeType)();
  pluginRueckgabeType pluginRueckgabetyp;
  pluginRueckgabetyp = (pluginRueckgabeType)GetProcAddress(plugin, "pluginRueckgabetyp");
  plugin_rueckgabe = (pluginRueckgabetyp)();

  if (MDIChildCount)
  {
   if (plugin_rueckgabe == 1)
   {
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = text_aus_dem_editor;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
   }
   else if (plugin_rueckgabe == 2)
   {
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelectAll();
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = text_aus_dem_editor;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
   }
   else if (plugin_rueckgabe == 3)
   {
    TempMemo->Lines->Clear();
    TempMemo->SelText = text_aus_dem_editor;
    TempMemo->Lines->SaveToFile(program_dir + "~temp.html");
    CreateChildForm("", "", program_dir + "~temp.html");
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
   }
  }
 }
 FreeLibrary (plugin);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::ProjectsLoad(String show_this_one)
{
 //-----------------
 // Lädt Projekt ein
 //-----------------
 //VerwControl->ActivePage = VerwTab2;
 String HauptPfad;
 ProjekteOrdner1->Directory = project_dir;
 ProjekteOrdner1->Update();
 ProjekteAuswahl->Items->Clear();
 ProjekteAuswahl->Items->Add(SprachenWaehler->GetString(4));

 if (ProjekteOrdner1->Items->IndexOf("[Storage!]") > -1)
  ProjekteOrdner1->Items->Delete(ProjekteOrdner1->Items->IndexOf("[Storage!]"));

 if (ProjekteOrdner1->Items->Count > 2)
 {
  ProjekteOrdner1->Items->Delete(0);
  ProjekteOrdner1->Items->Delete(0);
  for (int i = 0; i < ProjekteOrdner1->Items->Count; i++)
  {
   HauptPfad = ProjekteOrdner1->Items->Strings[i];
   HauptPfad = HauptPfad.SubString(2, HauptPfad.Length());
   HauptPfad = HauptPfad.SubString(0, HauptPfad.Length() - 1);
   ProjekteAuswahl->Items->Add(HauptPfad);
  }
 }
 if (ProjekteAuswahl->Items->IndexOf(show_this_one) > -1)
  ProjekteAuswahl->ItemIndex = ProjekteAuswahl->Items->IndexOf(show_this_one);
 else
  ProjekteAuswahl->ItemIndex = 0;
 ProjectsLoadFolders(show_this_one);
 if (ProjekteAuswahl->Items->Count > 1)
  return (true);
 else
  return (false);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::ProjectsLoadFolders(String show_this_one)
{
 //-----------------------
 // Lädt Projektordner ein
 //-----------------------
 String HauptPfad, NebenPfad;
 TTreeNode *Node;
 TTreeNode *MasterNode;
 ProjekteExplorer->Enabled = true;
 ProjekteListe->Enabled = true;
 ProjekteExplorer->Items->Clear();
 ProjekteListe->Items->Clear();

 if (ProjekteAuswahl->ItemIndex != 0)
 {
  if (ProjekteAuswahl->Items->IndexOf(show_this_one) > -1)
  {
   ProjekteOrdner1->Directory = project_dir + "\\" + show_this_one;
   ProjekteOrdner1->Update();
   ProjekteOrdner1->Items->Delete(0);
   ProjekteOrdner1->Items->Delete(0);
   MasterNode = ProjekteExplorer->Items->Add(NULL, show_this_one);
   MasterNode->ImageIndex = 28;
   for (int f = 0; f < ProjekteOrdner1->Items->Count; f++)
   {
    HauptPfad = ProjekteOrdner1->Items->Strings[f];
    HauptPfad = HauptPfad.SubString(2, HauptPfad.Length());
    HauptPfad = HauptPfad.SubString(0, HauptPfad.Length() - 1);
    Node = ProjekteExplorer->Items->AddChild (MasterNode, HauptPfad);
    Node->ImageIndex = 26;
    ProjekteOrdner2->Directory = project_dir + "\\" + show_this_one + "\\" + HauptPfad;
    ProjekteOrdner2->Items->Delete(0);
    ProjekteOrdner2->Items->Delete(0);
    for (int a = 0; a < ProjekteOrdner2->Items->Count; a++)
    {
     NebenPfad = ProjekteOrdner2->Items->Strings[a];
     NebenPfad = NebenPfad.SubString(2, NebenPfad.Length());
     NebenPfad = NebenPfad.SubString(0, NebenPfad.Length() - 1);
     ProjekteExplorer->Items->AddChild (Node, NebenPfad);
    }
   }
   MasterNode->Expand(false);
   projectexplorer_dir = project_dir + show_this_one + "\\";
  }
  else
   ProjekteAuswahl->ItemIndex = 0;
 }
 else
 {
  ProjekteExplorer->Enabled = false;
  ProjekteListe->Enabled = false;
  projectexplorer_dir = fileexplorer_dir;
 }
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::BuildFilter(String temp_filter)
{
 //----------------------------------------
 // Erstellt aus Endungen einen Dateifilter
 //----------------------------------------
 String filter_part = "";
 filter_part = "*." + temp_filter;
 filter_part = filter_part.SubString(0, filter_part.Length() - 1);
 filter_part = ReplaceString(filter_part, ";", ";*.", true, true);
 return (" (" + ReplaceString(filter_part, ";", ",", true, true) + ")|" + filter_part);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::FileExecute(String file, String parameters)
{
 //----------------------------------
 // Startet Anwendungen oder Dokumente
 //-----------------------------------
 ShellExecute(Application->MainForm->Handle, NULL, file.c_str(), parameters.c_str(), NULL, SW_SHOW);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::FileSave(TPlusMemo *PlusMemoFileSave, String file, bool append_recent)
{
 //------------------
 // Speichert Dateien
 //------------------
 if (FTPFile(file))
 {
  if (DirectFTPCheckConnection())
  {
   String CompleteServer = "ftp://" + DirektFTPClient->Server;
   String cap = (dynamic_cast<TKindFormular*>((PlusMemoFileSave->Parent)->Parent))->FTPProfil->Caption;
   if (directftp_current_profile == cap)
   {
    String old_path = ReplaceString(DirectFTPURLDecompatible(directftp_current_dir), CompleteServer, "", false, false);
    String new_path = ReplaceString(DirectFTPURLDecompatible(ExtractFilePath(file)), CompleteServer, "", false, false);
    String new_file = ReplaceString(DirectFTPURLDecompatible(file), CompleteServer, "", false, false);
    if (textarea_save_files_in_unix)
     PlusMemoFileSave->LineBreak = pbCR;
    PlusMemoFileSave->Lines->SaveToFile(program_dir + "~temp.html");
    PlusMemoFileSave->LineBreak = pbCRLF;
    DirektFTPClient->PutFile(program_dir + "~temp.html", new_file);
    PlusMemoFileSave->Modified = false;
    if (old_path == new_path)
    {
     if (!DirektFTPListe->FindCaption(0, ExtractFileName(file), false, true, false))
     {
      TListItem  *ListItem;
      ListItem = DirektFTPListe->Items->Add();
      ListItem->Caption = ExtractFileName(file);
      ListItem->SubItems->Add("n/a");
      ListItem->SubItems->Add("n/a");
      ListItem->SubItems->Add("n/a");
      ListItem->ImageIndex = FileCalculateIcon(ExtractFileName(file));
     }
    }
   }
   else
   {
    int close_button = Application->MessageBox(SprachenWaehler->GetStringEx(57, file).c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON2 + MB_ICONQUESTION);
    if (close_button == IDYES)
     return (true);
    else
     return (false);
   }
  }
  else
  {
   int close_button = Application->MessageBox(SprachenWaehler->GetStringEx(56, file).c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON2 + MB_ICONQUESTION);
   if (close_button == IDYES)
    return (true);
   else
    return (false);
  }
 }
 else
 {
  bool datei_wirklich_speichern = false;

  if (FileExists(file))
  {
   int Attrs = FileGetAttr(file);
   if (Attrs & faReadOnly)
   {
    int readonly_button = Application->MessageBox(SprachenWaehler->GetStringEx(13, file).c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON1 + MB_ICONQUESTION);
    if (readonly_button == IDYES)
    {
     Attrs = Attrs & ~faReadOnly;
     FileSetAttr(file, Attrs);
     datei_wirklich_speichern = true;
    }
   }
   else
    datei_wirklich_speichern = true;
  }
  else
   datei_wirklich_speichern = true;

  if (datei_wirklich_speichern)
  {
   FileAppendToFileList(file);
   if (append_recent)
    FileAppendToRecent(file);
   if (textarea_save_files_in_unix)
    PlusMemoFileSave->LineBreak = pbCR;
   PlusMemoFileSave->Lines->SaveToFile(file);
   PlusMemoFileSave->LineBreak = pbCRLF;
   PlusMemoFileSave->Modified = false;
   return (true);
  }
  else
   return (true);
 }
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::FileAppendToFileList(String file)
{
 //-----------------------------------------
 // Fügt eine Datei zu den Dateilisten hinzu
 //-----------------------------------------
 TListItem  *ListItem;

 if (!FileExists(file))
 {
  String file_path = ExtractFilePath(file);
  String file_name = ExtractFileName(file);
  if (AnsiLowerCase(file_path) == AnsiLowerCase(fileexplorer_dir))
  {
   ListItem = DateimanagerListe->Items->Add();
   ListItem->Caption = file_name;
   ListItem->SubItems->Add("n/a");
   ListItem->SubItems->Add("n/a");
   ListItem->SubItems->Add("n/a");
   ListItem->ImageIndex = FileCalculateIcon(file_name);
  }
  //-----------------------------
  if (AnsiLowerCase(file_path) == AnsiLowerCase(projectexplorer_dir))
  {
   ListItem = ProjekteListe->Items->Add();
   ListItem->Caption = file_name;
   ListItem->SubItems->Add("n/a");
   ListItem->SubItems->Add("n/a");
   ListItem->SubItems->Add("n/a");
   ListItem->ImageIndex = FileCalculateIcon(file_name);
  }
  int objects = (StatusLeiste->Panels->Items[2]->Text.SubString(0, StatusLeiste->Panels->Items[2]->Text.AnsiPos(" ") - 1)).ToIntDef(0);
  objects++;
  StatusLeiste->Panels->Items[2]->Text = String(objects) + " " + SprachenWaehler->GetString(28);
 }
}
//---------------------------------------------------------------------------
int __fastcall THauptformular::FileCalculateIcon(String file)
{
 //-----------------------------------------------------
 // Gibt den mit der Datei verknüpften Bild-Index zurück
 //-----------------------------------------------------
 if (DocumentFile(file))
  return (0);
 else if (CSSFile(file))
  return (72);
 else if (JavaScriptFile(file))
  return (105);
 else if (GraphicFile(file))
  return (56);
 else if (MultimediaFile(file))
  return (62);
 else if (AddLangFile(file))
  return (0);
 else
  return (20);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::FileAppendToRecent(String file)
{
 //---------------------------------
 // Fügt die Datei den Recents hinzu
 //---------------------------------
 TempMemo3->Lines->Clear();
 TempMemo3->Lines->LoadFromFile(program_dir + "Storage!\\recent.ini");
 TempMemo3->SelStart = 0;
 if (TempMemo3->FindTxt(file, true, false, false, false))
  TempMemo3->Lines->Delete(TempMemo3->SelLine);
 TempMemo3->Lines->Insert(0, file);
 if (TempMemo3->Lines->Count > 19)
 {
  TempMemo3->Lines->Delete(20);
  TempMemo3->Lines->Delete(21);
  TempMemo3->Lines->Delete(22);
 }
 TempMemo3->Lines->SaveToFile(program_dir + "Storage!\\recent.ini");
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::ButtonsEnable()
{
 //--------------------------------------------------------------------
 // Aktiviert die Buttons, wenn eine oder mehrere Dateien geöffnet sind
 //--------------------------------------------------------------------
 if (MDIChildCount == 1)
 {
  ToolButton3->Enabled = true;
  ToolButton4->Enabled = true;
  ToolButton12->Enabled = false;
  ToolButton13->Enabled = false;
  ToolButton14->Enabled = true;
  ToolButton15->Enabled = false;
  ToolButton16->Enabled = false;
  ToolButton21->Enabled = true;
  ToolButton22->Enabled = true;
  KomponentenLeiste->Enabled = true;
  ToolButton8->Enabled = true;
  ToolButton9->Enabled = true;
  ToolButton6->Enabled = true;
  ToolButton19->Enabled = true;
  ToolButton26->Enabled = true;

  TToolButton* MenueEntry;
  for (int i = 0; i < addlang_langs_count; i++)
  {
   MenueEntry = dynamic_cast<TToolButton *>(FindComponent("AddLangButton" + String(i)));
   MenueEntry->Enabled = true;
  }
 }
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::ButtonsDisable()
{
 //-------------------------------------------------------
 // Deaktiviert die Buttons, wenn keine Datei geöffnet ist
 //-------------------------------------------------------
 if (MDIChildCount == 1)
 {
  ToolButton3->Enabled = false;
  ToolButton4->Enabled = false;
  ToolButton12->Enabled = false;
  ToolButton13->Enabled = false;
  ToolButton14->Enabled = false;
  ToolButton15->Enabled = false;
  ToolButton16->Enabled = false;
  ToolButton21->Enabled = false;
  ToolButton22->Enabled = false;
  KomponentenLeiste->Enabled = false;
  ToolButton8->Enabled = false;
  ToolButton9->Enabled = false;
  ToolButton6->Enabled = false;
  ToolButton19->Enabled = false;
  ToolButton26->Enabled = false;

  TToolButton* MenueEntry;
  for (int i = 0; i < addlang_langs_count; i++)
  {
   MenueEntry = dynamic_cast<TToolButton *>(FindComponent("AddLangButton" + String(i)));
   MenueEntry->Enabled = false;
  }
 }
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::DirectoryFindSubs(String anfangs_verzeichnis, TListBox *DirectorySubsListe)
{
 //-------------------------------------------------------------------------
 // Erstellt eine Liste von einem Verzeichnis und seinen Unterverzeichnissen
 //-------------------------------------------------------------------------
 struct ffblk dirinfo;
 int result;
 if (anfangs_verzeichnis[anfangs_verzeichnis.Length()] != '\\')
  anfangs_verzeichnis += '\\';

 DirectorySubsListe->Items->Add(anfangs_verzeichnis);
 result = findfirst ((anfangs_verzeichnis + "*.*").c_str(), &dirinfo, FA_DIREC);

 while(result == 0)
 {
  if ((dirinfo.ff_attrib & FA_DIREC) && *dirinfo.ff_name != '.')
   DirectoryFindSubs(anfangs_verzeichnis + dirinfo.ff_name, DirectorySubsListe);
  result = findnext(&dirinfo);
 }
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::CSSEditorFileOpen(String file)
{
 //----------------------------------------------
 // Startet den internen oder externen CSS-Editor
 //----------------------------------------------
 if ((use_topstyle == true) && (EnableTopStyleIntegration("Scribe!")) == true)
  tsEditStyleSheet(file, program_dir + "~temp.html");
 else
 {
  css_openfile = file;
  TStyleSheetEditor* StyleSheetEditor = new TStyleSheetEditor(Application);
  SprachenWaehler->SetFormLanguage(StyleSheetEditor);
  StyleSheetEditor->Caption = ReplaceString(StyleSheetEditor1->Caption, "&", "", false, true);
  StyleSheetEditor->ShowModal();
  css_openfile = "";
 }
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::CSSEditorEditStyle(String style)
{
 //----------------------------------------------------------------
 // Editiert eine Style-Angabe im internen oder externen CSS-Editor
 //----------------------------------------------------------------
 if ((use_topstyle == true) && (EnableTopStyleIntegration("Scribe!")) == true)
 {
  tsEditStyleAttribute(style, NULL);
  return (style);
 }
 else
 {
  css_editstyle = style;
  css_edit_editstyle = true;
  TStyleSheetEditor* StyleSheetEditor = new TStyleSheetEditor(Application);
  SprachenWaehler->SetFormLanguage(StyleSheetEditor);
  StyleSheetEditor->Caption = ReplaceString(StyleSheetEditor1->Caption, "&", "", false, true);
  StyleSheetEditor->ShowModal();
  style = css_editstyle;
  css_editstyle = "";
  css_edit_editstyle = false;
  return (style);
 }
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::CSSEditorEditStyleBlock(String style)
{
 //----------------------------------------------------------------
 // Editiert einen Style-Block im internen oder externen CSS-Editor
 //----------------------------------------------------------------
 if ((use_topstyle == true) && (EnableTopStyleIntegration("Scribe!")) == true)
 {
  tsEditStyleBlock(style, NULL);
  return (style);
 }
 else
 {
  css_editstyleblock = style;
  css_edit_editstyleblock = true;
  TStyleSheetEditor* StyleSheetEditor = new TStyleSheetEditor(Application);
  SprachenWaehler->SetFormLanguage(StyleSheetEditor);
  StyleSheetEditor->Caption = ReplaceString(StyleSheetEditor1->Caption, "&", "", false, true);
  StyleSheetEditor->ShowModal();
  style = css_editstyleblock;
  css_editstyleblock = "";
  css_edit_editstyleblock = false;
  return (style);
 }
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::FileCopy(TListBox *FileCopySource, String target_dir)
{
 //-----------------------------------
 // Kopiert Dateien in ein Verzeichnis
 //-----------------------------------
 String From = "";
 int items_count = FileCopySource->Items->Count;

 for (int i = 0; i < items_count; i++)
  From = From + FileCopySource->Items->Strings[i] + "|";
 From = From.SubString(0, From.Length() - 1);
 String Dest = target_dir;

 TSHFileOpStruct *SHFileOpStruct = new TSHFileOpStruct();
 char zFrom[10000];
 char zDest[MAX_PATH+2];
 ZeroMemory(zFrom, sizeof(zFrom));
 ZeroMemory(zDest, sizeof(zDest));
 StrCopy(zFrom, From.c_str());
 for (int i = 0; i < sizeof(zFrom); i++)
 {
  if (zFrom[i] == '|')
   zFrom[i] = '\0';
 }
 StrCopy(zDest, Dest.c_str());
 for (int i = 0; i < sizeof(zDest); i++)
 {
  if (zDest[i] == '|')
   zDest[i] = '\0';
 }
 SHFileOpStruct->hwnd  = ::GetActiveWindow();
 SHFileOpStruct->wFunc = FO_COPY;
 SHFileOpStruct->pFrom = zFrom;
 SHFileOpStruct->pTo   = zDest;
 SHFileOpStruct->fFlags = NULL;
 SHFileOperation(SHFileOpStruct);
 delete SHFileOpStruct;
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::FileCopyOnlyOne(String file_1, String file_2)
{
 //--------------------------------------
 // Kopiert eine Datei in ein Verzeichnis
 //--------------------------------------
 String From = "";
 String Dest = "";
 bool result = false;

 From = From + file_1 + "|";
 From = From.SubString(0, From.Length() - 1);

 Dest = Dest + file_2 + "|";
 Dest = Dest.SubString(0, Dest.Length() - 1);

 TSHFileOpStruct *SHFileOpStruct = new TSHFileOpStruct();
 char zFrom[800];
 char zDest[800];

 ZeroMemory(zFrom, sizeof(zFrom));
 ZeroMemory(zDest, sizeof(zDest));

 StrCopy(zFrom, From.c_str());
 for (int i = 0; i < sizeof(zFrom); i++)
 {
  if (zFrom[i] == '|')
   zFrom[i] = '\0';
 }
 StrCopy(zDest, Dest.c_str());
 for (int i = 0; i < sizeof(zDest); i++)
 {
  if (zDest[i] == '|')
   zDest[i] = '\0';
 }
 SHFileOpStruct->hwnd  = ::GetActiveWindow();
 SHFileOpStruct->wFunc = FO_COPY;
 SHFileOpStruct->pFrom = zFrom;
 SHFileOpStruct->pTo   = zDest;
 SHFileOpStruct->fFlags = NULL;
 if (SHFileOperation(SHFileOpStruct) == 0)
  result = true;
 else
  result = false;
 delete SHFileOpStruct;
 return (result);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::FileDelete(TListBox *FileDeleteSource, bool silent)
{
 //---------------
 // Löscht Dateien
 //---------------
 String From = "";
 int items_count = FileDeleteSource->Items->Count;

 for (int i = 0; i < items_count; i++)
  From = From + FileDeleteSource->Items->Strings[i] + "|";
 From = From.SubString(0, From.Length() - 1);

 TSHFileOpStruct *SHFileOpStruct = new TSHFileOpStruct();
 char zFrom[10000];
 ZeroMemory(zFrom, sizeof(zFrom));
 StrCopy(zFrom, From.c_str());
 for (int i = 0; i < sizeof(zFrom); i++)
 {
  if (zFrom[i] == '|')
   zFrom[i] = '\0';
 }
 SHFileOpStruct->hwnd  = ::GetActiveWindow();
 SHFileOpStruct->wFunc = FO_DELETE;
 SHFileOpStruct->pFrom = zFrom;
 SHFileOpStruct->pTo   = NULL;
 if (silent)
  SHFileOpStruct->fFlags = FOF_ALLOWUNDO + FOF_NOCONFIRMATION;
 else
  SHFileOpStruct->fFlags = FOF_ALLOWUNDO;
 SHFileOperation(SHFileOpStruct);
 delete SHFileOpStruct;
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::FileDeleteOnlyOne(String file, bool silent)
{
 //------------------
 // Löscht eine Datei
 //------------------
 String From = "";
 bool result = false;

 From = From + file + "|";
 From = From.SubString(0, From.Length() - 1);

 TSHFileOpStruct *SHFileOpStruct = new TSHFileOpStruct();
 char zFrom[800];
 ZeroMemory(zFrom, sizeof(zFrom));
 StrCopy(zFrom, From.c_str());
 for (int i = 0; i < sizeof(zFrom); i++)
 {
  if (zFrom[i] == '|')
   zFrom[i] = '\0';
 }
 SHFileOpStruct->hwnd  = ::GetActiveWindow();
 SHFileOpStruct->wFunc = FO_DELETE;
 SHFileOpStruct->pFrom = zFrom;
 SHFileOpStruct->pTo   = NULL;
 if (silent)
  SHFileOpStruct->fFlags = FOF_ALLOWUNDO + FOF_NOCONFIRMATION;
 else
  SHFileOpStruct->fFlags = FOF_ALLOWUNDO;
 if (SHFileOperation(SHFileOpStruct) == 0)
  result = true;
 else
  result = false;
 delete SHFileOpStruct;
 return (result);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::FileRename(String vorher, String nachher)
{
 //-------------------
 // Benennt Dateien um
 //-------------------
 String From = vorher;
 String Dest = nachher;
 bool result = false;

 TSHFileOpStruct *SHFileOpStruct = new TSHFileOpStruct();
 char zFrom[MAX_PATH+2];
 char zDest[MAX_PATH+2];
 ZeroMemory(zFrom, sizeof(zFrom));
 ZeroMemory(zDest, sizeof(zDest));
 StrCopy(zFrom, From.c_str());
 StrCopy(zDest, Dest.c_str());
 SHFileOpStruct->hwnd  = ::GetActiveWindow();
 SHFileOpStruct->wFunc = FO_RENAME;
 SHFileOpStruct->pFrom = zFrom;
 SHFileOpStruct->pTo   = zDest;
 SHFileOpStruct->fFlags = NULL;
 if (SHFileOperation(SHFileOpStruct) == 0)
  result = true;
 else
  result = false;
 delete SHFileOpStruct;
 return (result);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::DirectoryDelete(String dir)
{
 //-----------------------
 // Löscht ein Verzeichnis
 //-----------------------
 dir = dir.SubString(0, dir.Length() - 1);

 bool result;
 char zFrom[MAX_PATH+2];

 TSHFileOpStruct *SHFileOpStruct = new TSHFileOpStruct();
 ZeroMemory(zFrom, sizeof(zFrom));
 StrCopy(zFrom, dir.c_str());
 SHFileOpStruct->hwnd = ::GetActiveWindow();
 SHFileOpStruct->wFunc = FO_DELETE;
 SHFileOpStruct->pFrom = zFrom;
 SHFileOpStruct->pTo = NULL;
 SHFileOpStruct->fFlags = FOF_ALLOWUNDO + FOF_NOCONFIRMATION;
 if (SHFileOperation(SHFileOpStruct) == 0)
  result = true;
 else
  result = false;
 delete SHFileOpStruct;
 return (result);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::ColorColorToXHTMLCode(TColor ColorValue)
{
 //------------------------------------------------------------------
 // Wandelt Farbwert (TColor) in hexadezimalen Code bzw. Farbnamen um
 //------------------------------------------------------------------
  String ColStr = IntToHex(ColorToRGB(ColorValue), 6);
  ColStr = "#" + ColStr.SubString(5,2) + ColStr.SubString(3,2) + ColStr.SubString(1,2);
  if (use_color_names)
  {
   if (ColorXHTMLCodes->Items->IndexOf(ColStr) > -1)
    ColStr = ColorColorNames->Items->Strings[ColorXHTMLCodes->Items->IndexOf(ColStr)];
  }
  return (ColStr);
}
//---------------------------------------------------------------------------
TColor __fastcall THauptformular::ColorXHTMLCodeToColor(String ColorValue)
{
 //------------------------------------------------------------------
 // Wandelt hexadezimalen Code bzw. Farbnamen in Farbwert (TColor) um
 //------------------------------------------------------------------
 String ColStr;
 if (ColorColorNames->Items->IndexOf(ColorValue) > -1)
  ColStr = ColorXHTMLCodes->Items->Strings[ColorColorNames->Items->IndexOf(ColorValue)];
 else
  ColStr = ColorValue;

 ColStr = ReplaceString(ColStr, "#", "", true, true);

 try
 {
  String temp_str = ColStr;
  String right = temp_str.SubString(5, 2);
  String left = temp_str.SetLength(2);
  ColStr = ColStr.SubString(3, 2);
  ColStr = right + ColStr + left;
  ColStr = "0x00" + ColStr;
  return (StringToColor(ColStr));
 }
 catch (...)
 {
  Application->MessageBox(SprachenWaehler->GetString(90).c_str(), "Scribe!", MB_OK + MB_ICONERROR);
  ColStr = "0x00000000";
  return (StringToColor(ColStr));
 }
}
//---------------------------------------------------------------------------
TColor __fastcall THauptformular::ColorWindowsDialogShow(TColor ColorValue)
{
 //-----------------------------------
 // Zeigt den Windows - Colordialog an
 //-----------------------------------
 ColorSetUserDefined(GemeinsamerFarbDialog);
 GemeinsamerFarbDialog->Color = ColorValue;
 if (GemeinsamerFarbDialog->Execute())
 {
  ColorReadUserDefined(GemeinsamerFarbDialog);
  return (GemeinsamerFarbDialog->Color);
 }
 else
  return (ColorValue);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::HelpShow(TForm *SubmittedHelpForm, String hilfe_datei, bool dockit)
{
 //-----------------------------------------------------------
 // Zeigt die Hilfe-Datei im internen oder externen Browser an
 //-----------------------------------------------------------
 hilfe_datei = program_dir + "Storage!\\Help\\" + hilfe_datei;

 wchar_t hilfe_temp[400];
 StringToWideChar(hilfe_datei, hilfe_temp, 400);

 if (msie_installed)
 {
  if ((dockit) && (help_dock_window))
  {
   SubmittedHelpForm->Left = (Screen->Width  / 2) - (SubmittedHelpForm->Width / 2);
   SubmittedHelpForm->Top = (Screen->Height  / 2) - (SubmittedHelpForm->Height / 2);
   Hilfe->ControlBar1->Visible = false;
   if (help_align == "left")
   {
    SubmittedHelpForm->Left = SubmittedHelpForm->Left + (help_size / 2);
    Hilfe->Left = SubmittedHelpForm->Left - help_size;
    Hilfe->Width = help_size;
    Hilfe->Top = SubmittedHelpForm->Top;
    Hilfe->Height = SubmittedHelpForm->Height;
   }
   else if (help_align == "top")
   {
    SubmittedHelpForm->Top = SubmittedHelpForm->Top + (help_size / 2);
    Hilfe->Top = SubmittedHelpForm->Top - help_size;
    Hilfe->Width = SubmittedHelpForm->Width;
    Hilfe->Left = SubmittedHelpForm->Left;
    Hilfe->Height = help_size;
   }
   else if (help_align == "bottom")
   {
    SubmittedHelpForm->Top = SubmittedHelpForm->Top - (help_size / 2);
    Hilfe->Top = SubmittedHelpForm->Top + SubmittedHelpForm->Height;
    Hilfe->Width = SubmittedHelpForm->Width;
    Hilfe->Left = SubmittedHelpForm->Left;
    Hilfe->Height = help_size;
   }
   else
   {
    SubmittedHelpForm->Left = SubmittedHelpForm->Left - (help_size / 2);
    Hilfe->Left = SubmittedHelpForm->Left + SubmittedHelpForm->Width;
    Hilfe->Width = help_size;
    Hilfe->Top = SubmittedHelpForm->Top;
    Hilfe->Height = SubmittedHelpForm->Height;
   }
  }
  else
  {
   if ((dockit) && (!help_dock_window))
    Hilfe->ControlBar1->Visible = false;
   else
    Hilfe->ControlBar1->Visible = true;
   Hilfe->Top = help_window_top;
   Hilfe->Left = help_window_left;
   Hilfe->Height = help_window_height;
   Hilfe->Width = help_window_width;
  }
  Hilfe->Caption = SprachenWaehler->GetString(27) + "...";
  msie_helpbrowser->Navigate(hilfe_temp);
  Hilfe->Show();
 }
 else
 {
  String browser = browser_path_1;
  hilfe_datei = ReplaceString(hilfe_datei, "\\", "/", true, true);
  hilfe_datei = "file:///" + hilfe_datei;
  FileExecute(browser, hilfe_datei);
 }
}

//---------------------------------------------------------------------------
void __fastcall THauptformular::HelpKeywordShow(String keyword)
{
 HelpShow(this, keyword, false);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::InternalBrowserShow(String datei)
{
 //----------------------------------------
 // Zeigt eine Datei im internen Browser an
 //----------------------------------------
 if (FTPFile(datei))
  datei = ReplaceString(datei, "ftp://", "http://", true, true);
 else
 {
  datei = ReplaceString(datei, "\\", "/", true, true);
  datei = "file:///" + datei;
 }

 if (localhost_use)
 {
  String temp_project_dir;
  temp_project_dir = "file:///" + ReplaceString(project_dir, "\\", "/", true, true);
  if (AnsiPos(AnsiLowerCase(temp_project_dir), AnsiLowerCase(datei)))
   datei = ReplaceString(datei, temp_project_dir, localhost_adress, true, true);
 }

 InternerBrowser->Ursprung->Caption = datei;
 wchar_t temp[400];
 StringToWideChar(datei, temp, 400);
 msie_previewbrowser->Navigate(temp);
 InternerBrowser->Caption = SprachenWaehler->GetString(30) + "...";
 InternerBrowser->Show();
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::BrowserShow(int b_index, String datei)
{
 //--------------------------------------------
 // Zeigt eine Datei im Browser (1,2 oder 3) an
 //--------------------------------------------
 if (FTPFile(datei))
  datei = ReplaceString(datei, "ftp://", "http://", true, true);
 else
 {
  datei = ReplaceString(datei, "\\", "/", true, true);
  datei = "file:///" + datei;
 }

 if (localhost_use)
 {
  String temp_project_dir;
  temp_project_dir = "file:///" + ReplaceString(project_dir, "\\", "/", true, true);
  if (AnsiPos(AnsiLowerCase(temp_project_dir), AnsiLowerCase(datei)))
   datei = ReplaceString(datei, temp_project_dir, localhost_adress, true, true);
 }

 String browser = browser_path_1;
 if (b_index == 1)
  browser = browser_path_1;
 else if (b_index == 2)
  browser = browser_path_2;
 else if (b_index == 3)
  browser = browser_path_3;
 FileExecute(browser, datei);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::FileAskSave(TPlusMemo *PlusMemoFileAskSave, String datei)
{
 //---------------------------------------------
 // Fragt, ob eine Datei gespeichert werden soll
 //---------------------------------------------
 int save_button = Application->MessageBox(SprachenWaehler->GetStringEx(31, datei).c_str(), "Scribe!", MB_YESNOCANCEL + MB_DEFBUTTON1 + MB_ICONQUESTION);
 if (save_button == IDCANCEL)
  return (false);
 else if (save_button == IDYES)
 {
  return (FileSave(PlusMemoFileAskSave, datei, true));
 }
 else
  return (true);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::DirectFTPLoadProfiles(String profil)
{
 //---------------------
 // Lädt FTP-Profile ein
 //---------------------
 DirektFTPAuswahl->Items->Clear();
 TIniFile* Profile = new TIniFile(program_dir + "Storage!\\ftpprofiles.ini");
 Profile->ReadSections(DirektFTPAuswahl->Items);
 delete Profile;
 DirektFTPAuswahl->Items->Insert(0, SprachenWaehler->GetString(4));

 if (DirektFTPAuswahl->Items->IndexOf(profil) > -1)
 {
  DirektFTPAuswahl->ItemIndex = DirektFTPAuswahl->Items->IndexOf(profil);
  if (DirektFTPAuswahl->ItemIndex != 0)
  {
   DirektFTPExplorer->Enabled = true;
   DirektFTPListe->Enabled = true;
   directftp_current_profile = "";
  }
  else
  {
   DirektFTPExplorer->Enabled = false;
   DirektFTPListe->Enabled = false;
   directftp_current_profile = "";
  }
 }
 else
 {
  DirektFTPAuswahl->ItemIndex = 0;
  DirektFTPExplorer->Enabled = false;
  DirektFTPListe->Enabled = false;
  directftp_current_profile = "";
 }
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::Base64Decode(String slToDec)
{
 //------------------------
 // Decodiert Zeichenketten
 //------------------------
 if (slToDec == "")
  return ("");
 const char Base64Table[64] = "Z8YDEzhgGs3QkWP7uRqVATfo1pntxLw2UNMvHFI4OBC56-amJ0jdXKyl9Scribe!";
 char * buftodec = slToDec.c_str();
 int bufsize = slToDec.Length() + 1;
 char * decbuf = new char[slToDec.Length() * 5];
 decbuf[0] = '\0';
 int ilStrLen = -1;
 String slRetVal = EmptyStr;

 int i = 0;
 unsigned char binbyte[4];
 int cpos[5];
 unsigned char *buftemp;
 buftemp = (unsigned char *) malloc(bufsize);
 strcpy(buftemp, buftodec);
 if (fmod(bufsize, 4) == 1)
 {
  buftemp[bufsize] = '\0';
  buftemp[bufsize + 1] = '\0';
  buftemp[bufsize + 2] = '\0';
 }
 if (fmod(bufsize, 4) == 2)
 {
  buftemp[bufsize] = '\0';
  buftemp[bufsize + 1] = '\0';
 }

 if (fmod(bufsize, 4) == 3)
  buftemp[bufsize] = '\0';
 while (i < bufsize)
 {
  cpos[0] = strchr(Base64Table, buftemp[i]) - Base64Table;
  cpos[1] = strchr(Base64Table, buftemp[i + 1]) - Base64Table;
  cpos[2] = strchr(Base64Table, buftemp[i + 2]) - Base64Table;
  cpos[3] = strchr(Base64Table, buftemp[i + 3]) - Base64Table;
  binbyte[0] = ((cpos[0] << 2) | (cpos[1] >> 4));
  binbyte[1] = ((cpos[1] << 4) | (cpos[2] >> 2));
  binbyte[2] = (((cpos[2] & 0x03) << 6) | (cpos[3] & 0x3f));
  decbuf[i -(i / 4)] = binbyte[0];
  decbuf[i -(i / 4) + 1] = binbyte[1];
  decbuf[i -(i / 4) + 2] = binbyte[2];
  i += 4;
 }
 free(buftemp);
 if (fmod(bufsize,4) == 0)
  ilStrLen = bufsize * 6 / 8;
 else if (fmod(bufsize, 4) == 1)
  ilStrLen = ((bufsize + 3) * 6 / 8) - 3;
 else if (fmod(bufsize, 4) == 2)
  ilStrLen = ((bufsize + 2) * 6 / 8) - 2;
 else if (fmod(bufsize, 4) == 3)
  ilStrLen = ((bufsize + 1)* 6 / 8 ) - 1;
 else
  ilStrLen = -1;

 if (ilStrLen > 0)
  slRetVal = AnsiString(decbuf).SubString(1, ilStrLen);
 if (decbuf != NULL)
 {
  delete decbuf;
  decbuf = NULL;
 }
 return slRetVal;
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::Base64Encode(String slToEnc)
{
 //------------------------
 // Encodiert Zeichenketten
 //------------------------
 if (slToEnc == "")
  return ("");
 const char Base64Table[64] = "Z8YDEzhgGs3QkWP7uRqVATfo1pntxLw2UNMvHFI4OBC56-amJ0jdXKyl9Scribe!";
 char * buftoenc = slToEnc.c_str();
 int bufsize = slToEnc.Length() + 1;
 char * encbuf = new char[slToEnc.Length() * 5];
 encbuf[0] = '\0';
 int ilStrLen = -1;
 int i = 0;
 int b64byte[5];
 unsigned char *buftemp;
 String slRetVal = EmptyStr;

 buftemp = (unsigned char *) malloc(bufsize + 2);
 strcpy(buftemp, buftoenc);
 if (fmod(bufsize, 3) == 1)
 {
  buftemp[bufsize] = '\0';
  buftemp[bufsize + 1] = '\0';
 }
 if (fmod(bufsize, 3) == 2)
  buftemp[bufsize] = '\0';

 while (i < bufsize)
 {
  b64byte[0] = buftemp[i] >> 2;
  b64byte[1] = ((buftemp[i] & 3) << 4) | (buftemp[i + 1] >> 4);
  b64byte[2] = ((buftemp[i + 1] & 0x0F) << 2) | (buftemp[i + 2] >> 6);
  b64byte[3] = buftemp[i + 2] & 0x3F;
  encbuf[i + (i / 3)] = Base64Table[b64byte[0]];
  encbuf[i + (i / 3) + 1] = Base64Table[b64byte[1]];
  encbuf[i + (i / 3) + 2] = Base64Table[b64byte[2]];
  encbuf[i + (i / 3) + 3] = Base64Table[b64byte[3]];
  i += 3;
 }
 free(buftemp);
 if (fmod(bufsize, 3) == 0)
  ilStrLen = bufsize * 8 / 6;
 else if (fmod(bufsize, 3) == 1)
  ilStrLen = ((bufsize + 2) * 8 / 6 ) - 2;
 else if (fmod(bufsize, 3) == 2)
  ilStrLen = ((bufsize + 1) * 8 / 6) - 1;
 else
  ilStrLen = -1;
 if (ilStrLen > 0)
  slRetVal = String(encbuf).SubString(1, ilStrLen);
 if (encbuf != NULL)
 {
  delete encbuf;
  encbuf = NULL;
 }
 return slRetVal;
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::ConvertDateToDatum(String date)
{
 //-------------------------------------------------------
 // Konvertiert das englische in das deutsche Datumsformat
 //-------------------------------------------------------
 String datum = date.SubString(0, AnsiPos(" ", date) - 1);
 String zeit = date.SubString(AnsiPos(" ", date) + 1, 50);
 String tag;
 String monat;
 String jahr;

 monat = datum.SubString(1, AnsiPos("/", datum) - 1);
 if (monat.Length() == 1)
  monat = "0" + monat;
 datum = datum.SubString(AnsiPos("/", datum) + 1, 100);
 tag = datum.SubString(1, AnsiPos("/", datum) - 1);
 if (tag.Length() == 1)
  tag = "0" + tag;
 datum = datum.SubString(AnsiPos("/", datum) + 1, 100);
 jahr = datum;
 date = tag + "." + monat + "." + jahr + " " + zeit;
 return (date);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::DirectFTPURLCompatible(String url)
{
 //----------------------------------
 // Macht eine URL Scribe!-kompatibel
 //----------------------------------
 url = ReplaceString(url, "ftp://", "", true, true);
 url = ReplaceString(url, "/", "\\", true, true);
 url = "ftp://" + url;
 return (url);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::DirectFTPURLDecompatible(String url)
{
 //-----------------------------------------
 // Macht eine Scribe!-kompatible URL normal
 //-----------------------------------------
 url = ReplaceString(url, "ftp://", "", true, true);
 url = ReplaceString(url, "\\", "/", true, true);
 url = "ftp://" + url;
 return (url);
}
/*int ilFilesCount, ilStrLength;
 char caFileName[MAX_PATH];

 ilFilesCount = DragQueryFile((HDROP)Msg.Drop, -1, NULL, 0);
 TempDateiOperationenKopierenExplorer->Items->Clear();
 TempDateiOperationenKopierenExplorer->Items = TempDateiOperationenKopieren->Items;
 TempDateiOperationenKopieren->Items->Clear();
 for (int ilIndex = 0; ilIndex < ilFilesCount; ilIndex++)
 {
  ilStrLength = DragQueryFile((HDROP)Message.Drop, ilIndex, NULL, 0);
  DragQueryFile((HDROP)Message.Drop, ilIndex, caFileName, ilStrLength + 1);
  TempDateiOperationenKopieren->Items->Add(caFileName);
 }
 if (VerwControl->ActivePage == VerwTab1)
  Einfgen2Click(this);
 else if (VerwControl->ActivePage == VerwTab2)
  Einfgen3Click(this);
 else if (VerwControl->ActivePage == VerwTab3)
  Einfgen4Click(this);
 TempDateiOperationenKopieren->Items->Clear();
 TempDateiOperationenKopieren->Items = TempDateiOperationenKopierenExplorer->Items;*/
//---------------------------------------------------------------------------
void __fastcall THauptformular::WebBrowserProgressChange(TObject *Sender, long Progress, long ProgressMax)
{
 //--------------------------------------------------
 // Zeigt den Fortschritt des Ladevorgangs im Browser
 //--------------------------------------------------
 if (Progress > -1 && ProgressMax > 0)
  InternerBrowser->StatusBar1->Panels->Items[0]->Text = FloatToStrF(Progress * 100.0/ProgressMax, ffFixed, 15, 0) + " %";
 else
  InternerBrowser->StatusBar1->Panels->Items[0]->Text = "100 %";
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::WebBrowserDocumentComplete(TObject *Sender, LPDISPATCH pDisp, TVariant* URL)
{
 //--------------------------------------------
 // Reagiert, wenn Dokument vollständig geladen
 //--------------------------------------------
 InternerBrowser->StatusBar1->Panels->Items[1]->Text = msie_previewbrowser->LocationURL;
 InternerBrowser->Edit1->Text = msie_previewbrowser->LocationURL;
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::TagInsert(String start_tag, String end_tag)
{
 //-------------------
 // Fügt einen Tag ein
 //-------------------
 long int temp_1, temp_2, start;
 String selected_text;

 if (MDIChildCount)
 {
  if (tag_currently_editing)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ClearSelection();

  selected_text = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;

  if (tag_php_compatible)
  {
   start_tag = ReplaceString(start_tag, "\"", "\\\"", true, true);
   end_tag = ReplaceString(end_tag, "\"", "\\\"", true, true);
  }

  if (start_tag != "")
   start = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + start_tag.Length();
  else
   start = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + end_tag.Length();

  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength != 0)
  {
   temp_1 = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
   temp_2 = (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength);
  }
  else
   temp_1 = -1;

  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = start_tag;
  if (temp_1 != -1)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = selected_text;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = end_tag;

  if (temp_1 != -1)
  {
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = temp_1 + start_tag.Length();
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = temp_2;
  }
  else
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = start;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::DirectorySameAndRelative(String file)
{
 //--------------------------------------------------------------------------
 // Überprüft, ob sich Datei im gleichen oder untergeordnetem Ordner befindet
 // Berechnet den relativen Pfad
 //--------------------------------------------------------------------------
 if (MDIChildCount)
 {
  if (!FTPFile(ActiveMDIChild->Caption))
  {
   if (!DirectorySame(file))
   {
    int save_button = Application->MessageBox(SprachenWaehler->GetString(64).c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON1 + MB_ICONQUESTION);
    if (save_button == IDNO)
     return(file);
    else
     return(DirectoryRelativePath(DirectoryWrongPath(file)));
   }
   else
    return(DirectoryRelativePath(file));
  }
  else
   return (file);
 }
 else
  return(DirectoryRelativePath(file));
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::DirectoryRelativePath(String file)
{
 //-----------------------------
 // Berechnet den relativen Pfad
 //-----------------------------
 String all;
 String temp_str = ExtractFilePath(ActiveMDIChild->Caption);
 String temp_str2 = ExtractFileName(file);
 file = ExtractFilePath(file);

 if (temp_str == file)
  return (temp_str2);
 else
 {
  all = ExtractRelativePath(temp_str, file) + temp_str2;
  all = ReplaceString(all, "\\", "/", true, true);
  return (all);
 }
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::DirectorySame(String file)
{
 //--------------------------------------------------------------------------
 // Überprüft, ob sich Datei im gleichen oder untergeordnetem Ordner befindet
 //--------------------------------------------------------------------------
 if (MDIChildCount)
 {
  if (!AnsiPos("\\Storage!\\", file))
  {
   String temp_str = ActiveMDIChild->Caption;
   String temp_project_dir = project_dir.SubString(0, project_dir.Length() - 1);

   if (AnsiPos(temp_project_dir, temp_str))
   {
    temp_str = ExtractFilePath(temp_str);
    temp_str =  ReplaceString(temp_str, temp_project_dir, "", true, true);
    temp_str = temp_str.SubString(2, temp_str.Length());
    temp_str = temp_str.SubString(0, temp_str.Length() - 1);

    if (AnsiPos("\\", temp_str))
     temp_str = temp_str.SubString(0, (AnsiPos("\\", temp_str) - 1));
    temp_str = temp_project_dir + "\\" + temp_str;
    if (!AnsiPos(AnsiLowerCase(temp_str), AnsiLowerCase(file)))
     return (false);
    else
     return (true);
   }
   else
    return (true);
  }
  else
   return (false);
 }
 else
  return (false);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::DirectoryWrongPath(String file)
{
 //-------------------------------------------------
 // Soll Dateien in das richige Verzeichnis kopieren
 //-------------------------------------------------
 String filter_temp = SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 String filter_gesamt = filter_gesamt + filter_temp;

 do
 {
  DirectoryWrongPathDialog->FileName = ExtractFileName(file);
  DirectoryWrongPathDialog->InitialDir = ExtractFilePath(ActiveMDIChild->Caption);
  DirectoryWrongPathDialog->Filter = filter_gesamt;
  DirectoryWrongPathDialog->Title = ReplaceString(Speichernunter1->Caption, "&", "", false, true);
  if (DirectoryWrongPathDialog->Execute())
   FileCopyOnlyOne(file, DirectoryWrongPathDialog->FileName);
  else
   return ("");
 }
 while (!DirectorySame(DirectoryWrongPathDialog->FileName));
 FileAppendToFileList(DirectoryWrongPathDialog->FileName);
 return (DirectoryWrongPathDialog->FileName);
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::TagInsertAndFindPosition(String tag, String end_tag, String location, String alternative)
{
 //-----------------------------------------------
 // Fügt Tags ein und positioniert sie automatisch
 //-----------------------------------------------
 int ursprung = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;

 if (tag_automatic_position)
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt(location, true, false, false, false))
  {
   int sel_line = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine;
   int sel_start = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;

   if (tag_php_compatible)
   {
    tag = ReplaceString(tag, "\"", "\\\"", true, true);
    end_tag = ReplaceString(end_tag, "\"", "\\\"", true, true);
   }

   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Insert(sel_line, tag + end_tag);
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = sel_start + tag.Length() - location.Length();
  }
  else
  {
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = ursprung;
   TagInsert(tag, end_tag);
  }
 }
 else
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = ursprung;
  TagInsert(tag, end_tag);
 }
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::ButtonxListItems()
{
 //----------------------
 // Erstellt die Buttonx!
 //----------------------
 ButtonxControl->Tabs->Clear();
 TIniFile* Buttonx = new TIniFile(program_dir + "Storage!\\buttonx.ini");
 Buttonx->ReadSections(ButtonxControl->Tabs);
 delete Buttonx;
 ButtonxControl->TabIndex = -1;
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::ButtonxEngine(String code)
{
 //------------------
 // Buttonx! - Engine
 //------------------
 code = ReplaceString(code, "#Br", "\r\n",  true, false);
 code = ReplaceString(code, "#SelText", ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText, true, false);
 code = ReplaceString(code, "#ProgramPath", program_dir, true, false);
 code = ReplaceString(code, "#ProgramVersion", program_version, true, false);
 code = ReplaceString(code, "#Year/S", (TDateTime().CurrentDate()).FormatString("yy"), true, false);
 code = ReplaceString(code, "#Year", (TDateTime().CurrentDate()).FormatString("yyyy"), true, false);
 code = ReplaceString(code, "#MonthN/S", (TDateTime().CurrentDate()).FormatString("mmm"), true, false);
 code = ReplaceString(code, "#MonthN", (TDateTime().CurrentDate()).FormatString("mmmm"), true, false);
 code = ReplaceString(code, "#Month/S", (TDateTime().CurrentDate()).FormatString("m"), true, false);
 code = ReplaceString(code, "#Month", (TDateTime().CurrentDate()).FormatString("mm"), true, false);
 code = ReplaceString(code, "#DayN/S", (TDateTime().CurrentDate()).FormatString("ddd"), true, false);
 code = ReplaceString(code, "#DayN", (TDateTime().CurrentDate()).FormatString("dddd"), true, false);
 code = ReplaceString(code, "#Day/S", (TDateTime().CurrentDate()).FormatString("d"), true, false);
 code = ReplaceString(code, "#Day", (TDateTime().CurrentDate()).FormatString("dd"), true, false);
 code = ReplaceString(code, "#Hour/S", (TDateTime().CurrentTime()).FormatString("h"), true, false);
 code = ReplaceString(code, "#Hour", (TDateTime().CurrentTime()).FormatString("hh"), true, false);
 code = ReplaceString(code, "#Min/S", (TDateTime().CurrentTime()).FormatString("n"), true, false);
 code = ReplaceString(code, "#Min", (TDateTime().CurrentTime()).FormatString("nn"), true, false);
 code = ReplaceString(code, "#Sec/S", (TDateTime().CurrentTime()).FormatString("s"), true, false);
 code = ReplaceString(code, "#Sec", (TDateTime().CurrentTime()).FormatString("ss"), true, false);

 if (AnsiPos("#LoadFile[", code))
 {
  String temp_str, temp_str2;
  int pos_1 = AnsiPos("#LoadFile[", code);
  pos_1 += 10;
  temp_str = code;
  temp_str = temp_str.SubString(pos_1, temp_str.Length());
  int pos2 = AnsiPos("]", temp_str);
  temp_str = temp_str.SubString(0, pos2 - 1);
  temp_str2 = temp_str;
  temp_str2 = "#LoadFile[" + temp_str2 + "]";
  TempMemo->Clear();
  try
  {
   TempMemo->Lines->LoadFromFile(temp_str);
   TempMemo->SelectAll();
   temp_str = TempMemo->SelText;
  }
  catch (...)
  {
   temp_str = "";
  }
  code = ReplaceString(code, temp_str2, temp_str, true, false);
 }
 return (code);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::TagInIt()
{
 //-------------------
 // Im Tag oder nicht?
 //-------------------
 String line = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Strings[((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine];
 int position = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol;
 int part_pos = 0;
 String right_part = "";
 String left_part = "";
 String all = "";
 String part = "";
 bool abort = false;

 if (Trim(line) != "")
 {
  if (AnsiPos("<", line))
  {
   if (AnsiPos(">", line))
   {
    right_part = line.SubString(position + 1, line.Length());
    if (AnsiPos(">", right_part))
    {
     while (!abort)
     {
      part = right_part.SubString(part_pos, 1);
      if (part == ">")
      {
       right_part = right_part.SubString(0, part_pos);
       abort = true;
      }
      else if (part == "<")
       return (false);
      else
       part_pos++;
     }
     left_part = line.SubString(0, position);
     if (AnsiPos("<", left_part))
     {
      abort = false;
      part = "";
      part_pos = position;
      while (!abort)
      {
       part = left_part.SubString(part_pos, 1);
       if (part == "<")
       {
        left_part = left_part.SubString(part_pos, left_part.Length() - part_pos + 1);
        abort = true;
       }
       else if (part == ">")
        return (false);
       else
        part_pos--;
      }
      if (!AnsiPos(">", right_part))
       right_part += ">";
      all = left_part + right_part;
      if (AnsiPos("<", all) && AnsiPos(">", all))
       return (true);
      else
       return (false);
     }
     else
      return (false);
    }
    else
     return (false);
   }
   else
    return (false);
  }
  else
   return (false);
 }
 else
  return (false);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::TagCurrent()
{
 //---------------------------------
 // Liefert den aktuellen Tag zurück
 //---------------------------------
 String line = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Strings[((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine];
 int position = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol;
 int part_pos = 0;
 String right_part = "";
 String left_part = "";
 String all = "";
 String part = "";
 bool abort = false;

 if (Trim(line) != "")
 {
  if (AnsiPos("<", line))
  {
   if (AnsiPos(">", line))
   {
    right_part = line.SubString(position + 1, line.Length());
    if (AnsiPos(">", right_part))
    {
     while (!abort)
     {
      part = right_part.SubString(part_pos, 1);
      if (part == ">")
      {
       right_part = right_part.SubString(0, part_pos);
       abort = true;
      }
      else if (part == "<")
      {
       right_part = "";
       abort = true;
      }
      else
       part_pos++;
     }
     left_part = line.SubString(0, position);
     if (AnsiPos("<", left_part))
     {
      abort = false;
      part = "";
      part_pos = position;
      while (!abort)
      {
       part = left_part.SubString(part_pos, 1);
       if (part == "<")
       {
        left_part = left_part.SubString(part_pos, left_part.Length() - part_pos + 1);
        abort = true;
       }
       else if (part == ">")
       {
        left_part = "";
        abort = true;
       }
       else
        part_pos--;
      }
      if (!AnsiPos(">", right_part))
       right_part += ">";
      all = left_part + right_part;
      if (AnsiPos("<", all) && AnsiPos(">", all))
      {
       tag_sel_position = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart - (position - part_pos);
       tag_sel_position--;
       return (all);
      }
      else
       return ("");
     }
     else
      return ("");
    }
    else
     return ("");
   }
   else
    return ("");
  }
  else
   return ("");
 }
 else
  return ("");
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::TagAppendAttribute(String attr)
{
 //--------------------------------
 // Hängt ein Attribut an einen Tag
 //--------------------------------
 TempMemo->Lines->Clear();
 String line;
 String temp_str;
 line = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Strings[((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine];
 TempMemo->Lines->Add(line);
 TempMemo->SelStart = 0;
 TempMemo->SelCol = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol;
 TempMemo->FindTxt(">", true, false, false, false);
 TempMemo->SelCol = TempMemo->SelCol - 3;
 TempMemo->SelLength = 3;
 temp_str = TempMemo->SelText;

 if (temp_str == " />")
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = TempMemo->SelCol;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = attr;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = TempMemo->SelCol + attr.Length() - 1;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
 else if (AnsiPos("/>", temp_str))
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = TempMemo->SelCol + 1;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = attr;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = TempMemo->SelCol + attr.Length();
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
 else
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = TempMemo->SelCol + 2;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = attr;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = TempMemo->SelCol + attr.Length() + 1;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::QuotesDelete(String tag)
{
 //---------------------------
 // Entfernt Anführungszeichen
 //---------------------------
 int pos_1, pos_2;
 bool found = false;

 do
 {
  tag = ReplaceString(tag, " =", "=", true, true);
  tag = ReplaceString(tag, "= ", "=", true, true);
  pos_1 = AnsiPos(" =", tag);
  pos_2 = AnsiPos("= ", tag);
  if ((pos_1 == 0) && (pos_2 == 0))
   found = true;
 }
 while (!found);
 tag = ReplaceString(tag, "\"", "", true, true);
 return (tag);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::TagNormalize(String tag, bool lowercase)
{
 //-----------------------
 // Normalisiert einen Tag
 //-----------------------
 int pos_1, pos_2;
 bool found = false;
 String part_1, part_2;

 part_1 = tag.SubString(tag.Length(), 1);
 if (part_1 != ">")
  tag = tag + ">";

 do
 {
  tag = ReplaceString(tag, " =", "=", true, true);
  tag = ReplaceString(tag, "= ", "=", true, true);
  pos_1 = AnsiPos(" =", tag);
  pos_2 = AnsiPos("= ", tag);
  if ((pos_1 == 0) && (pos_2 == 0))
   found = true;
 }
 while (!found);

 tag = ReplaceString(tag, "\\\"", "\"", true, true);

 tag = TrimLeft(tag);
 tag = TrimRight(tag);

 pos_1 = 0;
 pos_2 = 0;

 do
 {
  part_1 = tag.SubString(pos_1, 1);
  if (part_1 == "=")
  {
   part_2 = tag.SubString(pos_1 + 1, 1);
   if (part_2 != "\"")
   {
    pos_1++;
    tag = tag.Insert("\"", pos_1);
    do
    {
     part_1 = tag.SubString(pos_1, 1);
     pos_1++;
     if (part_1 == ">")
      break;
    }
    while (part_1 != " ");
    pos_1--;
    tag = tag.Insert("\"", pos_1);
   }
   else
   {
    pos_1 = pos_1 + 2;
    do
    {
     part_1 = tag.SubString(pos_1, 1);
     pos_1++;
     if (part_1 == ">")
      break;
    }
    while (part_1 != "\"");
    pos_1--;
   }
  }
  pos_1++;
 }
 while (part_1 != ">");

 if (lowercase)
 {
  String complete_tag;
  char *teil_lower;

  tag = ReplaceString(tag, "\"\"", "_Scribe![]-", true, false);
  teil_lower = strtok(tag.c_str(), "\"");
  if (teil_lower)
   complete_tag = AnsiLowerCase(String(teil_lower));

  while (teil_lower)
  {
   teil_lower = strtok(NULL, "\"");
   if (teil_lower)
    complete_tag += "\"" + String (teil_lower) + "\"";
   teil_lower = strtok(NULL, "\"");
   if (teil_lower)
    complete_tag += AnsiLowerCase(String(teil_lower));
  }
  complete_tag = ReplaceString(complete_tag, "_scribe![]-", "\"\"", true, false);
  tag = complete_tag;
 }
 return (tag);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::TagAttributeContainsStandalone(String attribute, String tag)
{
 //----------------------------------------------------
 // Enthält der Tag das übergebene StandAlone-Attribut?
 //----------------------------------------------------

 //-Vorbehalt - Anfang-
 String temp_tag;
 temp_tag = attribute + "=";
 tag = TagAttributeRemoveAttribute(temp_tag, tag);
 //-Vorbehalt - Ende-

 attribute = " " + attribute;
 if (AnsiPos(attribute, tag))
  return (true);
 else
  return (false);
}
//---------------------------------------------------------------------------
int __fastcall THauptformular::TagAttributeGetNumeric(String attribute, String tag)
{
 //----------------------------------------
 // Ermittelt eine numerische Wertzuweisung
 //----------------------------------------
 int pos_1, pos_2, pos_3;
 String part_1, part_2;

 pos_1 = 0;
 pos_2 = 0;
 pos_3 = 0;

 attribute = " " + attribute + "\"";
 pos_1 = AnsiPos(attribute, tag);
 if (pos_1 != 0)
 {
  pos_2 = pos_1 + attribute.Length() + 1;
  pos_3 = pos_2 - 1;
  do
  {
   part_2 = tag.SubString(pos_3, 1);
   pos_3++;
  }
  while (part_2 != "\"");
  part_2 = tag.SubString(pos_2 - 1, pos_3 - pos_2);
  pos_3 = part_2.ToInt();
  return (pos_3);
 }
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::TagAttributeGetString(String attribute, String tag)
{
 //-------------------------------------
 // Ermittelt eine String-Wertzuweisung
 //-------------------------------------
 int pos_1, pos_2, pos_3;
 String part_1, part_2;

 pos_1 = 0;
 pos_2 = 0;
 pos_3 = 0;

 attribute = " " + attribute + "\"";
 if (AnsiPos(attribute, tag))
 {
  pos_1 = AnsiPos(attribute, tag);
  pos_2 = pos_1 + attribute.Length() + 1;
  pos_3 = pos_2 - 1;
  do
  {
   part_2 = tag.SubString(pos_3, 1);
   pos_3++;
  }
  while (part_2 != "\"");
  part_2 = tag.SubString(pos_2 - 1, pos_3 - pos_2);
  return (part_2);
 }
 else
  return ("");

}
//---------------------------------------------------------------------------
TColor __fastcall THauptformular::TagAttributeGetColor(String attribute, String tag)
{
 //----------------------------------
 // Ermittelt eine Farb-Wertzuweisung
 //----------------------------------
 int pos_1, pos_2, pos_3;
 String part_1, part_2;

 pos_1 = 0;
 pos_2 = 0;
 pos_3 = 0;

 attribute = " " + attribute + "\"";
 pos_1 = AnsiPos(attribute, tag);
 pos_2 = pos_1 + attribute.Length() + 1;
 pos_3 = pos_2 - 1;
 do
 {
  part_2 = tag.SubString(pos_3, 1);
  pos_3++;
 }
 while (part_2 != "\"");
 part_2 = tag.SubString(pos_2 - 1, pos_3 - pos_2);
 return (ColorXHTMLCodeToColor(part_2));
}
//---------------------------------------------------------------------------
int __fastcall THauptformular::TagAttributeGetPercent(String attribute, String tag)
{
 //-------------------------------------
 // Ermittelt eine Prozent-Wertzuweisung
 //-------------------------------------
 int pos_1, pos_2, pos_3;
 String part_1, part_2;

 pos_1 = 0;
 pos_2 = 0;
 pos_3 = 0;

 attribute = " " + attribute + "\"";
 pos_1 = AnsiPos(attribute, tag);
 if (pos_1 != 0)
 {
  pos_2 = pos_1 + attribute.Length() + 1;
  pos_3 = pos_2 - 1;
  do
  {
   part_2 = tag.SubString(pos_3, 1);
   pos_3++;
  }
  while (part_2 != "\"");
  part_2 = tag.SubString(pos_2 - 1, pos_3 - pos_2);
  part_2 = ReplaceString(part_2, "%", "", false, false);
  pos_3 = part_2.ToInt();
  return (pos_3);
 }
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::TagAttributeContainsPercent(String attribute, String tag)
{
 //---------------------------------------------
 // Ist das Attribut eine Prozent-Wertzuweisung?
 //---------------------------------------------
 int pos_1, pos_2, pos_3;
 String part_1, part_2;

 pos_1 = 0;
 pos_2 = 0;
 pos_3 = 0;

 attribute = " " + attribute + "\"";
 pos_1 = AnsiPos(attribute, tag);
 pos_2 = pos_1 + attribute.Length() + 1;
 pos_3 = pos_2 - 1;
 do
 {
  part_2 = tag.SubString(pos_3, 1);
  pos_3++;
 }
 while (part_2 != "\"");
 part_2 = tag.SubString(pos_2 - 1, pos_3 - pos_2);

 if (AnsiPos("%", part_2))
  return (true);
 else
  return (false);
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::TagAttributeContainsAttribute(String attribute, String tag)
{
 //-----------------------------------------
 // Enthält der Tag des übergebene Attribut?
 //-----------------------------------------
 int pos_1, pos_2, pos_3;
 String part_1, part_2;

 pos_1 = 0;
 pos_2 = 0;
 pos_3 = 0;

 attribute = " " + attribute + "\"";
 if (AnsiPos(attribute, tag))
 {
  pos_1 = AnsiPos(attribute, tag);
  pos_2 = pos_1 + attribute.Length() + 1;
  pos_3 = pos_2 - 1;
  do
  {
   part_2 = tag.SubString(pos_3, 1);
   pos_3++;
  }
  while (part_2 != "\"");
  part_2 = tag.SubString(pos_2 - 1, pos_3 - pos_2);
  part_2 = Trim(part_2);
  if (part_2 != "")
   return (true);
  else
   return (false);
 }
 else
  return (false);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::TagAttributeRemoveMainTag(String maintag, String tag)
{
 //----------------------
 // Entfernt den Haupttag
 //----------------------
 maintag = "<" + maintag;
 tag = ReplaceString(tag, maintag, "", false, false);
 tag = ReplaceString(tag, ">", "", false, false);
 return (tag);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::TagAttributeRemoveAttribute(String attribute, String tag)
{
 //----------------------
 // Entfernt ein Attribut
 //----------------------
 int pos_1, pos_2, pos_3;
 String part_1, part_2;

 pos_1 = 0;
 pos_2 = 0;
 pos_3 = 0;

 attribute = " " + attribute + "\"";

 if (AnsiPos(attribute, tag))
 {
  pos_1 = AnsiPos(attribute, tag);
  pos_2 = pos_1 + attribute.Length() + 1;
  pos_3 = pos_2 - 1;
  do
  {
   part_2 = tag.SubString(pos_3, 1);
   pos_3++;
  }
  while (part_2 != "\"");
  part_2 = tag.SubString(pos_2 - 1, pos_3 - pos_2);
  attribute = attribute + part_2 + "\"";
  tag = ReplaceString(tag, attribute, "", false, false);
  return (tag);
 }
 else
  return (tag);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::TagAttributeRemoveStandalone(String attribute, String tag)
{
 //---------------------------------
 // Entfernt ein StandAlone-Attribut
 //---------------------------------
 attribute = " " + attribute;
 tag = ReplaceString(tag, attribute, "", false, false);
 return (tag);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::ImageCatalogShow()
{
 //----------------------------
 // Zeigt den Grafik-Katalog an
 //----------------------------
 TGrafikKatalog* GrafikKatalog = new TGrafikKatalog(Application);
 SprachenWaehler->SetFormLanguage(GrafikKatalog);
 GrafikKatalog->Caption = ReplaceString(GrafikKatalog1->Caption, "&", "", false, true);
 GrafikKatalog->BitBtn1->Enabled = true;
 GrafikKatalog->ShowModal();
 if (Trim(image_catalog_file) != "")
  image_catalog_file = DirectorySameAndRelative(image_catalog_file);
 return (image_catalog_file);
}
//---------------------------------------------------------------------------
String __fastcall THauptformular::XHTMLBracketAdd(String tag)
{
 //----------------------------------------
 // Formatiert Tag in XHTML-Mode oder nicht
 //----------------------------------------
 if (Trim(tag) == "")
 {
  if (editor_xhtml_mode)
   tag = tag + " /";
  return (tag);
 }
 else
 {
  tag = TrimRight(tag);
  String lastchar = tag.AnsiLastChar();
  if (lastchar == "/")
   tag = tag.SubString(0, tag.Length()-1);
  tag = TrimRight(tag);
  if (editor_xhtml_mode)
   tag = tag + " /";
  return (tag);
 }
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::ColorAssignColorToButton(TSpeedButton *ColorAssignButton, TColor color, TColorDialog *ColorAssignDialog)
{
 //------------------------------------------------------
 // Weist einem Button und einem ColorDialog die Farbe zu
 //------------------------------------------------------
 Graphics::TBitmap* bitmap1 = new Graphics::TBitmap();
 bitmap1->Height = 15;
 bitmap1->Width = 39;
 bitmap1->Canvas->Pen->Color = StringToColor(0x00FAFFFE);
 bitmap1->Canvas->Brush->Color = StringToColor(0x00FAFFFE);
 bitmap1->Canvas->Rectangle(0, 0, 39, 15);
 if (color == clBlack)
  bitmap1->Canvas->Pen->Color = clBlack;
 else
  bitmap1->Canvas->Pen->Color = clBlack;
 bitmap1->Canvas->Brush->Color = color;
 bitmap1->Canvas->Rectangle(0, 0, 39, 14);
 ColorAssignButton->Glyph = bitmap1;
 ColorAssignDialog->Color = color;
 delete bitmap1;
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::ColorButton(TSpeedButton *ColorButton, TColor color)
{
 //--------------------------------
 // Weist einem Button die Farbe zu
 //--------------------------------
 Graphics::TBitmap* bitmap1 = new Graphics::TBitmap();
 bitmap1->Height = 15;
 bitmap1->Width = 39;
 bitmap1->Canvas->Pen->Color = StringToColor(0x00FAFFFE);
 bitmap1->Canvas->Brush->Color = StringToColor(0x00FAFFFE);
 bitmap1->Canvas->Rectangle(0, 0, 39, 15);
 if (color == clBlack)
  bitmap1->Canvas->Pen->Color = clBlack;
 else
  bitmap1->Canvas->Pen->Color = clBlack;
 bitmap1->Canvas->Brush->Color = color;
 bitmap1->Canvas->Rectangle(0, 0, 39, 14);
 ColorButton->Glyph = bitmap1;
 delete bitmap1;
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::ColorSetUserDefined(TColorDialog *ColorSetDialog)
{
 //--------------------------------------------------------------------------
 // Weist einem ColorDialog die benutzerdefinierten Farben aus einer Datei zu
 //--------------------------------------------------------------------------
 ColorSetDialog->CustomColors->Clear();

 TIniFile* Farben = new TIniFile(program_dir + "Storage!\\settings.ini");
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color1", "ColorA=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color2", "ColorB=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color3", "ColorC=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color4", "ColorD=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color5", "ColorE=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color6", "ColorF=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color7", "ColorG=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color8", "ColorH=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color9", "ColorI=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color10", "ColorJ=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color11", "ColorK=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color12", "ColorL=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color13", "ColorM=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color14", "ColorN=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color15", "ColorO=FFFFFF"));
 ColorSetDialog->CustomColors->Add(Farben->ReadString("Custom colors", "Color16", "ColorP=FFFFFF"));

 delete Farben;
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::ColorReadUserDefined(TColorDialog *ColorReadDialog)
{
 //------------------------------------------------------------------------
 // Schreibt die benutzerdefinierten Farben eines ColorDialog in eine Datei
 //------------------------------------------------------------------------
 TIniFile* Farben = new TIniFile(program_dir + "Storage!\\settings.ini");

 Farben->WriteString("Custom colors", "Color1", ColorReadDialog->CustomColors->Strings[0]);
 Farben->WriteString("Custom colors", "Color2", ColorReadDialog->CustomColors->Strings[1]);
 Farben->WriteString("Custom colors", "Color3", ColorReadDialog->CustomColors->Strings[2]);
 Farben->WriteString("Custom colors", "Color4", ColorReadDialog->CustomColors->Strings[3]);
 Farben->WriteString("Custom colors", "Color5", ColorReadDialog->CustomColors->Strings[4]);
 Farben->WriteString("Custom colors", "Color6", ColorReadDialog->CustomColors->Strings[5]);
 Farben->WriteString("Custom colors", "Color7", ColorReadDialog->CustomColors->Strings[6]);
 Farben->WriteString("Custom colors", "Color8", ColorReadDialog->CustomColors->Strings[7]);
 Farben->WriteString("Custom colors", "Color9", ColorReadDialog->CustomColors->Strings[8]);
 Farben->WriteString("Custom colors", "Color10", ColorReadDialog->CustomColors->Strings[9]);
 Farben->WriteString("Custom colors", "Color11", ColorReadDialog->CustomColors->Strings[10]);
 Farben->WriteString("Custom colors", "Color12", ColorReadDialog->CustomColors->Strings[11]);
 Farben->WriteString("Custom colors", "Color13", ColorReadDialog->CustomColors->Strings[12]);
 Farben->WriteString("Custom colors", "Color14", ColorReadDialog->CustomColors->Strings[13]);
 Farben->WriteString("Custom colors", "Color15", ColorReadDialog->CustomColors->Strings[14]);
 Farben->WriteString("Custom colors", "Color16", ColorReadDialog->CustomColors->Strings[15]);

 delete Farben;
}
//---------------------------------------------------------------------------
bool __fastcall THauptformular::DirectFTPCheckConnection()
{
 //--------------------------------------------------------------
 // Überprüft die Verbindung zum Internet (wahlweise abschaltbar)
 //--------------------------------------------------------------
 if (directftp_check_connection)
 {
  if (InternetGetConnectedState(NULL, 0))
   return (true);
  else
   return (false);
 }
 else
  return (true);
}

//---------------------------------------------------------------------------
// Eigene Funktionen - Ende
//---------------------------------------------------------------------------
__fastcall THauptformular::THauptformular(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FormShow(TObject *Sender)
{
 //----------------------
 // Programmpfad auslesen
 //----------------------
 program_dir = AnsiLowerCase(ExtractFilePath(Application->ExeName));

 //--------------------
 // Einstellungen lesen
 //--------------------
 TIniFile* Einstellungen = new TIniFile(program_dir + "Storage!\\settings.ini");

 //---------------------
 // Editorsprache setzen
 //---------------------
 editor_language = Einstellungen->ReadInteger("Others", "Language", 0);
 SprachenWaehler->Language = editor_language;
 SprachenWaehler->LanguageFile = program_dir + "Storage!\\language.ini";

 if (editor_language > 0)
  SprachenWaehler->SetApplicationLanguage();
 //---------------------

 // Fenster-Positionen
 Hauptformular->Left = Einstellungen->ReadInteger("Positions", "MainformXPos", 5);
 Hauptformular->Top = Einstellungen->ReadInteger("Positions", "MainformYPos", 5);
 Hauptformular->Height = Einstellungen->ReadInteger("Positions", "MainformHeight", 442);
 Hauptformular->Width = Einstellungen->ReadInteger("Positions", "MainformWidth", 630);
 Hauptformular->WindowState = Einstellungen->ReadInteger("Positions", "MainformState", wsNormal);
 MenuLeiste->Left = Einstellungen->ReadInteger("Positions", "MenuBarXPos", 11);
 MenuLeiste->Top = Einstellungen->ReadInteger("Positions", "MenuBarYPos", 2);
 DateiOpLeiste->Left = Einstellungen->ReadInteger("Positions", "FileOperationsBarXPos", 11);
 DateiOpLeiste->Top = Einstellungen->ReadInteger("Positions", "FileOperationsBarYPos", 28);
 AndereLeiste->Left = Einstellungen->ReadInteger("Positions", "OthersBarXPos", 170);
 AndereLeiste->Top = Einstellungen->ReadInteger("Positions", "OthersBarYPos", 28);
 BearbeitenOpLeiste->Left = Einstellungen->ReadInteger("Positions", "EditOperationsBarXPos", 11);
 BearbeitenOpLeiste->Top = Einstellungen->ReadInteger("Positions", "EditOperationsBarYPos", 54);
 BrowserLeiste->Left = Einstellungen->ReadInteger("Positions", "BrowserBarXPos", 193);
 BrowserLeiste->Top = Einstellungen->ReadInteger("Positions", "BrowserBarYPos", 54);
 FensterLeiste->Left = Einstellungen->ReadInteger("Positions", "WindowBarXPos", 11);
 FensterLeiste->Top = Einstellungen->ReadInteger("Positions", "WindowBarYPos", 80);
 KomponentenLeiste->Left = Einstellungen->ReadInteger("Positions", "ComponentsBarXPos", 229);
 KomponentenLeiste->Top = Einstellungen->ReadInteger("Positions", "ComponentsBarYPos", 28);
 KomponentenLeiste->ActivePage = KomponentenLeiste->Pages[Einstellungen->ReadInteger("Positions", "ComponentsActiveTab", 0)];
 VerwaltungsPaneel->Width = Einstellungen->ReadInteger("Positions", "AdministrationXPos", 212);
 VerwControl->ActivePage = VerwControl->Pages[Einstellungen->ReadInteger("Positions", "AdministrationActiveTab", 0)];
 DateimanagerExplorer->Height = Einstellungen->ReadInteger("Positions", "FileManagerYPos", 120);
 ProjekteExplorer->Height = Einstellungen->ReadInteger("Positions", "ProjectManagerYPos", 120);
 VerwaltungsPaneel->Visible = Einstellungen->ReadBool("Positions", "Administration", true);
 StatusLeiste->Visible = Einstellungen->ReadBool("Positions", "Statusbar", true);
 DirektFTPExplorer->Height = Einstellungen->ReadInteger("Positions", "DirektFTPManagerYPos", 120);

 //Browser
 browser_path_1 = Einstellungen->ReadString("Browser", "BrowserPath1", "");
 browser_desc_1 = Einstellungen->ReadString("Browser", "BrowserDescription1", "");
 browser_path_2 = Einstellungen->ReadString("Browser", "BrowserPath2", "");
 browser_desc_2 = Einstellungen->ReadString("Browser", "BrowserDescription2", "");
 browser_path_3 = Einstellungen->ReadString("Browser", "BrowserPath3", "");
 browser_desc_3 = Einstellungen->ReadString("Browser", "BrowserDescription3", "");
 browser_confirm_save = Einstellungen->ReadBool("Browser", "BrowserConfirmSave", true);

 //Interner Browser
 InternerBrowser->Top = Einstellungen->ReadInteger("InternalBrowser", "Top", 50);
 InternerBrowser->Left = Einstellungen->ReadInteger("InternalBrowser", "Left", 50);
 InternerBrowser->Height = Einstellungen->ReadInteger("InternalBrowser", "Height", 300);
 InternerBrowser->Width = Einstellungen->ReadInteger("InternalBrowser", "Width", 400);

 //Dokumente
 documents_extension = Einstellungen->ReadString("Files", "StandardDocumentExtension", ".html");
 docfile_extensions = Einstellungen->ReadString("Files", "DocumentExtensions", "html;shtml;txt;php;php3;php4;inc;asp;");
 graphicfile_extensions = Einstellungen->ReadString("Files", "GraphicExtensions", "gif;jpg;jpeg;png;");
 multimediafile_extensions = Einstellungen->ReadString("Files", "MultimediaExtensions", "mid;au;avi;wav;wrl;");
 cssfile_extensions = Einstellungen->ReadString("Files", "CSSExtensions", "css;");
 javascriptfile_extensions = Einstellungen->ReadString("Files", "JavaScriptExtensions", "js;");

 // Hilfe
 help_align = Einstellungen->ReadString("Help", "HelpAlign", "right");
 help_size = Einstellungen->ReadInteger("Help", "HelpSize", 190);
 help_dock_window = Einstellungen->ReadBool("Help", "HelpDockWindow", true);
 help_window_top = Einstellungen->ReadInteger("Help", "HelpTop", 100);
 help_window_left = Einstellungen->ReadInteger("Help", "HelpLeft", 100);
 help_window_height = Einstellungen->ReadInteger("Help", "HelpHeight", 300);
 help_window_width = Einstellungen->ReadInteger("Help", "HelpWidth", 400);

 //Quickstart
 quickstart_path_1 = Einstellungen->ReadString("Quickstart", "QuickStartAppPath1", "");
 quickstart_desc_1 = Einstellungen->ReadString("Quickstart", "QuickStartAppDesc1", "");
 quickstart_para_1 = Einstellungen->ReadString("Quickstart", "QuickStartAppPara1", "");
 quickstart_path_2 = Einstellungen->ReadString("Quickstart", "QuickStartAppPath2", "");
 quickstart_desc_2 = Einstellungen->ReadString("Quickstart", "QuickStartAppDesc2", "");
 quickstart_para_2 = Einstellungen->ReadString("Quickstart", "QuickStartAppPara2", "");
 quickstart_path_3 = Einstellungen->ReadString("Quickstart", "QuickStartAppPath3", "");
 quickstart_desc_3 = Einstellungen->ReadString("Quickstart", "QuickStartAppDesc3", "");
 quickstart_para_3 = Einstellungen->ReadString("Quickstart", "QuickStartAppPara3", "");
 quickstart_path_4 = Einstellungen->ReadString("Quickstart", "QuickStartAppPath4", "");
 quickstart_desc_4 = Einstellungen->ReadString("Quickstart", "QuickStartAppDesc4", "");
 quickstart_para_4 = Einstellungen->ReadString("Quickstart", "QuickStartAppPara4", "");
 quickstart_path_5 = Einstellungen->ReadString("Quickstart", "QuickStartAppPath5", "");
 quickstart_desc_5 = Einstellungen->ReadString("Quickstart", "QuickStartAppDesc5", "");
 quickstart_para_5 = Einstellungen->ReadString("Quickstart", "QuickStartAppPara5", "");

 // Andere Einstellungen
 use_ascii_code = Einstellungen->ReadBool("Others", "UseASCIICode", false);
 textarea_read_xhtml_title = Einstellungen->ReadBool("Others", "ReadXHTMLTitle", true);
 DateimanagerExplorer->OpenPath(Einstellungen->ReadString("Others", "LastExplorerDir", "C:\\"));
 DateimanagerExplorerDirChange(Sender, DateimanagerExplorer->SelectedPath);
 max_history_entries = Einstellungen->ReadInteger("Others", "MaxHistoryEntries", 5);
 standard_xhtml_documentation = Einstellungen->ReadString("Others", "StandardXHTMLDocumentation", "http://www.teamone.de/selfhtml");
 project_dir = Einstellungen->ReadString("Others", "ProjectDir", program_dir);
 String project_temp = Einstellungen->ReadString("Others", "LastProject", "(Bla)");
 String directftp_temp = Einstellungen->ReadString("Others", "LastProfile", "(Bla)");
 standard_graphic_tool = Einstellungen->ReadString("Others", "StandardGraphicTool", "");
 textarea_save_files_in_unix = Einstellungen->ReadBool("Others", "SaveFilesInUnixFormat", false);
 textarea_print_plaintext = Einstellungen->ReadBool("Others", "PrintPlaintext", false);
 textarea_tabstops = Einstellungen->ReadInteger("Others", "TabStops", 8);
 textarea_wordwrap = Einstellungen->ReadBool("Others", "WordWrap", false);
 textarea_linenumbers  = Einstellungen->ReadBool("Others", "LineNumbers", false);
 color_palette = Einstellungen->ReadString("Others", "ColorPalette", program_dir + "Storage!\\Palettes\\palette16.bmp");
 use_color_names = Einstellungen->ReadBool("Others", "UseColorNames", true);
 textarea_convert_special_chars = Einstellungen->ReadBool("Others", "ConvertSpecialChars", true);
 standard_template = Einstellungen->ReadString("Others", "StandardTemplate", "Standard");
 editor_file_at_start = Einstellungen->ReadBool("Others", "CreateFileAtStart", true);
 directftp_connect_at_start = Einstellungen->ReadBool("Others", "ConnectToFTPAtStart", false);
 editor_show_tip = Einstellungen->ReadBool("Others", "ShowTip", true);
 plugin_read_name_title = Einstellungen->ReadBool("Others", "ReadPluginNameAndAuthor", true);
 editor_xhtml_mode = Einstellungen->ReadBool("Others", "XHTMLMode", true);
 tag_php_compatible = Einstellungen->ReadBool("Others", "TagPHPCompatible", false);
 tag_automatic_position = Einstellungen->ReadBool("Others", "TagAutomaticPosition", true);
 localhost_use = Einstellungen->ReadBool("Others", "LocalhostUse", false);
 localhost_adress = Einstellungen->ReadString("Others", "LocalhostAdress", "127.0.0.1");
 tag_auto_complete = Einstellungen->ReadBool("Others", "TagAutoComplete", true);
 editor_events_tab = Einstellungen->ReadBool("Others", "ShowEventsTab", false);
 includes_dir = Einstellungen->ReadString("Others", "IncludesDir", program_dir + "Storage!\\Includes\\");
 use_topstyle = Einstellungen->ReadBool("Others", "UseTopStyle", false);
 editor_font_face = Einstellungen->ReadString("Others", "EditorFontFace", "Courier New");
 editor_font_size = Einstellungen->ReadInteger("Others", "EditorFontSize", 10);
 editor_word_delimiters = Einstellungen->ReadString("Others", "WordDelimiters", "\"(), .:;<=>");
 first_date = Einstellungen->ReadBool("Others", "FirstDate", true);
 directftp_show_menue = Einstellungen->ReadBool("Others", "ShowFTPUploadMenue", false);
 directftp_check_connection = Einstellungen->ReadBool("Others", "CheckConnection", true);
 editor_background_color = StringToColor(Einstellungen->ReadString("Others", "EditorBackground", "clWindow"));

 //Syntax-Farben
 syntax_color_tags = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorTags", "clNavy"));
 syntax_color_attributes = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorAttributes", "clBlue"));
 syntax_color_links = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorLinks", "clMaroon"));
 syntax_color_linkattrs = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorLinkAttrs", "clRed"));
 syntax_color_comments = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorComments", "clGray"));
 syntax_color_styles = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorStyles", "clPurple"));
 syntax_color_styleattrs = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorStyleAttrs", "clFuchsia"));
 syntax_color_stylecomments = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorStyleComments", "clBlack"));
 syntax_color_javascript = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorJavascript", "clNavy"));
 syntax_color_tables = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorTables", "clTeal"));
 syntax_color_tableattrs = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorTableAttrs", "clNavy"));
 syntax_color_specialchars = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorSpecialchars", "clBlack"));
 syntax_color_php_area = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorPHPArea", "clBlack"));
 syntax_color_php_comments = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorPHPComments", "clGray"));
 syntax_color_php_keywords = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorPHPKeywords", "clNavy"));
 syntax_color_php_attrs = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorPHPAttrs", "clMaroon"));
 syntax_color_sql_functions = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorSQLFunctions", "clGreen"));
 syntax_color_css_comments = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorCSSComments", "clGray"));
 syntax_color_css_strings = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorCSSStrings", "clRed"));
 syntax_color_css_chars = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorCSSChars", "clNavy"));
 syntax_color_css_tags = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorCSSTags", "clGreen"));
 syntax_color_css_attrs = StringToColor(Einstellungen->ReadString("Syntax scheme", "ColorCSSAttrs", "clBlack"));
 syntax_bold_tags = Einstellungen->ReadBool("Syntax scheme", "BoldTags", false);
 syntax_bold_attributes = Einstellungen->ReadBool("Syntax scheme", "BoldAttributes", false);
 syntax_bold_links = Einstellungen->ReadBool("Syntax scheme", "BoldLinks", false);
 syntax_bold_linkattrs = Einstellungen->ReadBool("Syntax scheme", "BoldLinkAttrs", false);
 syntax_bold_comments = Einstellungen->ReadBool("Syntax scheme", "BoldComments", false);
 syntax_bold_styles = Einstellungen->ReadBool("Syntax scheme", "BoldStyles", false);
 syntax_bold_styleattrs = Einstellungen->ReadBool("Syntax scheme", "BoldStyleAttrs", false);
 syntax_bold_stylecomments = Einstellungen->ReadBool("Syntax scheme", "BoldStyleComments", false);
 syntax_bold_javascript = Einstellungen->ReadBool("Syntax scheme", "BoldJavascript", true);
 syntax_bold_tables = Einstellungen->ReadBool("Syntax scheme", "BoldTables", false);
 syntax_bold_tableattrs = Einstellungen->ReadBool("Syntax scheme", "BoldTableAttrs", false);
 syntax_bold_specialchars = Einstellungen->ReadBool("Syntax scheme", "BoldSpecialchars", true);
 syntax_bold_php_area = Einstellungen->ReadBool("Syntax scheme", "BoldPHPArea", false);
 syntax_bold_php_comments = Einstellungen->ReadBool("Syntax scheme", "BoldPHPComments", false);
 syntax_bold_php_keywords = Einstellungen->ReadBool("Syntax scheme", "BoldPHPKeywords", false);
 syntax_bold_php_attrs = Einstellungen->ReadBool("Syntax scheme", "BoldPHPAttrs", false);
 syntax_bold_sql_functions = Einstellungen->ReadBool("Syntax scheme", "BoldSQLFunctions", false);
 syntax_bold_css_comments = Einstellungen->ReadBool("Syntax scheme", "BoldCSSComments", false);
 syntax_bold_css_strings = Einstellungen->ReadBool("Syntax scheme", "BoldCSSStrings", false);
 syntax_bold_css_chars = Einstellungen->ReadBool("Syntax scheme", "BoldCSSChars", true);
 syntax_bold_css_tags = Einstellungen->ReadBool("Syntax scheme", "BoldCSSTags", false);
 syntax_bold_css_attrs = Einstellungen->ReadBool("Syntax scheme", "BoldCSSAttrs", false);
 syntax_italic_tags = Einstellungen->ReadBool("Syntax scheme", "ItalicTags", false);
 syntax_italic_attributes = Einstellungen->ReadBool("Syntax scheme", "ItalicAttributes", false);
 syntax_italic_links = Einstellungen->ReadBool("Syntax scheme", "ItalicLinks", false);
 syntax_italic_linkattrs = Einstellungen->ReadBool("Syntax scheme", "ItalicLinkAttrs", false);
 syntax_italic_comments = Einstellungen->ReadBool("Syntax scheme", "ItalicComments", true);
 syntax_italic_styles = Einstellungen->ReadBool("Syntax scheme", "ItalicStyles", false);
 syntax_italic_styleattrs = Einstellungen->ReadBool("Syntax scheme", "ItalicStyleAttrs", false);
 syntax_italic_stylecomments = Einstellungen->ReadBool("Syntax scheme", "ItalicStyleComments", false);
 syntax_italic_javascript = Einstellungen->ReadBool("Syntax scheme", "ItalicJavascript", false);
 syntax_italic_tables = Einstellungen->ReadBool("Syntax scheme", "ItalicTables", false);
 syntax_italic_tableattrs = Einstellungen->ReadBool("Syntax scheme", "ItalicTableAttrs", false);
 syntax_italic_specialchars = Einstellungen->ReadBool("Syntax scheme", "ItalicSpecialchars", true);
 syntax_italic_php_area = Einstellungen->ReadBool("Syntax scheme", "ItalicPHPArea", false);
 syntax_italic_php_comments = Einstellungen->ReadBool("Syntax scheme", "ItalicPHPComments", true);
 syntax_italic_php_keywords = Einstellungen->ReadBool("Syntax scheme", "ItalicPHPKeywords", false);
 syntax_italic_php_attrs = Einstellungen->ReadBool("Syntax scheme", "ItalicPHPAttrs", false);
 syntax_italic_sql_functions = Einstellungen->ReadBool("Syntax scheme", "ItalicSQLFunctions", false);
 syntax_italic_css_comments = Einstellungen->ReadBool("Syntax scheme", "ItalicCSSComments", true);
 syntax_italic_css_strings = Einstellungen->ReadBool("Syntax scheme", "ItalicCSSStrings", false);
 syntax_italic_css_chars = Einstellungen->ReadBool("Syntax scheme", "ItalicCSSChars", false);
 syntax_italic_css_tags = Einstellungen->ReadBool("Syntax scheme", "ItalicCSSTags", false);
 syntax_italic_css_attrs = Einstellungen->ReadBool("Syntax scheme", "ItalicCSSAttrs", false);

 delete Einstellungen;

 //-----------------------
 // Syntax-Schema zuweisen
 //-----------------------
 // Keywords laden
 MySQLSyntax->Items->LoadFromFile(program_dir + "Storage!\\mysqlkeys.ini");
 PHPKeywordsSyntax->Items->LoadFromFile(program_dir + "Storage!\\phpkeys.ini");
 JavaScriptSyntax->Items->LoadFromFile(program_dir + "Storage!\\javascriptkeys.ini");

 // Schema aufbauen
 TWordOptions Worter;
 TExtFontStyles Styles;
 TextfeldHighlighter->StartStopKeys->Clear();
 TextfeldHighlighter->Keywords->Clear();

 if (syntax_bold_links)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_links)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<a", ">", Worter, Styles, 3, 0, 1, crDefault, editor_background_color, syntax_color_links, true);
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("</a", ">", Worter, Styles, 4, 0, 1, crDefault, editor_background_color, syntax_color_links, true);

 if (syntax_bold_linkattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_linkattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 5, 3, 1, crDefault, editor_background_color, syntax_color_linkattrs, true);

 if (syntax_bold_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<!--", "-->", Worter, Styles, 6, 0, 1, crDefault, editor_background_color, syntax_color_comments, false);

 if (syntax_bold_specialchars)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_specialchars)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("&", ";", Worter, Styles, 7, 0, 1, crDefault, editor_background_color, syntax_color_specialchars, true);

 if (syntax_bold_styles)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_styles)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<script", "</script>", Worter, Styles, 8, 0, 1, crDefault, editor_background_color, syntax_color_styles, false);

 if (syntax_bold_styleattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_styleattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 9, 8, 1, crDefault, editor_background_color, syntax_color_styleattrs, true);

 if (syntax_bold_stylecomments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_stylecomments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<!--", "-->", Worter, Styles, 10, 8, 1, crDefault, editor_background_color, syntax_color_stylecomments, false);

 if (syntax_bold_styles)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_styles)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<style", "</style>", Worter, Styles, 14, 0, 1, crDefault, editor_background_color, syntax_color_styles, false);

 if (syntax_bold_styleattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_styleattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 15, 14, 1, crDefault, editor_background_color, syntax_color_styleattrs, true);

 if (syntax_bold_css_tags)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_css_tags)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<!--", "-->", Worter, Styles, 16, 14, 1, crDefault, editor_background_color, syntax_color_css_tags, false);

 if (syntax_bold_css_attrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_css_attrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("{", "}", Worter, Styles, 81, 16, 0, crDefault, editor_background_color, syntax_color_css_attrs, false);

 if (syntax_bold_css_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_css_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 82, 16, 2, crDefault, editor_background_color, syntax_color_css_comments, false);

 if (syntax_bold_css_chars)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_css_chars)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->Keywords->AddExtKeyWord("{", TWordOptions(), Styles, 83, 81, 1, crDefault, editor_background_color, syntax_color_css_chars);
 TextfeldHighlighter->Keywords->AddExtKeyWord("}", TWordOptions(), Styles, 84, 81, 1, crDefault, editor_background_color, syntax_color_css_chars);
 TextfeldHighlighter->Keywords->AddExtKeyWord(";", TWordOptions(), Styles, 85, 81, 1, crDefault, editor_background_color, syntax_color_css_chars);
 TextfeldHighlighter->Keywords->AddExtKeyWord(":", TWordOptions(), Styles, 86, 81, 1, crDefault, editor_background_color, syntax_color_css_chars);

 if (syntax_bold_css_strings)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_css_strings)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 87, 81, 2, crDefault, editor_background_color, syntax_color_css_strings, true);

 if (syntax_bold_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 23, 10, 1, crDefault, editor_background_color, syntax_color_comments, true);
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 24, 16, 1, crDefault, editor_background_color, syntax_color_comments, true);

 TextfeldHighlighter->Keywords->AddExtKeyWord("{", Worter, TExtFontStyles() << fsBold, 17, 14, 1, crDefault, editor_background_color, syntax_color_styles);
 TextfeldHighlighter->Keywords->AddExtKeyWord("}", Worter, TExtFontStyles() << fsBold, 17, 14, 1, crDefault, editor_background_color, syntax_color_styles);
 TextfeldHighlighter->Keywords->AddExtKeyWord("{", Worter, TExtFontStyles() << fsBold, 18, 16, 1, crDefault, editor_background_color, syntax_color_stylecomments);
 TextfeldHighlighter->Keywords->AddExtKeyWord("}", Worter, TExtFontStyles() << fsBold, 18, 16, 1, crDefault, editor_background_color, syntax_color_stylecomments);

 if (syntax_bold_tables)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_tables)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 for (int i = 0; i < TabellenSyntax->Items->Count; i++)
  TextfeldHighlighter->StartStopKeys->AddExStartStopKey(TabellenSyntax->Items->Strings[i], ">", Worter, Styles, 12, 0, 1, crDefault, editor_background_color, syntax_color_tables, true);

 if (syntax_bold_tableattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_tableattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 13, 12, 1, crDefault, editor_background_color, syntax_color_tableattrs, true);

 if (syntax_bold_javascript)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_javascript)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 for (int i = 0; i < JavaScriptSyntax->Items->Count; i++)
  TextfeldHighlighter->Keywords->AddExtKeyWord(JavaScriptSyntax->Items->Strings[i], TWordOptions() << woWholeWordsOnly << woMatchCase, Styles, 11, 10, 0, crDefault, editor_background_color, syntax_color_javascript);

 if (syntax_bold_php_area)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_php_area)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<?", "?>", Worter, Styles, 61, 0, 1, crDefault, editor_background_color, syntax_color_php_area, false);

 if (syntax_bold_php_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_php_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 62, 61, 1, crDefault, editor_background_color, syntax_color_php_comments, false);
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("//", "", Worter, Styles, 62, 61, 1, crDefault, editor_background_color, syntax_color_php_comments, true);

 if (syntax_bold_php_keywords)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_php_keywords)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 for (int i = 0; i < PHPKeywordsSyntax->Items->Count; i++)
  TextfeldHighlighter->Keywords->AddExtKeyWord(PHPKeywordsSyntax->Items->Strings[i], TWordOptions() << woWholeWordsOnly << woMatchCase, Styles, 63, 61, 1, crDefault, editor_background_color, syntax_color_php_keywords);

 if (syntax_bold_sql_functions)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_sql_functions)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 for (int i = 0; i < MySQLSyntax->Items->Count; i++)
  TextfeldHighlighter->Keywords->AddExtKeyWord(MySQLSyntax->Items->Strings[i], TWordOptions() << woWholeWordsOnly << woMatchCase, Styles, 66, 61, 1, crDefault, editor_background_color, syntax_color_sql_functions);

 if (syntax_bold_php_attrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_php_attrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 67, 61, 1, crDefault, editor_background_color, syntax_color_php_attrs, true);
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("'", "'", Worter, Styles, 71, 61, 1, crDefault, editor_background_color, syntax_color_php_attrs, true);

 if (syntax_bold_tags)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_tags)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<", ">", Worter, Styles, 1, 0, 0, crDefault, editor_background_color, syntax_color_tags, true);

 if (syntax_bold_attributes)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_attributes)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 2, 1, 0, crDefault, editor_background_color, syntax_color_attributes, true);

 if (syntax_bold_attributes)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (syntax_italic_attributes)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\\\"", "\\\"", Worter, Styles, 352, 1, 0, crDefault, editor_background_color, syntax_color_attributes, true);

 //------------------------------
 // Statuszeile: Normal oder PHP?
 //------------------------------
 if (tag_php_compatible)
  StatusLeiste->Panels->Items[3]->Text = SprachenWaehler->GetString(79);
 else
  StatusLeiste->Panels->Items[3]->Text = SprachenWaehler->GetString(78);

 //--------------
 // Projeke laden
 //--------------
 ProjectsLoad(project_temp);
 ProjectsLoadFolders(project_temp);
 if (ProjekteAuswahl->ItemIndex != 0)
 {
  (ProjekteExplorer->Items->GetFirstNode())->Selected = true;
  ProjekteExplorerChange(Sender, ProjekteExplorer->Items->GetFirstNode());
 }

 //------------------
 // FTP-Profile laden
 //-------------------
 DirectFTPLoadProfiles(directftp_temp);

 //--------------
 // Buttonx laden
 //--------------
 ButtonxListItems();

 //-----------------------
 // Allgemeine Zuweisungen
 //-----------------------
 program_version = "2.2";
 file_counter = 0;
 documents_name = SprachenWaehler->GetString(1);

 //----------------------
 // EPS-Eintrag schreiben
 //----------------------
 try
 {
  TRegistry* Reg = new TRegistry;
  Reg->RootKey = HKEY_LOCAL_MACHINE;
  Reg->OpenKey("Software\\EPS\\Installed Editors", true);
  Reg->WriteString("Scribe!", program_dir + "Storage!\\Plugins\\");
  delete Reg;
 }
 catch (...)
 {
  1 == 1;
 }

 //------------------
 // Farbpalette laden
 //------------------
 Graphics::TPicture* color_pic = new Graphics::TPicture();
 color_pic->LoadFromFile(color_palette);
 Graphics::TBitmap* color_bitmap = new Graphics::TBitmap();
 color_bitmap->Assign(color_pic->Graphic);
 FarbPaletteBild->Picture->Bitmap = color_bitmap;
 FarbPaletteEdit->Text = ExtractFileName(color_palette);
 delete color_bitmap;
 delete color_pic;

 //---------------------------
 // Farbcodes und -namen laden
 //---------------------------
 ColorColorNames->Items->LoadFromFile(program_dir + "Storage!\\colornames.ini");
 ColorXHTMLCodes->Items->LoadFromFile(program_dir + "Storage!\\colorcodes.ini");

 //-----------------------------------------------------
 // Sonderzeichencodes, -namen und -beschreibungen laden
 //-----------------------------------------------------
 SonderzeichenNames->Items->LoadFromFile(program_dir + "Storage!\\specialnames.ini");
 SonderzeichenCodes->Items->LoadFromFile(program_dir + "Storage!\\specialcodes.ini");
 SonderzeichenDescs->Items->LoadFromFile(program_dir + "Storage!\\specialdesc.ini");

 //-----------------------------------------------------
 // AutoComplete-Zeugs laden
 //-----------------------------------------------------
 AutoComplete->Items->LoadFromFile(program_dir + "Storage!\\autocomplete.ini");

 //-------------------------------------------
 // Sonderzeichen in die Auswahlliste einfügen
 //-------------------------------------------
 int akueller_zeichenindex = 0;
 String leer = "";
 int zeichen_count = SonderzeichenCodes->Items->Count;
 zeichen_count = zeichen_count;
 for (int i = 0; i < SonderZeichenGrid->RowCount; i++)
 {
  for (int a = 0; a < SonderZeichenGrid->ColCount; a++)
  {
   leer = "";
   SonderZeichenGrid->Cells[a][i] = leer.sprintf("%c", SonderzeichenCodes->Items->Strings[akueller_zeichenindex].ToInt());
   akueller_zeichenindex++;
   if (akueller_zeichenindex == zeichen_count)
    break;
  }
  if (akueller_zeichenindex == zeichen_count)
   break;
 }

 //----------------
 // Sonstige Sachen
 //----------------
 // Startet das AddLang!-System
 AddLangPrepareSystem();
 // Cursor laden
 Screen->Cursors[crPipette] = LoadCursor(HInstance, "Pipette");
 FarbPaletteBild->Cursor = TCursor(crPipette);
 // Der Rest
 graphics_viewer_file = "";
 directftp_current_profile = "";
 directftp_current_dir = projectexplorer_dir;
 directftp_file_size = 0;
 directftp_temp_input = "";
 tag_currently_editing = false;
 tag_current = "";
 tag_sel_position = 0;
 image_catalog_file = "";
 css_editstyle = "";
 css_editstyleblock = "";
 css_openfile = "";
 css_edit_editstyle = false;
 css_edit_editstyleblock = false;

 //-------------------------------------------------
 // Testen, ob der Internet Explorer installiert ist
 //-------------------------------------------------
 try
 {
  msie_helpbrowser = new TWebBrowser(this);
  Hilfe->Panel1->InsertControl(msie_helpbrowser);
  msie_helpbrowser->Align = alClient;
  msie_previewbrowser = new TWebBrowser(this);
  InternerBrowser->Panel1->InsertControl(msie_previewbrowser);
  msie_previewbrowser->Align = alClient;
  msie_installed = true;
  msie_previewbrowser->OnProgressChange = WebBrowserProgressChange;
  msie_previewbrowser->OnDocumentComplete = WebBrowserDocumentComplete;
 }
 catch (...)
 {
  msie_installed = false;
 }

 //---------------
 // Hints zuweisen
 //---------------
 ToolButton35->Hint = Seiteneigenschaften1->Caption;
 ToolButton37->Hint = ReplaceString(ReplaceString(Paragraph1->Caption, "&", "", false, true), "...", "", false, true);
 ToolButton38->Hint = ReplaceString(Zeilenumbruch2->Caption, "&", "", false, true);
 ToolButton40->Hint = ReplaceString(Hyperlink1->Caption, "&", "", false, true);
 ToolButton41->Hint = ReplaceString(Grafik1->Caption, "&", "", false, true);
 ToolButton42->Hint = ReplaceString(Trennlinie1->Caption, "&", "", false, true);
 ToolButton43->Hint = ReplaceString(MultimediaObjekt1->Caption, "&", "", false, true);
 ToolButton44->Hint = ReplaceString(Metatag1->Caption, "&", "", false, true);
 ToolButton46->Hint = ReplaceString(Liste1->Caption, "&", "", false, true);
 ToolButton47->Hint = ReplaceString(Listeneintrag1->Caption, "&", "", false, true);
 ToolButton48->Hint = ReplaceString(eMailVerweis1->Caption, "&", "", false, true);
 ToolButton49->Hint = ReplaceString(Anker1->Caption, "&", "", false, true);
 ToolButton93->Hint = ReplaceString(FramesAssistent1->Caption, "&", "", false, true);
 ToolButton94->Hint = ReplaceString(FrameBereich1->Caption, "&", "", false, true);
 ToolButton95->Hint = ReplaceString(Frame1->Caption, "&", "", false, true);
 ToolButton96->Hint = ReplaceString(EingebettetesFrame1->Caption, "&", "", false, true);
 ToolButton98->Hint = ReplaceString(StyleSheetDefinition1->Caption, "&", "", false, true);
 ToolButton99->Hint = ReplaceString(StyleSheetZuweisungen1->Caption, "&", "", false, true);
 ToolButton101->Hint = ReplaceString(JavaScript2->Caption, "&", "", false, true);
 ToolButton51->Hint = ReplaceString(TabellenAssistent1->Caption, "&", "", false, true);
 ToolButton53->Hint = ReplaceString(Tabelle2->Caption, "&", "", false, true);
 ToolButton54->Hint = ReplaceString(Zeile1->Caption, "&", "", false, true);
 ToolButton55->Hint = ReplaceString(Kopfzelle1->Caption, "&", "", false, true);
 ToolButton56->Hint = ReplaceString(Zelle1->Caption, "&", "", false, true);
 ToolButton58->Hint = ReplaceString(berUnterschrift1->Caption, "&", "", false, true);
 ToolButton59->Hint = ReplaceString(Schrift1->Caption, "&", "", false, true);
 ToolButton60->Hint = ReplaceString(Schnellformatierung1->Caption, "&", "", false, true);
 ToolButton62->Hint = ReplaceString(Fett1->Caption, "&", "", false, true);
 ToolButton63->Hint = ReplaceString(Kursiv1->Caption, "&", "", false, true);
 ToolButton65->Hint = ReplaceString(Linksbndig1->Caption, "&", "", false, true);
 ToolButton66->Hint = ReplaceString(Zentriert1->Caption, "&", "", false, true);
 ToolButton67->Hint = ReplaceString(Rechtsbndig1->Caption, "&", "", false, true);
 ToolButton77->Hint = ReplaceString(Blocksatz1->Caption, "&", "", false, true);
 ToolButton69->Hint = ReplaceString(Hochgestellt1->Caption, "&", "", false, true);
 ToolButton70->Hint = ReplaceString(Tiefgestellt1->Caption, "&", "", false, true);
 ToolButton71->Hint = ReplaceString(Prformatiert1->Caption, "&", "", false, true);
 ToolButton72->Hint = ReplaceString(Emphatisch1->Caption, "&", "", false, true);
 ToolButton74->Hint = ReplaceString(Definitionsliste1->Caption, "&", "", false, true);
 ToolButton75->Hint = ReplaceString(Definitionsabschnitt1->Caption, "&", "", false, true);
 ToolButton76->Hint = ReplaceString(Definitionseintrag1->Caption, "&", "", false, true);
 ToolButton78->Hint = ReplaceString(Formular2->Caption, "&", "", false, true);
 ToolButton80->Hint = ReplaceString(Eingabefeld1->Caption, "&", "", false, true);
 ToolButton81->Hint = ReplaceString(Textfeld1->Caption, "&", "", false, true);
 ToolButton82->Hint = ReplaceString(AbsendenundZurcksetzenbutton1->Caption, "&", "", false, true);
 ToolButton83->Hint = ReplaceString(Passwortfeld1->Caption, "&", "", false, true);
 ToolButton84->Hint = ReplaceString(VerstecktesFeld1->Caption, "&", "", false, true);
 ToolButton86->Hint = ReplaceString(Checkbox1->Caption, "&", "", false, true);
 ToolButton87->Hint = ReplaceString(Radiobutton1->Caption, "&", "", false, true);
 ToolButton89->Hint = ReplaceString(Auswahlliste1->Caption, "&", "", false, true);
 ToolButton90->Hint = ReplaceString(Auswahleintrag1->Caption, "&", "", false, true);
 ToolButton92->Hint = ReplaceString(Button1->Caption, "&", "", false, true);

 //--------------------
 // Menüs echter machen
 //--------------------
 SeiteMenu->TrackButton = tbLeftButton;
 BearbeitenMenu->TrackButton = tbLeftButton;
 AnsichtMenu->TrackButton = tbLeftButton;
 EinfgenMenu->TrackButton = tbLeftButton;
 FormatMenu->TrackButton = tbLeftButton;
 ToolsMenu->TrackButton = tbLeftButton;
 FensterMenu->TrackButton = tbLeftButton;
 HilfeMenu->TrackButton = tbLeftButton;
 BrowserMenu->TrackButton = tbLeftButton;
 QuickstartMenu->TrackButton = tbLeftButton;
 DateimanagerListeMenu->TrackButton = tbLeftButton;
 DateimanagerExplorerMenu->TrackButton = tbLeftButton;
 ProjekteListeMenu->TrackButton = tbLeftButton;
 ProjekteExplorerMenu->TrackButton = tbLeftButton;
 DirektFTPExplorerMenu->TrackButton = tbLeftButton;
 DirektFTPListeMenu->TrackButton = tbLeftButton;

 //--------------
 // Erster Start?
 //--------------
 if (first_date)
 {
  TWillkommen* Willkommen = new TWillkommen(Application);
  SprachenWaehler->SetFormLanguage(Willkommen);
  Willkommen->ShowModal();
 }

 //-------------------------
 // Übergebene Dateien laden
 //-------------------------
 if (ParamCount() == 0)
 {
  if ((editor_file_at_start) && (!first_date))
   CreateChildForm(standard_template, "", "");
 }
 else
 {
  for (int i = 1; i < ParamCount() + 1; i++)
  {
   if (AddLangFile(ParamStr(i)) || JavaScriptFile(ParamStr(i)) || CSSFile(ParamStr(i)) || DocumentFile(ParamStr(i)))
    CreateChildForm("", ParamStr(i), "");
  }
 }

 //--------------------------------
 // Erster Start auf "false" setzen
 //--------------------------------
 if (first_date)
  first_date = false;

 //------------------------------
 // DirektFTP automatisch starten
 //------------------------------
 if (directftp_connect_at_start)
  ToolButton31Click(Sender);

 //------------------------
 // Tipp des Tages anzeigen
 //------------------------
 if (editor_show_tip)
 {
  TTippDesTages* TippDesTages = new TTippDesTages(Application);
  SprachenWaehler->SetFormLanguage(TippDesTages);
  TippDesTages->Caption = TippDesTages->Label1->Caption;
  TippDesTages->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FormClose(TObject *Sender, TCloseAction &Action)
{
 //------------------------
 // Einstellungen speichern
 //------------------------
 TIniFile* Einstellungen = new TIniFile(program_dir + "Storage!\\settings.ini");

 // Fenster-Positionen
 Einstellungen->WriteInteger("Positions", "MainformXPos", Hauptformular->Left);
 Einstellungen->WriteInteger("Positions", "MainformYPos", Hauptformular->Top);
 Einstellungen->WriteInteger("Positions", "MainformHeight", Hauptformular->Height);
 Einstellungen->WriteInteger("Positions", "MainformWidth", Hauptformular->Width);
 Einstellungen->WriteInteger("Positions", "MainformState", Hauptformular->WindowState);
 Einstellungen->WriteInteger("Positions", "MenuBarXPos", MenuLeiste->Left);
 Einstellungen->WriteInteger("Positions", "MenuBarYPos", MenuLeiste->Top);
 Einstellungen->WriteInteger("Positions", "FileOperationsBarXPos", DateiOpLeiste->Left);
 Einstellungen->WriteInteger("Positions", "FileOperationsBarYPos", DateiOpLeiste->Top);
 Einstellungen->WriteInteger("Positions", "OthersBarXPos", AndereLeiste->Left);
 Einstellungen->WriteInteger("Positions", "OthersBarYPos", AndereLeiste->Top);
 Einstellungen->WriteInteger("Positions", "EditOperationsBarXPos", BearbeitenOpLeiste->Left);
 Einstellungen->WriteInteger("Positions", "EditOperationsBarYPos", BearbeitenOpLeiste->Top);
 Einstellungen->WriteInteger("Positions", "BrowserBarXPos", BrowserLeiste->Left);
 Einstellungen->WriteInteger("Positions", "BrowserBarYPos", BrowserLeiste->Top);
 Einstellungen->WriteInteger("Positions", "WindowBarXPos", FensterLeiste->Left);
 Einstellungen->WriteInteger("Positions", "WindowBarYPos", FensterLeiste->Top);
 Einstellungen->WriteInteger("Positions", "ComponentsBarXPos", KomponentenLeiste->Left);
 Einstellungen->WriteInteger("Positions", "ComponentsBarYPos", KomponentenLeiste->Top);
 Einstellungen->WriteInteger("Positions", "ComponentsActiveTab", KomponentenLeiste->ActivePage->PageIndex);
 Einstellungen->WriteInteger("Positions", "AdministrationXPos", VerwaltungsPaneel->Width);
 Einstellungen->WriteInteger("Positions", "AdministrationActiveTab", VerwControl->ActivePage->PageIndex);
 Einstellungen->WriteInteger("Positions", "FileManagerYPos",  DateimanagerExplorer->Height);
 Einstellungen->WriteInteger("Positions", "ProjectManagerYPos",  ProjekteExplorer->Height);
 Einstellungen->WriteBool("Positions", "Administration", VerwaltungsPaneel->Visible);
 Einstellungen->WriteBool("Positions", "Statusbar", StatusLeiste->Visible);
 Einstellungen->WriteInteger("Positions", "DirektFTPManagerYPos",  DirektFTPExplorer->Height);

 //Browser
 Einstellungen->WriteString("Browser", "BrowserPath1", browser_path_1);
 Einstellungen->WriteString("Browser", "BrowserDescription1", browser_desc_1);
 Einstellungen->WriteString("Browser", "BrowserPath2", browser_path_2);
 Einstellungen->WriteString("Browser", "BrowserDescription2", browser_desc_2);
 Einstellungen->WriteString("Browser", "BrowserPath3", browser_path_3);
 Einstellungen->WriteString("Browser", "BrowserDescription3", browser_desc_3);
 Einstellungen->WriteBool("Browser", "BrowserConfirmSave", browser_confirm_save);

 //Interner Browser
 Einstellungen->WriteInteger("InternalBrowser", "Top", InternerBrowser->Top);
 Einstellungen->WriteInteger("InternalBrowser", "Left", InternerBrowser->Left);
 Einstellungen->WriteInteger("InternalBrowser", "Height", InternerBrowser->Height);
 Einstellungen->WriteInteger("InternalBrowser", "Width", InternerBrowser->Width);

 // Dokumente
 Einstellungen->WriteString("Files", "StandardDocumentExtension", documents_extension);
 Einstellungen->WriteString("Files", "DocumentExtensions", docfile_extensions);
 Einstellungen->WriteString("Files", "GraphicExtensions", graphicfile_extensions);
 Einstellungen->WriteString("Files", "MultimediaExtensions", multimediafile_extensions);
 Einstellungen->WriteString("Files", "CSSExtensions", cssfile_extensions);
 Einstellungen->WriteString("Files", "JavaScriptExtensions", javascriptfile_extensions);

 //Hilfe
 Einstellungen->WriteString("Help", "HelpAlign", help_align);
 Einstellungen->WriteInteger("Help", "HelpSize", help_size);
 Einstellungen->WriteBool("Help", "HelpDockWindow", help_dock_window);
 Einstellungen->WriteInteger("Help", "HelpTop", help_window_top);
 Einstellungen->WriteInteger("Help", "HelpLeft", help_window_left);
 Einstellungen->WriteInteger("Help", "HelpHeight", help_window_height);
 Einstellungen->WriteInteger("Help", "HelpWidth", help_window_width);

 //Quickstart
 Einstellungen->WriteString("Quickstart", "QuickStartAppPath1", quickstart_path_1);
 Einstellungen->WriteString("Quickstart", "QuickStartAppDesc1", quickstart_desc_1);
 Einstellungen->WriteString("Quickstart", "QuickStartAppPara1", quickstart_para_1);
 Einstellungen->WriteString("Quickstart", "QuickStartAppPath2", quickstart_path_2);
 Einstellungen->WriteString("Quickstart", "QuickStartAppDesc2", quickstart_desc_2);
 Einstellungen->WriteString("Quickstart", "QuickStartAppPara2", quickstart_para_2);
 Einstellungen->WriteString("Quickstart", "QuickStartAppPath3", quickstart_path_3);
 Einstellungen->WriteString("Quickstart", "QuickStartAppDesc3", quickstart_desc_3);
 Einstellungen->WriteString("Quickstart", "QuickStartAppPara3", quickstart_para_3);
 Einstellungen->WriteString("Quickstart", "QuickStartAppPath4", quickstart_path_4);
 Einstellungen->WriteString("Quickstart", "QuickStartAppDesc4", quickstart_desc_4);
 Einstellungen->WriteString("Quickstart", "QuickStartAppPara4", quickstart_para_4);
 Einstellungen->WriteString("Quickstart", "QuickStartAppPath5", quickstart_path_5);
 Einstellungen->WriteString("Quickstart", "QuickStartAppDesc5", quickstart_desc_5);
 Einstellungen->WriteString("Quickstart", "QuickStartAppPara5", quickstart_para_5);

 // Andere Einstellungen
 Einstellungen->WriteInteger("Others", "Language", editor_language);
 Einstellungen->WriteBool("Others", "UseASCIICode", use_ascii_code);
 Einstellungen->WriteBool("Others", "ReadXHTMLTitle", textarea_read_xhtml_title);
 Einstellungen->WriteString("Others", "LastExplorerDir", DateimanagerExplorer->SelectedPath);
 Einstellungen->WriteInteger("Others", "MaxHistoryEntries", max_history_entries);
 Einstellungen->WriteString("Others", "StandardXHTMLDocumentation", standard_xhtml_documentation);
 Einstellungen->WriteString("Others", "LastProject", ProjekteAuswahl->Items->Strings[ProjekteAuswahl->ItemIndex]);
 Einstellungen->WriteString("Others", "LastProfile", DirektFTPAuswahl->Items->Strings[DirektFTPAuswahl->ItemIndex]);
 Einstellungen->WriteString("Others", "StandardGraphicTool", standard_graphic_tool);
 Einstellungen->WriteBool("Others", "SaveFilesInUnixFormat", textarea_save_files_in_unix);
 Einstellungen->WriteBool("Others", "PrintPlaintext", textarea_print_plaintext);
 Einstellungen->WriteInteger("Others", "TabStops", textarea_tabstops);
 Einstellungen->WriteBool("Others", "WordWrap", textarea_wordwrap);
 Einstellungen->WriteBool("Others", "LineNumbers", textarea_linenumbers);
 Einstellungen->WriteString("Others", "ColorPalette", color_palette);
 Einstellungen->WriteBool("Others", "UseColorNames", use_color_names);
 Einstellungen->WriteBool("Others", "ConvertSpecialChars", textarea_convert_special_chars);
 Einstellungen->WriteString("Others", "StandardTemplate", standard_template);
 Einstellungen->WriteBool("Others", "CreateFileAtStart", editor_file_at_start);
 Einstellungen->WriteBool("Others", "ConnectToFTPAtStart", directftp_connect_at_start);
 Einstellungen->WriteBool("Others", "ShowTip", editor_show_tip);
 Einstellungen->WriteBool("Others", "ReadPluginNameAndAuthor", plugin_read_name_title);
 Einstellungen->WriteBool("Others", "XHTMLMode", editor_xhtml_mode);
 Einstellungen->WriteBool("Others", "TagPHPCompatible", tag_php_compatible);
 Einstellungen->WriteBool("Others", "TagAutomaticPosition", tag_automatic_position);
 Einstellungen->WriteBool("Others", "LocalhostUse", localhost_use);
 Einstellungen->WriteString("Others", "LocalhostAdress", localhost_adress);
 Einstellungen->WriteBool("Others", "TagAutoComplete", tag_auto_complete);
 Einstellungen->WriteBool("Others", "ShowEventsTab", editor_events_tab);
 Einstellungen->WriteString("Others", "IncludesDir", includes_dir);
 Einstellungen->WriteBool("Others", "UseTopStyle", use_topstyle);
 Einstellungen->WriteString("Others", "EditorFontFace", editor_font_face);
 Einstellungen->WriteInteger("Others", "EditorFontSize", editor_font_size);
 Einstellungen->WriteString("Others", "WordDelimiters", editor_word_delimiters);
 Einstellungen->WriteBool("Others", "FirstDate", first_date);
 Einstellungen->WriteBool("Others", "ShowFTPUploadMenue", directftp_show_menue);
 Einstellungen->WriteBool("Others", "CheckConnection", directftp_check_connection);
 Einstellungen->WriteString("Others", "EditorBackground", ColorToString(editor_background_color));

 //Syntax-Farben
 Einstellungen->WriteString("Syntax scheme", "ColorTags", ColorToString(syntax_color_tags));
 Einstellungen->WriteString("Syntax scheme", "ColorAttributes", ColorToString(syntax_color_attributes));
 Einstellungen->WriteString("Syntax scheme", "ColorLinks", ColorToString(syntax_color_links));
 Einstellungen->WriteString("Syntax scheme", "ColorLinkAttrs", ColorToString(syntax_color_linkattrs));
 Einstellungen->WriteString("Syntax scheme", "ColorComments", ColorToString(syntax_color_comments));
 Einstellungen->WriteString("Syntax scheme", "ColorStyles", ColorToString(syntax_color_styles));
 Einstellungen->WriteString("Syntax scheme", "ColorStyleAttrs", ColorToString(syntax_color_styleattrs));
 Einstellungen->WriteString("Syntax scheme", "ColorStyleComments", ColorToString(syntax_color_stylecomments));
 Einstellungen->WriteString("Syntax scheme", "ColorJavascript", ColorToString(syntax_color_javascript));
 Einstellungen->WriteString("Syntax scheme", "ColorTables", ColorToString(syntax_color_tables));
 Einstellungen->WriteString("Syntax scheme", "ColorTableAttrs", ColorToString(syntax_color_tableattrs));
 Einstellungen->WriteString("Syntax scheme", "ColorSpecialchars", ColorToString(syntax_color_specialchars));
 Einstellungen->WriteString("Syntax scheme", "ColorPHPArea", ColorToString(syntax_color_php_area));
 Einstellungen->WriteString("Syntax scheme", "ColorPHPComments", ColorToString(syntax_color_php_comments));
 Einstellungen->WriteString("Syntax scheme", "ColorPHPKeywords", ColorToString(syntax_color_php_keywords));
 Einstellungen->WriteString("Syntax scheme", "ColorPHPAttrs", ColorToString(syntax_color_php_attrs));
 Einstellungen->WriteString("Syntax scheme", "ColorSQLFunctions", ColorToString(syntax_color_sql_functions));
 Einstellungen->WriteString("Syntax scheme", "ColorCSSComments", ColorToString(syntax_color_css_comments));
 Einstellungen->WriteString("Syntax scheme", "ColorCSSStrings", ColorToString(syntax_color_css_strings));
 Einstellungen->WriteString("Syntax scheme", "ColorCSSChars", ColorToString(syntax_color_css_chars));
 Einstellungen->WriteString("Syntax scheme", "ColorCSSTags", ColorToString(syntax_color_css_tags));
 Einstellungen->WriteString("Syntax scheme", "ColorCSSAttrs", ColorToString(syntax_color_css_attrs));
 Einstellungen->WriteBool("Syntax scheme", "BoldTags", syntax_bold_tags);
 Einstellungen->WriteBool("Syntax scheme", "BoldAttributes", syntax_bold_attributes);
 Einstellungen->WriteBool("Syntax scheme", "BoldLinks", syntax_bold_links);
 Einstellungen->WriteBool("Syntax scheme", "BoldLinkAttrs", syntax_bold_linkattrs);
 Einstellungen->WriteBool("Syntax scheme", "BoldComments", syntax_bold_comments);
 Einstellungen->WriteBool("Syntax scheme", "BoldStyles", syntax_bold_styles);
 Einstellungen->WriteBool("Syntax scheme", "BoldStyleAttrs", syntax_bold_styleattrs);
 Einstellungen->WriteBool("Syntax scheme", "BoldStyleComments", syntax_bold_stylecomments);
 Einstellungen->WriteBool("Syntax scheme", "BoldJavascript", syntax_bold_javascript);
 Einstellungen->WriteBool("Syntax scheme", "BoldTables", syntax_bold_tables);
 Einstellungen->WriteBool("Syntax scheme", "BoldTableAttrs", syntax_bold_tableattrs);
 Einstellungen->WriteBool("Syntax scheme", "BoldSpecialchars", syntax_bold_specialchars);
 Einstellungen->WriteBool("Syntax scheme", "BoldPHPArea", syntax_bold_php_area);
 Einstellungen->WriteBool("Syntax scheme", "BoldPHPComments", syntax_bold_php_comments);
 Einstellungen->WriteBool("Syntax scheme", "BoldPHPKeywords", syntax_bold_php_keywords);
 Einstellungen->WriteBool("Syntax scheme", "BoldPHPAttrs", syntax_bold_php_attrs);
 Einstellungen->WriteBool("Syntax scheme", "BoldSQLFunctions", syntax_bold_sql_functions);
 Einstellungen->WriteBool("Syntax scheme", "BoldCSSComments", syntax_bold_css_comments);
 Einstellungen->WriteBool("Syntax scheme", "BoldCSSStrings", syntax_bold_css_strings);
 Einstellungen->WriteBool("Syntax scheme", "BoldCSSChars", syntax_bold_css_chars);
 Einstellungen->WriteBool("Syntax scheme", "BoldCSSTags", syntax_bold_css_tags);
 Einstellungen->WriteBool("Syntax scheme", "BoldCSSAttrs", syntax_bold_css_attrs);
 Einstellungen->WriteBool("Syntax scheme", "ItalicTags", syntax_italic_tags);
 Einstellungen->WriteBool("Syntax scheme", "ItalicAttributes", syntax_italic_attributes);
 Einstellungen->WriteBool("Syntax scheme", "ItalicLinks", syntax_italic_links);
 Einstellungen->WriteBool("Syntax scheme", "ItalicLinkAttrs", syntax_italic_linkattrs);
 Einstellungen->WriteBool("Syntax scheme", "ItalicComments", syntax_italic_comments);
 Einstellungen->WriteBool("Syntax scheme", "ItalicStyles", syntax_italic_styles);
 Einstellungen->WriteBool("Syntax scheme", "ItalicStyleAttrs", syntax_italic_styleattrs);
 Einstellungen->WriteBool("Syntax scheme", "ItalicStyleComments", syntax_italic_stylecomments);
 Einstellungen->WriteBool("Syntax scheme", "ItalicJavascript", syntax_italic_javascript);
 Einstellungen->WriteBool("Syntax scheme", "ItalicTables", syntax_italic_tables);
 Einstellungen->WriteBool("Syntax scheme", "ItalicTableAttrs", syntax_italic_tableattrs);
 Einstellungen->WriteBool("Syntax scheme", "ItalicSpecialchars", syntax_italic_specialchars);
 Einstellungen->WriteBool("Syntax scheme", "ItalicPHPArea", syntax_italic_php_area);
 Einstellungen->WriteBool("Syntax scheme", "ItalicPHPComments", syntax_italic_php_comments);
 Einstellungen->WriteBool("Syntax scheme", "ItalicPHPKeywords", syntax_italic_php_keywords);
 Einstellungen->WriteBool("Syntax scheme", "ItalicPHPAttrs", syntax_italic_php_attrs);
 Einstellungen->WriteBool("Syntax scheme", "ItalicSQLFunctions", syntax_italic_sql_functions);
 Einstellungen->WriteBool("Syntax scheme", "ItalicCSSComments", syntax_italic_css_comments);
 Einstellungen->WriteBool("Syntax scheme", "ItalicCSSStrings", syntax_italic_css_strings);
 Einstellungen->WriteBool("Syntax scheme", "ItalicCSSChars", syntax_italic_css_chars);
 Einstellungen->WriteBool("Syntax scheme", "ItalicCSSTags", syntax_italic_css_tags);
 Einstellungen->WriteBool("Syntax scheme", "ItalicCSSAttrs", syntax_italic_css_attrs);

 delete Einstellungen;

 //------------------------
 // Vom Server disconnecten
 //------------------------
 if (DirectFTPCheckConnection())
 {
  if (DirektFTPClient->Connected)
   DirektFTPClient->Quit();
 }

 //------------------------
 // Temporäre Datei löschen
 //------------------------
 DeleteFile(program_dir + "~temp.html");

 //-------------
 // Rest löschen
 //-------------
 Hilfe->Close();
 InternerBrowser->Close();

 try
 {
  delete msie_helpbrowser;
  delete msie_previewbrowser;
 }
 catch (...)
 {
  1 == 1; // Bis dann
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Beenden1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Druckereinrichten1Click(TObject *Sender)
{
 DruckerSetup->Execute();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::berlappend1Click(TObject *Sender)
{
 Cascade();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Symboleanordnen1Click(TObject *Sender)
{
 ArrangeIcons();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Nebeneinander1Click(TObject *Sender)
{
 TileMode = tbVertical;
 Tile();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Untereinander1Click(TObject *Sender)
{
 TileMode = tbHorizontal;
 Tile();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FensterLeisteChange(TObject *Sender)
{
 String mdi_title = MDIKinderTitel->Items->Strings[FensterLeiste->TabIndex];
 int mdis_count = MDIChildCount;

 for (int i = 0; i < mdis_count; i++)
 {
  if (MDIChildren[i]->Caption == mdi_title)
  {
   MDIChildren[i]->BringToFront();;
   break;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DateimanagerExplorerDirChange(
      TObject *Sender, AnsiString SelectedPath)
{
 String last_char = SelectedPath.AnsiLastChar();

 if (last_char == "\\")
  fileexplorer_dir = SelectedPath;
 else
  fileexplorer_dir = SelectedPath + "\\";

 DateimanagerTemp->Directory = fileexplorer_dir;
 FileFillList(DateimanagerTemp, DateimanagerListe);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DateimanagerListeClick(TObject *Sender)
{
 if (DateimanagerListe->Selected)
 {
  String temp_str = DateimanagerListe->Column[1]->Caption + ": " + DateimanagerListe->Selected->SubItems->Strings[0] + " - " + DateimanagerListe->Selected->SubItems->Strings[2];
  StatusLeiste->Panels->Items[0]->Text = temp_str;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ffnen1Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = SprachenWaehler->GetString(5);
 filter_temp = filter_temp + BuildFilter(docfile_extensions + addlang_extensions_all);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(7);
 filter_temp = filter_temp + BuildFilter(cssfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(21);
 filter_temp = filter_temp + BuildFilter(javascriptfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(6);
 filter_temp = filter_temp + BuildFilter(graphicfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(89);
 filter_temp = filter_temp + " (*.inc)|*.inc";
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;

 if (MDIChildCount)
  OeffnenDialog->InitialDir = ExtractFilePath(ActiveMDIChild->Caption);
 else
 {
  if (VerwControl->ActivePage == VerwTab1)
   OeffnenDialog->InitialDir = fileexplorer_dir;
  else
   OeffnenDialog->InitialDir = projectexplorer_dir;
 }

 OeffnenDialog->Title = ReplaceString(ffnen1->Caption, "&", "", false, true);
 if (OeffnenDialog->Execute())
 {
  for (int i = 0; i < OeffnenDialog->Files->Count; i++)
  {
   if (GraphicFile(OeffnenDialog->Files->Strings[i]))
   {
    graphics_viewer_file = OeffnenDialog->Files->Strings[i];
    TGrafikBetrachter* GrafikBetrachter = new TGrafikBetrachter(Application);
    SprachenWaehler->SetFormLanguage(GrafikBetrachter);
    GrafikBetrachter->Caption = SprachenWaehler->GetString(9);
    GrafikBetrachter->ShowModal();
   }
   else if (CSSFile(OeffnenDialog->Files->Strings[i]))
   {
    CSSEditorFileOpen(OeffnenDialog->Files->Strings[i]);
   }
   else
    CreateChildForm("", OeffnenDialog->Files->Strings[i], "");
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Neu1Click(TObject *Sender)
{
 TNeu* Neu = new TNeu(Application);
 SprachenWaehler->SetFormLanguage(Neu);
 Neu->Caption = ReplaceString(Neu1->Caption, "&", "", false, true);
 Neu->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ffnenausdemInternet1Click(TObject *Sender)
{
 if (DirectFTPCheckConnection())
 {
  TOeffnenausdemInternet* OeffnenausdemInternet = new TOeffnenausdemInternet(Application);
  SprachenWaehler->SetFormLanguage(OeffnenausdemInternet);
  OeffnenausdemInternet->Caption = ReplaceString(ffnenausdemInternet1->Caption, "&", "", false, true);
  OeffnenausdemInternet->ShowModal();
 }
 else
  Application->MessageBox(SprachenWaehler->GetString(36).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONEXCLAMATION);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::HTTPClientDoneFile(TObject *Sender,
      AnsiString FileName, int FileSize)
{
 CreateChildForm("", "", program_dir + "~temp.html");
 Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::BrowserMenuPopup(TObject *Sender)
{
 Browser11->Caption = browser_desc_1;
 Browser21->Caption = browser_desc_2;
 Browser31->Caption = browser_desc_3;

 if (!msie_installed)
 {
  Browserintern->Visible = false;
  N31->Visible = false;
 }
 else
 {
  Browserintern->Visible = true;
  N31->Visible = true;
 }
 if (Trim(browser_path_1) == "")
  Browser11->Visible = false;
 else
  Browser11->Visible = true;
 if (Trim(browser_path_2) == "")
  Browser21->Visible = false;
 else
  Browser21->Visible = true;
 if (Trim(browser_path_3) == "")
  Browser31->Visible = false;
 else
  Browser31->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Schlieen1Click(TObject *Sender)
{
 ActiveMDIChild->Close();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::SeiteMenuPopup(TObject *Sender)
{
 if (MDIChildCount)
 {
  Speichern1->Enabled = true;
  Speichernunter1->Enabled = true;
  SpeichernalsVorlage1->Enabled = true;
  Allespeichern1->Enabled = true;
  Schlieen1->Enabled = true;
  Alleschlieen1->Enabled = true;
  Drucken1->Enabled = true;
 }
 else
 {
  Speichern1->Enabled = false;
  Speichernunter1->Enabled = false;
  SpeichernalsVorlage1->Enabled = false;
  Allespeichern1->Enabled = false;
  Schlieen1->Enabled = false;
  Alleschlieen1->Enabled = false;
  Drucken1->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ProjekteListeClick(TObject *Sender)
{
 if (ProjekteListe->Selected)
 {
  String temp_str = ProjekteListe->Column[1]->Caption + ": " + ProjekteListe->Selected->SubItems->Strings[0] + " - " + ProjekteListe->Selected->SubItems->Strings[2];
  StatusLeiste->Panels->Items[0]->Text = temp_str;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::NeuesProjekt1Click(TObject *Sender)
{
 TNeuesProjekt* NeuesProjekt = new TNeuesProjekt(Application);
 SprachenWaehler->SetFormLanguage(NeuesProjekt);
 NeuesProjekt->Caption = ReplaceString(NeuesProjekt1->Caption, "&", "", false, true);
 NeuesProjekt->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ProjekteAuswahlChange(TObject *Sender)
{
 ProjectsLoadFolders(ProjekteAuswahl->Items->Strings[ProjekteAuswahl->ItemIndex]);
 if (ProjekteAuswahl->ItemIndex != 0)
  (ProjekteExplorer->Items->GetFirstNode())->Selected = true;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ProjekteExplorerChange(TObject *Sender,
      TTreeNode *Node)
{
 if (ProjekteExplorer->Selected != ProjekteExplorer->Items->GetFirstNode())
 {
  String Pfad;
  TTreeNode *TempNode;
  Node->SelectedIndex = 25;
  Pfad = Node->Text;
  TempNode = Node;

  while (TempNode->Parent)
  {
   TempNode = TempNode->Parent;
   if (TempNode != ProjekteExplorer->Items->GetFirstNode())
    Pfad = TempNode->Text + "\\" + Pfad;
  }
  projectexplorer_dir = project_dir + ProjekteAuswahl->Items->Strings[ProjekteAuswahl->ItemIndex] + "\\" + Pfad + "\\";
  ProjektmanagerTemp->Directory = projectexplorer_dir;
  FileFillList(ProjektmanagerTemp, ProjekteListe);
 }
 else
 {
  Node->SelectedIndex = 28;
  projectexplorer_dir = project_dir + ProjekteAuswahl->Items->Strings[ProjekteAuswahl->ItemIndex] + "\\";
  ProjektmanagerTemp->Directory = projectexplorer_dir;
  FileFillList(ProjektmanagerTemp, ProjekteListe);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ProjekteExplorerExpanding(TObject *Sender,
      TTreeNode *Node, bool &AllowExpansion)
{
 Node->DeleteChildren();
 String Pfad;
 String HauptPfad;
 String NebenPfad;
 TTreeNode *TempNode;
 TTreeNode *TempNode2;
 Pfad = Node->Text;
 TempNode = Node;

 if (Node != ProjekteExplorer->Items->GetFirstNode())
 {
  while (TempNode->Parent)
  {
   TempNode = TempNode->Parent;
   if (TempNode != ProjekteExplorer->Items->GetFirstNode())
    Pfad = TempNode->Text + "\\" + Pfad;
  }
  Pfad = project_dir + "\\" + ProjekteAuswahl->Items->Strings[ProjekteAuswahl->ItemIndex] + "\\" + Pfad;
 }
 else
  Pfad = project_dir + "\\" + ProjekteAuswahl->Items->Strings[ProjekteAuswahl->ItemIndex];

 ProjekteOrdner1->Directory = Pfad;
 ProjekteOrdner1->Update();
 ProjekteOrdner2->Update();
 ProjekteOrdner1->Items->Delete(0);
 ProjekteOrdner1->Items->Delete(0);

 for (int i = 0; i < ProjekteOrdner1->Items->Count; i++)
 {
  HauptPfad = ProjekteOrdner1->Items->Strings[i];
  HauptPfad = HauptPfad.SubString(2, HauptPfad.Length());
  HauptPfad = HauptPfad.SubString(0, HauptPfad.Length() - 1);
  TempNode2 = ProjekteExplorer->Items->AddChild(Node, HauptPfad);
  TempNode2->ImageIndex = 26;
  ProjekteOrdner2->Directory = Pfad + "\\" + HauptPfad;
  ProjekteOrdner2->Items->Delete(0);
  ProjekteOrdner2->Items->Delete(0);
  for (int f = 0; f < ProjekteOrdner2->Items->Count; f++)
  {
   NebenPfad = ProjekteOrdner2->Items->Strings[f];
   NebenPfad = NebenPfad.SubString(2, NebenPfad.Length());
   NebenPfad = NebenPfad.SubString(0, NebenPfad.Length() - 1);
   ProjekteExplorer->Items->AddChild (TempNode2, NebenPfad);
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Info1Click(TObject *Sender)
{
 TInfoDialog* InfoDialog = new TInfoDialog(Application);
 InfoDialog->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Speichern1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  if ( (!FileExists(ActiveMDIChild->Caption)) && (AnsiPos(AnsiLowerCase(documents_name), AnsiLowerCase(ActiveMDIChild->Caption)))  && (!AnsiPos("ftp://", AnsiLowerCase(ActiveMDIChild->Caption))))
   Speichernunter1Click(Sender);
  else
   FileSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, ActiveMDIChild->Caption, true);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Speichernunter1Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = SprachenWaehler->GetString(5);
 filter_temp = filter_temp + BuildFilter(docfile_extensions + addlang_extensions_all);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(7);
 filter_temp = filter_temp + BuildFilter(cssfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(21);
 filter_temp = filter_temp + BuildFilter(javascriptfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(89);
 filter_temp = filter_temp + " (*.inc)|*.inc";
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 SpeichernunterDialog->Filter = filter_gesamt;
 SpeichernunterDialog->Title = ReplaceString(Speichernunter1->Caption, "&", "", false, true);

 SpeichernunterDialog->InitialDir = ExtractFilePath(ActiveMDIChild->Caption);
 SpeichernunterDialog->FileName = ExtractFileName(ActiveMDIChild->Caption);

 if (SpeichernunterDialog->Execute())
 {
  FileSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, SpeichernunterDialog->FileName, true);
  int fenster_pos = MDIKinderTitel->Items->IndexOf(ActiveMDIChild->Caption);
  MDIKinderTitel->Items->Strings[fenster_pos] = SpeichernunterDialog->FileName;
  FensterLeiste->Tabs->Strings[fenster_pos] = ExtractFileName(SpeichernunterDialog->FileName);
  ActiveMDIChild->Caption = SpeichernunterDialog->FileName;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Alleschlieen1Click(TObject *Sender)
{
 for (int i = 0; i < MDIChildCount; i++)
 {
  //MDIChildren[i]->BringToFront();
  ActiveMDIChild->Close();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Allespeichern1Click(TObject *Sender)
{
 int mdis_count = MDIChildCount;
 TForm *aktuell;
 aktuell = Hauptformular->ActiveMDIChild;
 for (int i = 0; i < mdis_count; i++)
 {
  MDIChildren[i]->BringToFront();
  FileSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, ActiveMDIChild->Caption, true);
 }
 aktuell->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::SpeichernalsVorlage1Click(TObject *Sender)
{
 String eingabe;
 String endung = ExtractFileExt(ActiveMDIChild->Caption);
 String datei = ExtractFileName(ActiveMDIChild->Caption);
 eingabe = ReplaceString(datei, endung, "", false, true);

 if (InputQuery(ReplaceString(SpeichernalsVorlage1->Caption, "&", "", false, true), SprachenWaehler->GetString(14), eingabe))
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->SaveToFile(program_dir + "Storage!\\Templates\\" + eingabe + ".sct");
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::Drucken1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  TextfeldDrucker->PlainText = textarea_print_plaintext;
  TextfeldDrucker->Print();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::BearbeitenMenuPopup(TObject *Sender)
{
 Rckgngig1->Enabled = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->CanUndo;
 Widerrufen1->Enabled = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->CanRedo;
 Einfgen1->Enabled = Clipboard()->HasFormat(CF_TEXT);

 if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength != 0)
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

 if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Count > 0)
 {
  Allesmarkieren1->Enabled = true;
  Suchen1->Enabled = true;
  Ersetzen1->Enabled = true;
  GehezuZeile1->Enabled = true;
 }
 else
 {
  Allesmarkieren1->Enabled = false;
  Suchen1->Enabled = false;
  Ersetzen1->Enabled = false;
  GehezuZeile1->Enabled = false;
 }

 String line = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Strings[((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine];
 if (Trim(line) != "")
 {
  Einrcken1->Enabled = true;
  Ausrcken1->Enabled = true;
 }
 else
 {
  Einrcken1->Enabled = false;
  Ausrcken1->Enabled = false;
 }
}
//---------------------------------------------------------------------------


void __fastcall THauptformular::Rckgngig1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->CanUndo)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Undo();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Widerrufen1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->CanRedo)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Redo();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Ausschneiden1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength != 0)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->CutToClipboard();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Kopieren1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength != 0)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->CopyToClipboard();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Einfgen1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  if (Clipboard()->HasFormat(CF_TEXT))
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->PasteFromClipboard();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Lschen1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength != 0)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ClearSelection();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Allesmarkieren1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Count > 0)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelectAll();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Suchen1Click(TObject *Sender)
{
 SuchenEinzel->FindText = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
 SuchenEinzel->Execute();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Einrcken1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength != 0)
  {
   String line_check;
   String spaces;
   String line;

   TempMemo->Lines->Clear();
   TempMemo->SelText = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;

   for (int a = 0; a < TempMemo->Lines->Count; a++)
   {
    line_check = TempMemo->Lines->Strings[a];
    if (Trim(line_check) != "")
    {
     spaces = AnsiString::StringOfChar(' ', textarea_tabstops);
     TempMemo->SelLine = a;
     TempMemo->SelCol = 0;
     TempMemo->SelText = spaces;

     line = TempMemo->Lines->Strings[a];
     for (int i = 0; i < line.Length() + 1; i++)
     {
      if (line.SubString(i, 1) != " ")
       break;
     }
    }
   }
   TempMemo->SelectAll();
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = TempMemo->SelText;
  }
  else
  {
   String line_check = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Strings[((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine];
   if (Trim(line_check) != "")
   {
    String spaces = AnsiString::StringOfChar(' ', textarea_tabstops);
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = 0;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = spaces;

    String line = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Strings[((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelPar];
    for (int i = 0; i < line.Length() + 1; i++)
    {
     if (line.SubString(i, 1) != " ")
     {
      ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = i - 1;
      break;
     }
    }
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Ausrcken1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength != 0)
  {
   String line_check;
   int count = 0;
   String now_line;
   String teil;
   String line;

   TempMemo->Lines->Clear();
   TempMemo->SelText = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;

   for (int a = 0; a < TempMemo->Lines->Count; a++)
   {
    line_check = TempMemo->Lines->Strings[a];

    if (Trim(line_check) != "")
    {
     now_line = TempMemo->Lines->Strings[a];
     teil = now_line.SubString(0, textarea_tabstops);
     for (int i = 0; i < teil.Length() + 1; i++)
     {
      if (teil.SubString(i, 1) != " ")
       break;
      count = i;
     }

     TempMemo->SelLine = a;
     TempMemo->SelCol = 0;
     TempMemo->SelLength = count;
     TempMemo->SelText = "";

     line = TempMemo->Lines->Strings[a];
     for (int i = 0; i < line.Length() + 1; i++)
     {
      if (line.SubString(i, 1) != " ")
      {
       TempMemo->SelCol = i - 1;
       break;
      }
     }
     if (TempMemo->SelCol == -1)
      TempMemo->SelCol = 0;
    }
   }
   TempMemo->SelectAll();
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = TempMemo->SelText;
  }
  else
  {
   String line_check = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Strings[((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLine];
   int count = 0;
   String now_line;
   String teil;
   String line;

   if (Trim(line_check) != "")
   {
    now_line = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Strings[((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelPar];
    teil = now_line.SubString(0, textarea_tabstops);

    for (int i = 0; i < teil.Length() + 1; i++)
    {
     if (teil.SubString(i, 1) != " ")
      break;
     count = i;
    }

    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = 0;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = count;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = "";

    line = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Strings[((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelPar];
    for (int i = 0; i < line.Length() + 1; i++)
    {
     if (line.SubString(i, 1) != " ")
     {
      ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = i - 1;
      break;
     }
    }
    if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol == -1)
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol = 0;
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::GehezuZeile1Click(TObject *Sender)
{
 int curline = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelPar;
 String InputString = InputBox(ReplaceString(GehezuZeile1->Caption, "&", "", false, true), SprachenWaehler->GetString(18), String(curline+1));
 int nowline = InputString.ToIntDef(curline);
 nowline = nowline - 1;
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelPar = nowline;
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::SuchenEinzelFind(TObject *Sender)
{
 if (MDIChildCount)
 {
  bool MatchCase = false;
  bool WholeWord = false;
  bool Forward = false;

  if (SuchenEinzel->Options.Contains(frMatchCase))
   MatchCase = true;
  if (SuchenEinzel->Options.Contains(frWholeWord))
   WholeWord = true;
  if (SuchenEinzel->Options.Contains(frDown))
   Forward = true;

  String temp = SprachenWaehler->GetStringEx(16, SuchenEinzel->FindText);

  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt(SuchenEinzel->FindText, Forward, MatchCase, WholeWord, false))
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
  else
   Application->MessageBox(temp.c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);

  Weitersuchen1->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ErweitertesSuchenundErsetzen1Click(
      TObject *Sender)
{
 Suchen->Caption = ReplaceString(ErweitertesSuchenundErsetzen1->Caption, "&", "", false, true);
 Suchen->Caption = ReplaceString(Suchen->Caption, "&", "", false, true);
 Suchen->Show();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Ersetzen1Click(TObject *Sender)
{
 ErsetzenEinzel->FindText = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
 ErsetzenEinzel->Execute();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ErsetzenEinzelFind(TObject *Sender)
{
 bool MatchCase = false;
 bool WholeWord = false;
 bool Forward = false;

 if (ErsetzenEinzel->Options.Contains(frMatchCase))
  MatchCase = true;
 if (ErsetzenEinzel->Options.Contains(frWholeWord))
  WholeWord = true;
 if (ErsetzenEinzel->Options.Contains(frDown))
  Forward = true;

 String temp = SprachenWaehler->GetStringEx(16, ErsetzenEinzel->FindText);

 if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt(ErsetzenEinzel->FindText, Forward, MatchCase, WholeWord, false))
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
 else
  Application->MessageBox(temp.c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ErsetzenEinzelReplace(TObject *Sender)
{
 int start = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
 int laenge = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength;
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = start + laenge;
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = laenge * -1;

 bool MatchCase = false;
 bool WholeWord = false;
 bool Forward = false;

 if (ErsetzenEinzel->Options.Contains(frMatchCase))
  MatchCase = true;
 if (ErsetzenEinzel->Options.Contains(frWholeWord))
  WholeWord = true;
 if (ErsetzenEinzel->Options.Contains(frDown))
  Forward = true;

 String temp = SprachenWaehler->GetStringEx(16, ErsetzenEinzel->FindText);

 if (ErsetzenEinzel->Options.Contains(frReplace))
 {
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt(ErsetzenEinzel->FindText, Forward, MatchCase, WholeWord, false))
  {
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = ErsetzenEinzel->ReplaceText;
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = -1 * (ErsetzenEinzel->ReplaceText.Length());
  }
  else
   Application->MessageBox(temp.c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);
 }
 else
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
  while (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt(ErsetzenEinzel->FindText, Forward, MatchCase, WholeWord, false))
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = ErsetzenEinzel->ReplaceText;
  Application->MessageBox(SprachenWaehler->GetString(19).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Neu2Click(TObject *Sender)
{
 if (addlang_langs_count > 0)
 {
  N17->Visible = true;

  if (AddLangStuff->Items->Count > 0)
  {
   AddLangNewDocLeer11->Visible = true;
   AddLangNewDocLeer11->Caption = ParseString(AddLangStuff->Items->Strings[0], "|", 1);
  }
  if (AddLangStuff->Items->Count > 1)
  {
   AddLangNewDocLeer12->Visible = true;
   AddLangNewDocLeer12->Caption = ParseString(AddLangStuff->Items->Strings[1], "|", 1);
  }
  if (AddLangStuff->Items->Count > 2)
  {
   AddLangNewDocLeer13->Visible = true;
   AddLangNewDocLeer13->Caption = ParseString(AddLangStuff->Items->Strings[2], "|", 1);
  }
 }
 else
 {
  N17->Visible = false;
  AddLangNewDocLeer11->Visible = false;
  AddLangNewDocLeer12->Visible = false;
  AddLangNewDocLeer13->Visible = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ffnen2Click(TObject *Sender)
{
 TListItem *ListItem;
 String gewdatei;
 int items_count = DateimanagerListe->Items->Count;

 if (DateimanagerListe->Selected)
 {
  for (int i = 0; i < items_count; i++)
  {
   ListItem = DateimanagerListe->Items->Item[i];
   if (ListItem->Selected)
   {
    gewdatei = fileexplorer_dir + ListItem->Caption;
    if (GraphicFile(gewdatei))
    {
     TGrafikBetrachter* GrafikBetrachter = new TGrafikBetrachter(Application);
     SprachenWaehler->SetFormLanguage(GrafikBetrachter);
     GrafikBetrachter->Caption = SprachenWaehler->GetString(9);
     GrafikBetrachter->ShowModal();
    }
    else if (CSSFile(gewdatei))
    {
     CSSEditorFileOpen(gewdatei);
    }
    else
     CreateChildForm("", gewdatei, "");
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Ausfhren1Click(TObject *Sender)
{
 String file = fileexplorer_dir + DateimanagerListe->ItemFocused->Caption;
 FileExecute(file, "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DateimanagerListeMenuPopup(TObject *Sender)
{
 if (directftp_show_menue)
 {
  N74->Visible = true;
  Upload2->Visible = true;
 }
 else
 {
  N74->Visible = false;
  Upload2->Visible = false;
 }

 if (DateimanagerListe->Selected)
 {
  ffnen2->Enabled = true;
  Ausfhren1->Enabled = true;
  Kopieren2->Enabled = true;
  Lschen2->Enabled = true;
  Umbenennen1->Enabled = true;
  Eigenschaften1->Enabled = true;
  if (Trim(directftp_current_profile) != "")
   Upload2->Enabled = true;
  else
   Upload2->Enabled = false;
 }
 else
 {
  ffnen2->Enabled = false;
  Ausfhren1->Enabled = false;
  Kopieren2->Enabled = false;
  Lschen2->Enabled = false;
  Umbenennen1->Enabled = false;
  Eigenschaften1->Enabled = false;
  Upload2->Enabled = false;
 }

 if (TempDateiOperationenKopieren->Items->Count)
  Einfgen2->Enabled = true;
 else
  Einfgen2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Kopieren2Click(TObject *Sender)
{
 TListItem *ListItem;
 TempDateiOperationenKopieren->Items->Clear();
 int items_count = DateimanagerListe->Items->Count;

 for (int i = 0; i < items_count; i++)
 {
  ListItem = DateimanagerListe->Items->Item[i];
  if (ListItem->Selected)
   TempDateiOperationenKopieren->Items->Add(fileexplorer_dir + ListItem->Caption);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Einfgen2Click(TObject *Sender)
{
 if (FTPFile(TempDateiOperationenKopieren->Items->Strings[0]))
 {
  String CompleteServer = "ftp://" + DirektFTPClient->Server;
  String path = ReplaceString(DirectFTPURLDecompatible(ExtractFilePath(TempDateiOperationenKopieren->Items->Strings[0])), CompleteServer, "", false, false);

  DirektFTPClient->Asynchronous = true;
  TStrings* StrLst = new TStringList();
  TStrings* StrLst2 = new TStringList();
  for (int i = 0; i < TempDateiOperationenKopieren->Items->Count; i++)
  {
   StrLst->Add(path + ExtractFileName(TempDateiOperationenKopieren->Items->Strings[i]));
   StrLst2->Add(fileexplorer_dir + ExtractFileName(TempDateiOperationenKopieren->Items->Strings[i]));
  }
  DirektFTPClient->GetFile(StrLst, StrLst2);
  while (DirektFTPClient->Busy)
   Application->ProcessMessages();
  DirektFTPClient->Asynchronous = false;
 }
 else
  FileCopy(TempDateiOperationenKopieren, fileexplorer_dir);

 DateimanagerTemp->UpdateFileList();
 FileFillList(DateimanagerTemp, DateimanagerListe);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Aktualisieren1Click(TObject *Sender)
{
 DateimanagerTemp->UpdateFileList();
 FileFillList(DateimanagerTemp, DateimanagerListe);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Lschen2Click(TObject *Sender)
{
 TListItem *ListItem;
 TempDateiOperationenLoeschen->Items->Clear();
 int items_count = DateimanagerListe->Items->Count;

 if (!DateimanagerListe->IsEditing())
 {
  for (int i = 0; i < items_count; i++)
  {
   ListItem = DateimanagerListe->Items->Item[i];
   if (ListItem->Selected)
    TempDateiOperationenLoeschen->Items->Add(fileexplorer_dir + ListItem->Caption);
  }
 }
 FileDelete(TempDateiOperationenLoeschen, false);
 DateimanagerTemp->UpdateFileList();
 FileFillList(DateimanagerTemp, DateimanagerListe);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Umbenennen1Click(TObject *Sender)
{
 DateimanagerListe->ItemFocused->EditCaption();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DateimanagerListeEdited(TObject *Sender,
      TListItem *Item, AnsiString &S)
{
 String Bez_Vorher = Item->Caption;
 String Bez_Nachher = S;
 Bez_Vorher = fileexplorer_dir + Bez_Vorher;
 Bez_Nachher = fileexplorer_dir + Bez_Nachher;
 if (!FileRename(Bez_Vorher, Bez_Nachher))
  S = Item->Caption;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Eigenschaften1Click(TObject *Sender)
{
 String FileName = fileexplorer_dir + DateimanagerListe->ItemFocused->Caption;
 TShellExecuteInfo ShellExecuteInfo;
 ZeroMemory(&ShellExecuteInfo, sizeof(TShellExecuteInfo));
 ShellExecuteInfo.cbSize = sizeof(ShellExecuteInfo);
 ShellExecuteInfo.lpFile = FileName.c_str();
 ShellExecuteInfo.lpVerb = "properties";
 ShellExecuteInfo.fMask  = SEE_MASK_INVOKEIDLIST;
 ShellExecuteEx(&ShellExecuteInfo);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AlleDateien1Click(TObject *Sender)
{
 AlleDateien1->Checked = true;
 DateimanagerTemp->Mask = "*.*";
 Aktualisieren1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Dokumente1Click(TObject *Sender)
{
 String filter_part = "";
 filter_part = "*." + docfile_extensions + addlang_extensions_all;
 filter_part = filter_part.SubString(0, filter_part.Length() - 1);
 Dokumente1->Checked = true;
 DateimanagerTemp->Mask = ReplaceString(filter_part, ";", ";*.", true, true);
 Aktualisieren1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Grafiken1Click(TObject *Sender)
{
 String filter_part = "";
 filter_part = "*." + graphicfile_extensions;
 filter_part = filter_part.SubString(0, filter_part.Length() - 1);
 Grafiken1->Checked = true;
 DateimanagerTemp->Mask = ReplaceString(filter_part, ";", ";*.", true, true);
 Aktualisieren1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Andere1Click(TObject *Sender)
{
 String filter_part = "";
 filter_part = "*." + multimediafile_extensions + cssfile_extensions + javascriptfile_extensions;
 filter_part = filter_part.SubString(0, filter_part.Length() - 1);
 Andere1->Checked = true;
 DateimanagerTemp->Mask = ReplaceString(filter_part, ";", ";*.", true, true);
 Aktualisieren1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::StandardDokumentClick(TObject *Sender)
{
 CreateChildForm(standard_template, "", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton1Click(TObject *Sender)
{
 CreateChildForm(standard_template, "", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AddLangNewDocLeer1Click(TObject *Sender)
{
 String vtemplate = ParseString(AddLangStuff->Items->Strings[0], "|", 2);
 CreateChildForm(vtemplate, "", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AddLangNewDocLeer2Click(TObject *Sender)
{
 String vtemplate = ParseString(AddLangStuff->Items->Strings[1], "|", 2);
 CreateChildForm(vtemplate, "", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AddLangNewDocLeer3Click(TObject *Sender)
{
 String vtemplate = ParseString(AddLangStuff->Items->Strings[2], "|", 2);
 CreateChildForm(vtemplate, "", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ProjekteExplorerMenuPopup(TObject *Sender)
{
 if (ProjekteExplorer->Selected == ProjekteExplorer->Items->GetFirstNode())
 {
  Lschen3->Enabled = false;
  Umbenennen2->Enabled = false;
 }
 else
 {
  Lschen3->Enabled = true;
  Umbenennen2->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Umbenennen2Click(TObject *Sender)
{
 ProjekteExplorer->Selected->EditText();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ProjekteExplorerEdited(TObject *Sender,
      TTreeNode *Node, AnsiString &S)
{
 if (ProjekteExplorer->Selected != ProjekteExplorer->Items->GetFirstNode())
 {
  String hauptpfad = projectexplorer_dir + "@()]";
  hauptpfad = ReplaceString(hauptpfad, Node->Text + "\\@()]", "", false, true);
  String Bez_Vorher = hauptpfad + Node->Text;
  String Bez_Nachher = hauptpfad + S;

  if (RenameFile(Bez_Vorher, Bez_Nachher))
  {
   if (ProjekteAuswahl->ItemIndex != 0)
    (ProjekteExplorer->Items->GetFirstNode())->Selected = true;
  }
  else
   S = Node->Text;
 }
 else
  S = Node->Text;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Aktualisieren2Click(TObject *Sender)
{
 String project_temp = ProjekteAuswahl->Items->Strings[ProjekteAuswahl->ItemIndex];
 ProjectsLoad(project_temp);
 ProjectsLoadFolders(project_temp);
 if (ProjekteAuswahl->ItemIndex != 0)
  (ProjekteExplorer->Items->GetFirstNode())->Selected = true;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Lschen3Click(TObject *Sender)
{
 int button = Application->MessageBox(SprachenWaehler->GetStringEx(22, ProjekteExplorer->Selected->Text).c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON2 + MB_ICONQUESTION);
 if (button == IDYES)
 {
  if (DirectoryDelete(projectexplorer_dir))
   ProjekteExplorer->Selected->Delete();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton28Click(TObject *Sender)
{
 if (ProjekteAuswahl->ItemIndex != 0)
 {
  String project_name = ProjekteAuswahl->Items->Strings[ProjekteAuswahl->ItemIndex];
  int button = Application->MessageBox(SprachenWaehler->GetStringEx(23, project_name).c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON2 + MB_ICONQUESTION);
  if (button == IDYES)
  {
   if (DirectoryDelete(project_dir + project_name + "\\"))
   {
    ProjectsLoad("Zaphod");
    ProjectsLoadFolders("Zaphod");
    if (ProjekteAuswahl->ItemIndex != 0)
     (ProjekteExplorer->Items->GetFirstNode())->Selected = true;
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::NeuerOrdner1Click(TObject *Sender)
{
 TTreeNode *Node;
 TTreeNode *Node_vorher = ProjekteExplorer->Selected;

 String eingabe;
 eingabe = SprachenWaehler->GetString(25) + "_";
 String subfolder_count = Node_vorher->Count + 1;
 eingabe = eingabe + subfolder_count;

 if (InputQuery(ReplaceString(NeuerOrdner1->Caption, "&", "", false, true), SprachenWaehler->GetString(24), eingabe))
 {
  if (CreateDir(projectexplorer_dir + eingabe))
  {
   Node = ProjekteExplorer->Items->AddChild(ProjekteExplorer->Selected, eingabe);
   Node->ImageIndex = 26;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ProjekteListeMenuPopup(TObject *Sender)
{
 if (directftp_show_menue)
 {
  N75->Visible = true;
  Upload3->Visible = true;
 }
 else
 {
  N75->Visible = false;
  Upload3->Visible = false;
 }

 if (ProjekteListe->Selected)
 {
  ffnen3->Enabled = true;
  Ausfhren2->Enabled = true;
  Kopieren3->Enabled = true;
  Lschen4->Enabled = true;
  Umbenennen3->Enabled = true;
  Eigenschaften2->Enabled = true;
  if (Trim(directftp_current_profile) != "")
   Upload3->Enabled = true;
  else
   Upload3->Enabled = false;
 }
 else
 {
  ffnen3->Enabled = false;
  Ausfhren2->Enabled = false;
  Kopieren3->Enabled = false;
  Lschen4->Enabled = false;
  Umbenennen3->Enabled = false;
  Eigenschaften2->Enabled = false;
  Upload3->Enabled = false;
 }

 if (TempDateiOperationenKopieren->Items->Count)
  Einfgen3->Enabled = true;
 else
  Einfgen3->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ffnen3Click(TObject *Sender)
{
 TListItem *ListItem;
 String gewdatei;
 int items_count = ProjekteListe->Items->Count;

 if (ProjekteListe->Selected)
 {
  for (int i = 0; i < items_count; i++)
  {
   ListItem = ProjekteListe->Items->Item[i];
   if (ListItem->Selected)
   {
    gewdatei = projectexplorer_dir + ListItem->Caption;
    if (GraphicFile(gewdatei))
    {
     TGrafikBetrachter* GrafikBetrachter = new TGrafikBetrachter(Application);
     SprachenWaehler->SetFormLanguage(GrafikBetrachter);
     GrafikBetrachter->Caption = SprachenWaehler->GetString(9);
     GrafikBetrachter->ShowModal();
    }
    else if (CSSFile(gewdatei))
    {
     CSSEditorFileOpen(gewdatei);
    }
    else
     CreateChildForm("", gewdatei, "");
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Ausfhren2Click(TObject *Sender)
{
 String file = projectexplorer_dir + ProjekteListe->ItemFocused->Caption;
 FileExecute(file, "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Kopieren3Click(TObject *Sender)
{
 TListItem *ListItem;
 TempDateiOperationenKopieren->Items->Clear();
 int items_count = ProjekteListe->Items->Count;

 for (int i = 0; i < items_count; i++)
 {
  ListItem = ProjekteListe->Items->Item[i];
  if (ListItem->Selected)
   TempDateiOperationenKopieren->Items->Add(projectexplorer_dir + ListItem->Caption);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Einfgen3Click(TObject *Sender)
{
 if (FTPFile(TempDateiOperationenKopieren->Items->Strings[0]))
 {
  String CompleteServer = "ftp://" + DirektFTPClient->Server;
  String path = ReplaceString(DirectFTPURLDecompatible(ExtractFilePath(TempDateiOperationenKopieren->Items->Strings[0])), CompleteServer, "", false, false);

  DirektFTPClient->Asynchronous = true;
  TStrings* StrLst = new TStringList();
  TStrings* StrLst2 = new TStringList();
  for (int i = 0; i < TempDateiOperationenKopieren->Items->Count; i++)
  {
   StrLst->Add(path + ExtractFileName(TempDateiOperationenKopieren->Items->Strings[i]));
   StrLst2->Add(projectexplorer_dir + ExtractFileName(TempDateiOperationenKopieren->Items->Strings[i]));
  }
  DirektFTPClient->GetFile(StrLst, StrLst2);
  while (DirektFTPClient->Busy)
   Application->ProcessMessages();
  DirektFTPClient->Asynchronous = false;
 }
 else
  FileCopy(TempDateiOperationenKopieren, projectexplorer_dir);

 ProjektmanagerTemp->UpdateFileList();
 FileFillList(ProjektmanagerTemp, ProjekteListe);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Lschen4Click(TObject *Sender)
{
 TListItem *ListItem;
 TempDateiOperationenLoeschen->Items->Clear();
 int items_count = ProjekteListe->Items->Count;

 if (!ProjekteListe->IsEditing())
 {
  for (int i = 0; i < items_count; i++)
  {
   ListItem = ProjekteListe->Items->Item[i];
   if (ListItem->Selected)
    TempDateiOperationenLoeschen->Items->Add(projectexplorer_dir + ListItem->Caption);
  }
 }
 FileDelete(TempDateiOperationenLoeschen, false);
 ProjektmanagerTemp->UpdateFileList();
 FileFillList(ProjektmanagerTemp, ProjekteListe);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Umbenennen3Click(TObject *Sender)
{
 ProjekteListe->ItemFocused->EditCaption();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ProjekteListeEdited(TObject *Sender,
      TListItem *Item, AnsiString &S)
{
 String Bez_Vorher = Item->Caption;
 String Bez_Nachher = S;
 Bez_Vorher = projectexplorer_dir + Bez_Vorher;
 Bez_Nachher = projectexplorer_dir + Bez_Nachher;
 if (!FileRename(Bez_Vorher, Bez_Nachher))
  S = Item->Caption;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Aktualisieren3Click(TObject *Sender)
{
 ProjektmanagerTemp->UpdateFileList();
 FileFillList(ProjektmanagerTemp, ProjekteListe);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Eigenschaften2Click(TObject *Sender)
{
 String FileName = projectexplorer_dir + ProjekteListe->ItemFocused->Caption;
 TShellExecuteInfo ShellExecuteInfo;
 ZeroMemory(&ShellExecuteInfo, sizeof(TShellExecuteInfo));
 ShellExecuteInfo.cbSize = sizeof(ShellExecuteInfo);
 ShellExecuteInfo.lpFile = FileName.c_str();
 ShellExecuteInfo.lpVerb = "properties";
 ShellExecuteInfo.fMask  = SEE_MASK_INVOKEIDLIST;
 ShellExecuteEx(&ShellExecuteInfo);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AlleDateien2Click(TObject *Sender)
{
 AlleDateien2->Checked = true;
 ProjektmanagerTemp->Mask = "*.*";
 Aktualisieren3Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Dokumente2Click(TObject *Sender)
{
 String filter_part = "";
 filter_part = "*." + docfile_extensions + addlang_extensions_all;
 filter_part = filter_part.SubString(0, filter_part.Length() - 1);
 Dokumente2->Checked = true;
 ProjektmanagerTemp->Mask = ReplaceString(filter_part, ";", ";*.", true, true);
 Aktualisieren3Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Grafiken2Click(TObject *Sender)
{
 String filter_part = "";
 filter_part = "*." + graphicfile_extensions;
 filter_part = filter_part.SubString(0, filter_part.Length() - 1);
 Grafiken2->Checked = true;
 ProjektmanagerTemp->Mask = ReplaceString(filter_part, ";", ";*.", true, true);
 Aktualisieren3Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Andere2Click(TObject *Sender)
{
 String filter_part = "";
 filter_part = "*." + multimediafile_extensions + cssfile_extensions + javascriptfile_extensions;
 filter_part = filter_part.SubString(0, filter_part.Length() - 1);
 Andere2->Checked = true;
 ProjektmanagerTemp->Mask = ReplaceString(filter_part, ";", ";*.", true, true);
 Aktualisieren3Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Neu3Click(TObject *Sender)
{
 if (addlang_langs_count > 0)
 {
  N21->Visible = true;

  if (AddLangStuff->Items->Count > 0)
  {
   AddLangNewDocLeer21->Visible = true;
   AddLangNewDocLeer21->Caption = ParseString(AddLangStuff->Items->Strings[0], "|", 1);
  }
  if (AddLangStuff->Items->Count > 1)
  {
   AddLangNewDocLeer22->Visible = true;
   AddLangNewDocLeer22->Caption = ParseString(AddLangStuff->Items->Strings[1], "|", 1);
  }
  if (AddLangStuff->Items->Count > 2)
  {
   AddLangNewDocLeer23->Visible = true;
   AddLangNewDocLeer23->Caption = ParseString(AddLangStuff->Items->Strings[2], "|", 1);
  }
 }
 else
 {
  N21->Visible = false;
  AddLangNewDocLeer21->Visible = false;
  AddLangNewDocLeer22->Visible = false;
  AddLangNewDocLeer23->Visible = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FarbPaletteBildMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 FarbPaletteShape->Brush->Color = FarbPaletteBild->Canvas->Pixels[X][Y];
 if (FarbPaletteShape->Brush->Color < 10000000)
  AktuelleFarbeinPalette->Font->Color = clWhite;
 else
  AktuelleFarbeinPalette->Font->Color = clBlack;
 AktuelleFarbeinPalette->Caption = ColorColorToXHTMLCode(FarbPaletteShape->Brush->Color);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FarbPaletteBildClick(TObject *Sender)
{
 if (MDIChildCount)
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = AktuelleFarbeinPalette->Caption;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton29Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = SprachenWaehler->GetString(26);
 filter_temp = filter_temp + " (*.bmp,*.gif,*.jpg,*.jpeg,*.png)|*.bmp;*.gif;*.jpg;*.jpeg;*.png";
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 PaletteOeffnenDialog->Filter = filter_gesamt;
 PaletteOeffnenDialog->Title = ToolButton29->Hint;

 if (PaletteOeffnenDialog->Execute())
 {
  color_palette = PaletteOeffnenDialog->FileName;
  Graphics::TPicture* color_pic = new Graphics::TPicture();
  color_pic->LoadFromFile(color_palette);
  Graphics::TBitmap* color_bitmap = new Graphics::TBitmap();
  color_bitmap->Assign(color_pic->Graphic);
  FarbPaletteBild->Picture->Bitmap = color_bitmap;
  if (FarbPaletteBild->Picture->Width < ScrollBox1->Width)
   FarbPaletteBild->Left = ((ScrollBox1->Width / 2) - 3) - (FarbPaletteBild->Picture->Width / 2);
  else
   FarbPaletteBild->Left = 0;
  if (FarbPaletteBild->Picture->Height < ScrollBox1->Height)
   FarbPaletteBild->Top = ((ScrollBox1->Height / 2) - 3) - (FarbPaletteBild->Picture->Height / 2);
  else
   FarbPaletteBild->Top = 0;
  FarbPaletteEdit->Text = ExtractFileName(color_palette);
  delete color_bitmap;
  delete color_pic;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton30Click(TObject *Sender)
{
 TColor temp_color = FarbPaletteShape->Brush->Color;
 TColor temp_color2;

 temp_color2 = ColorWindowsDialogShow(FarbPaletteShape->Brush->Color);
 if (temp_color != temp_color2)
 {
  AktuelleFarbeinPalette->Caption = ColorColorToXHTMLCode(temp_color2);
  FarbPaletteShape->Brush->Color = temp_color2;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::SonderZeichenPaneelResize(TObject *Sender)
{
 if (SonderZeichenGrid->Width < SonderZeichenPaneel->Width)
  SonderZeichenGrid->Left = ((SonderZeichenPaneel->Width + 2) / 2) - (SonderZeichenGrid->Width / 2);
 else
  SonderZeichenGrid->Left = 0;
 if (SonderZeichenGrid->Height < SonderZeichenPaneel->Height)
  SonderZeichenGrid->Top = ((SonderZeichenPaneel->Height + 2) / 2) - (SonderZeichenGrid->Height / 2);
 else
  SonderZeichenGrid->Top = 0;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ScrollBox1Resize(TObject *Sender)
{
 if (FarbPaletteBild->Picture->Width < ScrollBox1->Width)
  FarbPaletteBild->Left = ((ScrollBox1->Width / 2) - 3) - (FarbPaletteBild->Picture->Width / 2);
 else
  FarbPaletteBild->Left = 0;
 if (FarbPaletteBild->Picture->Height < ScrollBox1->Height)
  FarbPaletteBild->Top = ((ScrollBox1->Height / 2) - 3) - (FarbPaletteBild->Picture->Height / 2);
 else
  FarbPaletteBild->Top = 0;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::VerwControlChange(TObject *Sender)
{
 if (VerwControl->ActivePage == VerwTab1)
  StatusLeiste->Panels->Items[2]->Text = String(DateimanagerListe->Items->Count) + " " + SprachenWaehler->GetString(28);
 else if (VerwControl->ActivePage == VerwTab2)
  StatusLeiste->Panels->Items[2]->Text = String(ProjekteListe->Items->Count) + " " + SprachenWaehler->GetString(28);
 else
  StatusLeiste->Panels->Items[2]->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::SonderZeichenGridMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 try
 {
  int ACol, ARow;
  TPoint plPoint;
  ::GetCursorPos(&plPoint);
  plPoint = SonderZeichenGrid->ScreenToClient(plPoint);
  SonderZeichenGrid->MouseToCell(plPoint.x, plPoint.y, ACol, ARow);
  char *zeichen = SonderZeichenGrid->Cells[ACol][ARow].c_str();
  int zeichen_ascii = zeichen[0];
  if (zeichen_ascii < 0)
   zeichen_ascii = zeichen_ascii + 256;
  if (SonderzeichenCodes->Items->IndexOf(zeichen_ascii) > -1)
   StatusLeiste->Panels->Items[0]->Text = ParseString(SonderzeichenDescs->Items->Strings[SonderzeichenCodes->Items->IndexOf(zeichen_ascii)], "|", editor_language);
  delete zeichen;
 }
 catch (...)
 {
  1 == 1;
 }
}
//---------------------------------------------------------------------------


void __fastcall THauptformular::SonderZeichenGridClick(TObject *Sender)
{
 if (MDIChildCount)
 {
  char *zeichen = SonderZeichenGrid->Cells[SonderZeichenGrid->Col][SonderZeichenGrid->Row].c_str();
  int zeichen_ascii = zeichen[0];
  if (zeichen_ascii < 0)
   zeichen_ascii = zeichen_ascii + 256;
  if (use_ascii_code)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = "&#" + String(zeichen_ascii) + ";";
  else
  {
   if (SonderzeichenCodes->Items->IndexOf(zeichen_ascii) > -1)
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = SonderzeichenNames->Items->Strings[SonderzeichenCodes->Items->IndexOf(zeichen_ascii)];
  }
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AnsichtMenuPopup(TObject *Sender)
{
 ExternerBrowser11->Caption = SprachenWaehler->GetString(29) + " " + browser_desc_1;
 ExternerBrowser21->Caption = SprachenWaehler->GetString(29) + " " + browser_desc_2;
 ExternerBrowser31->Caption = SprachenWaehler->GetString(29) + " " + browser_desc_3;

 if (!msie_installed)
 {
  InternerBrowser1->Visible = false;
  N27->Visible = false;
 }
 else
 {
  InternerBrowser1->Visible = true;
  N27->Visible = true;
 }
 if (Trim(browser_path_1) == "")
  ExternerBrowser11->Visible = false;
 else
  ExternerBrowser11->Visible = true;
 if (Trim(browser_path_2) == "")
  ExternerBrowser21->Visible = false;
 else
  ExternerBrowser21->Visible = true;
 if (Trim(browser_path_3) == "")
  ExternerBrowser31->Visible = false;
 else
  ExternerBrowser31->Visible = true;

 if (MDIChildCount)
  Dokumenteinfrbungaktualisieren1->Enabled = true;
 else
  Dokumenteinfrbungaktualisieren1->Enabled = false;

 Verwaltung1->Checked = VerwaltungsPaneel->Visible;
 Statusleiste1->Checked = StatusLeiste->Visible;
 Zeilennummerierung1->Checked = textarea_linenumbers;
 Zeilenumbruch1->Checked = textarea_wordwrap;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::InternerBrowser1Click(TObject *Sender)
{
 if (msie_installed)
 {
  if (MDIChildCount)
  {
   if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Modified)
   {
    if (browser_confirm_save)
    {
     if (FileAskSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, ActiveMDIChild->Caption))
      InternalBrowserShow(ActiveMDIChild->Caption);
    }
    else
    {
     FileSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, ActiveMDIChild->Caption, true);
     InternalBrowserShow(ActiveMDIChild->Caption);
    }
   }
   else
    InternalBrowserShow(ActiveMDIChild->Caption);
  }
  else
   InternalBrowserShow("");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ExternerBrowser11Click(TObject *Sender)
{
 if (Trim(browser_path_1) != "")
 {
  if (MDIChildCount)
  {
   if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Modified)
   {
    if (browser_confirm_save)
    {
     if (FileAskSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, ActiveMDIChild->Caption))
      BrowserShow(1, ActiveMDIChild->Caption);
    }
    else
    {
     FileSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, ActiveMDIChild->Caption, true);
     BrowserShow(1, ActiveMDIChild->Caption);
    }
   }
   else
    BrowserShow(1, ActiveMDIChild->Caption);
  }
  else
   BrowserShow(1, "");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ExternerBrowser21Click(TObject *Sender)
{
 if (Trim(browser_path_2) != "")
 {
  if (MDIChildCount)
  {
   if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Modified)
   {
    if (browser_confirm_save)
    {
     if (FileAskSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, ActiveMDIChild->Caption))
      BrowserShow(2, ActiveMDIChild->Caption);
    }
    else
    {
     FileSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, ActiveMDIChild->Caption, true);
     BrowserShow(2, ActiveMDIChild->Caption);
    }
   }
   else
    BrowserShow(2, ActiveMDIChild->Caption);
  }
  else
   BrowserShow(2, "");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ExternerBrowser31Click(TObject *Sender)
{
 if (Trim(browser_path_3) != "")
 {
  if (MDIChildCount)
  {
   if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Modified)
   {
    if (browser_confirm_save)
    {
     if (FileAskSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, ActiveMDIChild->Caption))
      BrowserShow(3, ActiveMDIChild->Caption);
    }
    else
    {
     FileSave(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld, ActiveMDIChild->Caption, true);
     BrowserShow(3, ActiveMDIChild->Caption);
    }
   }
   else
    BrowserShow(3, ActiveMDIChild->Caption);
  }
  else
   BrowserShow(3, "");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Verwaltung1Click(TObject *Sender)
{
 if (Verwaltung1->Checked)
 {
  VerwaltungsPaneel->Visible = false;
  Verwaltung1->Checked = false;
 }
 else
 {
  VerwaltungsPaneel->Visible = true;
  Verwaltung1->Checked = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Statusleiste1Click(TObject *Sender)
{
 if (Statusleiste1->Checked)
 {
  StatusLeiste->Visible = false;
  Statusleiste1->Checked = false;
 }
 else
 {
  StatusLeiste->Visible = true;
  Statusleiste1->Checked = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Zeilennummerierung1Click(TObject *Sender)
{
 if (Zeilennummerierung1->Checked)
 {
  textarea_linenumbers = false;
  Zeilennummerierung1->Checked = false;
 }
 else
 {
  textarea_linenumbers = true;
  Zeilennummerierung1->Checked = true;
 }

 int mdis_count = Hauptformular->MDIChildCount;
 for (int i = 0; i < mdis_count; i++)
  Hauptformular->MDIChildren[i]->OnShow(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Dokumenteinfrbungaktualisieren1Click(
      TObject *Sender)
{
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ReApplyKeywords();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Zeilenumbruch1Click(TObject *Sender)
{
 if (Zeilenumbruch1->Checked)
 {
  textarea_wordwrap = false;
  Zeilenumbruch1->Checked = false;
 }
 else
 {
  textarea_wordwrap = true;
  Zeilenumbruch1->Checked = true;
 }

 for (int i = 0; i < Hauptformular->MDIChildCount; i++)
  Hauptformular->MDIChildren[i]->OnShow(Sender);
}
//---------------------------------------------------------------------------


void __fastcall THauptformular::DirektFTPAuswahlChange(TObject *Sender)
{
 if (DirektFTPAuswahl->ItemIndex != 0)
 {
  DirektFTPExplorer->Enabled = true;
  DirektFTPListe->Enabled = true;
 }
 else
 {
  DirektFTPExplorer->Enabled = false;
  DirektFTPListe->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::NeuerOrdner2Click(TObject *Sender)
{
 String eingabe;
 eingabe = SprachenWaehler->GetString(25) + "_";
 String subfolder_count = DirektFTPExplorer->Items->Count + 1;
 eingabe = eingabe + subfolder_count;

 if (InputQuery(ReplaceString(NeuerOrdner2->Caption, "&", "", false, true), SprachenWaehler->GetString(24), eingabe))
 {
  directftp_temp_input = eingabe;
  DirektFTPClient->CreateFTPDirectory(eingabe);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Lschen5Click(TObject *Sender)
{
 directftp_temp_input = DirektFTPExplorer->ItemFocused->Caption;
 DirektFTPClient->DeleteDirectory(DirektFTPExplorer->ItemFocused->Caption);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Umbenennen4Click(TObject *Sender)
{
 DirektFTPExplorer->ItemFocused->EditCaption();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPAktualisieren(TObject *Sender)
{
 DirektFTPExplorer->Items->Clear();
 DirektFTPListe->Items->Clear();

 DirektFTPClient->Refresh();

 TListItem *ListItem_1;
 TListItem *ListItem_2;
 TListItem *ListItem_3;

 //--------------------
 String CompleteServer = "ftp://" + DirektFTPClient->Server;
 String PathResult = ReplaceString(DirektFTPClient->URL, CompleteServer, "", true, true);
 if (PathResult != "/")
 {
  ListItem_3 = DirektFTPExplorer->Items->Add();
  ListItem_3->Caption = SprachenWaehler->GetString(40);
  ListItem_3->ImageIndex = 42;
 }
 //--------------------

 for (int i = 0; i < DirektFTPTemp->Items->Count; i++)
 {
  ListItem_1 = DirektFTPTemp->Items->Item[i];

  if (ListItem_1->SubItems->Strings[1] == "File Folder")
  {
   ListItem_2 = DirektFTPExplorer->Items->Add();
   ListItem_2->Caption = ListItem_1->Caption;
   ListItem_2->ImageIndex = 40;
   DirektFTPExplorer->Update();
  }
  else
  {
   ListItem_2 = DirektFTPListe->Items->Add();
   ListItem_2->Caption = ListItem_1->Caption;
   ListItem_2->ImageIndex = FileCalculateIcon(ListItem_1->Caption);
   ListItem_2->SubItems->Add(ListItem_1->SubItems->Strings[0].Insert(" ", ListItem_1->SubItems->Strings[0].AnsiPos("KB")));
   ListItem_2->SubItems->Add(ListItem_1->SubItems->Strings[1]);
   ListItem_2->SubItems->Add(ConvertDateToDatum(ListItem_1->SubItems->Strings[2]));
   DirektFTPListe->Update();
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton31Click(TObject *Sender)
{
 directftp_temp_input = "";
 if (DirektFTPAuswahl->ItemIndex != 0)
 {
  if (DirectFTPCheckConnection())
  {
   String sel_profil = DirektFTPAuswahl->Items->Strings[DirektFTPAuswahl->ItemIndex];
   if (Trim(directftp_current_profile) != "")
    DirektFTPClient->Quit();

   TIniFile* Profil = new TIniFile(program_dir + "Storage!\\ftpprofiles.ini");

   DirektFTPClient->Account = Profil->ReadString(sel_profil, "Account", "");
   DirektFTPClient->NoopInterval = Profil->ReadInteger(sel_profil, "NoopInterval", 30);
   DirektFTPClient->Passive = Profil->ReadBool(sel_profil, "Passive", false);
   //-----------------------------
   String password_temp = Base64Decode(Profil->ReadString(sel_profil, "Password", ""));
   if (Trim(password_temp) == "")
   {
    TDirektesFTPPasswort* DirektesFTPPasswort = new TDirektesFTPPasswort(Application);
    SprachenWaehler->SetFormLanguage(DirektesFTPPasswort);
    DirektesFTPPasswort->ShowModal();
    DirektFTPClient->Password = directftp_temp_input;

   }
   else
    DirektFTPClient->Password = password_temp;
   //-----------------------------
   DirektFTPClient->Port = Profil->ReadInteger(sel_profil, "Port", 21);
   DirektFTPClient->ProxyPassword = Base64Decode(Profil->ReadString(sel_profil, "ProxyPassword", ""));
   DirektFTPClient->ProxyPort = Profil->ReadInteger(sel_profil, "ProxyPort", 21);
   DirektFTPClient->ProxyServer = Profil->ReadString(sel_profil, "ProxyServer", "");
   //-----------------------------
   if (Profil->ReadString(sel_profil, "ProxyType", "None") == "Host")
    DirektFTPClient->ProxyType = proxyHost;
   else if (Profil->ReadString(sel_profil, "ProxyType", "None") == "Host user")
    DirektFTPClient->ProxyType = proxyHostUser;
   else if (Profil->ReadString(sel_profil, "ProxyType", "None") == "Open")
    DirektFTPClient->ProxyType = proxyOpen;
   else if (Profil->ReadString(sel_profil, "ProxyType", "None") == "Site")
    DirektFTPClient->ProxyType = proxySite;
   else if (Profil->ReadString(sel_profil, "ProxyType", "None") == "User site")
    DirektFTPClient->ProxyType = proxyUserSite;
   else
    DirektFTPClient->ProxyType = proxyNone;
   //-----------------------------
   DirektFTPClient->ProxyUsername = Profil->ReadString(sel_profil, "ProxyUsername", "");
   DirektFTPClient->Retries = Profil->ReadInteger(sel_profil, "Retries", 5);
   DirektFTPClient->RetryInterval = Profil->ReadInteger(sel_profil, "RetryInterval", 15);
   DirektFTPClient->Server = Profil->ReadString(sel_profil, "Server", "");
   DirektFTPClient->TimeOut = Profil->ReadInteger(sel_profil, "TimeOut", 20);
   //-----------------------------
   if (Profil->ReadString(sel_profil, "TransferMode", "BinaryTransfer") == "BinaryTransfer")
    DirektFTPClient->TransferMode = BinaryTransfer;
   else
    DirektFTPClient->TransferMode = AsciiTransfer;
   //-----------------------------
   DirektFTPClient->Username = Profil->ReadString(sel_profil, "Username", "Anonymous");

   delete Profil;

   DirektFTPClient->Login();
  }
  else
   Application->MessageBox(SprachenWaehler->GetString(36).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONEXCLAMATION);
 }
 directftp_temp_input = "";
}
//---------------------------------------------------------------------------


void __fastcall THauptformular::DirektFTPExplorerMenuPopup(TObject *Sender)
{
 if (Trim(directftp_current_profile) != "")
 {
  NeuerOrdner2->Enabled = true;
  Lschen5->Enabled = DirektFTPExplorer->Selected;
  Umbenennen4->Enabled = DirektFTPExplorer->Selected;
  Aktualisieren4->Enabled = true;
  //------------------
  if (DirektFTPExplorer->Selected)
  {
   String Caption = (DirektFTPExplorer->Selected)->Caption;
   if (Caption == SprachenWaehler->GetString(40))
   {
    Lschen5->Enabled = false;
    Umbenennen4->Enabled = false;
   }
   else
   {
    Lschen5->Enabled = true;
    Umbenennen4->Enabled = true;
   }
  }
 }
 else
 {
  NeuerOrdner2->Enabled = false;
  Lschen5->Enabled = false;
  Umbenennen4->Enabled = false;
  Aktualisieren4->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPListeMenuPopup(TObject *Sender)
{
 if (Trim(directftp_current_profile) != "")
 {
  ffnen4->Enabled = DirektFTPListe->Selected;
  Neu4->Enabled = true;
  Kopieren4->Enabled = DirektFTPListe->Selected;
  Lschen6->Enabled = DirektFTPListe->Selected;
  Umbenennen5->Enabled = DirektFTPListe->Selected;
  Filter3->Enabled = true;
  Aktualisieren5->Enabled = true;
  Eigenschaften3->Enabled = DirektFTPListe->Selected;

  if (TempDateiOperationenKopieren->Items->Count)
  {
   if (FTPFile(TempDateiOperationenKopieren->Items->Strings[0]))
    Einfgen4->Enabled = false;
   else
    Einfgen4->Enabled = true;
  }
  else
   Einfgen4->Enabled = false;
 }
 else
 {
  ffnen4->Enabled = false;
  Neu4->Enabled = false;
  Kopieren4->Enabled = false;
  Einfgen4->Enabled = false;
  Lschen6->Enabled = false;
  Umbenennen5->Enabled = false;
  Filter3->Enabled = false;
  Aktualisieren5->Enabled = false;
  Eigenschaften3->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientFtpQuit(TObject *Sender)
{
 DirektFTPStatus->Position = 0;
 Screen->Cursor = crDefault;
 directftp_current_profile = "";
 directftp_temp_input = "";
 directftp_current_dir = projectexplorer_dir;;
 DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(35);
 DirektFTPLabel->Hint = SprachenWaehler->GetString(35);
 DirektFTPExplorer->Items->Clear();
 DirektFTPListe->Items->Clear();
 if (TempDateiOperationenKopieren->Items->Count)
 {
  if (FTPFile(TempDateiOperationenKopieren->Items->Strings[0]))
   TempDateiOperationenKopieren->Items->Clear();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton32Click(TObject *Sender)
{
 if (Trim(directftp_current_profile) != "")
  DirektFTPClient->Quit();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientLoggedIn(TObject *Sender)
{
 DirektFTPStatus->Position = 0;
 DirektFTPExplorer->Items->Clear();
 DirektFTPListe->Items->Clear();

 directftp_current_profile = DirektFTPAuswahl->Items->Strings[DirektFTPAuswahl->ItemIndex];
 DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(34);
 DirektFTPLabel->Hint = SprachenWaehler->GetString(34);
 DirektFTPClient->Refresh();
 directftp_current_dir = DirectFTPURLCompatible(DirektFTPClient->URL);

 TListItem *ListItem_1;
 TListItem *ListItem_2;
 for (int i = 0; i < DirektFTPTemp->Items->Count; i++)
 {
  ListItem_1 = DirektFTPTemp->Items->Item[i];

  if (ListItem_1->SubItems->Strings[1] == "File Folder")
  {
   ListItem_2 = DirektFTPExplorer->Items->Add();
   ListItem_2->Caption = ListItem_1->Caption;
   ListItem_2->ImageIndex = 40;
   DirektFTPExplorer->Update();
  }
  else
  {
   ListItem_2 = DirektFTPListe->Items->Add();
   ListItem_2->Caption = ListItem_1->Caption;
   ListItem_2->ImageIndex = FileCalculateIcon(ListItem_1->Caption);
   ListItem_2->SubItems->Add(ListItem_1->SubItems->Strings[0].Insert(" ", ListItem_1->SubItems->Strings[0].AnsiPos("KB")));
   ListItem_2->SubItems->Add(ListItem_1->SubItems->Strings[1]);
   ListItem_2->SubItems->Add(ConvertDateToDatum(ListItem_1->SubItems->Strings[2]));
   DirektFTPListe->Update();
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientFtpInfo(TObject *Sender,
      FtpInfo info, AnsiString addinfo)
{
 if (info == ftpDataTrace)
  DirektFTPStatus->Position = DirektFTPClient->BytesTransferred;
 else if (info == ftpFileSize)
  DirektFTPStatus->Max = addinfo.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientFtpReady(TObject *Sender)
{
 DirektFTPStatus->Position = 0;
 Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientFtpBusy(TObject *Sender)
{
 Screen->Cursor = crHourGlass;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientFtpError(TObject *Sender,
      FtpError error, AnsiString addinfo)
{
 DirektFTPStatus->Position = 0;
 if (!DirektFTPClient->Connected)
  Application->MessageBox(SprachenWaehler->GetString(37).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientFileTransferred(
      TObject *Sender)
{
 if (DirektFTPClient->Success)
 {
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(38);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(38);
 }
 else
 {
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(39);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(39);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientAborted(TObject *Sender)
{
 DirektFTPClient->Asynchronous = false;
 Application->ProcessMessages();
 DirektFTPStatus->Position = 0;
 DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(43);
 DirektFTPLabel->Hint = SprachenWaehler->GetString(43);
 directftp_temp_input = "";
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientDirectoryChanged(
      TObject *Sender)
{
 DirektFTPExplorer->Items->Clear();
 DirektFTPListe->Items->Clear();

 DirektFTPLabel->Caption = " " + SprachenWaehler->GetStringEx(41, ReplaceString(DirektFTPClient->URL, ("ftp://" + DirektFTPClient->Server), "", true, true));
 DirektFTPLabel->Hint = SprachenWaehler->GetStringEx(41, ReplaceString(DirektFTPClient->URL, ("ftp://" + DirektFTPClient->Server), "", true, true));
 DirektFTPClient->Refresh();
 directftp_current_dir = DirectFTPURLCompatible(DirektFTPClient->URL);

 TListItem *ListItem_1;
 TListItem *ListItem_2;
 TListItem *ListItem_3;

 //--------------------
 String CompleteServer = "ftp://" + DirektFTPClient->Server;
 String PathResult = ReplaceString(DirektFTPClient->URL, CompleteServer, "", true, true);
 if (PathResult != "/")
 {
  ListItem_3 = DirektFTPExplorer->Items->Add();
  ListItem_3->Caption = SprachenWaehler->GetString(40);
  ListItem_3->ImageIndex = 42;
 }
 //--------------------

 for (int i = 0; i < DirektFTPTemp->Items->Count; i++)
 {
  ListItem_1 = DirektFTPTemp->Items->Item[i];

  if (ListItem_1->SubItems->Strings[1] == "File Folder")
  {
   ListItem_2 = DirektFTPExplorer->Items->Add();
   ListItem_2->Caption = ListItem_1->Caption;
   ListItem_2->ImageIndex = 40;
   DirektFTPExplorer->Update();
  }
  else
  {
   ListItem_2 = DirektFTPListe->Items->Add();
   ListItem_2->Caption = ListItem_1->Caption;
   ListItem_2->ImageIndex = FileCalculateIcon(ListItem_1->Caption);
   ListItem_2->SubItems->Add(ListItem_1->SubItems->Strings[0].Insert(" ", ListItem_1->SubItems->Strings[0].AnsiPos("KB")));
   ListItem_2->SubItems->Add(ListItem_1->SubItems->Strings[1]);
   ListItem_2->SubItems->Add(ConvertDateToDatum(ListItem_1->SubItems->Strings[2]));
   DirektFTPListe->Update();
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientDirectoryCreated(
      TObject *Sender)
{
 if (DirektFTPClient->Success)
 {
  TListItem *ListItem;
  ListItem = DirektFTPExplorer->Items->Add();
  ListItem->Caption = directftp_temp_input;
  ListItem->ImageIndex = 40;
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(44);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(44);
 }
 else
 {
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(45);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(45);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientDirectoryDeleted(
      TObject *Sender)
{
 if (DirektFTPClient->Success)
 {
  (DirektFTPExplorer->ItemFocused)->Delete();
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(46);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(46);
 }
 else
 {
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(47);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(47);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientFileDeleted(TObject *Sender)
{
 if (DirektFTPClient->Success)
 {
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(50);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(50);
 }
 else
 {
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(51);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(51);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientFileReceived(
      TObject *Sender)
{
 if (DirektFTPClient->Success)
 {
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(54);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(54);
 }
 else
 {
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(55);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(55);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPClientFileRenamed(TObject *Sender)
{
 if (DirektFTPClient->Success)
 {
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(48);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(48);
 }
 else
 {
  DirektFTPLabel->Caption = " " + SprachenWaehler->GetString(49);
  DirektFTPLabel->Hint = SprachenWaehler->GetString(49);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ffnen4Click(TObject *Sender)
{
 if (GraphicFile(DirektFTPListe->ItemFocused->Caption))
 {
  String datei = AnsiLowerCase(ExtractFileExt(DirektFTPListe->ItemFocused->Caption));
  if (datei == ".gif")
   datei = program_dir + "~temp.gif";
  else if (datei == ".jpg")
   datei = program_dir + "~temp.jpg";
  else if (datei == ".png")
   datei = program_dir + "~temp.png";
  else if (datei == ".jpeg")
   datei = program_dir + "~temp.jpg";
  else if (datei == ".bmp")
   datei = program_dir + "~temp.bmp";

  if (Trim(datei) != "")
  {
   DirektFTPClient->GetFile(DirektFTPListe->ItemFocused->Caption, datei);
   graphics_viewer_file = datei;
   TGrafikBetrachter* GrafikBetrachter = new TGrafikBetrachter(Application);
   SprachenWaehler->SetFormLanguage(GrafikBetrachter);
   GrafikBetrachter->Caption = SprachenWaehler->GetString(9);
   GrafikBetrachter->ShowModal();
  }
  DeleteFile(datei);
 }
 //else if (CSSFile(DirektFTPListe->ItemFocused->Caption))
 // CSSEditorFileOpen(directftp_current_dir + DirektFTPListe->ItemFocused->Caption);
 else
 {
  int mdis_count = MDIChildCount;
  bool schon_vorhanden = false;

  for (int i = 0; i < mdis_count; i++)
  {
   if (MDIChildren[i]->Caption == (directftp_current_dir + DirektFTPListe->ItemFocused->Caption))
   {
    schon_vorhanden = true;
    MDIChildren[i]->BringToFront();
    break;
   }
  }

  if (!schon_vorhanden)
  {
   DeleteFile(program_dir + "~temp.html");
   DirektFTPClient->GetFile(DirektFTPListe->ItemFocused->Caption, program_dir + "~temp.html");
   LockWindowUpdate(Application->MainForm->ClientHandle);
   TKindFormular* KindFormular = new TKindFormular(Application);
   LockWindowUpdate(NULL);
   KindFormular->Caption =  directftp_current_dir + (DirektFTPListe->ItemFocused->Caption);
   KindFormular->Textfeld->Lines->LoadFromFile(program_dir + "~temp.html");
   KindFormular->Textfeld->SetFocus();
   KindFormular->Textfeld->Modified = false;
   KindFormular->Textfeld->ClearUndo();
   FensterLeiste->Tabs->Add(ExtractFileName(KindFormular->Caption));
   MDIKinderTitel->Items->Add(KindFormular->Caption);
   FensterLeiste->TabIndex = FensterLeiste->Tabs->Count - 1;
   KindFormular->Title->Caption = SearchXHTMLTitle(KindFormular->Textfeld->Lines);
   KindFormular->FTPProfil->Caption = directftp_current_profile;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Kopieren4Click(TObject *Sender)
{
 TListItem *ListItem;
 TempDateiOperationenKopieren->Items->Clear();
 int items_count = DirektFTPListe->Items->Count;

 for (int i = 0; i < items_count; i++)
 {
  ListItem = DirektFTPListe->Items->Item[i];
  if (ListItem->Selected)
   TempDateiOperationenKopieren->Items->Add(directftp_current_dir + ListItem->Caption);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Einfgen4Click(TObject *Sender)
{
 if (FTPFile(TempDateiOperationenKopieren->Items->Strings[0]))
 {
 }
 else
 {
  DirektFTPClient->Asynchronous = true;
  TStrings* StrLst = new TStringList();
  TStrings* StrLst2 = new TStringList();
  for (int i = 0; i < TempDateiOperationenKopieren->Items->Count; i++)
  {
   StrLst->Add(TempDateiOperationenKopieren->Items->Strings[i]);
   StrLst2->Add(ExtractFileName(TempDateiOperationenKopieren->Items->Strings[i]));
  }
  DirektFTPClient->PutFile(StrLst, StrLst2);
  while (DirektFTPClient->Busy)
   Application->ProcessMessages();
  DirektFTPClient->Asynchronous = false;
 }
 DirektFTPAktualisieren(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Lschen6Click(TObject *Sender)
{
 if (DirektFTPListe->Selected)
 {
  DirektFTPClient->Asynchronous = true;
  TStrings* StrLst = new TStringList();
  TListItem *ListItem;

  for (int i = 0; i < DirektFTPListe->Items->Count; i++)
  {
   ListItem = DirektFTPListe->Items->Item[i];
   if (ListItem->Selected)
    StrLst->Add(ListItem->Caption);
  }

  String temp_str;
  int delete_button = 0;
  if (StrLst->Count == 1)
   temp_str = SprachenWaehler->GetString(52);
  else
   temp_str = SprachenWaehler->GetString(53);

  delete_button = Application->MessageBox(temp_str.c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON1 + MB_ICONQUESTION);
  if (delete_button == IDYES)
  {
   DirektFTPClient->DeleteFTPFile(StrLst);
   while (DirektFTPClient->Busy)
    Application->ProcessMessages();
  }
  DirektFTPClient->Asynchronous = false;
  DirektFTPAktualisieren(Sender);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Umbenennen5Click(TObject *Sender)
{
 DirektFTPListe->ItemFocused->EditCaption();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AlleDateien3Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Dokumente3Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Grafiken3Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Andere3Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::StandardDokument3Click(TObject *Sender)
{
 CreateChildForm(standard_template, "", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AddLangNewDocLeer31Click(TObject *Sender)
{
 String vtemplate = ParseString(AddLangStuff->Items->Strings[0], "|", 2);
 CreateChildForm(vtemplate, "", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AddLangNewDocLeer32Click(TObject *Sender)
{
 String vtemplate = ParseString(AddLangStuff->Items->Strings[1], "|", 2);
 CreateChildForm(vtemplate, "", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AddLangNewDocLeer33Click(TObject *Sender)
{
 String vtemplate = ParseString(AddLangStuff->Items->Strings[2], "|", 2);
 CreateChildForm(vtemplate, "", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Neu4Click(TObject *Sender)
{
 if (addlang_langs_count > 0)
 {
  N39->Visible = true;

  if (AddLangStuff->Items->Count > 0)
  {
   AddLangNewDocLeer31->Visible = true;
   AddLangNewDocLeer31->Caption = ParseString(AddLangStuff->Items->Strings[0], "|", 1);
  }
  if (AddLangStuff->Items->Count > 1)
  {
   AddLangNewDocLeer32->Visible = true;
   AddLangNewDocLeer32->Caption = ParseString(AddLangStuff->Items->Strings[1], "|", 1);
  }
  if (AddLangStuff->Items->Count > 2)
  {
   AddLangNewDocLeer33->Visible = true;
   AddLangNewDocLeer33->Caption = ParseString(AddLangStuff->Items->Strings[2], "|", 1);
  }
 }
 else
 {
  N39->Visible = false;
  AddLangNewDocLeer31->Visible = false;
  AddLangNewDocLeer32->Visible = false;
  AddLangNewDocLeer33->Visible = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPExplorerDblClick(TObject *Sender)
{
 if (DirektFTPExplorer->Selected)
 {
  String Caption;
  Caption = (DirektFTPExplorer->Selected)->Caption;
  if (Caption == SprachenWaehler->GetString(40))
   DirektFTPClient->ChangeToParentDirectory();
  else
   DirektFTPClient->ChangeDirectory(Caption);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton33Click(TObject *Sender)
{
 if (Trim(directftp_current_profile) == "")
 {
  TFTPProfile* FTPProfile = new TFTPProfile(Application);
  SprachenWaehler->SetFormLanguage(FTPProfile);
  FTPProfile->Caption = ToolButton33->Hint;
  FTPProfile->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPExplorerEdited(TObject *Sender,
      TListItem *Item, AnsiString &S)
{
 String Caption = Item->Caption;
 if (Caption != SprachenWaehler->GetString(40))
 {
  directftp_temp_input = S;
  DirektFTPClient->RenameFile(Item->Caption, S);
  if (DirektFTPClient->Success)
   Item->Caption = S;
  else
   S = Item->Caption;
 }
 else
  S = Item->Caption;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::QuickstartMenuPopup(TObject *Sender)
{
 QuickstartApp1->Caption = quickstart_desc_1;
 QuickstartApp2->Caption = quickstart_desc_2;
 QuickstartApp3->Caption = quickstart_desc_3;
 QuickstartApp4->Caption = quickstart_desc_4;
 QuickstartApp5->Caption = quickstart_desc_5;

 if (Trim(quickstart_path_1) == "")
  QuickstartApp1->Visible = false;
 else
  QuickstartApp1->Visible = true;
 if (Trim(quickstart_path_2) == "")
  QuickstartApp2->Visible = false;
 else
  QuickstartApp2->Visible = true;
 if (Trim(quickstart_path_3) == "")
  QuickstartApp3->Visible = false;
 else
  QuickstartApp3->Visible = true;
 if (Trim(quickstart_path_4) == "")
  QuickstartApp4->Visible = false;
 else
  QuickstartApp4->Visible = true;
 if (Trim(quickstart_path_5) == "")
  QuickstartApp5->Visible = false;
 else
  QuickstartApp5->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::QuickstartApp1Click(TObject *Sender)
{
 String para = quickstart_para_1;
 para = ReplaceString(para, "#File", ActiveMDIChild->Caption, true, false);
 FileExecute(quickstart_path_1, para);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::QuickstartApp2Click(TObject *Sender)
{
 String para = quickstart_para_2;
 para = ReplaceString(para, "#File", ActiveMDIChild->Caption, true, false);
 FileExecute(quickstart_path_2, para);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::QuickstartApp3Click(TObject *Sender)
{
 String para = quickstart_para_3;
 para = ReplaceString(para, "#File", ActiveMDIChild->Caption, true, false);
 FileExecute(quickstart_path_3, para);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::QuickstartApp4Click(TObject *Sender)
{
 String para = quickstart_para_4;
 para = ReplaceString(para, "#File", ActiveMDIChild->Caption, true, false);
 FileExecute(quickstart_path_4, para);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::QuickstartApp5Click(TObject *Sender)
{
 String para = quickstart_para_5;
 para = ReplaceString(para, "#File", ActiveMDIChild->Caption, true, false);
 FileExecute(quickstart_path_5, para);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::NeueVerknpfung1Click(TObject *Sender)
{
 TNeueVerknuepfung* NeueVerknuepfung = new TNeueVerknuepfung(Application);
 SprachenWaehler->SetFormLanguage(NeueVerknuepfung);
 NeueVerknuepfung->Caption = ReplaceString(NeueVerknpfung1->Caption, "&", "", false, true);
 NeueVerknuepfung->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPListeEdited(TObject *Sender,
      TListItem *Item, AnsiString &S)
{
 directftp_temp_input = S;
 DirektFTPClient->RenameFile(Item->Caption, S);
 if (DirektFTPClient->Success)
  Item->Caption = S;
 else
  S = Item->Caption;
}
//---------------------------------------------------------------------------
void __fastcall THauptformular::FormatMenuPopup(TObject *Sender)
{
 if (editor_xhtml_mode)
 {
  Schrift1->Visible = false;
  N43->Visible = false;
 }
 else
 {
  Schrift1->Visible = true;
  N43->Visible = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::EinfgenMenuPopup(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Schrift1Click(TObject *Sender)
{
 TSchrift* Schrift = new TSchrift(Application);
 SprachenWaehler->SetFormLanguage(Schrift);
 Schrift->Caption = ReplaceString(Schrift1->Caption, "&", "", false, true);
 Schrift->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Fett1Click(TObject *Sender)
{
 if (MDIChildCount)
  TagInsert("<b>", "</b>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Kursiv1Click(TObject *Sender)
{
 if (MDIChildCount)
  TagInsert("<i>", "</i>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Hochgestellt1Click(TObject *Sender)
{
 TagInsert("<sup>", "</sup>");        
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Tiefgestellt1Click(TObject *Sender)
{
 TagInsert("<sub>", "</sub>");        
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Prformatiert1Click(TObject *Sender)
{
 TagInsert("<pre>", "</pre>");        
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Code1Click(TObject *Sender)
{
 TagInsert("<code>", "</code>");        
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Emphatisch1Click(TObject *Sender)
{
 TagInsert("<em>", "</em>");        
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Zitat1Click(TObject *Sender)
{
 TagInsert("<blockquote>", "</blockquote>");        
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Adresse1Click(TObject *Sender)
{
 TagInsert("<address>", "</address>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Gro1Click(TObject *Sender)
{
 TagInsert("<big>", "</big>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Klein1Click(TObject *Sender)
{
 TagInsert("<small>", "</small>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Gre11Click(TObject *Sender)
{
 TagInsert("<h1>", "</h1>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Gre21Click(TObject *Sender)
{
 TagInsert("<h2>", "</h2>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Gre31Click(TObject *Sender)
{
 TagInsert("<h3>", "</h3>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Gre41Click(TObject *Sender)
{
 TagInsert("<h4>", "</h4>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Gre51Click(TObject *Sender)
{
 TagInsert("<h5>", "</h5>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Gre61Click(TObject *Sender)
{
 TagInsert("<h6>", "</h6>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Listeneintrag1Click(TObject *Sender)
{
 TagInsert("<li>", "</li>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Definitionsliste1Click(TObject *Sender)
{
 TagInsert("<dl>\r\n", "\r\n</dl>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Definitionsabschnitt1Click(TObject *Sender)
{
 TagInsert("<dt>", "</dt>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Definitionseintrag1Click(TObject *Sender)
{
 TagInsert("<dd>", "</dd>");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Abschnitt1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  TAbschnitt* Abschnitt = new TAbschnitt(Application);
  SprachenWaehler->SetFormLanguage(Abschnitt);
  Abschnitt->Caption = ReplaceString(Abschnitt1->Caption, "&", "", false, true);
  Abschnitt->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Hyperlink1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  THyperlink* Hyperlink = new THyperlink(Application);
  SprachenWaehler->SetFormLanguage(Hyperlink);
  Hyperlink->Caption = ReplaceString(Hyperlink1->Caption, "&", "", false, true);
  Hyperlink->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::eMailVerweis1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  TEmailVerweis* EmailVerweis = new TEmailVerweis(Application);
  SprachenWaehler->SetFormLanguage(EmailVerweis);
  EmailVerweis->Caption = ReplaceString(eMailVerweis1->Caption, "&", "", false, true);
  EmailVerweis->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Grafik1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  TGrafik* Grafik = new TGrafik(Application);
  SprachenWaehler->SetFormLanguage(Grafik);
  Grafik->Caption = ReplaceString(Grafik1->Caption, "&", "", false, true);
  Grafik->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Metatag1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  TMetatag* Metatag = new TMetatag(Application);
  SprachenWaehler->SetFormLanguage(Metatag);
  Metatag->Caption = ReplaceString(Metatag1->Caption, "&", "", false, true);
  Metatag->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::httpscribede1Click(TObject *Sender)
{
 FileExecute(browser_path_1, "http://scribe.de");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Plugins1Click(TObject *Sender)
{
 TPlugins* Plugins = new TPlugins(Application);
 SprachenWaehler->SetFormLanguage(Plugins);
 Plugins->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Buttonx1Click(TObject *Sender)
{
 TButtonx* Buttonx = new TButtonx(Application);
 SprachenWaehler->SetFormLanguage(Buttonx);
 Buttonx->Caption = ReplaceString(Buttonx1->Caption, "&", "", false, true);
 Buttonx->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ButtonxControlChange(TObject *Sender)
{
 if (MDIChildCount)
 {
  String code;
  TIniFile* Buttonx = new TIniFile(program_dir + "Storage!\\buttonx.ini");
  code = Buttonx->ReadString(ButtonxControl->Tabs->Strings[ButtonxControl->TabIndex], "Code", "");
  delete Buttonx;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = ButtonxEngine(code);
  ButtonxControl->TabIndex = -1;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::TabellenAssistent1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  TTabellenAssistent* TabellenAssistent = new TTabellenAssistent(Application);
  SprachenWaehler->SetFormLanguage(TabellenAssistent);
  TabellenAssistent->Caption = ReplaceString(TabellenAssistent1->Caption, "&", "", false, true);
  TabellenAssistent->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::MultimediaObjekt1Click(TObject *Sender)
{
 TMultimedia* Multimedia = new TMultimedia(Application);
 SprachenWaehler->SetFormLanguage(Multimedia);
 Multimedia->Caption = ReplaceString(MultimediaObjekt1->Caption, "&", "", false, true);
 Multimedia->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Trennlinie1Click(TObject *Sender)
{
 TTrennlinie* Trennlinie = new TTrennlinie(Application);
 SprachenWaehler->SetFormLanguage(Trennlinie);
 Trennlinie->Caption = ReplaceString(Trennlinie1->Caption, "&", "", false, true);
 Trennlinie->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Anker1Click(TObject *Sender)
{
 TAnker* Anker = new TAnker(Application);
 SprachenWaehler->SetFormLanguage(Anker);
 Anker->Caption = ReplaceString(Anker1->Caption, "&", "", false, true);
 Anker->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall THauptformular::Tabelle2Click(TObject *Sender)
{
 TTabelle* Tabelle = new TTabelle(Application);
 SprachenWaehler->SetFormLanguage(Tabelle);
 Tabelle->Caption = ReplaceString(Tabelle2->Caption, "&", "", false, true);
 Tabelle->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Zeile1Click(TObject *Sender)
{
 TZeile* Zeile = new TZeile(Application);
 SprachenWaehler->SetFormLanguage(Zeile);
 Zeile->Caption = ReplaceString(Zeile1->Caption, "&", "", false, true);
 Zeile->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Kopfzelle1Click(TObject *Sender)
{
 TKopfzelle* Kopfzelle = new TKopfzelle(Application);
 SprachenWaehler->SetFormLanguage(Kopfzelle);
 Kopfzelle->Caption = ReplaceString(Kopfzelle1->Caption, "&", "", false, true);
 Kopfzelle->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Zelle1Click(TObject *Sender)
{
 TZelle* Zelle = new TZelle(Application);
 SprachenWaehler->SetFormLanguage(Zelle);
 Zelle->Caption = ReplaceString(Zelle1->Caption, "&", "", false, true);
 Zelle->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::berUnterschrift1Click(TObject *Sender)
{
 TUeberUnterschrift* UeberUnterschrift = new TUeberUnterschrift(Application);
 SprachenWaehler->SetFormLanguage(UeberUnterschrift);
 UeberUnterschrift->Caption = ReplaceString(berUnterschrift1->Caption, "&", "", false, true);
 UeberUnterschrift->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Formular2Click(TObject *Sender)
{
 TFormular* Formular = new TFormular(Application);
 SprachenWaehler->SetFormLanguage(Formular);
 Formular->Caption = ReplaceString(Formular2->Caption, "&", "", false, true);
 Formular->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Eingabefeld1Click(TObject *Sender)
{
 TEingabefeld* Eingabefeld = new TEingabefeld(Application);
 SprachenWaehler->SetFormLanguage(Eingabefeld);
 Eingabefeld->Caption = ReplaceString(Eingabefeld1->Caption, "&", "", false, true);
 Eingabefeld->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Textfeld1Click(TObject *Sender)
{
 TTextfeld* Textfeld = new TTextfeld(Application);
 SprachenWaehler->SetFormLanguage(Textfeld);
 Textfeld->Caption = ReplaceString(Textfeld1->Caption, "&", "", false, true);
 Textfeld->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AbsendenundZurcksetzenbutton1Click(
      TObject *Sender)
{
 TAbsendenZuruecksetzen* AbsendenZuruecksetzen = new TAbsendenZuruecksetzen(Application);
 SprachenWaehler->SetFormLanguage(AbsendenZuruecksetzen);
 AbsendenZuruecksetzen->Caption = ReplaceString(AbsendenundZurcksetzenbutton1->Caption, "&", "", false, true);
 AbsendenZuruecksetzen->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Passwortfeld1Click(TObject *Sender)
{
 TPasswortfeld* Passwortfeld = new TPasswortfeld(Application);
 SprachenWaehler->SetFormLanguage(Passwortfeld);
 Passwortfeld->Caption = ReplaceString(Passwortfeld1->Caption, "&", "", false, true);
 Passwortfeld->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::VerstecktesFeld1Click(TObject *Sender)
{
 TVerstecktesFeld* VerstecktesFeld = new TVerstecktesFeld(Application);
 SprachenWaehler->SetFormLanguage(VerstecktesFeld);
 VerstecktesFeld->Caption = ReplaceString(VerstecktesFeld1->Caption, "&", "", false, true);
 VerstecktesFeld->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Checkbox1Click(TObject *Sender)
{
 TCheckboxTag* CheckboxTag = new TCheckboxTag(Application);
 SprachenWaehler->SetFormLanguage(CheckboxTag);
 CheckboxTag->Caption = ReplaceString(Checkbox1->Caption, "&", "", false, true);
 CheckboxTag->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Radiobutton1Click(TObject *Sender)
{
 TRadiobutton* Radiobutton = new TRadiobutton(Application);
 SprachenWaehler->SetFormLanguage(Radiobutton);
 Radiobutton->Caption = ReplaceString(Radiobutton1->Caption, "&", "", false, true);
 Radiobutton->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Auswahlliste1Click(TObject *Sender)
{
 TAuswahlliste* Auswahlliste = new TAuswahlliste(Application);
 SprachenWaehler->SetFormLanguage(Auswahlliste);
 Auswahlliste->Caption = ReplaceString(Auswahlliste1->Caption, "&", "", false, true);
 Auswahlliste->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Auswahleintrag1Click(TObject *Sender)
{
 TAuswahleintrag* Auswahleintrag = new TAuswahleintrag(Application);
 SprachenWaehler->SetFormLanguage(Auswahleintrag);
 Auswahleintrag->Caption = ReplaceString(Auswahleintrag1->Caption, "&", "", false, true);
 Auswahleintrag->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Button1Click(TObject *Sender)
{
 TButtonTag* ButtonTag = new TButtonTag(Application);
 SprachenWaehler->SetFormLanguage(ButtonTag);
 ButtonTag->Caption = ReplaceString(Button1->Caption, "&", "", false, true);
 ButtonTag->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FramesAssistent1Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  TFrameAssistent* FrameAssistent = new TFrameAssistent(Application);
  SprachenWaehler->SetFormLanguage(FrameAssistent);
  FrameAssistent->Caption = ReplaceString(FramesAssistent1->Caption, "&", "", false, true);
  FrameAssistent->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FrameBereich1Click(TObject *Sender)
{
 TFrameBereich* FrameBereich = new TFrameBereich(Application);
 SprachenWaehler->SetFormLanguage(FrameBereich);
 FrameBereich->Caption = ReplaceString(FrameBereich1->Caption, "&", "", false, true);
 FrameBereich->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Frame1Click(TObject *Sender)
{
 TEinzelnerFrame* EinzelnerFrame = new TEinzelnerFrame(Application);
 SprachenWaehler->SetFormLanguage(EinzelnerFrame);
 EinzelnerFrame->Caption = ReplaceString(Frame1->Caption, "&", "", false, true);
 EinzelnerFrame->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::EingebettetesFrame1Click(TObject *Sender)
{
 TEingebettetesFrame* EingebettetesFrame = new TEingebettetesFrame(Application);
 SprachenWaehler->SetFormLanguage(EingebettetesFrame);
 EingebettetesFrame->Caption = ReplaceString(EingebettetesFrame1->Caption, "&", "", false, true);
 EingebettetesFrame->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::StyleSheetDefinition1Click(TObject *Sender)
{
 String tag;
 tag = " <style type=\"text/css\">\r\n <!--\r\n  ";
 TagInsertAndFindPosition(tag, "\r\n //-->\r\n </style>", "</head>", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::StyleSheetZuweisungen1Click(
      TObject *Sender)
{
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = CSSEditorEditStyleBlock("");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ExterneStyleSheetDatei1Click(
      TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = SprachenWaehler->GetString(7);
 filter_temp = filter_temp + BuildFilter(cssfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;

 if (MDIChildCount)
  OeffnenDialog->InitialDir = ExtractFilePath(ActiveMDIChild->Caption);

 OeffnenDialog->Title = ReplaceString(ExterneStyleSheetDatei1->Caption, "&", "", false, true);

 if (OeffnenDialog->Execute())
 {
  String file = Hauptformular->DirectorySameAndRelative(OeffnenDialog->FileName);
  String tag;
  if (editor_xhtml_mode)
  tag = " <link rel=\"stylesheet\" type=\"text/css\" href=\"" + file + "\" />";
  else
   tag = " <link rel=\"stylesheet\" type=\"text/css\" href=\"" + file + "\">";
  TagInsertAndFindPosition(tag, "", "</head>", "");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::JavaScriptVorlagen1Click(TObject *Sender)
{
 TJavaScriptVorlagen* JavaScriptVorlagen = new TJavaScriptVorlagen(Application);
 SprachenWaehler->SetFormLanguage(JavaScriptVorlagen);
 JavaScriptVorlagen->Caption = ReplaceString(JavaScriptVorlagen1->Caption, "&", "", false, true);
 JavaScriptVorlagen->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::JavaScript2Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  String tag;
  tag = " <script type=\"text/javascript\">\r\n <!--\r\n  ";
  TagInsertAndFindPosition(tag, "\r\n //-->\r\n </script>", "</head>", "");
 }
}
//---------------------------------------------------------------------------


void __fastcall THauptformular::IncludeDatei1Click(TObject *Sender)
{
 TIncludeDatei* IncludeDatei = new TIncludeDatei(Application);
 SprachenWaehler->SetFormLanguage(IncludeDatei);
 IncludeDatei->Caption = ReplaceString(IncludeDatei1->Caption, "&", "", false, true);
 IncludeDatei->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolsMenuPopup(TObject *Sender)
{
 if (MDIChildCount)
 {
  Linkberprfung1->Enabled = true;
  Downloadzeit1->Enabled = true;
  Includesaktualisieren1->Enabled = true;
  XHTMLKonverter1->Enabled = true;
 }
 else
 {
  Linkberprfung1->Enabled = false;
  Downloadzeit1->Enabled = false;
  Includesaktualisieren1->Enabled = false;
  XHTMLKonverter1->Enabled = false;
 }

 if (ProjekteAuswahl->Items->Count > 1)
  ProjektBackup1->Enabled = true;
 else
  ProjektBackup1->Enabled = false;
}
//---------------------------------------------------------------------------



void __fastcall THauptformular::Schnellformatierung1Click(TObject *Sender)
{
 TSchnellformat* Schnellformat = new TSchnellformat(Application);
 SprachenWaehler->SetFormLanguage(Schnellformat);
 Schnellformat->Caption = ReplaceString(Schnellformatierung1->Caption, "&", "", false, true);
 Schnellformat->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Paragraph1Click(TObject *Sender)
{
 TParagraph* Paragraph = new TParagraph(Application);
 SprachenWaehler->SetFormLanguage(Paragraph);
 Paragraph->Caption = ReplaceString(Paragraph1->Caption, "&", "", false, true);
 Paragraph->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Liste1Click(TObject *Sender)
{
 TListe* Liste = new TListe(Application);
 SprachenWaehler->SetFormLanguage(Liste);
 Liste->Caption = ReplaceString(Liste1->Caption, "&", "", false, true);
 Liste->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ExterneJavaScriptDatei1Click(
      TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = SprachenWaehler->GetString(21);
 filter_temp = filter_temp + BuildFilter(javascriptfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;

 if (MDIChildCount)
  OeffnenDialog->InitialDir = ExtractFilePath(ActiveMDIChild->Caption);

 OeffnenDialog->Title = ReplaceString(ExterneJavaScriptDatei1->Caption, "&", "", false, true);

 if (OeffnenDialog->Execute())
 {
  String file = Hauptformular->DirectorySameAndRelative(OeffnenDialog->FileName);
  String tag;
  tag = " <script type=\"text/javascript\" src=\"" + file + "\">\r\n </script>";
  Hauptformular->TagInsertAndFindPosition(tag, "", "</head>", "");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ProjektBackup1Click(TObject *Sender)
{
 TProjektBackup* ProjektBackup = new TProjektBackup(Application);
 SprachenWaehler->SetFormLanguage(ProjektBackup);
 ProjektBackup->Caption = ReplaceString(ProjektBackup1->Caption, "&", "", false, true);
 ProjektBackup->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::GrafikKatalog1Click(TObject *Sender)
{
 TGrafikKatalog* GrafikKatalog = new TGrafikKatalog(Application);
 SprachenWaehler->SetFormLanguage(GrafikKatalog);
 GrafikKatalog->Caption = ReplaceString(GrafikKatalog1->Caption, "&", "", false, true);
 GrafikKatalog->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ThumbnailGenerator1Click(TObject *Sender)
{
 TThumbnailGenerator* ThumbnailGenerator = new TThumbnailGenerator(Application);
 SprachenWaehler->SetFormLanguage(ThumbnailGenerator);
 ThumbnailGenerator->Caption = ReplaceString(ThumbnailGenerator1->Caption, "&", "", false, true);
 ThumbnailGenerator->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::StatusLeisteClick(TObject *Sender)
{
 if (tag_php_compatible)
  tag_php_compatible = false;
 else
  tag_php_compatible = true;

 if (tag_php_compatible)
  StatusLeiste->Panels->Items[3]->Text = SprachenWaehler->GetString(79);
 else
  StatusLeiste->Panels->Items[3]->Text = SprachenWaehler->GetString(78);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::StyleSheetEditor1Click(TObject *Sender)
{
 if ((use_topstyle == true) && (EnableTopStyleIntegration("Scribe!")) == true)
  tsEditStyleSheet("", "");
 else
 {
  TStyleSheetEditor* StyleSheetEditor = new TStyleSheetEditor(Application);
  SprachenWaehler->SetFormLanguage(StyleSheetEditor);
  StyleSheetEditor->Caption = ReplaceString(StyleSheetEditor1->Caption, "&", "", false, true);
  StyleSheetEditor->ShowModal();
 }
}
//---------------------------------------------------------------------------



void __fastcall THauptformular::XHTMLKonverter1Click(TObject *Sender)
{
 TXHTMLKonverter* XHTMLKonverter = new TXHTMLKonverter(Application);
 SprachenWaehler->SetFormLanguage(XHTMLKonverter);
 XHTMLKonverter->Caption = ReplaceString(XHTMLKonverter1->Caption, "&", "", false, true);
 XHTMLKonverter->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Includesaktualisieren1Click(
      TObject *Sender)
{
 TIncludesAktualisieren* IncludesAktualisieren = new TIncludesAktualisieren(Application);
 SprachenWaehler->SetFormLanguage(IncludesAktualisieren);
 IncludesAktualisieren->Caption = ReplaceString(Includesaktualisieren1->Caption, "&", "", false, true);
 IncludesAktualisieren->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Linkberprfung1Click(TObject *Sender)
{
 TLinkUeberpruefung* LinkUeberpruefung = new TLinkUeberpruefung(Application);
 SprachenWaehler->SetFormLanguage(LinkUeberpruefung);
 LinkUeberpruefung->Caption = ReplaceString(Linkberprfung1->Caption, "&", "", false, true);
 LinkUeberpruefung->Show();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FormResize(TObject *Sender)
{
 FensterLeiste->Width = Width;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::MenuItem23Click(TObject *Sender)
{
 String vorher = DateimanagerExplorer->SelectedPath;
 DateimanagerExplorer->ReLoad();
 DateimanagerExplorer->OpenPath(vorher);
 DateimanagerExplorerDirChange(Sender, vorher);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::LeerzeichenShortCutExecute(TObject *Sender)
{
 if (MDIChildCount)
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = "&nbsp;";
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ZeilenumbruchShortCut2Execute(
      TObject *Sender)
{
 if (MDIChildCount)
 {
  if (editor_xhtml_mode)
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = "<br />";
  else
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = "<br>";
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::KlammerAufShortCutExecute(TObject *Sender)
{
 if (MDIChildCount)
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = "&lt;";
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::KlammerZuShortCutExecute(TObject *Sender)
{
 if (MDIChildCount)
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = "&gt;";
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AnfuehrungszeichenShortCutExecute(
      TObject *Sender)
{
 if (MDIChildCount)
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = "&quot;";
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DateimanagerListeSelectItem(
      TObject *Sender, TListItem *Item, bool Selected)
{
 DateimanagerListeClick(Sender);          
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ProjekteListeSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
 ProjekteListeClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FastCode1Click(TObject *Sender)
{
 TFastTag* FastTag = new TFastTag(Application);
 SprachenWaehler->SetFormLanguage(FastTag);
 FastTag->Caption = ReplaceString(FastCode1->Caption, "&", "", false, true);
 FastTag->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton35MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Common", "Body", "<body bgcolor=\"#FFFFFF\" link=\"#FF0000\">");
  end_tag = FastTagsIni->ReadString("Common", "BodyEnd", "</body>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  int temp_int = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt("<body", true, false, false, false))
  {
   int temp_int_2 = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart - 5;
   int temp_int_3 = 0;
   if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt(">", true, false, false, false))
    temp_int_3 = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = temp_int_2;
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = temp_int_3 - temp_int_2;
   tag_current = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;
   tag_currently_editing = true;
   TSeiteneigen* Seiteneigen = new TSeiteneigen(Application);
   SprachenWaehler->SetFormLanguage(Seiteneigen);
   Seiteneigen->Caption = ReplaceString(Seiteneigenschaften1->Caption, "&", "", false, true);
   Seiteneigen->ShowModal();
  }
  else
  {
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = temp_int;
   TSeiteneigen* Seiteneigen = new TSeiteneigen(Application);
   SprachenWaehler->SetFormLanguage(Seiteneigen);
   Seiteneigen->Caption = ReplaceString(Seiteneigenschaften1->Caption, "&", "", false, true);
   Seiteneigen->ShowModal();
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton37MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Common", "Paragraph", "<p align=\"center\">");
  end_tag = FastTagsIni->ReadString("Common", "ParagraphEnd", "</p>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TagInsert("<p>", "</p>");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton38MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Common", "Break", "");
  end_tag = FastTagsIni->ReadString("Common", "BreakEnd", "<br clear=\"all\" />");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  if (editor_xhtml_mode)
   TagInsert("", "<br />");
  else
   TagInsert("", "<br>");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton40MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Common", "Hyperlink", "<a href=\"http://\" target=\"_blank\">");
  end_tag = FastTagsIni->ReadString("Common", "HyperlinkEnd", "</a>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  THyperlink* Hyperlink = new THyperlink(Application);
  SprachenWaehler->SetFormLanguage(Hyperlink);
  Hyperlink->Caption = ReplaceString(Hyperlink1->Caption, "&", "", false, true);
  Hyperlink->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton41MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Common", "Image", "<img src=\"\" alt=\"\" border=\"0\" />");
  end_tag = FastTagsIni->ReadString("Common", "ImageEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TGrafik* Grafik = new TGrafik(Application);
  SprachenWaehler->SetFormLanguage(Grafik);
  Grafik->Caption = ReplaceString(Grafik1->Caption, "&", "", false, true);
  Grafik->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton42MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Common", "Rule", "<hr noshade=\"noshade\" />");
  end_tag = FastTagsIni->ReadString("Common", "RuleEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TTrennlinie* Trennlinie = new TTrennlinie(Application);
  SprachenWaehler->SetFormLanguage(Trennlinie);
  Trennlinie->Caption = ReplaceString(Trennlinie1->Caption, "&", "", false, true);
  Trennlinie->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton43MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Common", "Object", "<object data=\"\" border=\"0\">");
  end_tag = FastTagsIni->ReadString("Common", "ObjectEnd", "</object>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TMultimedia* Multimedia = new TMultimedia(Application);
  SprachenWaehler->SetFormLanguage(Multimedia);
  Multimedia->Caption = ReplaceString(MultimediaObjekt1->Caption, "&", "", false, true);
  Multimedia->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton44MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Common", "Meta", "<meta name=\"\" content=\"\" />");
  end_tag = FastTagsIni->ReadString("Common", "MetaEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TMetatag* Metatag = new TMetatag(Application);
  SprachenWaehler->SetFormLanguage(Metatag);
  Metatag->Caption = ReplaceString(Metatag1->Caption, "&", "", false, true);
  Metatag->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton46MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Common", "List", "<ol type=\"i\">");
  end_tag = FastTagsIni->ReadString("Common", "ListEnd", "</ol>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TListe* Liste = new TListe(Application);
  SprachenWaehler->SetFormLanguage(Liste);
  Liste->Caption = ReplaceString(Liste1->Caption, "&", "", false, true);
  Liste->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton47MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Common", "ListItem", "<li value=\"\">");
  end_tag = FastTagsIni->ReadString("Common", "ListItemEnd", "</li>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TagInsert("<li>", "</li>");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton48MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Additional", "eMail", "<a href=\"MailTo:\">");
  end_tag = FastTagsIni->ReadString("Additional", "eMailEnd", "</a>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TEmailVerweis* EmailVerweis = new TEmailVerweis(Application);
  SprachenWaehler->SetFormLanguage(EmailVerweis);
  EmailVerweis->Caption = ReplaceString(eMailVerweis1->Caption, "&", "", false, true);
  EmailVerweis->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton49MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Additional", "Anchor", "<a name=\"\" id=\"\">");
  end_tag = FastTagsIni->ReadString("Additional", "AnchorEnd", "</a>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TAnker* Anker = new TAnker(Application);
  SprachenWaehler->SetFormLanguage(Anker);
  Anker->Caption = ReplaceString(Anker1->Caption, "&", "", false, true);
  Anker->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton93Click(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton94MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Additional", "FrameSet", "<frameset cols=\"100,*\" frameborder=\"0\">");
  end_tag = FastTagsIni->ReadString("Additional", "FrameSetEnd", "</frameset>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TFrameBereich* FrameBereich = new TFrameBereich(Application);
  SprachenWaehler->SetFormLanguage(FrameBereich);
  FrameBereich->Caption = ReplaceString(FrameBereich1->Caption, "&", "", false, true);
  FrameBereich->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton95MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Additional", "Frame", "<frame src=\"http://\" name=\"\" noresize=\"noresize\" />");
  end_tag = FastTagsIni->ReadString("Additional", "FrameEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TEinzelnerFrame* EinzelnerFrame = new TEinzelnerFrame(Application);
  SprachenWaehler->SetFormLanguage(EinzelnerFrame);
  EinzelnerFrame->Caption = ReplaceString(Frame1->Caption, "&", "", false, true);
  EinzelnerFrame->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton96MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Additional", "IFrame", "<iframe src=\"http://\" name=\"\">");
  end_tag = FastTagsIni->ReadString("Additional", "IFrameEnd", "</iframe>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TEingebettetesFrame* EingebettetesFrame = new TEingebettetesFrame(Application);
  SprachenWaehler->SetFormLanguage(EingebettetesFrame);
  EingebettetesFrame->Caption = ReplaceString(EingebettetesFrame1->Caption, "&", "", false, true);
  EingebettetesFrame->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton98MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Additional", "CSSDefinition", "<style type=\"text/css\"><!-- body { font-family:Arial; color:#000000; } //-->");
  end_tag = FastTagsIni->ReadString("Additional", "CSSDefinitionEnd", "</style>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  tag = " <style type=\"text/css\">\r\n <!--\r\n  ";
  TagInsertAndFindPosition(tag, "\r\n //-->\r\n </style>", "</head>", "");
 }
}
//---------------------------------------------------------------------------
 
void __fastcall THauptformular::ToolButton99Click(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton101Click(TObject *Sender)
{
 String tag;
 tag = " <script type=\"text/javascript\">\r\n <!--\r\n  ";
 TagInsertAndFindPosition(tag, "\r\n //-->\r\n </script>", "</head>", "");
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton59MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (editor_xhtml_mode)
 {
  if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
  {
   String tag;
   String end_tag;
   TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
   tag = FastTagsIni->ReadString("Format", "FastFormat", "<span style=\"\" class=\"\">");
   end_tag = FastTagsIni->ReadString("Format", "FastFormatEnd", "</span>");
   delete FastTagsIni;
   TagInsert(tag, end_tag);
  }
  else if (Button == mbLeft && X <= 23 && Y <= 22)
  {
   TSchnellformat* Schnellformat = new TSchnellformat(Application);
   SprachenWaehler->SetFormLanguage(Schnellformat);
   Schnellformat->Caption = ReplaceString(Schnellformatierung1->Caption, "&", "", false, true);
   Schnellformat->ShowModal();
  }
 }
 else
 {
  if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
  {
   String tag;
   String end_tag;
   TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
   tag = FastTagsIni->ReadString("Format", "Font", "<font size=\"\" color=\"#FF0000\"><b>");
   end_tag = FastTagsIni->ReadString("Format", "FontEnd", "</b></font>");
   delete FastTagsIni;
   TagInsert(tag, end_tag);
  }
  else if (Button == mbLeft && X <= 23 && Y <= 22)
  {
   TSchrift* Schrift = new TSchrift(Application);
   SprachenWaehler->SetFormLanguage(Schrift);
   Schrift->Caption = ReplaceString(Schrift1->Caption, "&", "", false, true);
   Schrift->ShowModal();
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton60MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Format", "FastFormat", "<span style=\"\" class=\"\">");
  end_tag = FastTagsIni->ReadString("Format", "FastFormatEnd", "</span>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TSchnellformat* Schnellformat = new TSchnellformat(Application);
  SprachenWaehler->SetFormLanguage(Schnellformat);
  Schnellformat->Caption = ReplaceString(Schnellformatierung1->Caption, "&", "", false, true);
  Schnellformat->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton62MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Format", "Bold", "<b>");
  end_tag = FastTagsIni->ReadString("Format", "BoldEnd", "</b>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TagInsert("<b>", "</b>");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton63MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Format", "Italic", "<i>");
  end_tag = FastTagsIni->ReadString("Format", "ItalicEnd", "</i>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TagInsert("<i>", "</i>");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton65MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Format", "Left", "<div align=\"left\">");
  end_tag = FastTagsIni->ReadString("Format", "LeftEnd", "</div>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TagInsert("<p>", "</p>");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton66MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Format", "Center", "<div align=\"center\">");
  end_tag = FastTagsIni->ReadString("Format", "CenterEnd", "</div>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TagInsert("<p align=\"center\">", "</p>");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton67MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Format", "Right", "<div align=\"right\">");
  end_tag = FastTagsIni->ReadString("Format", "RightEnd", "</div>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TagInsert("<p align=\"right\">", "</p>");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton77MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Format", "Justify", "<p align=\"justify\">");
  end_tag = FastTagsIni->ReadString("Format", "JustifyEnd", "</p>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TagInsert("<p align=\"justify\">", "</p>");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton53MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Tables", "Table", "<table width=\"\" bgcolor=\"#000000\" border=\"0\">");
  end_tag = FastTagsIni->ReadString("Tables", "TableEnd", "</table>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TTabelle* Tabelle = new TTabelle(Application);
  SprachenWaehler->SetFormLanguage(Tabelle);
  Tabelle->Caption = ReplaceString(Tabelle2->Caption, "&", "", false, true);
  Tabelle->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton54MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Tables", "Row", "<tr>");
  end_tag = FastTagsIni->ReadString("Tables", "RowEnd", "</tr>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TZeile* Zeile = new TZeile(Application);
  SprachenWaehler->SetFormLanguage(Zeile);
  Zeile->Caption = ReplaceString(Zeile1->Caption, "&", "", false, true);
  Zeile->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton55MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Tables", "Header", "<th height=\"\" width=\"\" bgcolor=\"#000000\" rowspan=\"\" colspan=\"\">");
  end_tag = FastTagsIni->ReadString("Tables", "HeaderEnd", "</th>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TKopfzelle* Kopfzelle = new TKopfzelle(Application);
  SprachenWaehler->SetFormLanguage(Kopfzelle);
  Kopfzelle->Caption = ReplaceString(Kopfzelle1->Caption, "&", "", false, true);
  Kopfzelle->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton56MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Tables", "Data", "<td height=\"\" width=\"\" bgcolor=\"#000000\" rowspan=\"\" colspan=\"\">");
  end_tag = FastTagsIni->ReadString("Tables", "DataEnd", "</td>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TZelle* Zelle = new TZelle(Application);
  SprachenWaehler->SetFormLanguage(Zelle);
  Zelle->Caption = ReplaceString(Zelle1->Caption, "&", "", false, true);
  Zelle->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton58MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Tables", "Caption", "<caption align=\"bottom\">");
  end_tag = FastTagsIni->ReadString("Tables", "CaptionEnd", "</caption>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TUeberUnterschrift* UeberUnterschrift = new TUeberUnterschrift(Application);
  SprachenWaehler->SetFormLanguage(UeberUnterschrift);
  UeberUnterschrift->Caption = ReplaceString(berUnterschrift1->Caption, "&", "", false, true);
  UeberUnterschrift->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton78MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "Form", "<form name=\"\" action=\"MailTo:\" method=\"post\" enctype=\"text/plain\" target=\"\">");
  end_tag = FastTagsIni->ReadString("Forms", "FormEnd", "</form>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TFormular* Formular = new TFormular(Application);
  SprachenWaehler->SetFormLanguage(Formular);
  Formular->Caption = ReplaceString(Formular2->Caption, "&", "", false, true);
  Formular->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton80MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "InputText", "<input type=\"text\" name=\"\" size=\"\" maxlength=\"100\" />");
  end_tag = FastTagsIni->ReadString("Forms", "InputTextEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TEingabefeld* Eingabefeld = new TEingabefeld(Application);
  SprachenWaehler->SetFormLanguage(Eingabefeld);
  Eingabefeld->Caption = ReplaceString(Eingabefeld1->Caption, "&", "", false, true);
  Eingabefeld->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton81MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "Textarea", "<textarea name=\"\" rows=\"\" cols=\"\">");
  end_tag = FastTagsIni->ReadString("Forms", "TextareaEnd", "</textarea>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TTextfeld* Textfeld = new TTextfeld(Application);
  SprachenWaehler->SetFormLanguage(Textfeld);
  Textfeld->Caption = ReplaceString(Textfeld1->Caption, "&", "", false, true);
  Textfeld->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton82MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "Submit", "<input type=\"submit\" value=\"Send!\" />");
  end_tag = FastTagsIni->ReadString("Forms", "SubmitEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TAbsendenZuruecksetzen* AbsendenZuruecksetzen = new TAbsendenZuruecksetzen(Application);
  SprachenWaehler->SetFormLanguage(AbsendenZuruecksetzen);
  AbsendenZuruecksetzen->Caption = ReplaceString(AbsendenundZurcksetzenbutton1->Caption, "&", "", false, true);
  AbsendenZuruecksetzen->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton83MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "Password", "<input type=\"password\" name=\"\" size=\"\" maxlength=\"\" />");
  end_tag = FastTagsIni->ReadString("Forms", "PasswordEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TPasswortfeld* Passwortfeld = new TPasswortfeld(Application);
  SprachenWaehler->SetFormLanguage(Passwortfeld);
  Passwortfeld->Caption = ReplaceString(Passwortfeld1->Caption, "&", "", false, true);
  Passwortfeld->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton84MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "Hidden", "<input type=\"hidden\" name=\"\" value=\"\" />");
  end_tag = FastTagsIni->ReadString("Forms", "HiddenEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TVerstecktesFeld* VerstecktesFeld = new TVerstecktesFeld(Application);
  SprachenWaehler->SetFormLanguage(VerstecktesFeld);
  VerstecktesFeld->Caption = ReplaceString(VerstecktesFeld1->Caption, "&", "", false, true);
  VerstecktesFeld->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton86MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "Checkbox", "<input type=\"radio\" name=\"\" value=\"\" checked=\"checked\" />");
  end_tag = FastTagsIni->ReadString("Forms", "CheckboxEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TCheckboxTag* CheckboxTag = new TCheckboxTag(Application);
  SprachenWaehler->SetFormLanguage(CheckboxTag);
  CheckboxTag->Caption = ReplaceString(Checkbox1->Caption, "&", "", false, true);
  CheckboxTag->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton87MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "Radiobutton", "<input type=\"checkbox\" name=\"\" value=\"\" checked=\"checked\" />");
  end_tag = FastTagsIni->ReadString("Forms", "RadiobuttonEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TRadiobutton* Radiobutton = new TRadiobutton(Application);
  SprachenWaehler->SetFormLanguage(Radiobutton);
  Radiobutton->Caption = ReplaceString(Radiobutton1->Caption, "&", "", false, true);
  Radiobutton->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton89MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "Select", "<select name=\"\" size=\"\" multiple=\"multiple\">");
  end_tag = FastTagsIni->ReadString("Forms", "SelectEnd", "</select>");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TAuswahlliste* Auswahlliste = new TAuswahlliste(Application);
  SprachenWaehler->SetFormLanguage(Auswahlliste);
  Auswahlliste->Caption = ReplaceString(Auswahlliste1->Caption, "&", "", false, true);
  Auswahlliste->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton90MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "Option", "<option value=\"\">");
  end_tag = FastTagsIni->ReadString("Forms", "OptionEnd", "<option");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TAuswahleintrag* Auswahleintrag = new TAuswahleintrag(Application);
  SprachenWaehler->SetFormLanguage(Auswahleintrag);
  Auswahleintrag->Caption = ReplaceString(Auswahleintrag1->Caption, "&", "", false, true);
  Auswahleintrag->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton92MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssCtrl) && Button == mbLeft && X <= 23 && Y <= 22)
 {
  String tag;
  String end_tag;
  TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");
  tag = FastTagsIni->ReadString("Forms", "Button", "<input type=\"button\" name=\"\" value=\"\" />");
  end_tag = FastTagsIni->ReadString("Forms", "ButtonEnd", "");
  delete FastTagsIni;
  TagInsert(tag, end_tag);
 }
 else if (Button == mbLeft && X <= 23 && Y <= 22)
 {
  TButtonTag* ButtonTag = new TButtonTag(Application);
  SprachenWaehler->SetFormLanguage(ButtonTag);
  ButtonTag->Caption = ReplaceString(Button1->Caption, "&", "", false, true);
  ButtonTag->ShowModal();
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Downloadzeit1Click(TObject *Sender)
{
 TDownloadzeit* Downloadzeit = new TDownloadzeit(Application);
 SprachenWaehler->SetFormLanguage(Downloadzeit);
 Downloadzeit->Caption = ReplaceString(Downloadzeit1->Caption, "&", "", false, true);
 Downloadzeit->Show();
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Optionen1Click(TObject *Sender)
{
 TOptionen* Optionen = new TOptionen(Application);
 SprachenWaehler->SetFormLanguage(Optionen);
 Optionen->Caption = ReplaceString(Optionen1->Caption, "&", "", false, true);
 Optionen->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall THauptformular::DateimanagerListeKeyPress(TObject *Sender,
      char &Key)
{
 if (Key == 13)
 {
  if (!DateimanagerListe->IsEditing())
   ffnen2Click(Sender);
 }
}
//---------------------------------------------------------------------------


void __fastcall THauptformular::ProjekteListeKeyPress(TObject *Sender,
      char &Key)
{
 if (Key == 13)
 {
  if (!ProjekteListe->IsEditing())
   ffnen3Click(Sender);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::DirektFTPListeKeyPress(TObject *Sender,
      char &Key)
{
 if (Key == 13)
 {
  if (!DirektFTPListe->IsEditing())
   ffnen4Click(Sender);
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Hilfethemen1Click(TObject *Sender)
{
 TOSVersionInfo* os = new TOSVersionInfo;
 GetVersionEx(os);
 if (os->dwPlatformId == VER_PLATFORM_WIN32_NT)
  FileExecute(browser_path_1, program_dir + "Storage!\\Help\\index.html");
 else
  Hauptformular->HelpShow(this, "index.html", false);
 delete os;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Editor1Click(TObject *Sender)
{
 TOSVersionInfo* os = new TOSVersionInfo;
 GetVersionEx(os);
 if (os->dwPlatformId == VER_PLATFORM_WIN32_NT)
  FileExecute(browser_path_1, program_dir + "Storage!\\Help\\editor.html");
 else
  Hauptformular->HelpShow(this, "editor.html", false);
 delete os;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::XHTML1Click(TObject *Sender)
{
 TOSVersionInfo* os = new TOSVersionInfo;
 GetVersionEx(os);
 if (os->dwPlatformId == VER_PLATFORM_WIN32_NT)
  FileExecute(browser_path_1, program_dir + "Storage!\\Help\\tag_list.html");
 else
  Hauptformular->HelpShow(this, "tag_list.html", false);
 delete os;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::BinrModus1Click(TObject *Sender)
{
 VerwControl->ActivePage = VerwTab3;
 int vorheriger_modus = DirektFTPClient->TransferMode;
 TempDateiOperationenKopieren2->Items->Clear();
 DirektFTPClient->TransferMode = BinaryTransfer;

 TListItem *ListItem;
 int items_count = DateimanagerListe->Items->Count;

 for (int i = 0; i < items_count; i++)
 {
  ListItem = DateimanagerListe->Items->Item[i];
  if (ListItem->Selected)
   TempDateiOperationenKopieren2->Items->Add(fileexplorer_dir + ListItem->Caption);
 }

 if (FTPFile(TempDateiOperationenKopieren2->Items->Strings[0]))
 {
 }
 else
 {
  DirektFTPClient->Asynchronous = true;
  TStrings* StrLst = new TStringList();
  TStrings* StrLst2 = new TStringList();
  for (int i = 0; i < TempDateiOperationenKopieren2->Items->Count; i++)
  {
   StrLst->Add(TempDateiOperationenKopieren2->Items->Strings[i]);
   StrLst2->Add(ExtractFileName(TempDateiOperationenKopieren2->Items->Strings[i]));
  }
  DirektFTPClient->PutFile(StrLst, StrLst2);
  while (DirektFTPClient->Busy)
   Application->ProcessMessages();
  DirektFTPClient->Asynchronous = false;
 }

 DirektFTPClient->TransferMode = vorheriger_modus;
 DirektFTPAktualisieren(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AsciiModus1Click(TObject *Sender)
{
 VerwControl->ActivePage = VerwTab3;
 int vorheriger_modus = DirektFTPClient->TransferMode;
 TempDateiOperationenKopieren2->Items->Clear();
 DirektFTPClient->TransferMode = AsciiTransfer;

 TListItem *ListItem;
 int items_count = DateimanagerListe->Items->Count;

 for (int i = 0; i < items_count; i++)
 {
  ListItem = DateimanagerListe->Items->Item[i];
  if (ListItem->Selected)
   TempDateiOperationenKopieren2->Items->Add(fileexplorer_dir + ListItem->Caption);
 }

 if (FTPFile(TempDateiOperationenKopieren2->Items->Strings[0]))
 {
 }
 else
 {
  DirektFTPClient->Asynchronous = true;
  TStrings* StrLst = new TStringList();
  TStrings* StrLst2 = new TStringList();
  for (int i = 0; i < TempDateiOperationenKopieren2->Items->Count; i++)
  {
   StrLst->Add(TempDateiOperationenKopieren2->Items->Strings[i]);
   StrLst2->Add(ExtractFileName(TempDateiOperationenKopieren2->Items->Strings[i]));
  }
  DirektFTPClient->PutFile(StrLst, StrLst2);
  while (DirektFTPClient->Busy)
   Application->ProcessMessages();
  DirektFTPClient->Asynchronous = false;
 }

 DirektFTPClient->TransferMode = vorheriger_modus;
 DirektFTPAktualisieren(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::BinrModus2Click(TObject *Sender)
{
 VerwControl->ActivePage = VerwTab3;
 int vorheriger_modus = DirektFTPClient->TransferMode;
 TempDateiOperationenKopieren2->Items->Clear();
 DirektFTPClient->TransferMode = BinaryTransfer;

 TListItem *ListItem;
 int items_count = ProjekteListe->Items->Count;

 for (int i = 0; i < items_count; i++)
 {
  ListItem = ProjekteListe->Items->Item[i];
  if (ListItem->Selected)
   TempDateiOperationenKopieren2->Items->Add(projectexplorer_dir + ListItem->Caption);
 }

 if (FTPFile(TempDateiOperationenKopieren2->Items->Strings[0]))
 {
 }
 else
 {
  DirektFTPClient->Asynchronous = true;
  TStrings* StrLst = new TStringList();
  TStrings* StrLst2 = new TStringList();
  for (int i = 0; i < TempDateiOperationenKopieren2->Items->Count; i++)
  {
   StrLst->Add(TempDateiOperationenKopieren2->Items->Strings[i]);
   StrLst2->Add(ExtractFileName(TempDateiOperationenKopieren2->Items->Strings[i]));
  }
  DirektFTPClient->PutFile(StrLst, StrLst2);
  while (DirektFTPClient->Busy)
   Application->ProcessMessages();
  DirektFTPClient->Asynchronous = false;
 }

 DirektFTPClient->TransferMode = vorheriger_modus;
 DirektFTPAktualisieren(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::AsciiModus2Click(TObject *Sender)
{
 VerwControl->ActivePage = VerwTab3;
 int vorheriger_modus = DirektFTPClient->TransferMode;
 TempDateiOperationenKopieren2->Items->Clear();
 DirektFTPClient->TransferMode = AsciiTransfer;

 TListItem *ListItem;
 int items_count = ProjekteListe->Items->Count;

 for (int i = 0; i < items_count; i++)
 {
  ListItem = ProjekteListe->Items->Item[i];
  if (ListItem->Selected)
   TempDateiOperationenKopieren2->Items->Add(projectexplorer_dir + ListItem->Caption);
 }

 if (FTPFile(TempDateiOperationenKopieren2->Items->Strings[0]))
 {
 }
 else
 {
  DirektFTPClient->Asynchronous = true;
  TStrings* StrLst = new TStringList();
  TStrings* StrLst2 = new TStringList();
  for (int i = 0; i < TempDateiOperationenKopieren2->Items->Count; i++)
  {
   StrLst->Add(TempDateiOperationenKopieren2->Items->Strings[i]);
   StrLst2->Add(ExtractFileName(TempDateiOperationenKopieren2->Items->Strings[i]));
  }
  DirektFTPClient->PutFile(StrLst, StrLst2);
  while (DirektFTPClient->Busy)
   Application->ProcessMessages();
  DirektFTPClient->Asynchronous = false;
 }

 DirektFTPClient->TransferMode = vorheriger_modus;
 DirektFTPAktualisieren(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ParagraphShortCutExecute(TObject *Sender)
{
 if (MDIChildCount)
 {
  TagInsert("<p>", "</p>");
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::Eigenschaften3Click(TObject *Sender)
{
 TDirektFTPEigenschaften* DirektFTPEigenschaften = new TDirektFTPEigenschaften(Application);
 SprachenWaehler->SetFormLanguage(DirektFTPEigenschaften);
 DirektFTPEigenschaften->Caption = ReplaceString(Eigenschaften3->Caption, "&", "", false, true);
 DirektFTPEigenschaften->ShowModal();
 DirektFTPAktualisieren(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::ToolButton102Click(TObject *Sender)
{
 if (MDIChildCount)
 {
  String farbe = "Black";
  int davor = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;

  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength != 0)
   farbe = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;
  else
  {
   if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt("\"", false, true, false, false))
   {
    int sel_start = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + 1;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt("\"", true, true, false, false);
    int sel_end = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = sel_start + 1;
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = (sel_end - sel_start) - 2;
    farbe = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;
   }
  }

  FarbCursorShape->Brush->Color = ColorXHTMLCodeToColor(farbe);
  if (FarbCursorShape->Brush->Color < 10000000)
   AktuelleFarbebeiCursor->Font->Color = clWhite;
  else
   AktuelleFarbebeiCursor->Font->Color = clBlack;
  AktuelleFarbebeiCursor->Caption = ColorColorToXHTMLCode(FarbCursorShape->Brush->Color);

  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = davor;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
 }
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FarbPaletteShapeMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (MDIChildCount)
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = AktuelleFarbeinPalette->Caption;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::FarbCursorShapeMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (MDIChildCount)
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = AktuelleFarbebeiCursor->Caption;
}
//---------------------------------------------------------------------------

void __fastcall THauptformular::PassendeKlammerfinden1Click(
      TObject *Sender)
{
 if (MDIChildCount)
 {
  bool go_on = false;
  String klammer = "";
  String such_klammer = "";
  String kompletter_suchtext = "";
  String temp;
  int interner_zaehler = -1;
  int vorsprung = 0;

  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength != 0)
  {
   klammer = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;
   if (AnsiPos(klammer, "{}()[]<>"))
   {
    go_on = true;
    if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength < 0)
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart - 1;
   }
  }
  else
  {
   ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
   klammer = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;

   if (AnsiPos(klammer, "{}()[]<>"))
    go_on = true;
   else
   {
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = -1;
    klammer = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;
    if (AnsiPos(klammer, "{}()[]<>"))
    {
     go_on = true;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart - 1;
    }
   }
  }

  if (go_on)
  {
   if (klammer == "(")
   {
    such_klammer = ")";
    kompletter_suchtext = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart, ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextLen());

    for (int i = 1; i < kompletter_suchtext.Length(); i++)
    {
     temp = kompletter_suchtext.SubString(i, 1);
     if (temp == klammer)
      interner_zaehler++;
     else if (temp == such_klammer && interner_zaehler == 0)
     {
      vorsprung = i;
      break;
     }
     else if (temp == such_klammer)
      interner_zaehler--;
    }
    if (interner_zaehler == 0 && temp == such_klammer)
    {
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + vorsprung - 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
    }
    else
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
   }
   else if (klammer == "{")
   {
    such_klammer = "}";
    kompletter_suchtext = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart, ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextLen());

    for (int i = 1; i < kompletter_suchtext.Length(); i++)
    {
     temp = kompletter_suchtext.SubString(i, 1);
     if (temp == klammer)
      interner_zaehler++;
     else if (temp == such_klammer && interner_zaehler == 0)
     {
      vorsprung = i;
      break;
     }
     else if (temp == such_klammer)
      interner_zaehler--;
    }
    if (interner_zaehler == 0 && temp == such_klammer)
    {
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + vorsprung - 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
    }
    else
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
   }
   else if (klammer == "[")
   {
    such_klammer = "]";
    kompletter_suchtext = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart, ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextLen());

    for (int i = 1; i < kompletter_suchtext.Length(); i++)
    {
     temp = kompletter_suchtext.SubString(i, 1);
     if (temp == klammer)
      interner_zaehler++;
     else if (temp == such_klammer && interner_zaehler == 0)
     {
      vorsprung = i;
      break;
     }
     else if (temp == such_klammer)
      interner_zaehler--;
    }
    if (interner_zaehler == 0 && temp == such_klammer)
    {
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + vorsprung - 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
    }
    else
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
   }
   else if (klammer == "<")
   {
    such_klammer = ">";
    kompletter_suchtext = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart, ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextLen());

    for (int i = 1; i < kompletter_suchtext.Length(); i++)
    {
     temp = kompletter_suchtext.SubString(i, 1);
     if (temp == klammer)
      interner_zaehler++;
     else if (temp == such_klammer && interner_zaehler == 0)
     {
      vorsprung = i;
      break;
     }
     else if (temp == such_klammer)
      interner_zaehler--;
    }
    if (interner_zaehler == 0 && temp == such_klammer)
    {
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + vorsprung - 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
    }
    else
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
   }
   else if (klammer == ")")
   {
    such_klammer = "(";
    kompletter_suchtext = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(0, ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + 1);

    for (int i = kompletter_suchtext.Length(); i > 0; i--)
    {
     temp = kompletter_suchtext.SubString(i, 1);
     if (temp == klammer)
      interner_zaehler++;
     else if (temp == such_klammer && interner_zaehler == 0)
     {
      vorsprung = i;
      break;
     }
     else if (temp == such_klammer)
      interner_zaehler--;
    }
    if (interner_zaehler == 0 && temp == such_klammer)
    {
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = vorsprung - 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
    }
    else
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
   }
   else if (klammer == "}")
   {
    such_klammer = "{";
    kompletter_suchtext = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(0, ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + 1);

    for (int i = kompletter_suchtext.Length(); i > 0; i--)
    {
     temp = kompletter_suchtext.SubString(i, 1);
     if (temp == klammer)
      interner_zaehler++;
     else if (temp == such_klammer && interner_zaehler == 0)
     {
      vorsprung = i;
      break;
     }
     else if (temp == such_klammer)
      interner_zaehler--;
    }
    if (interner_zaehler == 0 && temp == such_klammer)
    {
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = vorsprung - 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
    }
     else
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
   }
   else if (klammer == "]")
   {
    such_klammer = "[";
    kompletter_suchtext = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(0, ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + 1);

    for (int i = kompletter_suchtext.Length(); i > 0; i--)
    {
     temp = kompletter_suchtext.SubString(i, 1);
     if (temp == klammer)
      interner_zaehler++;
     else if (temp == such_klammer && interner_zaehler == 0)
     {
      vorsprung = i;
      break;
     }
     else if (temp == such_klammer)
      interner_zaehler--;
    }
    if (interner_zaehler == 0 && temp == such_klammer)
    {
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = vorsprung - 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
    }
     else
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
   }
   else if (klammer == ">")
   {
    such_klammer = "<";
    kompletter_suchtext = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(0, ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart + 1);

    for (int i = kompletter_suchtext.Length(); i > 0; i--)
    {
     temp = kompletter_suchtext.SubString(i, 1);
     if (temp == klammer)
      interner_zaehler++;
     else if (temp == such_klammer && interner_zaehler == 0)
     {
      vorsprung = i;
      break;
     }
     else if (temp == such_klammer)
      interner_zaehler--;
    }
    if (interner_zaehler == 0 && temp == such_klammer)
    {
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = vorsprung - 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
    }
     else
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 1;
   }
  }
  else
    ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
 }
}
//---------------------------------------------------------------------------


