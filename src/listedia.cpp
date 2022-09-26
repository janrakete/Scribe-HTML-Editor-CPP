//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "listedia.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TListe *Liste;
//---------------------------------------------------------------------------
__fastcall TListe::TListe(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TListe::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_ol_ul.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TListe::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);
}
//---------------------------------------------------------------------------

void __fastcall TListe::FormClose(TObject *Sender, TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TListe::FormShow(TObject *Sender)
{
 item_index = 0;
 end_tag = "";

 if (Hauptformular->tag_currently_editing)
 {
  TabSheet3->TabVisible = false;
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  if (AnsiPos("<ul", AnsiLowerCase(Hauptformular->tag_current)))
  {
   ComboBox2->ItemIndex = 0;
   end_tag = "</ul>";
  }
  else if (AnsiPos("<ol", AnsiLowerCase(Hauptformular->tag_current)))
  {
   ComboBox2->ItemIndex = 1;
   end_tag = "</ol>";
  }
  ComboBox2Change(Sender);

  if (Hauptformular->TagAttributeContainsAttribute("start=", Hauptformular->tag_current))
  {
   UpDown3->Position = Hauptformular->TagAttributeGetNumeric("start=", Hauptformular->tag_current);
   Edit7->Enabled = true;
   UpDown3->Enabled = true;
  }

  if (ComboBox2->ItemIndex == 0)
  {
   if (AnsiLowerCase(Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current)) == "circle")
    ComboBox1->ItemIndex = 1;
   else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current)) == "square")
    ComboBox1->ItemIndex = 2;
   else if (AnsiLowerCase(Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current)) == "disc")
    ComboBox1->ItemIndex = 3;
   else
   ComboBox1->ItemIndex = 0;
  }
  else
  {
   if (Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current) == "1")
    ComboBox1->ItemIndex = 1;
   else if (Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current) == "a")
    ComboBox1->ItemIndex = 2;
   else if (Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current) == "A")
    ComboBox1->ItemIndex = 3;
   else if (Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current) == "i")
    ComboBox1->ItemIndex = 4;
   else if (Hauptformular->TagAttributeGetString("type=", Hauptformular->tag_current) == "I")
    ComboBox1->ItemIndex = 5;
   else
   ComboBox1->ItemIndex = 0;
  }

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("ul", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("ol", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("type=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("start=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
 }
 else
 {
  ComboBox2->ItemIndex = 0;
  ComboBox2Change(Sender);
 }
}
//---------------------------------------------------------------------------

void __fastcall TListe::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TListe::BitBtn1Click(TObject *Sender)
{
 String spaces = AnsiString::StringOfChar(' ', ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol);

 if (ComboBox2->ItemIndex == 0)
 {
  String tag;
  tag = "<ul";

  if (ComboBox1->ItemIndex == 1)
   tag = tag + " type=\"circle\"";
  else if (ComboBox1->ItemIndex == 2)
   tag = tag + " type=\"square\"";
  else if (ComboBox1->ItemIndex == 3)
   tag = tag + " type=\"disc\"";

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

  if (Hauptformular->tag_currently_editing)
  {
   tag = tag + Hauptformular->tag_current.SubString(0, Hauptformular->tag_current.Length());
   tag = TrimRight(tag);
   tag = tag + ">";
   Hauptformular->TagInsert(tag, "");

   if (end_tag != "</ul>")
   {
    if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt(end_tag, true, false, false, false))
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = "</ul>";
   }
  }
  else
  {
   tag = tag + ">\r\n";
   for (int i = 0; i < ListBox1->Items->Count; i++)
    tag = tag + spaces + " <li>" + ListBox1->Items->Strings[i] + "</li>\r\n";
   Hauptformular->TagInsert(tag, spaces + "</ul>");
  }
  Close();
 }
 else
 {
  String tag;
  tag = "<ol";

  if (ComboBox1->ItemIndex == 1)
   tag = tag + " type=\"1\"";
  else if (ComboBox1->ItemIndex == 2)
   tag = tag + " type=\"a\"";
  else if (ComboBox1->ItemIndex == 3)
   tag = tag + " type=\"A\"";
  else if (ComboBox1->ItemIndex == 4)
   tag = tag + " type=\"i\"";
  else if (ComboBox1->ItemIndex == 5)
   tag = tag + " type=\"I\"";

  if (UpDown3->Position != 0)
   tag = tag + " start=\"" + String(UpDown3->Position) + "\"";

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

  if (Hauptformular->tag_currently_editing)
  {
   tag = tag + Hauptformular->tag_current.SubString(0, Hauptformular->tag_current.Length());
   tag = TrimRight(tag);
   tag = tag + ">";
   Hauptformular->TagInsert(tag, "");

   if (end_tag != "</ol>")
   {
    if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt(end_tag, true, false, false, false))
     ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText = "</ol>";
   }
  }
  else
  {
   tag = tag + ">\r\n";
   for (int i = 0; i < ListBox1->Items->Count; i++)
    tag = tag + spaces + " <li>" + ListBox1->Items->Strings[i] + "</li>\r\n";
   Hauptformular->TagInsert(tag, spaces + "</ol>");
  }
  Close();
 }
}
//---------------------------------------------------------------------------

