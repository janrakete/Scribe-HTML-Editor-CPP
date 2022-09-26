//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ftpprofi.h"
#include "main.h"
#include "hilfed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFTPProfile *FTPProfile;
//---------------------------------------------------------------------------
__fastcall TFTPProfile::TFTPProfile(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFTPProfile::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->DirectFTPLoadProfiles(Hauptformular->DirektFTPAuswahl->Items->Strings[Hauptformular->DirektFTPAuswahl->ItemIndex]);
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TFTPProfile::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TFTPProfile::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_ftp_profiles.html", true);
}
//---------------------------------------------------------------------------
void __fastcall TFTPProfile::ProfileClick(TObject *Sender)
{
 if (Profile->Selected)
 {
  String sel_profil = Profile->Selected->Caption;
  Profilname->Text = sel_profil;

  TIniFile* Profil = new TIniFile(Hauptformular->program_dir + "Storage!\\ftpprofiles.ini");

  Account->Text = Profil->ReadString(sel_profil, "Account", "");
  Passive->Checked = Profil->ReadBool(sel_profil, "Passive", false);
  Password->Text = Hauptformular->Base64Decode(Profil->ReadString(sel_profil, "Password", ""));
  Port->Text = Profil->ReadInteger(sel_profil, "Port", 21);
  ProxyPassword->Text = Hauptformular->Base64Decode(Profil->ReadString(sel_profil, "ProxyPassword", ""));
  ProxyPort->Text = Profil->ReadInteger(sel_profil, "ProxyPort", 21);
  ProxyServer->Text = Profil->ReadString(sel_profil, "ProxyServer", "");
  //-----------------------------
  if (Profil->ReadString(sel_profil, "ProxyType", "None") == "Host")
   ProxyType->ItemIndex = 1;
  else if (Profil->ReadString(sel_profil, "ProxyType", "None") == "Host user")
   ProxyType->ItemIndex = 2;
  else if (Profil->ReadString(sel_profil, "ProxyType", "None") == "Open")
   ProxyType->ItemIndex = 3;
  else if (Profil->ReadString(sel_profil, "ProxyType", "None") == "Site")
   ProxyType->ItemIndex = 4;
  else if (Profil->ReadString(sel_profil, "ProxyType", "None") == "User site")
   ProxyType->ItemIndex = 5;
  else
   ProxyType->ItemIndex = 0;
  //-----------------------------
  ProxyUsername->Text = Profil->ReadString(sel_profil, "ProxyUsername", "");
  RetriesController->Position = Profil->ReadInteger(sel_profil, "Retries", 5);
  Server->Text = Profil->ReadString(sel_profil, "Server", "");
  //-----------------------------
  if (Profil->ReadString(sel_profil, "TransferMode", "BinaryTransfer") == "BinaryTransfer")
   TransferMode->ItemIndex = 0;
  else
   TransferMode->ItemIndex = 1;
  //-----------------------------
  Username->Text = Profil->ReadString(sel_profil, "Username", "Anonymous");

  delete Profil;
 }
}
//---------------------------------------------------------------------------
void __fastcall TFTPProfile::BitBtn1Click(TObject *Sender)
{
 if (Trim(Profilname->Text) != "")
 {
  if (Profile->FindCaption(0, Profilname->Text, false, true, false))
   Profile->FindCaption(0, Profilname->Text, false, true, false)->Delete();

  TListItem *ListItem;
  ListItem = Profile->Items->Add();
  ListItem->Caption =  Profilname->Text;
  ListItem->ImageIndex = 43;

  TIniFile* Profil = new TIniFile(Hauptformular->program_dir + "Storage!\\ftpprofiles.ini");

  Profil->WriteString(Profilname->Text, "Account", Account->Text);
  Profil->WriteBool(Profilname->Text, "Passive", Passive->Checked);
  Profil->WriteString(Profilname->Text, "Password", Hauptformular->Base64Encode(Password->Text));
  Profil->WriteInteger(Profilname->Text, "Port", Port->Text.ToIntDef(21));
  Profil->WriteString(Profilname->Text, "ProxyPassword", Hauptformular->Base64Encode(ProxyPassword->Text));
  Profil->WriteInteger(Profilname->Text, "ProxyPort", ProxyPort->Text.ToIntDef(21));
  Profil->WriteString(Profilname->Text, "ProxyServer", ProxyServer->Text);
  //-----------------------------
  if (ProxyType->ItemIndex == 1)
   Profil->WriteString(Profilname->Text, "ProxyType", "Host");
  else if (ProxyType->ItemIndex == 2)
   Profil->WriteString(Profilname->Text, "ProxyType", "Host user");
  else if (ProxyType->ItemIndex == 3)
   Profil->WriteString(Profilname->Text, "ProxyType", "Open");
  else if (ProxyType->ItemIndex == 4)
   Profil->WriteString(Profilname->Text, "ProxyType", "Site");
  else if (ProxyType->ItemIndex == 5)
   Profil->WriteString(Profilname->Text, "ProxyType", "User site");
  else
   Profil->WriteString(Profilname->Text, "ProxyType", "None");
  //-----------------------------
  Profil->WriteString(Profilname->Text, "ProxyUsername", ProxyUsername->Text);
  Profil->WriteInteger(Profilname->Text, "Retries", RetriesController->Position);
  Profil->WriteString(Profilname->Text, "Server", Server->Text);
  //-----------------------------
  if (TransferMode->ItemIndex == 0)
   Profil->WriteString(Profilname->Text, "TransferMode", "BinaryTransfer");
  else
   Profil->WriteString(Profilname->Text, "TransferMode", "AsciiTransfer");
  //-----------------------------
  Profil->WriteString(Profilname->Text, "Username", Username->Text);

  delete Profil;

  Profile->Selected = ListItem;
 }
 else
  Application->MessageBox(Hauptformular->SprachenWaehler->GetString(42).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
void __fastcall TFTPProfile::FormShow(TObject *Sender)
{
 TListItem *ListItem;

 for (int i = 1; i < Hauptformular->DirektFTPAuswahl->Items->Count; i++)
 {
  ListItem = Profile->Items->Add();
  ListItem->Caption = Hauptformular->DirektFTPAuswahl->Items->Strings[i];
  ListItem->ImageIndex = 43;
  Profile->Update();
 }

 if (Profile->Items->Count > 0)
 {
  String sel_profil = Hauptformular->DirektFTPAuswahl->Items->Strings[Hauptformular->DirektFTPAuswahl->ItemIndex];
  if (Profile->FindCaption(0, sel_profil, false, true, false))
   Profile->Selected = Profile->FindCaption(0, sel_profil, false, true, false);
  else
   Profile->Selected = Profile->Items->Item[0];
  ProfileClick(Sender);
 }
}
//---------------------------------------------------------------------------
void __fastcall TFTPProfile::PopupMenu1Popup(TObject *Sender)
{
 if (Profile->Selected)
  Lschen1->Enabled = true;
 else
  Lschen1->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFTPProfile::Lschen1Click(TObject *Sender)
{
 TIniFile* Profil = new TIniFile(Hauptformular->program_dir + "Storage!\\ftpprofiles.ini");
 Profil->EraseSection(Profile->Selected->Caption);
 Profile->Selected->Delete();
 delete Profil;
}
//---------------------------------------------------------------------------
