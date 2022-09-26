//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THilfe *Hilfe;
//---------------------------------------------------------------------------
__fastcall THilfe::THilfe(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THilfe::ToolButton3Click(TObject *Sender)
{
 Hauptformular->msie_helpbrowser->GoBack();
}
//---------------------------------------------------------------------------

void __fastcall THilfe::ToolButton4Click(TObject *Sender)
{
 Hauptformular->msie_helpbrowser->GoForward();
}
//---------------------------------------------------------------------------

void __fastcall THilfe::ToolButton1Click(TObject *Sender)
{
 String hilfe_datei = Hauptformular->program_dir + "Storage!\\Help\\index.html";
 wchar_t hilfe_temp[400];
 StringToWideChar(hilfe_datei, hilfe_temp, 400);
 Hauptformular->msie_helpbrowser->Navigate(hilfe_temp);
}
//---------------------------------------------------------------------------

void __fastcall THilfe::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->msie_helpbrowser->Stop();
 if (ControlBar1->Visible)
 {
  Hauptformular->help_window_top = Top;
  Hauptformular->help_window_left = Left;
  Hauptformular->help_window_height = Height;
  Hauptformular->help_window_width = Width;
 }
 else
 {
  //Hauptformular->window_that_started_help->Left = (Screen->Width  / 2) - (Hauptformular->window_that_started_help->Width / 2);
  //Hauptformular->window_that_started_help->Top = (Screen->Height  / 2) - (Hauptformular->window_that_started_help->Height / 2);
  //Hauptformular->window_that_started_help = NULL;
 }
}
//---------------------------------------------------------------------------

