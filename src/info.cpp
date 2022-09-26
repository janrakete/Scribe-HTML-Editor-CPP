//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "info.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "credits"
#pragma resource "*.dfm"
TInfoDialog *InfoDialog;
//---------------------------------------------------------------------------
__fastcall TInfoDialog::TInfoDialog(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInfoDialog::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TInfoDialog::Image1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TInfoDialog::Shape1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TInfoDialog::FormShow(TObject *Sender)
{
 Label1->Caption = "Version " + Hauptformular->program_version;
}
//---------------------------------------------------------------------------

void __fastcall TInfoDialog::SpeedButton1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

