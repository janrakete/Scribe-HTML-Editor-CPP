//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "thumbs.h"
#include "main.h"
#include "hilfed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Bffolder"
#pragma link "EnJpgGr"
#pragma link "EnTransf"
#pragma resource "*.dfm"
TThumbnailGenerator *ThumbnailGenerator;
//---------------------------------------------------------------------------
__fastcall TThumbnailGenerator::TThumbnailGenerator(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TThumbnailGenerator::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_thumb_generator.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;        
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::BitBtn2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::TrackBar1Change(TObject *Sender)
{
  Label13->Caption = TrackBar1->Position;        
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::SpeedButton1Click(TObject *Sender)
{
 Bffolder1->Caption = Hauptformular->SprachenWaehler->GetString(69);
 Bffolder1->Title = Hauptformular->SprachenWaehler->GetString(70);
 Bffolder1->SelectedDir = Edit1->Text;
 if (Bffolder1->Execute())
 {
  Edit1->Text = Bffolder1->SelectedDir + "\\";

  Grafiken->Items->Clear();
  TListItem *ListItem;
  Hauptformular->TempDateilistBox->Directory = Edit1->Text;
  Hauptformular->TempDateilistBox->Mask = "*.jpg;*.jpeg;*.png";
  Hauptformular->TempDateilistBox->Update();

  for (int i = 0; i < Hauptformular->TempDateilistBox->Items->Count; i++)
  {
   ListItem = Grafiken->Items->Add();
   ListItem->Caption = Hauptformular->TempDateilistBox->Items->Strings[i];
   ListItem->ImageIndex = 56;
  }
  if (Grafiken->Items->Count)
   BitBtn1->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::SpeedButton2Click(TObject *Sender)
{
 Bffolder2->Caption = Hauptformular->SprachenWaehler->GetString(69);
 Bffolder2->Title = Hauptformular->SprachenWaehler->GetString(70);
 Bffolder2->SelectedDir = Edit2->Text;
 if (Bffolder2->Execute())
  Edit2->Text = Bffolder2->SelectedDir + "\\";
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::SpeedButton3Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(5);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->docfile_extensions + Hauptformular->addlang_extensions_all);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;
 OeffnenDialog->InitialDir = Hauptformular->project_dir;
 OeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OeffnenDialog->Execute())
  Edit3->Text = OeffnenDialog->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::FormShow(TObject *Sender)
{
 if (Hauptformular->VerwControl->ActivePage == Hauptformular->VerwTab1)
  Edit1->Text = Hauptformular->fileexplorer_dir;
 else
  Edit1->Text = Hauptformular->projectexplorer_dir;
 Edit2->Text = Edit1->Text;

 ComboBox2->ItemIndex = 0;
 ComboBox3->ItemIndex = 0;
 ComboBox1->ItemIndex = 3;

 Hauptformular->TempDateilistBox->Directory = Hauptformular->program_dir + "Storage!\\Templates";
 Hauptformular->TempDateilistBox->Mask = "*.sct";
 Hauptformular->TempDateilistBox->Update();
 for (int i = 0; i < Hauptformular->TempDateilistBox->Items->Count; i++)
  ComboBox4->Items->Add(Hauptformular->ReplaceString(Hauptformular->TempDateilistBox->Items->Strings[i], ".sct", "", false, true));
 ComboBox5->Items = ComboBox4->Items;
 if (ComboBox4->Items->IndexOf("Standard") > -1)
  ComboBox4->ItemIndex = ComboBox4->Items->IndexOf("Standard");
 ComboBox5->ItemIndex = ComboBox4->ItemIndex;

 Edit8->Text = Hauptformular->documents_name + "#" + Hauptformular->documents_extension;

 TListItem *ListItem;
 Hauptformular->TempDateilistBox->Directory = Edit1->Text;
 Hauptformular->TempDateilistBox->Mask = "*.jpg;*.jpeg;*.png";
 Hauptformular->TempDateilistBox->Update();

 for (int i = 0; i < Hauptformular->TempDateilistBox->Items->Count; i++)
 {
  ListItem = Grafiken->Items->Add();
  ListItem->Caption = Hauptformular->TempDateilistBox->Items->Strings[i];
  ListItem->ImageIndex = 56;
 }
 if (Grafiken->Items->Count)
  BitBtn1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::Bffolder1SelectionChanged(
      TObject *Sender, AnsiString NewSel)
{
 Bffolder1->StatusText = NewSel;        
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::Bffolder2SelectionChanged(
      TObject *Sender, AnsiString NewSel)
{
 Bffolder2->StatusText = NewSel;
}
//---------------------------------------------------------------------------


void __fastcall TThumbnailGenerator::PopupMenu1Popup(TObject *Sender)
{
 if (Grafiken->Selected)
  Entfernen1->Enabled = true;
 else
  Entfernen1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::Entfernen1Click(TObject *Sender)
{
 Grafiken->Selected->Delete();
 if (Grafiken->Items->Count == 0)
  BitBtn1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TThumbnailGenerator::BitBtn1Click(TObject *Sender)
{
 Screen->Cursor = crHourGlass;
 BitBtn1->Enabled = false;

 TJpegGraphic* Grafik = new TJpegGraphic;
 TResizeTransform* Resizer = new TResizeTransform;

 int bilder_anzahl = Grafiken->Items->Count;
 int seiten = bilder_anzahl / (UpDown3->Position * UpDown1->Position);
 int bild_index = 0;

 String home_seite = Edit3->Text;
 String quell_pfad = Edit1->Text;
 String ziel_pfad = Edit2->Text;
 String beschriftungen;
 String zeilenumbruch;
 String dateiname_speichern;
 String temp_tag;
 String temp_tag_2;
 String temp_tag_3;
 String temp_tag_4;
 String gesamt_tag;
 String akt_ordner;

 float alte_hoehe = 0;
 float alte_breite = 0;
 float neue_hoehe = 0;
 float neue_breite = 0;

 ProgressBar1->Position = 0;
 ProgressBar1->Max = bilder_anzahl;

 if (Trim(home_seite) != "")
 {
  Hauptformular->FileCopyOnlyOne(home_seite, ziel_pfad + ExtractFileName(home_seite));
  home_seite = "&nbsp;|&nbsp;<a href=\"" + ExtractFileName(home_seite) + "\">Home" + "</a>&nbsp;|&nbsp;";
 }
 else
  home_seite = "&nbsp;|&nbsp;";

 if (Hauptformular->editor_xhtml_mode)
  zeilenumbruch = "<br />";
 else
  zeilenumbruch = "<br>";

 if (seiten * (UpDown3->Position * UpDown1->Position) != bilder_anzahl)
  seiten++;

 for (int akt_seite = 0; akt_seite < seiten; akt_seite++)
 {
  akt_ordner = Edit8->Text;
  akt_ordner = Hauptformular->ReplaceString(Edit8->Text, "#", String(akt_seite + 1), false, false);
  akt_ordner = Hauptformular->ReplaceString(akt_ordner, ExtractFileExt(akt_ordner), "", true, true);
  CreateDir(ziel_pfad + akt_ordner);
  gesamt_tag = "<table align=\"center\" border=\"0\" cellpadding=\"2\">\r\n\r\n";
  temp_tag = "";
  Hauptformular->TempMemo->Lines->Clear();
  dateiname_speichern = Hauptformular->ReplaceString(Edit8->Text, "#", String(akt_seite + 1), false, false);
  dateiname_speichern = ziel_pfad + dateiname_speichern;
  Hauptformular->TempMemo->Lines->LoadFromFile(Hauptformular->program_dir + "Storage!\\Templates\\" + ComboBox4->Items->Strings[ComboBox4->ItemIndex] + ".sct");
  if (Hauptformular->TempMemo->FindTxt("#Cursor", true, true, false, false));
  else
  {
   Hauptformular->TempMemo->FindTxt("<body", true, false, false, false);
   Hauptformular->TempMemo->SelLine = Hauptformular->TempMemo->SelLine + 1;
  }

  for (int a = 0; a < UpDown3->Position; a++)
  {
   if (bild_index < bilder_anzahl)
   {
    temp_tag = temp_tag + " <tr>\r\n";

    for (int b = 0; b < UpDown1->Position; b++)
    {
     if (bild_index < Grafiken->Items->Count)
     {
      temp_tag = temp_tag + "  <td><a href=\"" + akt_ordner + "/";
      Hauptformular->FileCopyOnlyOne(quell_pfad + Grafiken->Items->Item[bild_index]->Caption, ziel_pfad + akt_ordner + "\\" + Grafiken->Items->Item[bild_index]->Caption);
      temp_tag = temp_tag + Hauptformular->ReplaceString(Grafiken->Items->Item[bild_index]->Caption, ExtractFileExt(Grafiken->Items->Item[bild_index]->Caption), Hauptformular->documents_extension, true, true) + "\">";
      Grafik->LoadFromFile(quell_pfad + Grafiken->Items->Item[bild_index]->Caption);
      Image1->Picture->Graphic = Grafik;
      Grafik->SaveQuality = TrackBar1->Position;
      Grafik->SaveProgressive = true;

      alte_hoehe = Image1->Height;
      alte_breite = Image1->Width;

      if (ComboBox2->ItemIndex == 0)
      {
       neue_hoehe = UpDown2->Position * alte_hoehe;
       neue_hoehe = neue_hoehe / 100;
      }
      else
       neue_hoehe = UpDown2->Position;

      if (ComboBox3->ItemIndex == 0)
      {
       neue_breite = UpDown4->Position * alte_breite;
       neue_breite = neue_breite / 100;
      }
      else
       neue_breite = UpDown4->Position;

      Resizer->Interpolated = true;
      Resizer->Width = neue_breite;
      Resizer->Height = neue_hoehe;

      if (ComboBox1->ItemIndex == 0)
       Resizer->Filter = ifTriangle;
      else if (ComboBox1->ItemIndex == 1)
       Resizer->Filter = ifHermite;
      else if (ComboBox1->ItemIndex == 2)
       Resizer->Filter = ifBell;
      else if (ComboBox1->ItemIndex == 3)
       Resizer->Filter = ifBSpline;
      else if (ComboBox1->ItemIndex == 4)
       Resizer->Filter = ifLanczos3;
      else if (ComboBox1->ItemIndex == 5)
       Resizer->Filter = ifMitchell;
      Resizer->Apply(Grafik);

      temp_tag = temp_tag + "<img src=\"" + akt_ordner + "/";
      temp_tag_2 = Grafiken->Items->Item[bild_index]->Caption;
      temp_tag_3 = ExtractFileExt(temp_tag_2);
      temp_tag_2 = Hauptformular->ReplaceString(temp_tag_2, temp_tag_3, "", false, false);
      temp_tag_2 = temp_tag_2 + "_";
      temp_tag_2 = temp_tag_2 + temp_tag_3;
      Grafik->SaveToFile(ziel_pfad + akt_ordner + "\\" + temp_tag_2);
      temp_tag = temp_tag + temp_tag_2 + "\"";
      temp_tag = temp_tag + " alt=\"" + temp_tag_2 + "\" height=\"" + String(neue_hoehe) + "\" width=\"" + String(neue_breite);
      if (Hauptformular->editor_xhtml_mode)
       temp_tag = temp_tag + "\" border=\"0\" /></a>";
      else
       temp_tag = temp_tag + "\" border=\"0\"></a>";

      Hauptformular->TempMemo2->Lines->Clear();
      Hauptformular->TempMemo2->Lines->LoadFromFile(Hauptformular->program_dir + "Storage!\\Templates\\" + ComboBox5->Items->Strings[ComboBox5->ItemIndex] + ".sct");
      if (Hauptformular->TempMemo2->FindTxt("#Cursor", true, true, false, false));
      else
      {
       Hauptformular->TempMemo2->FindTxt("<body", true, false, false, false);
       Hauptformular->TempMemo2->SelLine = Hauptformular->TempMemo2->SelLine + 1;
      }
      temp_tag_4 = "<img src=\"" + Grafiken->Items->Item[bild_index]->Caption + "\"";
      temp_tag_4 = temp_tag_4 + " alt=\"" + Grafiken->Items->Item[bild_index]->Caption + "\" height=\"" + String(alte_hoehe) + "\" width=\"" + String(alte_breite);
      if (Hauptformular->editor_xhtml_mode)
       temp_tag_4 = temp_tag_4 + "\" border=\"0\" />";
      else
       temp_tag_4 = temp_tag_4 + "\" border=\"0\">" + zeilenumbruch;
      temp_tag_4 = temp_tag_4 + "\r\n<a href=\"../" + ExtractFileName(dateiname_speichern) + "\">" + Hauptformular->SprachenWaehler->GetString(76) + "</a>";
      Hauptformular->TempMemo2->SelText = temp_tag_4;
      Hauptformular->TempMemo2->Lines->SaveToFile(ziel_pfad + akt_ordner + "\\" + Hauptformular->ReplaceString(Grafiken->Items->Item[bild_index]->Caption, ExtractFileExt(Grafiken->Items->Item[bild_index]->Caption), Hauptformular->documents_extension, true, true));

      if (CheckBox1->Checked)
       temp_tag = temp_tag + zeilenumbruch + Grafiken->Items->Item[bild_index]->Caption;
      if (CheckBox2->Checked)
       temp_tag = temp_tag + zeilenumbruch + (String(Hauptformular->FileGetSize(quell_pfad + Grafiken->Items->Item[bild_index]->Caption) / 1024) + " KB");
      if (CheckBox3->Checked)
       temp_tag = temp_tag + zeilenumbruch + String(alte_hoehe) + " x " + String(alte_breite);
      if (CheckBox4->Checked)
       temp_tag = temp_tag + zeilenumbruch + (FileDateToDateTime(FileAge(quell_pfad + Grafiken->Items->Item[bild_index]->Caption))).DateString();

      temp_tag = temp_tag + "</td>\r\n";
      bild_index++;
      ProgressBar1->StepIt();
     }
     else
     {
      temp_tag = temp_tag + "  <td></td>";
      ProgressBar1->StepIt();
     }
    }
    temp_tag = temp_tag + " </tr>\r\n";
   }
  }

  gesamt_tag = gesamt_tag + temp_tag;
  gesamt_tag = gesamt_tag + "\r\n</table>\r\n\r\n";
  temp_tag = "";
  if (akt_seite == 0)
   temp_tag = temp_tag + "<a href=\"" + Hauptformular->ReplaceString(Edit8->Text, "#", String(seiten), false, false) + "\">" + Hauptformular->SprachenWaehler->GetString(76) + "</a>";
  else
   temp_tag = temp_tag + "<a href=\"" + Hauptformular->ReplaceString(Edit8->Text, "#", String(akt_seite), false, false) + "\">" + Hauptformular->SprachenWaehler->GetString(76) + "</a>";

  temp_tag = temp_tag + home_seite;

  if (akt_seite == (seiten - 1))
   temp_tag = temp_tag + "<a href=\"" + Hauptformular->ReplaceString(Edit8->Text, "#", "1", false, false) + "\">" + Hauptformular->SprachenWaehler->GetString(77) + "</a>";
  else
   temp_tag = temp_tag + "<a href=\"" + Hauptformular->ReplaceString(Edit8->Text, "#", String(akt_seite + 2), false, false) + "\">" + Hauptformular->SprachenWaehler->GetString(77) + "</a>";

  gesamt_tag = gesamt_tag + temp_tag;
  Hauptformular->TempMemo->SelText = gesamt_tag;
  Hauptformular->TempMemo->Lines->SaveToFile(dateiname_speichern);
 }
 ProgressBar1->Position = ProgressBar1->Max;
 delete Grafik;
 delete Resizer;
 Hauptformular->Aktualisieren1Click(Sender);
 Hauptformular->Aktualisieren3Click(Sender);

 BitBtn1->Enabled = true;
 Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

