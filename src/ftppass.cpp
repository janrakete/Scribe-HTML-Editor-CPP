//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ftppass.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDirektesFTPPasswort *DirektesFTPPasswort;
//---------------------------------------------------------------------------
__fastcall TDirektesFTPPasswort::TDirektesFTPPasswort(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDirektesFTPPasswort::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TDirektesFTPPasswort::FormShow(TObject *Sender)
{
 Caption = Label2->Caption;
}
//---------------------------------------------------------------------------
void __fastcall TDirektesFTPPasswort::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TDirektesFTPPasswort::BitBtn1Click(TObject *Sender)
{
 Hauptformular->directftp_temp_input = Edit1->Text;
 Close();
}
//---------------------------------------------------------------------------

