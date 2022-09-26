//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "openinet.h"
#include "main.h"
#include "hilfed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOeffnenausdemInternet *OeffnenausdemInternet;
//---------------------------------------------------------------------------
__fastcall TOeffnenausdemInternet::TOeffnenausdemInternet(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOeffnenausdemInternet::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->HistoryWrite("URLs", ComboBox1->Items);
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TOeffnenausdemInternet::FormShow(TObject *Sender)
{
 ComboBox1->Items = Hauptformular->HistoryRead("URLs");
}
//---------------------------------------------------------------------------

void __fastcall TOeffnenausdemInternet::BitBtn1Click(TObject *Sender)
{
 Screen->Cursor = crHourGlass;
 ComboBox1->Items->Insert(0, ComboBox1->Text);
 Hauptformular->HTTPClient->FileName = Hauptformular->program_dir + "~temp.html";
 Hauptformular->HTTPClient->URL = ComboBox1->Text;
 Hauptformular->HTTPClient->GetFile();
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TOeffnenausdemInternet::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TOeffnenausdemInternet::ComboBox1KeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
/* if (Key != 13)
 {
  int start = ComboBox1->SelStart;
  int Findex;
  Findex = SendMessage(ComboBox1->Handle, CB_FINDSTRING, Findex-1, (long)(ComboBox1->Text.c_str()));
  if ((Findex != -1) && !((Key == VK_DELETE)||Key ==8))
   SendMessage(ComboBox1->Handle, CB_SETCURSEL, Findex, 0);
  ComboBox1->SelStart = start;
  ComboBox1->SelLength = ComboBox1->GetTextLen() - start;
 }*/
}
//---------------------------------------------------------------------------

void __fastcall TOeffnenausdemInternet::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_openweb.html", true);
}
//---------------------------------------------------------------------------

