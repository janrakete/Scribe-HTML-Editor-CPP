//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "download.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDownloadzeit *Downloadzeit;
//---------------------------------------------------------------------------
__fastcall TDownloadzeit::TDownloadzeit(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDownloadzeit::FormShow(TObject *Sender)
{
 Kbps1->Caption = "0 " + Hauptformular->SprachenWaehler->GetString(83);
 Kbps2->Caption = "0 " + Hauptformular->SprachenWaehler->GetString(83);
 Kbps3->Caption = "0 " + Hauptformular->SprachenWaehler->GetString(83);
 abbruch = false;
}
//---------------------------------------------------------------------------

void __fastcall TDownloadzeit::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TDownloadzeit::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_download_time.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TDownloadzeit::BitBtn2Click(TObject *Sender)
{
 abbruch = true;
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TDownloadzeit::BitBtn1Click(TObject *Sender)
{
 abbruch = false;
 Screen->Cursor = crHourGlass;
 BitBtn1->Enabled = false;
 ProgressBar1->Position = 0;

 Links->Items->Clear();
 ListBox1->Clear();
 ListBox2->Clear();
 Doppelt->Clear();

 int total_size = 0;
 int klammer_auf_pos = 0;
 int klammer_zu_pos = 0;
 int edit_start = 0;
 TListItem *ListItem;
 String edit_text_temp;
 String edit_text_temp_2;
 int file_position = 0;
 String temp_str;
 bool comment = false;
 String comment_part;
 String edit_text;
 int edit_length;
 int doppelt = 0;
 int sel_start = 0;
 int links_count = 0;
 String links_temp_edit;

 sel_start = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
 edit_length = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextLen();
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
 edit_text = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->GetTextPart(0, edit_length);

 //Umfang berechnen
 links_count = 0;
 links_temp_edit = edit_text;
 while (AnsiPos(" src=", links_temp_edit))
 {
  links_temp_edit = links_temp_edit.Delete(AnsiPos(" src=", links_temp_edit), 4);
  links_count++;
 }
 ProgressBar1->Max = links_count;
 //----------------

 while (AnsiPos("<", edit_text) && AnsiPos(">", edit_text) && (AnsiPos("<", edit_text) < AnsiPos(">", edit_text)))
 {
  Application->ProcessMessages();
  klammer_auf_pos = AnsiPos("<", edit_text);
  comment_part = edit_text.SubString(klammer_auf_pos, 4);

  if (comment_part == "<!--")
   comment = true;
  else
   comment = false;

  if (comment)
  {
   klammer_zu_pos = AnsiPos ("-->", edit_text);
   klammer_zu_pos += 3;
  }
  else
   klammer_zu_pos = AnsiPos(">", edit_text) + 1;

  edit_text_temp = edit_text.SubString(klammer_auf_pos, klammer_zu_pos - klammer_auf_pos);
  edit_text = edit_text.SubString(klammer_zu_pos, edit_length);
  edit_start = (edit_length - edit_text.Length());

  if (abbruch)
   break;

  if (!AnsiPos("\r\n", edit_text_temp))
  {
   if (!comment)
   {
    edit_text_temp_2 = edit_text_temp;
    edit_text_temp = Hauptformular->TagNormalize(edit_text_temp, true);

    if (AnsiPos("#", edit_text_temp) && (AnsiPos(".", edit_text_temp)))
    {
     int anchor_1 = AnsiPos("#", edit_text_temp);
     String anchor_2;
     anchor_2 = edit_text_temp.SubString(anchor_1, edit_text_temp.Length());
     anchor_1 = AnsiPos("\"", anchor_2);
     anchor_2 = anchor_2.SubString(0, (anchor_1) - 1);
     edit_text_temp = Hauptformular->ReplaceString(edit_text_temp, anchor_2, "", true, false);
    }

    if ((!AnsiPos("://", edit_text_temp)) && (!AnsiPos("mailto:", AnsiLowerCase(edit_text_temp))) && (!AnsiPos("#", AnsiLowerCase(edit_text_temp))) && (!AnsiPos("<frame", AnsiLowerCase(edit_text_temp))) && (!AnsiPos("javascript:", AnsiLowerCase(edit_text_temp))))
    {
     if (Hauptformular->TagAttributeContainsAttribute("src=", edit_text_temp))
     {
      ListBox1->Items->Add(String(edit_start));
      ListBox2->Items->Add(String((klammer_zu_pos - klammer_auf_pos) + 1));
      edit_text_temp = Hauptformular->TagAttributeGetString("src=", edit_text_temp);
      edit_text_temp = Hauptformular->ReplaceString(edit_text_temp, "/", "\\", true, true);
      doppelt = Doppelt->Items->IndexOf(edit_text_temp);

      if (doppelt < 0)
      {
       Doppelt->Items->Add(edit_text_temp);
       try
       {
        if (AnsiPos(":", edit_text_temp))
         FileListBox1->Directory = ExtractFilePath(edit_text_temp);
        else
         FileListBox1->Directory = ExtractFilePath(ExtractFilePath(Hauptformular->ActiveMDIChild->Caption) + edit_text_temp);

        file_position = FileListBox1->Items->IndexOf(ExtractFileName(edit_text_temp));
        if (file_position > -1)
        {
         temp_str = FileListBox1->Items->Strings[file_position];
         temp_str = FileListBox1->Directory + "\\" + temp_str;
         if  (AnsiPos(temp_str, ExpandFileName(ExtractFileName(edit_text_temp))))
         {
          ListItem = Links->Items->Add();
          ListItem->ImageIndex = 112;
          ListItem->SubItems->Add(String(int(Hauptformular->FileGetSize(temp_str) / 1024)) + " KB");
          total_size += Hauptformular->FileGetSize(temp_str);
          ListItem->Caption = edit_text_temp;
         }
         else
         {
          ListItem = Links->Items->Add();
          ListItem->ImageIndex = 112;
          ListItem->SubItems->Add(String(int(Hauptformular->FileGetSize(temp_str) / 1024)) + " KB");
          total_size += Hauptformular->FileGetSize(temp_str);
          ListItem->Caption = edit_text_temp;
         }
        }
        else
        {
         ListItem = Links->Items->Add();
         ListItem->ImageIndex = 113;
         ListItem->Caption = edit_text_temp;
        }
       }
       catch (...)
       {
        FileListBox1->Directory = "";
        ListItem = Links->Items->Add();
        ListItem->ImageIndex = 113;
        ListItem->Caption = edit_text_temp;
       }
      }
      else
      {
       ListItem = Links->Items->Add();
       ListItem->ImageIndex = 112;
       ListItem->Caption = edit_text_temp;
      }
     }
    }
   }
  }
  Links->Update();
  ProgressBar1->StepBy(1);
 }

 ProgressBar1->Position = ProgressBar1->Max;
 BitBtn1->Enabled = true;
 Screen->Cursor = crDefault;

 DocumentSize->Caption = String(Hauptformular->FileGetSize(Hauptformular->ActiveMDIChild->Caption) / 1024) + " KB";
 LinkedFiles->Caption = String(total_size / 1024) + " KB";
 total_size = total_size + Hauptformular->FileGetSize(Hauptformular->ActiveMDIChild->Caption);
 Total->Caption = String(total_size / 1024) + " KB";

 Kbps1->Caption = String((total_size / 1800)) + " " + Hauptformular->SprachenWaehler->GetString(83);
 Kbps2->Caption = String((total_size / 4200)) + " " + Hauptformular->SprachenWaehler->GetString(83);
 Kbps3->Caption = String((total_size / 8050)) + " " + Hauptformular->SprachenWaehler->GetString(83);

 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = sel_start;
}
//---------------------------------------------------------------------------

void __fastcall TDownloadzeit::LinksClick(TObject *Sender)
{
 if (Links->Selected)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = (ListBox1->Items->Strings[Links->Selected->Index]).ToInt() + ((ListBox2->Items->Strings[Links->Selected->Index]).ToInt() * (-1)) + 1;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = (((ListBox2->Items->Strings[Links->Selected->Index]).ToInt())) - 1;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
 }
}
//---------------------------------------------------------------------------

