//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "seitprop.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSeiteneigen *Seiteneigen;
//---------------------------------------------------------------------------
__fastcall TSeiteneigen::TSeiteneigen(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSeiteneigen::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;        
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_body.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);        
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::SpeedButton4Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog1);
 if (ColorDialog1->Execute())
 {
  Hauptformular->ColorButton(SpeedButton4, ColorDialog1->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog1);
  Panel2->Color = ColorDialog1->Color;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::SpeedButton5Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog2);
 if (ColorDialog2->Execute())
 {
  Hauptformular->ColorButton(SpeedButton5, ColorDialog2->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog2);
  Label14->Font->Color = ColorDialog2->Color;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::SpeedButton6Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog3);
 if (ColorDialog3->Execute())
 {
  Hauptformular->ColorButton(SpeedButton6, ColorDialog3->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog3);
  Label16->Font->Color = ColorDialog3->Color;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::SpeedButton7Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog4);
 if (ColorDialog4->Execute())
 {
  Hauptformular->ColorButton(SpeedButton7, ColorDialog4->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog4);
  Label17->Font->Color = ColorDialog4->Color;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::SpeedButton8Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog5);
 if (ColorDialog5->Execute())
 {
  Hauptformular->ColorButton(SpeedButton8, ColorDialog5->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog5);
  Label18->Font->Color = ColorDialog5->Color;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::SpeedButton2Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(6);
 filter_temp = filter_temp + Hauptformular->BuildFilter(Hauptformular->graphicfile_extensions);
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OeffnenDialog->Filter = filter_gesamt;
 OeffnenDialog->InitialDir = ExtractFilePath(Hauptformular->ActiveMDIChild->Caption);
 OeffnenDialog->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OeffnenDialog->Execute())
 {
  Edit1->Text = Hauptformular->DirectorySameAndRelative(OeffnenDialog->FileName);

  Graphics::TPicture* color_pic = new Graphics::TPicture();
  color_pic->LoadFromFile(OeffnenDialog->FileName);
  Graphics::TBitmap* bitmap1 = new Graphics::TBitmap();
  bitmap1->Assign(color_pic->Graphic);
  Graphics::TBitmap* bitmap2 = new Graphics::TBitmap();
  bitmap2->Height = Image1->Height;
  bitmap2->Width = Image1->Width;

  int x = Image1->Width / bitmap1->Width;
  int y = Image1->Height / bitmap1->Height;
  for (int i = 0; i < (y+1); i++)
  {
   for (int a = 0; a < (x+1); a++)
    bitmap2->Canvas->Draw(a * bitmap1->Width, i * bitmap1->Height, bitmap1);
  }
  Image1->Picture->Bitmap = bitmap2;

  delete bitmap1;
  delete bitmap2;
  delete color_pic;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::SpeedButton3Click(TObject *Sender)
{
 Edit1->Text = Hauptformular->ImageCatalogShow();

 if (Trim(Edit1->Text) != "")
 {
  String pfad_vorher = GetCurrentDir();
  SetCurrentDir (ExtractFilePath(Hauptformular->ActiveMDIChild->Caption));

  Graphics::TPicture* color_pic = new Graphics::TPicture();
  color_pic->LoadFromFile(Edit1->Text);
  Graphics::TBitmap* bitmap1 = new Graphics::TBitmap();
  bitmap1->Assign(color_pic->Graphic);
  Graphics::TBitmap* bitmap2 = new Graphics::TBitmap();
  bitmap2->Height = Image1->Height;
  bitmap2->Width = Image1->Width;

  int x = Image1->Width / bitmap1->Width;
  int y = Image1->Height / bitmap1->Height;
  for (int i = 0; i < (y+1); i++)
  {
   for (int a = 0; a < (x+1); a++)
    bitmap2->Canvas->Draw(a * bitmap1->Width, i * bitmap1->Height, bitmap1);
  }
  Image1->Picture->Bitmap = bitmap2;

  delete bitmap1;
  delete bitmap2;
  delete color_pic;

  SetCurrentDir (pfad_vorher);
 }
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::FormShow(TObject *Sender)
{
 Label14->Caption = Hauptformular->ReplaceString(Label11->Caption, ":", "", false, false);
 Label16->Caption = Hauptformular->ReplaceString(Label12->Caption, ":", "", false, false);
 Label17->Caption = Hauptformular->ReplaceString(Label13->Caption, ":", "", false, false);
 Label18->Caption = Hauptformular->ReplaceString(Label15->Caption, ":", "", false, false);

 EventsTabSheet->TabVisible = Hauptformular->editor_events_tab;

 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  if (Hauptformular->TagAttributeContainsAttribute("background=", Hauptformular->tag_current))
  {
   Edit1->Text = Hauptformular->TagAttributeGetString("background=", Hauptformular->tag_current);
   String pfad_vorher = GetCurrentDir();
   SetCurrentDir (ExtractFilePath(Hauptformular->ActiveMDIChild->Caption));
   try
   {
    Graphics::TPicture* color_pic = new Graphics::TPicture();
    color_pic->LoadFromFile(Edit1->Text);
    Graphics::TBitmap* bitmap1 = new Graphics::TBitmap();
    bitmap1->Assign(color_pic->Graphic);
    Graphics::TBitmap* bitmap2 = new Graphics::TBitmap();
    bitmap2->Height = Image1->Height;
    bitmap2->Width = Image1->Width;
    int x = Image1->Width / bitmap1->Width;
    int y = Image1->Height / bitmap1->Height;
    for (int i = 0; i < (y+1); i++)
    {
     for (int a = 0; a < (x+1); a++)
      bitmap2->Canvas->Draw(a * bitmap1->Width, i * bitmap1->Height, bitmap1);
    }
    Image1->Picture->Bitmap = bitmap2;
    delete bitmap1;
    delete bitmap2;
    delete color_pic;
   }
   catch (...)
   {
    1 == 1;
   }
   SetCurrentDir (pfad_vorher);
  }

  if (Hauptformular->TagAttributeContainsAttribute("bgcolor=", Hauptformular->tag_current))
  {
   Hauptformular->ColorAssignColorToButton(SpeedButton4, Hauptformular->TagAttributeGetColor("bgcolor=", Hauptformular->tag_current), ColorDialog1);
   Panel2->Color = ColorDialog1->Color;
  }
  else
   Hauptformular->ColorAssignColorToButton(SpeedButton4, clWindow, ColorDialog1);

  if (Hauptformular->TagAttributeContainsAttribute("text=", Hauptformular->tag_current))
  {
   Hauptformular->ColorAssignColorToButton(SpeedButton5, Hauptformular->TagAttributeGetColor("text=", Hauptformular->tag_current), ColorDialog2);
   Label14->Font->Color = ColorDialog2->Color;
  }
  else
   Hauptformular->ColorAssignColorToButton(SpeedButton5, clBlack, ColorDialog2);

  if (Hauptformular->TagAttributeContainsAttribute("link=", Hauptformular->tag_current))
  {
   Hauptformular->ColorAssignColorToButton(SpeedButton6, Hauptformular->TagAttributeGetColor("link=", Hauptformular->tag_current), ColorDialog3);
   Label16->Font->Color = ColorDialog3->Color;
  }
  else
   Hauptformular->ColorAssignColorToButton(SpeedButton6, clBlue, ColorDialog3);

  if (Hauptformular->TagAttributeContainsAttribute("vlink=", Hauptformular->tag_current))
  {
   Hauptformular->ColorAssignColorToButton(SpeedButton7, Hauptformular->TagAttributeGetColor("vlink=", Hauptformular->tag_current), ColorDialog4);
   Label17->Font->Color = ColorDialog4->Color;
  }
  else
   Hauptformular->ColorAssignColorToButton(SpeedButton7, clPurple, ColorDialog4);

  if (Hauptformular->TagAttributeContainsAttribute("alink=", Hauptformular->tag_current))
  {
   Hauptformular->ColorAssignColorToButton(SpeedButton8, Hauptformular->TagAttributeGetColor("alink=", Hauptformular->tag_current), ColorDialog5);
   Label18->Font->Color = ColorDialog5->Color;
  }
  else
   Hauptformular->ColorAssignColorToButton(SpeedButton8, clRed, ColorDialog5);

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);
  Edit2->Text = Hauptformular->TagAttributeGetString("onload=", Hauptformular->tag_current);
  Edit3->Text = Hauptformular->TagAttributeGetString("onunload=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("body", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("background=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("bgcolor=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("text=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("vlink=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("alink=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("link=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onload=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onunload=", Hauptformular->tag_current);
 }
 else
 {
  Hauptformular->ColorAssignColorToButton(SpeedButton4, clWindow, ColorDialog1);
  Hauptformular->ColorAssignColorToButton(SpeedButton5, clBlack, ColorDialog2);
  Hauptformular->ColorAssignColorToButton(SpeedButton6, clBlue, ColorDialog3);
  Hauptformular->ColorAssignColorToButton(SpeedButton7, clPurple, ColorDialog4);
  Hauptformular->ColorAssignColorToButton(SpeedButton8, clRed, ColorDialog5);
 }
}
//---------------------------------------------------------------------------

void __fastcall TSeiteneigen::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<body";

 if (Trim(Edit1->Text) != "")
  tag = tag + " background=\"" + Edit1->Text + "\"";
 if (ColorDialog1->Color != clWindow)
  tag = tag + " bgcolor=\"" + Hauptformular->ColorColorToXHTMLCode(ColorDialog1->Color) + "\"";
 if (ColorDialog2->Color != clBlack)
  tag = tag + " text=\"" + Hauptformular->ColorColorToXHTMLCode(ColorDialog2->Color) + "\"";
 if (ColorDialog3->Color != clBlue)
  tag = tag + " link=\"" + Hauptformular->ColorColorToXHTMLCode(ColorDialog3->Color) + "\"";
 if (ColorDialog4->Color != clPurple)
  tag = tag + " vlink=\"" + Hauptformular->ColorColorToXHTMLCode(ColorDialog4->Color) + "\"";
 if (ColorDialog5->Color != clRed)
  tag = tag + " alink=\"" + Hauptformular->ColorColorToXHTMLCode(ColorDialog5->Color) + "\"";

 //Cascading Style-Sheets - Anfang
 if (Trim(CssStyle->Text) != "")
  tag = tag + " style=\"" + CssStyle->Text + "\"";
 if (Trim(CssID->Text) != "")
  tag = tag + " id=\"" + CssID->Text + "\"";
 if (Trim(CssClass->Text) != "")
  tag = tag + " class=\"" + CssClass->Text + "\"";
 if (Trim(CssTitle->Text) != "")
  tag = tag + " title=\"" + CssTitle->Text + "\"";
 //Cascading Style-Sheets - Ende

 //JavaScript-Ereignisse - Anfang
 if (Trim(Edit2->Text) != "")
  tag = tag + " onLoad=\"" + Edit2->Text + "\"";
 if (Trim(Edit3->Text) != "")
  tag = tag + " onUnload=\"" + Edit3->Text + "\"";
 //JavaScript-Ereignisse - Ende

 if (Hauptformular->tag_currently_editing)
 {
  tag = tag + Hauptformular->tag_current.SubString(0, Hauptformular->tag_current.Length());
  tag = TrimRight(tag);
  tag = tag + ">";
  Hauptformular->TagInsert(tag, "");
 }
 else
 {
  tag = tag + ">";
  Hauptformular->TagInsert(tag + "\r\n", "\r\n</body>");
 }
 Close();
}
//---------------------------------------------------------------------------

