//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "addluni.h"
#include "main.h"
#include "hilfed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddLangUniDialog *AddLangUniDialog;
//---------------------------------------------------------------------------
__fastcall TAddLangUniDialog::TAddLangUniDialog(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAddLangUniDialog::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TAddLangUniDialog::FormShow(TObject *Sender)
{
 Caption = Hauptformular->ParseString(Hauptformular->addlang_current_tag, "|", 0);
}
//---------------------------------------------------------------------------

void __fastcall TAddLangUniDialog::SpeedButton2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