void __fastcall TListe::ListBox1DragDrop(TObject *Sender, TObject *Source,
      int X, int Y)
{
 try
 {
  int temp_int = ListBox1->ItemAtPos(Point(X,Y), true);
  ListBox1->Items->Move(item_index, ListBox1->ItemAtPos(Point(X,Y), true));
  ListBox1->ItemIndex = temp_int;
 }
 catch (...)
 {
  1 == 1;
 }
}
//---------------------------------------------------------------------------

void __fastcall TListe::ListBox1DragOver(TObject *Sender, TObject *Source,
      int X, int Y, TDragState State, bool &Accept)
{
 item_index = ListBox1->ItemIndex;        
}
//---------------------------------------------------------------------------

void __fastcall TListe::ToolButton5Click(TObject *Sender)
{
 if (ListBox1->ItemIndex > -1)
  ListBox1->Items->Delete(ListBox1->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TListe::ToolButton4Click(TObject *Sender)
{
 Edit1->SelectAll();
 ListBox1->Items->Add(Edit1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TListe::ListBox1Click(TObject *Sender)
{
 if (ListBox1->ItemIndex > -1)
  ToolButton5->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TListe::Edit1Change(TObject *Sender)
{
 if (Trim(Edit1->Text) == "")
  ToolButton4->Enabled = false;
 else
  ToolButton4->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TListe::PageControl1Change(TObject *Sender)
{
 if (PageControl1->ActivePage == TabSheet3)
  Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TListe::ComboBox2Change(TObject *Sender)
{
 if (ComboBox2->ItemIndex == 0)
 {
  ComboBox1->Items = ComboBox3->Items;
  ComboBox1->ItemIndex = 0;
  Edit7->Enabled = false;
  UpDown3->Enabled = false;
  UpDown3->Position = 0;
 }
 else
 {
  ComboBox1->Items = ComboBox4->Items;
  ComboBox1->ItemIndex = 0;
  Edit7->Enabled = false;
  UpDown3->Enabled = false;
  UpDown3->Position = 0;
 }
 ComboBox1Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TListe::ComboBox1Change(TObject *Sender)
{
 if ((ComboBox1->ItemIndex == 1) && (ComboBox2->ItemIndex == 1))
 {
  Edit7->Enabled = true;
  UpDown3->Enabled = true;
 }
 else
 {
  Edit7->Enabled = false;
  UpDown3->Enabled = false;
  UpDown3->Position = 0;
 }

 String item1;
 String item2;
 String item3;
 String item4;
 String item5;

 if (ComboBox2->ItemIndex == 0)
 {
  if (ComboBox1->ItemIndex == 0)
  {
   item1 = "•";
   item2 = "•";
   item3 = "•";
   item4 = "•";
   item5 = "•";
  }
  else if (ComboBox1->ItemIndex == 1)
  {
   item1 = "o";
   item2 = "o";
   item3 = "o";
   item4 = "o";
   item5 = "o";
  }
  else if (ComboBox1->ItemIndex == 2)
  {
   item1 = "";
   item2 = "";
   item3 = "";
   item4 = "";
   item5 = "";
  }
  else if (ComboBox1->ItemIndex == 3)
  {
   item1 = "•";
   item2 = "•";
   item3 = "•";
   item4 = "•";
   item5 = "•";
  }
 }
 else if (ComboBox2->ItemIndex == 1)
 {
  if (ComboBox1->ItemIndex == 0)
  {
   item1 = "1.";
   item2 = "2.";
   item3 = "3.";
   item4 = "4.";
   item5 = "5.";
  }
  else if (ComboBox1->ItemIndex == 1)
  {
   item1 = "1.";
   item2 = "2.";
   item3 = "3.";
   item4 = "4.";
   item5 = "5.";
  }
  else if (ComboBox1->ItemIndex == 2)
  {
   item1 = "a.";
   item2 = "b.";
   item3 = "c.";
   item4 = "d.";
   item5 = "e.";
  }
  else if (ComboBox1->ItemIndex == 3)
  {
   item1 = "A.";
   item2 = "B.";
   item3 = "C.";
   item4 = "D.";
   item5 = "E.";
  }
  else if (ComboBox1->ItemIndex == 4)
  {
   item1 = "i.";
   item2 = "ii.";
   item3 = "iii.";
   item4 = "iv.";
   item5 = "v.";
  }
  else if (ComboBox1->ItemIndex == 5)
  {
   item1 = "I.";
   item2 = "II.";
   item3 = "III.";
   item4 = "IV.";
   item5 = "V.";
  }
 }


 Item1->Caption = item1;
 Item2->Caption = item2;
 Item3->Caption = item3;
 Item4->Caption = item4;
 Item5->Caption = item5;
}
//---------------------------------------------------------------------------

