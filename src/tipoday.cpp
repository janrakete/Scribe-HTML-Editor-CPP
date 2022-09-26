//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "tipoday.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTippDesTages *TippDesTages;
//---------------------------------------------------------------------------
__fastcall TTippDesTages::TTippDesTages(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTippDesTages::FormShow(TObject *Sender)
{
 TippMemo->Lines->LoadFromFile(Hauptformular->program_dir + "Storage!\\tips.ini");
 int Zeile;
 randomize();
 Zeile = random (TippMemo->Lines->Count);
 Label2->Caption = TippMemo->Lines->Strings[Zeile];
 LineCounter->Caption = Zeile;
}
//---------------------------------------------------------------------------

void __fastcall TTippDesTages::SpeedButton1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TTippDesTages::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if (CheckBox1->Checked)
  Hauptformular->editor_show_tip = true;
 else
  Hauptformular->editor_show_tip = false;
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TTippDesTages::BitBtn1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TTippDesTages::BitBtn2Click(TObject *Sender)
{
 if ((LineCounter->Caption).ToInt() < TippMemo->Lines->Count - 1)
 {
  Label2->Caption = TippMemo->Lines->Strings[(LineCounter->Caption).ToInt() + 1];
  LineCounter->Caption = (LineCounter->Caption).ToInt() + 1;
 }
 else
 {
  Label2->Caption = TippMemo->Lines->Strings[0];
  LineCounter->Caption = 0;
 }
}
//---------------------------------------------------------------------------

