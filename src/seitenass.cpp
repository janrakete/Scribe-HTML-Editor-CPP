//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "seitenass.h"
#include "hilfed.h"
#include "main.h"
#include "seitprop.h"
#include "child.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSeitenAssistent *SeitenAssistent;
//---------------------------------------------------------------------------
__fastcall TSeitenAssistent::TSeitenAssistent(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSeitenAssistent::FormShow(TObject *Sender)
{
 Caption = Label1->Caption;        
 ComboBox1->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TSeitenAssistent::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TSeitenAssistent::BitBtn2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TSeitenAssistent::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_page_wiz.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TSeitenAssistent::BitBtn1Click(TObject *Sender)
{
 String temp_str;

 Hauptformular->CreateChildForm("[leer]", "", "");

 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>");

 if (ComboBox1->ItemIndex == 0)
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">");
 else if (ComboBox1->ItemIndex == 1)
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
 else if (ComboBox1->ItemIndex == 2)
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Frameset//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-frame-set.dtd\">");

 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"de\" lang=\"de\">");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("<head>");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add(" <title>" + Edit1->Text + "</title>");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add(" <meta name=\"generator\" content=\"Scribe! 2 [http://scribe.de]\" />");

 if (Trim(Edit2->Text) != "")
 {
  temp_str = " <meta name=\"author\" content=\"" + Edit2->Text + "\" />";
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add(temp_str);
 }
 if (Trim(Edit3->Text) != "")
 {
  temp_str = " <meta name=\"keywords\" content=\"" + Edit3->Text + "\" />";
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add(temp_str);
 }
 if (Trim(Edit4->Text) != "")
 {
  temp_str = " <meta name=\"description\" content=\"" + Edit4->Text + "\" />";
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add(temp_str);
 }

 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("</head>");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("<body>");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("</body>");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Lines->Add("</html>");
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SetFocus();
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = 0;
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->Modified = false;
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->ClearUndo();

 Visible = false;
 Close();
 ((TKindFormular*) Hauptformular->ActiveMDIChild)->Repaint();

 if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt("<body", true, false, false, false))
 {
  int temp_int_2 = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart - 5;
  int temp_int_3 = 0;
  if (((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->FindTxt(">", true, false, false, false))
   temp_int_3 = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelStart = temp_int_2;
  ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelLength = temp_int_3 - temp_int_2;
  Hauptformular->tag_current = ((TKindFormular*) Hauptformular->ActiveMDIChild)->Textfeld->SelText;
  Hauptformular->tag_currently_editing = true;
  TSeiteneigen* Seiteneigen = new TSeiteneigen(Application);
  Hauptformular->SprachenWaehler->SetFormLanguage(Seiteneigen);
  Seiteneigen->Caption = Hauptformular->ReplaceString(Hauptformular->Seiteneigenschaften1->Caption, "&", "", false, true);
  Seiteneigen->ShowModal();
 }
}
//---------------------------------------------------------------------------

