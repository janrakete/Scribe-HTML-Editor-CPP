//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "grafkata.h"
#include "main.h"
#include "hilfed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGrafikKatalog *GrafikKatalog;
//---------------------------------------------------------------------------
__fastcall TGrafikKatalog::TGrafikKatalog(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGrafikKatalog::BitBtn2Click(TObject *Sender)
{
 Hauptformular->image_catalog_file = "";
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_image_catalog.html", true);      
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::FormShow(TObject *Sender)
{
 drag_file == "";
 String temp_str;
 TListItem *ListItem;

 KategorieListe->Directory = Hauptformular->program_dir + "Storage!\\Catalog\\";
 KategorieListe->Items->Delete(0);
 KategorieListe->Items->Delete(0);
 for (int i = 0; i < KategorieListe->Items->Count; i++)
 {
  temp_str = KategorieListe->Items->Strings[i];
  temp_str = temp_str.SubString(2, temp_str.Length());
  temp_str = temp_str.SubString(0, temp_str.Length() - 1);
  ListItem = Kategorien->Items->Add();
  ListItem->Caption = temp_str;
  ListItem->ImageIndex = 57;
 }
 Kategorien->AlphaSort();
 if (Kategorien->Items->Count > - 1)
 {
  Kategorien->Selected = Kategorien->Items->Item[0];
  KategorienClick(Sender);
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::KategorienClick(TObject *Sender)
{
 if (Kategorien->Selected)
 {
  Grafiken->Items->Clear();
  String sel_kat = Kategorien->Selected->Caption;
  String temp_str;
  TListItem *ListItem;
  GrafikenListe->Directory = Hauptformular->program_dir + "Storage!\\Catalog\\" + sel_kat + "\\";
  GrafikenListe->Update();

  for (int i = 0; i < GrafikenListe->Items->Count; i++)
  {
   temp_str = GrafikenListe->Items->Strings[i];
   ListItem = Grafiken->Items->Add();
   ListItem->Caption = temp_str;
   ListItem->ImageIndex = 56;
  }
  if (Grafiken->Items->Count > 0)
  {
   Grafiken->Selected = Grafiken->Items->Item[0];
   GrafikenClick(Sender);
  }
  else
  {
   Image1->Picture = NULL;
   GrafikenClick(Sender);
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::GrafikenClick(TObject *Sender)
{
 if (Grafiken->Selected)
 {
  TListItem *ListItem;
  Image1->Picture->LoadFromFile(Hauptformular->program_dir + "Storage!\\Catalog\\" + Kategorien->Selected->Caption + "\\" + Grafiken->Selected->Caption);

  if (Image1->Picture->Width < 283)
   Image1->Left = 140 - (Image1->Picture->Width / 2);
  else
   Image1->Left = 0;
  if (Image1->Picture->Height < 201)
   Image1->Top = 99 - (Image1->Picture->Height / 2);
  else
   Image1->Top = 0;

  Height->Caption = String(Image1->Picture->Height) + " " + Hauptformular->SprachenWaehler->GetString(11);
  Width->Caption = String(Image1->Picture->Width) + " " + Hauptformular->SprachenWaehler->GetString(11);
  Size->Caption = String(Hauptformular->FileGetSize(Hauptformular->program_dir + "Storage!\\Catalog\\" + Kategorien->Selected->Caption + "\\" + Grafiken->Selected->Caption) / 1024) + " KB";
 }
 else
 {
  Image1->Picture = NULL;
  Height->Caption = "0 " + Hauptformular->SprachenWaehler->GetString(11);
  Width->Caption = "0 " + Hauptformular->SprachenWaehler->GetString(11);
  Size->Caption = "0 KB";
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::BitBtn1Click(TObject *Sender)
{
 if (Grafiken->Selected)
  Hauptformular->image_catalog_file = Hauptformular->program_dir + "Storage!\\Catalog\\" + Kategorien->Selected->Caption + "\\" + Grafiken->Selected->Caption;
 else
  Hauptformular->image_catalog_file = "";
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::GrafikenDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
 if (Grafiken->Selected)
  drag_file = Hauptformular->program_dir + "Storage!\\Catalog\\" + Kategorien->Selected->Caption + "\\" + Grafiken->Selected->Caption;
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::KategorienDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
 if (Kategorien->GetItemAt(X, Y))
 {
  if (Kategorien->Selected != Kategorien->GetItemAt(X, Y))
  {
   Kategorien->Selected = Kategorien->GetItemAt(X, Y);
   KategorienClick(Sender);
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::KategorienDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
 if (Source == Grafiken)
 {
  String file_1 = drag_file;
  String file_2 = Hauptformular->program_dir + "Storage!\\Catalog\\" + (Kategorien->GetItemAt(X, Y))->Caption + "\\" + ExtractFileName(drag_file);
  Hauptformular->FileCopyOnlyOne(file_1, file_2);
  Kategorien->Selected = Kategorien->GetItemAt(X, Y);
  Kategorien->Update();
  KategorienClick(Sender);
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::KategorienEdited(TObject *Sender,
      TListItem *Item, AnsiString &S)
{
 String path = Hauptformular->program_dir + "Storage!\\Catalog\\";
 String Bez_Vorher = Item->Caption;
 String Bez_Nachher = S;
 Bez_Vorher = path + Bez_Vorher;
 Bez_Nachher = path + Bez_Nachher;
 if (!RenameFile(Bez_Vorher, Bez_Nachher))
  S = Item->Caption;
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::GrafikenEdited(TObject *Sender,
      TListItem *Item, AnsiString &S)
{
 String path = Hauptformular->program_dir + "Storage!\\Catalog\\" + Kategorien->Selected->Caption + "\\";
 String Bez_Vorher = Item->Caption;
 String Bez_Nachher = S;
 Bez_Vorher = path + Bez_Vorher;
 Bez_Nachher = path + Bez_Nachher;
 if (!Hauptformular->FileRename(Bez_Vorher, Bez_Nachher))
  S = Item->Caption;
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::PopupMenu1Popup(TObject *Sender)
{
 if (Kategorien->Selected)
 {
  Lschen1->Enabled = true;
  Umbenennen1->Enabled = true;
 }
 else
 {
  Lschen1->Enabled = false;
  Umbenennen1->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::PopupMenu2Popup(TObject *Sender)
{
 if (Grafiken->Selected)
 {
  Lschen2->Enabled = true;
  Umbenennen2->Enabled = true;
 }
 else
 {
  Lschen2->Enabled = false;
  Umbenennen2->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::Lschen2Click(TObject *Sender)
{
 String complete_file;
 complete_file = Hauptformular->program_dir + "Storage!\\Catalog\\" + Kategorien->Selected->Caption + "\\";
 complete_file = complete_file + Grafiken->Selected->Caption;

 if (Hauptformular->FileDeleteOnlyOne(complete_file, true))
  Grafiken->Selected->Delete();
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::Lschen1Click(TObject *Sender)
{
 int button = Application->MessageBox(Hauptformular->SprachenWaehler->GetStringEx(75, Kategorien->Selected->Caption).c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON2 + MB_ICONQUESTION);
 if (button == IDYES)
 {
  String sel_kat = Kategorien->Selected->Caption;
  if (Hauptformular->DirectoryDelete(Hauptformular->program_dir + "Storage!\\Catalog\\" + sel_kat + "\\"))
  {
   Kategorien->Selected->Delete();
   if (Kategorien->Items->Count > 0)
   {
    Kategorien->Selected = Kategorien->Items->Item[0];
    KategorienClick(Sender);
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::NeueKategorie1Click(TObject *Sender)
{
 String eingabe = Hauptformular->SprachenWaehler->GetString(74) + "_" + String(Kategorien->Items->Count + 1);
 if (InputQuery(Hauptformular->ReplaceString(NeueKategorie1->Caption, "&", "", false, true), Hauptformular->SprachenWaehler->GetString(73), eingabe))
 {
  if (CreateDir(Hauptformular->program_dir + "Storage!\\Catalog\\" + eingabe))
  {
   TListItem *ListItem;
   ListItem = Kategorien->Items->Add();
   ListItem->Caption = eingabe;
   ListItem->ImageIndex = 57;
   Kategorien->AlphaSort();
   Kategorien->Selected = ListItem;
   KategorienClick(Sender);
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::Hinzufgen1Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(6);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->graphicfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OpenDialog1->Filter = filter_gesamt;
 OpenDialog1->Title = Hauptformular->ReplaceString(Hinzufgen1->Caption, "&", "", false, true);

 if (OpenDialog1->Execute())
 {
  String file_1;
  String file_2;
  for (int i = 0; i < OpenDialog1->Files->Count; i++)
  {
   file_1 = OpenDialog1->Files->Strings[i];
   file_2 = Hauptformular->program_dir + "Storage!\\Catalog\\" + Kategorien->Selected->Caption + "\\" + ExtractFileName(OpenDialog1->Files->Strings[i]);
   Hauptformular->FileCopyOnlyOne(file_1, file_2);
  }
  KategorienClick(Sender);
 }
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::Umbenennen1Click(TObject *Sender)
{
 Kategorien->ItemFocused->EditCaption();
}
//---------------------------------------------------------------------------

void __fastcall TGrafikKatalog::Umbenennen2Click(TObject *Sender)
{
 Grafiken->ItemFocused->EditCaption();
}
//---------------------------------------------------------------------------

