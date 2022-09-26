//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "auswahl.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAuswahlliste *Auswahlliste;
//---------------------------------------------------------------------------
__fastcall TAuswahlliste::TAuswahlliste(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAuswahlliste::CheckBox2Click(TObject *Sender)
{
 if (CheckBox2->Checked)
 {
  Edit3->Enabled = true;
  UpDown1->Enabled = true;
 }
 else
 {
  Edit3->Enabled = false;
  UpDown1->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::SpeedButton1Click(TObject *Sender)
{
 CssStyle->Text = Hauptformular->CSSEditorEditStyle(CssStyle->Text);
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::BitBtn1Click(TObject *Sender)
{
 String spaces = AnsiString::StringOfChar(' ', ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelCol);

 String tag;
 tag = "<select";

 if (Trim(Edit2->Text) != "")
  tag = tag + " name=\"" + Edit2->Text + "\"";

 if (CheckBox2->Checked)
  tag = tag + " size=\"" + String(UpDown1->Position) + "\"";

 if (CheckBox1->Checked)
 {
  if (Hauptformular->editor_xhtml_mode)
   tag = tag + " multiple=\"multiple\"";
  else
   tag = tag + " multiple";
 }

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
 if (Trim(Edit4->Text) != "")
  tag = tag + " onChange=\"" + Edit4->Text + "\"";
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
  tag = tag + ">\r\n";
  String option = "";
  for (int i = 0; i < ListBox1->Items->Count; i++)
  {
   option = "";
   if (Trim(ListBox2->Items->Strings[i]) == "")
    option = spaces + " <option";
   else
    option = spaces + " <option value=\"" + ListBox2->Items->Strings[i] + "\"";

   if (ListBox1->Checked[i])
   {
    if (Hauptformular->editor_xhtml_mode)
     option = option + " selected=\"selected\"";
    else
     option = option + " selected";
   }

   option = option + ">" + ListBox1->Items->Strings[i] + "</option>\r\n";
   tag = tag + option;
  }
  Hauptformular->TagInsert(tag, spaces + "</select>");
 }
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::BitBtn2Click(TObject *Sender)
{
 Close();
 if (Hauptformular->ActiveMDIChild)
 {
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = 0;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "tag_select.html", true);        
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Hauptformular->tag_current = "";
 Hauptformular->tag_currently_editing = false;
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::FormShow(TObject *Sender)
{
 item_index = 0;

 if (Hauptformular->tag_currently_editing)
 {
  TabSheet3->TabVisible = false;
  Hauptformular->tag_current = Hauptformular->TagNormalize(Hauptformular->tag_current, true);

  Edit2->Text = Hauptformular->TagAttributeGetString("name=", Hauptformular->tag_current);

  if (Hauptformular->TagAttributeContainsAttribute("size=", Hauptformular->tag_current))
  {
   CheckBox2->Checked = true;
   UpDown1->Position = Hauptformular->TagAttributeGetNumeric("size=", Hauptformular->tag_current);
  }

  if ((Hauptformular->TagAttributeContainsStandalone("multiple", Hauptformular->tag_current)) || (AnsiLowerCase(Hauptformular->TagAttributeGetString("multiple=", Hauptformular->tag_current)) == "multiple"))
   CheckBox1->Checked = true;

  CssStyle->Text = Hauptformular->TagAttributeGetString("style=", Hauptformular->tag_current);
  CssID->Text =    Hauptformular->TagAttributeGetString("id=", Hauptformular->tag_current);
  CssClass->Text = Hauptformular->TagAttributeGetString("class=", Hauptformular->tag_current);
  CssTitle->Text = Hauptformular->TagAttributeGetString("title=", Hauptformular->tag_current);

  Edit4->Text = Hauptformular->TagAttributeGetString("onchange=", Hauptformular->tag_current);

  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveMainTag("select", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("size=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("name=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("multiple=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveStandalone("multiple", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("style=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("id=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("class=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("title=", Hauptformular->tag_current);
  Hauptformular->tag_current = Hauptformular->TagAttributeRemoveAttribute("onchange=", Hauptformular->tag_current);
 }
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::Edit1Change(TObject *Sender)
{
 if (Trim(Edit1->Text) == "")
  ToolButton4->Enabled = false;
 else
  ToolButton4->Enabled = true;        
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::ListBox1Click(TObject *Sender)
{
 if (ListBox1->ItemIndex > -1)
  ToolButton5->Enabled = true;        
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::ToolButton4Click(TObject *Sender)
{
 Edit1->SelectAll();
 ListBox1->Items->Add(Edit1->Text);
 ListBox2->Items->Add(Edit5->Text);
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::ToolButton5Click(TObject *Sender)
{
 int index = ListBox1->ItemIndex;
 if (index > -1)
 {
  ListBox1->Items->Delete(index);
  ListBox2->Items->Delete(index);
 }
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::ListBox1DragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
 item_index = ListBox1->ItemIndex;          
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::PageControl1Change(TObject *Sender)
{
 if (PageControl1->ActivePage == TabSheet3)
  Edit1->SetFocus();        
}
//---------------------------------------------------------------------------

void __fastcall TAuswahlliste::ListBox1DragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
 try
 {
  int temp_int = ListBox1->ItemAtPos(Point(X,Y), true);
  ListBox1->Items->Move(item_index, ListBox1->ItemAtPos(Point(X,Y), true));
  ListBox1->ItemIndex = temp_int;
  ListBox2->Items->Move(item_index, ListBox2->ItemAtPos(Point(X,Y), true));
  ListBox2->ItemIndex = temp_int;
 }
 catch (...)
 {
  1 == 1;
 }
}
//---------------------------------------------------------------------------

