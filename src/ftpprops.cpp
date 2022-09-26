//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ftpprops.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDirektFTPEigenschaften *DirektFTPEigenschaften;
//---------------------------------------------------------------------------
__fastcall TDirektFTPEigenschaften::TDirektFTPEigenschaften(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDirektFTPEigenschaften::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TDirektFTPEigenschaften::BitBtn1Click(TObject *Sender)
{
 Hauptformular->DirektFTPClient->FileSetAttr(Hauptformular->DirektFTPListe->ItemFocused->Caption, CheckBox1->Checked, CheckBox2->Checked, CheckBox3->Checked, CheckBox6->Checked, CheckBox5->Checked, CheckBox4->Checked, CheckBox7->Checked, CheckBox8->Checked, CheckBox9->Checked);
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TDirektFTPEigenschaften::FormShow(TObject *Sender)
{
 int index = Hauptformular->DirektFTPListe->ItemFocused->Index;
 index = index + Hauptformular->DirektFTPExplorer->Items->Count;

 if ((Hauptformular->DirektFTPExplorer->Items->Item[0])->Caption == Hauptformular->SprachenWaehler->GetString(40))
  index--;

 Label7->Caption = Hauptformular->directftp_current_dir + Hauptformular->DirektFTPTemp->Items->Item[index]->Caption;
 Label8->Caption = Hauptformular->DirektFTPTemp->Items->Item[index]->SubItems->Strings[0];
 Label9->Caption = Hauptformular->DirektFTPTemp->Items->Item[index]->SubItems->Strings[2];
 Label10->Caption = Hauptformular->DirektFTPTemp->Items->Item[index]->SubItems->Strings[4];
 Label11->Caption = Hauptformular->DirektFTPTemp->Items->Item[index]->SubItems->Strings[5];

 String rechte = Hauptformular->DirektFTPTemp->Items->Item[index]->SubItems->Strings[3];
 String owner_read = rechte.SubString(2, 1);
 String owner_write = rechte.SubString(3, 1);
 String owner_execute = rechte.SubString(4, 1);
 String group_read = rechte.SubString(5, 1);
 String group_write = rechte.SubString(6, 1);
 String group_execute = rechte.SubString(7, 1);
 String public_read = rechte.SubString(8, 1);
 String public_write = rechte.SubString(9, 1);
 String public_execute = rechte.SubString(10, 1);

 if (owner_read != "-")
  CheckBox1->Checked = true;
 if (owner_write != "-")
  CheckBox2->Checked = true;
 if (owner_execute != "-")
  CheckBox3->Checked = true;

 if (group_read != "-")
  CheckBox6->Checked = true;
 if (group_write != "-")
  CheckBox5->Checked = true;
 if (group_execute != "-")
  CheckBox4->Checked = true;

 if (public_read != "-")
  CheckBox7->Checked = true;
 if (public_write != "-")
  CheckBox8->Checked = true;
 if (public_execute != "-")
  CheckBox9->Checked = true;
}
//---------------------------------------------------------------------------

