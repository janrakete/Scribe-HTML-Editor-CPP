//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "button.h"
#include "main.h"
#include "hilfed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Plusmemo"
#pragma resource "*.dfm"
TButtonx *Buttonx;
//---------------------------------------------------------------------------
__fastcall TButtonx::TButtonx(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TButtonx::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_buttonx.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->ButtonxListItems();
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::FormShow(TObject *Sender)
{
 TListItem *ListItem;

 for (int i = 0; i < Hauptformular->ButtonxControl->Tabs->Count; i++)
 {
  ListItem = ButtonxListe->Items->Add();
  ListItem->Caption = Hauptformular->ButtonxControl->Tabs->Strings[i];
  ListItem->ImageIndex = 52;
  ButtonxListe->Update();
 }

 if (ButtonxListe->Items->Count > 0)
 {
  ButtonxListe->Selected = ButtonxListe->Items->Item[0];
  ButtonxListeClick(Sender);
 }
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::BitBtn1Click(TObject *Sender)
{
 if (Trim(Edit2->Text) != "")
 {
  if (ButtonxListe->FindCaption(0, Edit2->Text, false, true, false))
   ButtonxListe->FindCaption(0, Edit2->Text, false, true, false)->Delete();

  PlusMemo1->SelectAll();
  String code = PlusMemo1->SelText;
  code = Hauptformular->ReplaceString(code, "\r\n", "#Br",  true, false);
  PlusMemo1->SelStart = 0;

  TListItem *ListItem;
  ListItem = ButtonxListe->Items->Add();
  ListItem->Caption = Edit2->Text;
  ListItem->ImageIndex = 52;

  TIniFile* Buttonx = new TIniFile(Hauptformular->program_dir + "Storage!\\buttonx.ini");
  Buttonx->WriteString(Edit2->Text, "Code", code);
  delete Buttonx;

  ButtonxListe->Selected = ListItem;
 }
 else
  Application->MessageBox(Hauptformular->SprachenWaehler->GetString(42).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::ButtonxListeClick(TObject *Sender)
{
 if (ButtonxListe->Selected)
 {
  PlusMemo1->Lines->Clear();
  String sel_profil = ButtonxListe->Selected->Caption;
  Edit2->Text = sel_profil;
  TIniFile* Buttonx = new TIniFile(Hauptformular->program_dir + "Storage!\\buttonx.ini");
  PlusMemo1->SelText = Hauptformular->ReplaceString(Buttonx->ReadString(sel_profil, "Code", ""), "#Br", "\r\n",  true, false);
  delete Buttonx;
 }
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::Lschen1Click(TObject *Sender)
{
 TIniFile* Buttonx = new TIniFile(Hauptformular->program_dir + "Storage!\\buttonx.ini");
 Buttonx->EraseSection(ButtonxListe->Selected->Caption);
 ButtonxListe->Selected->Delete();
 delete Buttonx;
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::PopupMenu1Popup(TObject *Sender)
{
 if (ButtonxListe->Selected)
  Lschen1->Enabled = true;
 else
  Lschen1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::PopupMenu2Popup(TObject *Sender)
{
 Einfgen2->Enabled = Clipboard()->HasFormat(CF_TEXT);

 if (PlusMemo1->SelLength != 0)
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

void __fastcall TButtonx::Ausschneiden2Click(TObject *Sender)
{
 PlusMemo1->CutToClipboard();        
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::Kopieren2Click(TObject *Sender)
{
 PlusMemo1->CopyToClipboard();        
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::Einfgen2Click(TObject *Sender)
{
 if (Clipboard()->HasFormat(CF_TEXT))
  PlusMemo1->PasteFromClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::Lschen2Click(TObject *Sender)
{
 PlusMemo1->ClearSelection();
}
//---------------------------------------------------------------------------

void __fastcall TButtonx::ButtonxListeDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
 ButtonxListe->Checkboxes = false;
 int NewItemIndex = ButtonxListe->Items->IndexOf(ButtonxListe->GetItemAt(X, Y));

 if (NewItemIndex > -1 && NewItemIndex < ButtonxListe->Items->Count)
 {
  ButtonxListe->Items->Insert(NewItemIndex);
  ButtonxListe->Items->Item[NewItemIndex] = ButtonxListe->Selected;
  ButtonxListe->Items->Delete(ButtonxListe->Items->IndexOf(ButtonxListe->Selected));
  ButtonxListe->Items->Item[NewItemIndex]->Selected = true;
  ButtonxListe->Items->Item[NewItemIndex]->Focused = true;
 }
 ButtonxListe->Checkboxes = false;
}
//---------------------------------------------------------------------------



void __fastcall TButtonx::ButtonxListeDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
//        
}
//---------------------------------------------------------------------------

