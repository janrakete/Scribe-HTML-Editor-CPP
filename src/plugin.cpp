//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "plugin.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPlugins *Plugins;
//---------------------------------------------------------------------------
__fastcall TPlugins::TPlugins(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPlugins::FormClose(TObject *Sender, TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TPlugins::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------


void __fastcall TPlugins::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_plugins.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TPlugins::BitBtn1Click(TObject *Sender)
{
 if (ListView1->Selected)
 {
  Visible = false;
  Hauptformular->ScribePluginEngine(Hauptformular->program_dir + "Storage!\\Plugins\\" + Hauptformular->TempDateilistBox->Items->Strings[ListView1->Selected->Index]);
  Close();
 }
}
//---------------------------------------------------------------------------

void __fastcall TPlugins::FormShow(TObject *Sender)
{
 HINSTANCE plugin;
 String PName;
 String PVersion;
 String PAutor;
 int pversion;
 TListItem *ListItem;
 Hauptformular->TempDateilistBox->Directory = Hauptformular->program_dir + "Storage!\\Plugins";
 Hauptformular->TempDateilistBox->Mask = "*.dll";
 Hauptformular->TempDateilistBox->Update();

 int items_count = Hauptformular->TempDateilistBox->Items->Count;
 for (int i = 0; i < items_count; i++)
 {
  if (Hauptformular->plugin_read_name_title)
  {
   plugin = LoadLibrary((Hauptformular->program_dir + "Storage!\\Plugins\\" + Hauptformular->TempDateilistBox->Items->Strings[i]).c_str());
   typedef int (__stdcall  *pluginInterfaceVersionType)();
   pluginInterfaceVersionType pluginInterfaceVersiontyp;
   pluginInterfaceVersiontyp = (pluginInterfaceVersionType)GetProcAddress(plugin, "pluginInterfaceVersion");
   pversion = (pluginInterfaceVersiontyp)();

   if (pversion == 2)
   {
    typedef PChar (__stdcall *pluginPluginInfoType)(int);
    pluginPluginInfoType pluginPluginInfotyp;
    pluginPluginInfotyp = (pluginPluginInfoType)GetProcAddress(plugin, "pluginInfo");
    PName = (pluginPluginInfotyp)(1);
    PVersion = (pluginPluginInfotyp)(2);
    PAutor = (pluginPluginInfotyp)(3);
   }
   else
   {
    PName = Hauptformular->TempDateilistBox->Items->Strings[i].SubString(0, (AnsiPos(".", Hauptformular->TempDateilistBox->Items->Strings[i])) - 1);
    PAutor = "";
    PVersion = "";
   }
  }
  else
  {
   PName = Hauptformular->TempDateilistBox->Items->Strings[i].SubString(0, (AnsiPos(".", Hauptformular->TempDateilistBox->Items->Strings[i])) - 1);
   PAutor = "";
   PVersion = "";
  }
  ListItem = ListView1->Items->Add();
  if (PVersion == "")
   ListItem->Caption = PName;
  else
   ListItem->Caption = PName + " " + PVersion;
  ListItem->SubItems->Add(PAutor);
  ListItem->ImageIndex = 4;
  FreeLibrary (plugin);
 }
}
//---------------------------------------------------------------------------

void __fastcall TPlugins::ToolButton1Click(TObject *Sender)
{
 if (ListView1->Selected)
 {
  HINSTANCE plugin = LoadLibrary((Hauptformular->program_dir + "Storage!\\Plugins\\" + Hauptformular->TempDateilistBox->Items->Strings[ListView1->Selected->Index]).c_str());
  typedef int (__stdcall *pluginInterfaceVersionType)();
  pluginInterfaceVersionType pluginInterfaceVersiontyp;
  pluginInterfaceVersiontyp = (pluginInterfaceVersionType)GetProcAddress(plugin, "pluginInterfaceVersion");
  int pversion = (pluginInterfaceVersiontyp)();

  if (pversion == 2)
  {
   typedef int (__stdcall *pluginKonfigType)();
   pluginKonfigType pluginKonfigtyp;
   pluginKonfigtyp = (pluginKonfigType)GetProcAddress(plugin, "pluginKonfig");
   int pconfig = (pluginKonfigtyp)();
   if (pconfig == -1)
    Application->MessageBox(Hauptformular->SprachenWaehler->GetString(59).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);
  }
  else
   Application->MessageBox(Hauptformular->SprachenWaehler->GetString(59).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);

  FreeLibrary (plugin);
 }
}
//---------------------------------------------------------------------------

void __fastcall TPlugins::ToolButton2Click(TObject *Sender)
{
 if (ListView1->Selected)
 {
  HINSTANCE plugin = LoadLibrary((Hauptformular->program_dir + "Storage!\\Plugins\\" + Hauptformular->TempDateilistBox->Items->Strings[ListView1->Selected->Index]).c_str());
  typedef int (__stdcall *pluginInterfaceVersionType)();
  pluginInterfaceVersionType pluginInterfaceVersiontyp;
  pluginInterfaceVersiontyp = (pluginInterfaceVersionType)GetProcAddress(plugin, "pluginInterfaceVersion");
  int pversion = (pluginInterfaceVersiontyp)();

  if (pversion == 2)
  {
   typedef PChar (__stdcall *pluginPluginInfoType)(int);
   pluginPluginInfoType pluginPluginInfotyp;
   pluginPluginInfotyp = (pluginPluginInfoType)GetProcAddress(plugin, "pluginInfo");
   String gesamt;

   String pname = (pluginPluginInfotyp)(1);
   String pversion = (pluginPluginInfotyp)(2);
   String pautor = (pluginPluginInfotyp)(3);
   String pcopy = (pluginPluginInfotyp)(4);
   String purl = (pluginPluginInfotyp)(5);
   String pmail = (pluginPluginInfotyp)(6);

   if (Trim(pname) != "")
    gesamt = gesamt + "Name: " + pname + "\n";
   if (Trim(pversion) != "")
    gesamt = gesamt + "Version: " + pversion + "\n";
   if (Trim(pautor) != "")
    gesamt = gesamt + ListView1->Column[1]->Caption + ": " + pautor + "\n";
   if (Trim(pcopy) != "")
    gesamt = gesamt + "Copyright: " + pcopy + "\n";
   if (Trim(purl) != "")
    gesamt = gesamt + "Homepage: " + purl + "\n";
   if (Trim(pmail) != "")
    gesamt = gesamt + "e-Mail: " + pmail;
   Application->MessageBox(gesamt.c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);
  }
  else
   Application->MessageBox(Hauptformular->SprachenWaehler->GetString(59).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);

  FreeLibrary (plugin);
 }
}
//---------------------------------------------------------------------------

void __fastcall TPlugins::ToolButton3Click(TObject *Sender)
{
 if (ListView1->Selected)
 {
  HINSTANCE plugin = LoadLibrary((Hauptformular->program_dir + "Storage!\\Plugins\\" + Hauptformular->TempDateilistBox->Items->Strings[ListView1->Selected->Index]).c_str());
  typedef int (__stdcall *pluginInterfaceVersionType)();
  pluginInterfaceVersionType pluginInterfaceVersiontyp;
  pluginInterfaceVersiontyp = (pluginInterfaceVersionType)GetProcAddress(plugin, "pluginInterfaceVersion");
  int pversion = (pluginInterfaceVersiontyp)();

  if (pversion == 2)
  {
   typedef int (__stdcall *pluginHilfeType)();
   pluginHilfeType pluginHilfetyp;
   pluginHilfetyp = (pluginHilfeType)GetProcAddress(plugin, "pluginHilfe");
   int philfe = (pluginHilfetyp)();
   if (philfe == -1)
    Application->MessageBox(Hauptformular->SprachenWaehler->GetString(59).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);
  }
  else
   Application->MessageBox(Hauptformular->SprachenWaehler->GetString(59).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);

  FreeLibrary (plugin);
 }
}
//---------------------------------------------------------------------------

void __fastcall TPlugins::ToolButton5Click(TObject *Sender)
{
 if (ListView1->Selected)
 {
  bool kill_dll = false;
  int remove_button = Application->MessageBox(Hauptformular->SprachenWaehler->GetStringEx(60, ListView1->Selected->Caption).c_str(), "Scribe!", MB_YESNO + MB_DEFBUTTON2 + MB_ICONQUESTION);

  if (remove_button == IDYES)
  {
   HINSTANCE plugin = LoadLibrary((Hauptformular->program_dir + "Storage!\\Plugins\\" + Hauptformular->TempDateilistBox->Items->Strings[ListView1->Selected->Index]).c_str());
   typedef int (__stdcall *pluginInterfaceVersionType)();
   pluginInterfaceVersionType pluginInterfaceVersiontyp;
   pluginInterfaceVersiontyp = (pluginInterfaceVersionType)GetProcAddress(plugin, "pluginInterfaceVersion");
   int pversion = (pluginInterfaceVersiontyp)();

   if (pversion == 2)
   {
    typedef int (__stdcall *pluginUninstallType)();
    pluginUninstallType pluginUninstalltyp;
    pluginUninstalltyp = (pluginUninstallType)GetProcAddress(plugin, "pluginUninstall");
    int puninstall = (pluginUninstalltyp)();
    if (puninstall == -1)
     Application->MessageBox(Hauptformular->SprachenWaehler->GetString(61).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);
    else
     kill_dll = true;
   }
   else
    kill_dll = true;

   FreeLibrary(plugin);

   if (kill_dll)
   {
    String complete_file = Hauptformular->program_dir + "Storage!\\Plugins\\" + Hauptformular->TempDateilistBox->Items->Strings[ListView1->Selected->Index];
    if (Hauptformular->FileDeleteOnlyOne(complete_file, true))
    {
     Hauptformular->TempDateilistBox->Items->Delete(ListView1->Selected->Index);
     ListView1->Selected->Delete();
     ListView1Click (Sender);
    }
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TPlugins::ListView1Click(TObject *Sender)
{
 ToolButton1->Enabled = ListView1->Selected;
 ToolButton2->Enabled = ListView1->Selected;
 ToolButton3->Enabled = ListView1->Selected;
 ToolButton5->Enabled = ListView1->Selected;
 BitBtn1->Enabled = ListView1->Selected;
}
//---------------------------------------------------------------------------

void __fastcall TPlugins::ToolButton4Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(62);
 filter_temp = filter_temp + " (*.dll)|*.dll";
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OpenDialog1->Filter = filter_gesamt;
 OpenDialog1->Title = ToolButton4->Hint;

 if (OpenDialog1->Execute())
 {
  String file_1 = OpenDialog1->FileName;
  String file_2 = Hauptformular->program_dir + "Storage!\\Plugins\\" + ExtractFileName(OpenDialog1->FileName);
  String PName;
  TListItem *ListItem;

  if (Hauptformular->FileCopyOnlyOne(file_1, file_2))
  {
   ListView1->Items->Clear();
   FormShow(Sender);
   //file_2 = ExtractFileName(file_2);
   //PName = file_2.SubString(0, (AnsiPos(".", file_2)) - 1);
   //ListItem = ListView1->Items->Add();
   //ListItem->Caption = PName;
   //ListItem->ImageIndex = 4;
   //Hauptformular->TempDateilistBox->Items->Add(PName);
   //ListView1Click (Sender);
  }
  else
   Application->MessageBox(Hauptformular->SprachenWaehler->GetString(63).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONERROR);
 }
}
//---------------------------------------------------------------------------

