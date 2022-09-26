/*Alter Code - funzt!
 abbruch = false;
 Screen->Cursor = crHourGlass;
 BitBtn1->Enabled = false;
 ProgressBar1->Position = 0;

 ListView1->Items->Clear();
 ListBox1->Clear();
 ListBox2->Clear();
 ListBox3->Clear();
 Verzeichnisse->Clear();

 String edit_text;
 int edit_length;
 int sel_start = 0;
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

 TabSheet2->TabVisible = true;
 PageControl1->ActivePage = TabSheet2;

 if (ComboBox4->ItemIndex == 0)
 {
  ProgressBar1->Max = Hauptformular->MDIChildCount;
  String dateiname;
  int mdis_count = Hauptformular->MDIChildCount;

  for (int i = 0; i < mdis_count; i++)
  {
   Hauptformular->TempMemo->Lines->Clear();
   Hauptformular->MDIChildren[i]->BringToFront();
   dateiname = Hauptformular->ActiveMDIChild->Caption;
   Hauptformular->TempMemo->Lines = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines;
   Hauptformular->TempMemo->SelStart = 0;

   sel_start = Hauptformular->TempMemo->SelStart;
   edit_length = Hauptformular->TempMemo->GetTextLen();
   Hauptformular->TempMemo->SelStart = 0;
   edit_text = Hauptformular->TempMemo->GetTextPart(0, edit_length);

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
       for (int x = 0; x < Attributes->Items->Count; x++)
       {
        if (Hauptformular->TagAttributeContainsAttribute(Attributes->Items->Strings[x], edit_text_temp))
        {
         ListBox1->Items->Add(dateiname);
         ListBox2->Items->Add(String(edit_start));
         ListBox3->Items->Add(String((klammer_zu_pos - klammer_auf_pos) + 1));
         edit_text_temp = Hauptformular->TagAttributeGetString(Attributes->Items->Strings[x], edit_text_temp);
         edit_text_temp = Hauptformular->ReplaceString(edit_text_temp, "/", "\\", true, true);

         try
         {
          if (AnsiPos(":", edit_text_temp))
           FileListBox1->Directory = ExtractFilePath(edit_text_temp);
          else
           FileListBox1->Directory = ExtractFilePath(ExtractFilePath(dateiname) + edit_text_temp);

          file_position = FileListBox1->Items->IndexOf(ExtractFileName(edit_text_temp));
          if (file_position > -1)
          {
           temp_str = FileListBox1->Items->Strings[file_position];
           temp_str = FileListBox1->Directory + "\\" + temp_str;
           if (AnsiPos(temp_str, ExpandFileName(ExtractFileName(edit_text_temp))))
           {
            ListItem = ListView1->Items->Add();
            if (ExpandFileName(temp_str) == ExpandFileName(ExtractFileName(edit_text_temp)))
             ListItem->ImageIndex = 112;
            else
             ListItem->ImageIndex = 132;
            ListItem->Caption = ExtractFileName(dateiname);
            ListItem->SubItems->Add(edit_text_temp);
           }
           else
           {
            ListItem = ListView1->Items->Add();
            if (ExpandFileName(temp_str) == ExpandFileName(ExtractFileName(edit_text_temp)))
             ListItem->ImageIndex = 112;
            else
             ListItem->ImageIndex = 132;
            ListItem->Caption = ExtractFileName(dateiname);
            ListItem->SubItems->Add(edit_text_temp);
           }
          }
          else
          {
           ListItem = ListView1->Items->Add();
           ListItem->ImageIndex = 113;
           ListItem->Caption = ExtractFileName(dateiname);
           ListItem->SubItems->Add(edit_text_temp);
          }
         }
         catch (...)
         {
          FileListBox1->Directory = "";
          ListItem = ListView1->Items->Add();
          ListItem->ImageIndex = 113;
          ListItem->Caption = ExtractFileName(dateiname);
          ListItem->SubItems->Add(edit_text_temp);
         }
        }
       }
      }
     }
    }
   }
   ListView1->Update();
   ProgressBar1->StepBy(1);
  }
 }
 else
 {
  if ((ComboBox4->ItemIndex == 2) || ((ComboBox4->ItemIndex == 1) && (CheckBox5->Checked)))
  {
   if (ComboBox4->ItemIndex == 1)
    Hauptformular->DirectoryFindSubs(Hauptformular->fileexplorer_dir, Verzeichnisse);
   else
    Hauptformular->DirectoryFindSubs(Hauptformular->project_dir + Hauptformular->ProjekteAuswahl->Items->Strings[Hauptformular->ProjekteAuswahl->ItemIndex] + "\\",Verzeichnisse);
  }
  else
   Verzeichnisse->Items->Add(Hauptformular->fileexplorer_dir);

  int items_count = Verzeichnisse->Items->Count;
  int items_count_2;
  String dateiname;
  ProgressBar1->Max = 500;

  for (int i = 0; i < items_count; i++)
  {
   Dateien->Mask = Edit2->Text;
   Dateien->Directory = Verzeichnisse->Items->Strings[i];
   items_count_2 = Dateien->Items->Count;

   for (int a = 0; a < items_count_2; a++)
   {
    dateiname = Dateien->Items->Strings[a];
    dateiname = Dateien->Directory + "\\" + dateiname;
    Hauptformular->TempMemo->Lines->LoadFromFile(dateiname);

    sel_start = Hauptformular->TempMemo->SelStart;
    edit_length = Hauptformular->TempMemo->GetTextLen();
    Hauptformular->TempMemo->SelStart = 0;
    edit_text = Hauptformular->TempMemo->GetTextPart(0, edit_length);

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
        for (int x = 0; x < Attributes->Items->Count; x++)
        {
         if (Hauptformular->TagAttributeContainsAttribute(Attributes->Items->Strings[x], edit_text_temp))
         {
          ListBox1->Items->Add(dateiname);
          ListBox2->Items->Add(String(edit_start));
          ListBox3->Items->Add(String((klammer_zu_pos - klammer_auf_pos) + 1));
          edit_text_temp = Hauptformular->TagAttributeGetString(Attributes->Items->Strings[x], edit_text_temp);
          edit_text_temp = Hauptformular->ReplaceString(edit_text_temp, "/", "\\", true, true);

          try
          {
           if (AnsiPos(":", edit_text_temp))
            FileListBox1->Directory = ExtractFilePath(edit_text_temp);
           else
            FileListBox1->Directory = ExtractFilePath(ExtractFilePath(dateiname) + edit_text_temp);

           file_position = FileListBox1->Items->IndexOf(ExtractFileName(edit_text_temp));
           if (file_position > -1)
           {
            temp_str = FileListBox1->Items->Strings[file_position];
            temp_str = FileListBox1->Directory + "\\" + temp_str;
            if (AnsiPos(temp_str, ExpandFileName(ExtractFileName(edit_text_temp))))
            {
             ListItem = ListView1->Items->Add();
             if (ExpandFileName(temp_str) == ExpandFileName(ExtractFileName(edit_text_temp)))
              ListItem->ImageIndex = 112;
             else
              ListItem->ImageIndex = 132;
             ListItem->Caption = ExtractFileName(dateiname);
             ListItem->SubItems->Add(edit_text_temp);
            }
            else
            {
             ListItem = ListView1->Items->Add();
             if (ExpandFileName(temp_str) == ExpandFileName(ExtractFileName(edit_text_temp)))
              ListItem->ImageIndex = 112;
             else
              ListItem->ImageIndex = 132;
             ListItem->Caption = ExtractFileName(dateiname);
             ListItem->SubItems->Add(edit_text_temp);
            }
           }
           else
           {
            ListItem = ListView1->Items->Add();
            ListItem->ImageIndex = 113;
            ListItem->Caption = ExtractFileName(dateiname);
            ListItem->SubItems->Add(edit_text_temp);
           }
          }
          catch (...)
          {
           FileListBox1->Directory = "";
           ListItem = ListView1->Items->Add();
           ListItem->ImageIndex = 113;
           ListItem->Caption = ExtractFileName(dateiname);
           ListItem->SubItems->Add(edit_text_temp);
          }
         }
        }
       }
      }
     }
    }
    ProgressBar1->StepBy(1);
   }
  }
 }

 ProgressBar1->Position = ProgressBar1->Max;
 BitBtn1->Enabled = true;
 Screen->Cursor = crDefault;
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "lcheck.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "HTTPGet"
#pragma resource "*.dfm"
TLinkUeberpruefung *LinkUeberpruefung;
//---------------------------------------------------------------------------
__fastcall TLinkUeberpruefung::TLinkUeberpruefung(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLinkUeberpruefung::FormShow(TObject *Sender)
{
 ComboBox4->ItemIndex = 0;
 Edit2->Enabled = false;
 CheckBox5->Enabled = false;

 if (Trim(Edit2->Text) == "")
 {
  String filter_part = "";
  filter_part = "*." + Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all;
  filter_part = filter_part.SubString(0, filter_part.Length() - 1);
  Edit2->Text = Hauptformular->ReplaceString(filter_part, ";", ";*.", true, true);
 }

 ProgressBar1->Position = 0;
 ListView1->Items->Clear();
 ListBox1->Clear();
 ListBox2->Clear();
 Verzeichnisse->Clear();

 TabSheet2->TabVisible = false;
 PageControl1->ActivePage = TabSheet1;
}
//---------------------------------------------------------------------------

void __fastcall TLinkUeberpruefung::BitBtn2Click(TObject *Sender)
{
 abbruch = true;
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TLinkUeberpruefung::ComboBox4Change(TObject *Sender)
{
 if (ComboBox4->ItemIndex == 1)
 {
  Edit2->Enabled = true;
  CheckBox5->Enabled = true;
 }
 else if (ComboBox4->ItemIndex == 2)
 {
  Edit2->Enabled = true;
  CheckBox5->Enabled = false;
 }
 else
 {
  Edit2->Enabled = false;
  CheckBox5->Enabled = false;
 }

 if (ComboBox4->ItemIndex == 2 && Hauptformular->ProjekteAuswahl->ItemIndex == 0)
 {
  Application->MessageBox(Hauptformular->SprachenWaehler->GetString(17).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONWARNING);
  ComboBox4->ItemIndex = 0;
 }
}
//---------------------------------------------------------------------------

void __fastcall TLinkUeberpruefung::PageControl1Change(TObject *Sender)
{
 if (TabSheet2->TabVisible)
  TabSheet2->TabVisible = false;        
}
//---------------------------------------------------------------------------

void __fastcall TLinkUeberpruefung::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_link_check.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TLinkUeberpruefung::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TLinkUeberpruefung::BitBtn1Click(TObject *Sender)
{
 TForm *aktuelles_mdi;
 aktuelles_mdi = Hauptformular->ActiveMDIChild;

 http_success = false;
 abbruch = false;
 Screen->Cursor = crHourGlass;
 BitBtn1->Enabled = false;
 ProgressBar1->Position = 0;

 ListView1->Items->Clear();
 ListBox1->Clear();
 ListBox2->Clear();
 ListBox3->Clear();
 Verzeichnisse->Clear();

 String edit_text;
 int edit_length;
 int sel_start = 0;
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

 TabSheet2->TabVisible = true;
 PageControl1->ActivePage = TabSheet2;

 if (ComboBox4->ItemIndex == 0)
 {
  ProgressBar1->Max = Hauptformular->MDIChildCount;
  String dateiname;
  int mdis_count = Hauptformular->MDIChildCount;

  for (int i = 0; i < mdis_count; i++)
  {
   Hauptformular->TempMemo->Lines->Clear();
   Hauptformular->MDIChildren[i]->BringToFront();
   dateiname = Hauptformular->ActiveMDIChild->Caption;
   Hauptformular->TempMemo->Lines = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines;
   Hauptformular->TempMemo->SelStart = 0;

   sel_start = Hauptformular->TempMemo->SelStart;
   edit_length = Hauptformular->TempMemo->GetTextLen();
   Hauptformular->TempMemo->SelStart = 0;
   edit_text = Hauptformular->TempMemo->GetTextPart(0, edit_length);

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

      if ((!AnsiPos("ftp://", edit_text_temp)) && (!AnsiPos("news://", edit_text_temp)) && (!AnsiPos("gopher://", edit_text_temp)) && (!AnsiPos("news://", edit_text_temp)) && (!AnsiPos("mailto:", AnsiLowerCase(edit_text_temp))) && (!AnsiPos("#", AnsiLowerCase(edit_text_temp))) && (!AnsiPos("<frame", AnsiLowerCase(edit_text_temp))) && (!AnsiPos("javascript:", AnsiLowerCase(edit_text_temp))))
      {
       for (int x = 0; x < Attributes->Items->Count; x++)
       {
        if (Hauptformular->TagAttributeContainsAttribute(Attributes->Items->Strings[x], edit_text_temp))
        {
         ListBox1->Items->Add(dateiname);
         ListBox2->Items->Add(String(edit_start));
         ListBox3->Items->Add(String((klammer_zu_pos - klammer_auf_pos) + 1));
         edit_text_temp = Hauptformular->TagAttributeGetString(Attributes->Items->Strings[x], edit_text_temp);

         if ((AnsiPos("http://", AnsiLowerCase(edit_text_temp))) && CheckBox1->Checked)
         {
          HTTPGet->FileName = Hauptformular->program_dir + "~temp.html";
          HTTPGet->URL = edit_text_temp;
          HTTPGet->GetFile();
          if (http_success)
          {
           ListItem = ListView1->Items->Add();
           ListItem->ImageIndex = 112;
           ListItem->Caption = ExtractFileName(dateiname);
           ListItem->SubItems->Add(edit_text_temp);
          }
          else
          {
           ListItem = ListView1->Items->Add();
           ListItem->ImageIndex = 113;
           ListItem->Caption = ExtractFileName(dateiname);
           ListItem->SubItems->Add(edit_text_temp);
          }
          http_success = false;
         }
         else if (AnsiPos("http://", AnsiLowerCase(edit_text_temp)))
          1 == 1;
         else
         {
          edit_text_temp = Hauptformular->ReplaceString(edit_text_temp, "/", "\\", true, true);
          try
          {
           if (AnsiPos(":", edit_text_temp))
            FileListBox1->Directory = ExtractFilePath(edit_text_temp);
           else
            FileListBox1->Directory = ExtractFilePath(ExtractFilePath(dateiname) + edit_text_temp);

           file_position = FileListBox1->Items->IndexOf(ExtractFileName(edit_text_temp));
           if (file_position > -1)
           {
            temp_str = FileListBox1->Items->Strings[file_position];
            temp_str = FileListBox1->Directory + "\\" + temp_str;
            if (AnsiPos(temp_str, ExpandFileName(ExtractFileName(edit_text_temp))))
            {
             ListItem = ListView1->Items->Add();
             if (ExpandFileName(temp_str) == ExpandFileName(ExtractFileName(edit_text_temp)))
              ListItem->ImageIndex = 112;
             else
              ListItem->ImageIndex = 132;
             ListItem->Caption = ExtractFileName(dateiname);
             ListItem->SubItems->Add(edit_text_temp);
            }
            else
            {
             ListItem = ListView1->Items->Add();
             if (ExpandFileName(temp_str) == ExpandFileName(ExtractFileName(edit_text_temp)))
              ListItem->ImageIndex = 112;
             else
              ListItem->ImageIndex = 132;
             ListItem->Caption = ExtractFileName(dateiname);
             ListItem->SubItems->Add(edit_text_temp);
            }
           }
           else
           {
            ListItem = ListView1->Items->Add();
            ListItem->ImageIndex = 113;
            ListItem->Caption = ExtractFileName(dateiname);
            ListItem->SubItems->Add(edit_text_temp);
           }
          }
          catch (...)
          {
           FileListBox1->Directory = "";
           ListItem = ListView1->Items->Add();
           ListItem->ImageIndex = 113;
           ListItem->Caption = ExtractFileName(dateiname);
           ListItem->SubItems->Add(edit_text_temp);
          }
         }
        }
       }
      }
     }
    }
   }
   ListView1->Update();
   ProgressBar1->StepBy(1);
  }
 }
 else
 {
  if ((ComboBox4->ItemIndex == 2) || ((ComboBox4->ItemIndex == 1) && (CheckBox5->Checked)))
  {
   if (ComboBox4->ItemIndex == 1)
    Hauptformular->DirectoryFindSubs(Hauptformular->fileexplorer_dir, Verzeichnisse);
   else
    Hauptformular->DirectoryFindSubs(Hauptformular->project_dir + Hauptformular->ProjekteAuswahl->Items->Strings[Hauptformular->ProjekteAuswahl->ItemIndex] + "\\",Verzeichnisse);
  }
  else
   Verzeichnisse->Items->Add(Hauptformular->fileexplorer_dir);

  int items_count = Verzeichnisse->Items->Count;
  int items_count_2;
  String dateiname;
  ProgressBar1->Max = 500;

  for (int i = 0; i < items_count; i++)
  {
   Dateien->Mask = Edit2->Text;
   Dateien->Directory = Verzeichnisse->Items->Strings[i];
   items_count_2 = Dateien->Items->Count;

   for (int a = 0; a < items_count_2; a++)
   {
    dateiname = Dateien->Items->Strings[a];
    dateiname = Dateien->Directory + "\\" + dateiname;
    Hauptformular->TempMemo->Lines->LoadFromFile(dateiname);

    sel_start = Hauptformular->TempMemo->SelStart;
    edit_length = Hauptformular->TempMemo->GetTextLen();
    Hauptformular->TempMemo->SelStart = 0;
    edit_text = Hauptformular->TempMemo->GetTextPart(0, edit_length);

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

       if ((!AnsiPos("ftp://", edit_text_temp)) && (!AnsiPos("news://", edit_text_temp)) && (!AnsiPos("gopher://", edit_text_temp)) && (!AnsiPos("news://", edit_text_temp)) && (!AnsiPos("mailto:", AnsiLowerCase(edit_text_temp))) && (!AnsiPos("#", AnsiLowerCase(edit_text_temp))) && (!AnsiPos("<frame", AnsiLowerCase(edit_text_temp))) && (!AnsiPos("javascript:", AnsiLowerCase(edit_text_temp))))
       {
        for (int x = 0; x < Attributes->Items->Count; x++)
        {
         if (Hauptformular->TagAttributeContainsAttribute(Attributes->Items->Strings[x], edit_text_temp))
         {
          ListBox1->Items->Add(dateiname);
          ListBox2->Items->Add(String(edit_start));
          ListBox3->Items->Add(String((klammer_zu_pos - klammer_auf_pos) + 1));
          edit_text_temp = Hauptformular->TagAttributeGetString(Attributes->Items->Strings[x], edit_text_temp);

          if ((AnsiPos("http://", AnsiLowerCase(edit_text_temp))) && CheckBox1->Checked)
          {
           HTTPGet->FileName = Hauptformular->program_dir + "~temp.html";
           HTTPGet->URL = edit_text_temp;
           HTTPGet->GetFile();
           if (http_success)
           {
            ListItem = ListView1->Items->Add();
            ListItem->ImageIndex = 112;
            ListItem->Caption = ExtractFileName(dateiname);
            ListItem->SubItems->Add(edit_text_temp);
           }
           else
           {
            ListItem = ListView1->Items->Add();
            ListItem->ImageIndex = 113;
            ListItem->Caption = ExtractFileName(dateiname);
            ListItem->SubItems->Add(edit_text_temp);
           }
           http_success = false;
          }
          else if (AnsiPos("http://", AnsiLowerCase(edit_text_temp)))
           1 == 1;
          else
          {
           edit_text_temp = Hauptformular->ReplaceString(edit_text_temp, "/", "\\", true, true);
           try
           {
            if (AnsiPos(":", edit_text_temp))
             FileListBox1->Directory = ExtractFilePath(edit_text_temp);
            else
             FileListBox1->Directory = ExtractFilePath(ExtractFilePath(dateiname) + edit_text_temp);

            file_position = FileListBox1->Items->IndexOf(ExtractFileName(edit_text_temp));
            if (file_position > -1)
            {
             temp_str = FileListBox1->Items->Strings[file_position];
             temp_str = FileListBox1->Directory + "\\" + temp_str;
             if (AnsiPos(temp_str, ExpandFileName(ExtractFileName(edit_text_temp))))
             {
              ListItem = ListView1->Items->Add();
              if (ExpandFileName(temp_str) == ExpandFileName(ExtractFileName(edit_text_temp)))
               ListItem->ImageIndex = 112;
              else
               ListItem->ImageIndex = 132;
              ListItem->Caption = ExtractFileName(dateiname);
              ListItem->SubItems->Add(edit_text_temp);
             }
             else
             {
              ListItem = ListView1->Items->Add();
              if (ExpandFileName(temp_str) == ExpandFileName(ExtractFileName(edit_text_temp)))
               ListItem->ImageIndex = 112;
              else
               ListItem->ImageIndex = 132;
              ListItem->Caption = ExtractFileName(dateiname);
              ListItem->SubItems->Add(edit_text_temp);
             }
            }
            else
            {
             ListItem = ListView1->Items->Add();
             ListItem->ImageIndex = 113;
             ListItem->Caption = ExtractFileName(dateiname);
             ListItem->SubItems->Add(edit_text_temp);
            }
           }
           catch (...)
           {
            FileListBox1->Directory = "";
            ListItem = ListView1->Items->Add();
            ListItem->ImageIndex = 113;
            ListItem->Caption = ExtractFileName(dateiname);
            ListItem->SubItems->Add(edit_text_temp);
           }
          }
         }
        }
       }
      }
     }
    }
    ProgressBar1->StepBy(1);
   }
  }
 }

 ProgressBar1->Position = ProgressBar1->Max;
 BitBtn1->Enabled = true;
 Screen->Cursor = crDefault;

 aktuelles_mdi->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TLinkUeberpruefung::CheckBox1Click(TObject *Sender)
{
 if (CheckBox1->Checked)
 {
  if (!Hauptformular->DirectFTPCheckConnection())
  {
   Application->MessageBox(Hauptformular->SprachenWaehler->GetString(36).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONEXCLAMATION);
   CheckBox1->Checked = false;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TLinkUeberpruefung::ListView1DblClick(TObject *Sender)
{
 if (ListView1->Selected)
 {
  String gewdatei = ListBox1->Items->Strings[ListView1->Selected->Index];
  Hauptformular->CreateChildForm("", gewdatei, "");
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = (ListBox2->Items->Strings[ListView1->Selected->Index]).ToInt() + ((ListBox3->Items->Strings[ListView1->Selected->Index]).ToInt() * (-1)) + 1;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = (((ListBox3->Items->Strings[ListView1->Selected->Index]).ToInt())) - 1;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ScrollInView();
 }
}
//---------------------------------------------------------------------------

void __fastcall TLinkUeberpruefung::HTTPGetProgress(TObject *Sender,
      int TotalSize, int Readed)
{
 http_success = true;            
}
//---------------------------------------------------------------------------

void __fastcall TLinkUeberpruefung::HTTPGetError(TObject *Sender)
{
 http_success = false;        
}
//---------------------------------------------------------------------------

