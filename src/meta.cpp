//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "meta.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMetatag *Metatag;
//---------------------------------------------------------------------------
__fastcall TMetatag::TMetatag(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMetatag::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TMetatag::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TMetatag::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_meta.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TMetatag::BitBtn1Click(TObject *Sender)
{
 String tag;
 tag = "<meta";


 if (ComboBox1->ItemIndex == 4)
 tag = tag + " http-equiv=\"" + Edit1->Text + "\"";
 else
 tag = tag + " name=\"" + Edit1->Text + "\"";

 tag = tag + " content=\"" + Edit2->Text + "\"";

 if (Hauptformular->tag_currently_editing)
 {
  tag = tag + Hauptformular->tag_current.SubString(0, Hauptformular->tag_current.Length());
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";
  Hauptformular->TagInsert(tag, "");
 }
 else
 {
  tag = Hauptformular->XHTMLBracketAdd(tag);
  tag = tag + ">";
  Hauptformular->TagInsertAndFindPosition(" " + tag, "", "</head>", "");
 }
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TMetatag::ComboBox1Change(TObject *Sender)
{
 TCHAR siBuffer[256];
 LPTSTR siValue = siBuffer;
 DWORD siBuffSize = 256;
 GetUserName(siValue, &siBuffSize);
 String user_name = String(siBuffer);
 if (Trim(user_name) == "")
  user_name = "Name";

 if (ComboBox1->ItemIndex == 0)
 {
  Edit1->Text = "";
  Edit2->Text = "";
 }
 else if (ComboBox1->ItemIndex == 1)
 {
  Edit1->Text = "description";
  Edit2->Text = "...";
 }
 else if (ComboBox1->ItemIndex == 2)
 {
  Edit1->Text = "author";
  Edit2->Text = user_name;
 }
 else if (ComboBox1->ItemIndex == 3)
 {
  Edit1->Text = "keywords";
  Edit2->Text = "Scribe!,Internet,Homepage";
 }
 else if (ComboBox1->ItemIndex == 4)
 {
  Edit1->Text = "refresh";
  Edit2->Text = "10;URL=http://www.scribe.de";
 }
 else if (ComboBox1->ItemIndex == 5)
 {
  Edit1->Text = "revisit-after";
  Edit2->Text = "30 days";
 }

 if (ComboBox1->ItemIndex == 0)
 {
  Edit1->SetFocus();
 }
 else
 {
  Edit2->SetFocus();
  Edit2->SelectAll();
 }
}
//---------------------------------------------------------------------------

void __fastcall TMetatag::FormShow(TObject *Sender)
{
 if (Hauptformular->tag_currently_editing)
 {
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);
  Hauptformular->tag_current = Hauptformular->ReplaceString(Hauptformular->tag_current, "http-equiv=", "name=", true, true);

  if (AnsiLowerCase(Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current)) == "description")
   ComboBox1->ItemIndex = 1;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current)) == "author")
   ComboBox1->ItemIndex = 2;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current)) == "keywords")
   ComboBox1->ItemIndex = 3;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current)) == "refresh")
   ComboBox1->ItemIndex = 4;
  else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current)) == "revisit-after")
   ComboBox1->ItemIndex = 5;
  else
   ComboBox1->ItemIndex = 0;

  Edit1->Text = Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current);
  Edit2->Text = Hauptformular->TagAttributeGetString("content=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("meta", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("name=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("content=", Hauptformular->tag_current);
 }
 else
 {
  ComboBox1->ItemIndex = 0;
  Edit1->SetFocus();
 }
}
//---------------------------------------------------------------------------

