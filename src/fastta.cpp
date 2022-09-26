//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "fastta.h"
#include "main.h"
#include "hilfed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFastTag *FastTag;
//---------------------------------------------------------------------------
__fastcall TFastTag::TFastTag(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFastTag::FormShow(TObject *Sender)
{
 TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");

 Edit1->Text = FastTagsIni->ReadString("Common", "Body", "<body bgcolor=\"#FFFFFF\" link=\"#FF0000\">");
 Edit2->Text = FastTagsIni->ReadString("Common", "BodyEnd", "</body>");
 Edit3->Text = FastTagsIni->ReadString("Common", "Paragraph", "<p align=\"center\">");
 Edit4->Text = FastTagsIni->ReadString("Common", "ParagraphEnd", "</p>");
 Edit5->Text = FastTagsIni->ReadString("Common", "Break", "");
 Edit6->Text = FastTagsIni->ReadString("Common", "BreakEnd", "<br clear=\"all\" />");
 Edit7->Text = FastTagsIni->ReadString("Common", "Hyperlink", "<a href=\"http://\" target=\"_blank\">");
 Edit8->Text = FastTagsIni->ReadString("Common", "HyperlinkEnd", "</a>");
 Edit9->Text = FastTagsIni->ReadString("Common", "Image", "<img src=\"\" alt=\"\" border=\"0\" />");
 Edit10->Text = FastTagsIni->ReadString("Common", "ImageEnd", "");
 Edit11->Text = FastTagsIni->ReadString("Common", "Rule", "<hr noshade=\"noshade\" />");
 Edit12->Text = FastTagsIni->ReadString("Common", "RuleEnd", "");
 Edit13->Text = FastTagsIni->ReadString("Common", "Object", "<object data=\"\" border=\"0\">");
 Edit14->Text = FastTagsIni->ReadString("Common", "ObjectEnd", "</object>");
 Edit15->Text = FastTagsIni->ReadString("Common", "Meta", "<meta name=\"\" content=\"\" />");
 Edit16->Text = FastTagsIni->ReadString("Common", "MetaEnd", "");
 Edit17->Text = FastTagsIni->ReadString("Common", "List", "<ol type=\"i\">");
 Edit18->Text = FastTagsIni->ReadString("Common", "ListEnd", "</ol>");
 Edit19->Text = FastTagsIni->ReadString("Common", "ListItem", "<li value=\"\">");
 Edit20->Text = FastTagsIni->ReadString("Common", "ListItemEnd", "</li>");

 Edit21->Text = FastTagsIni->ReadString("Additional", "eMail", "<a href=\"MailTo:\">");
 Edit22->Text = FastTagsIni->ReadString("Additional", "eMailEnd", "</a>");
 Edit23->Text = FastTagsIni->ReadString("Additional", "Anchor", "<a name=\"\" id=\"\">");
 Edit24->Text = FastTagsIni->ReadString("Additional", "AnchorEnd", "</a>");
 Edit25->Text = FastTagsIni->ReadString("Additional", "FrameSet", "<frameset cols=\"100,*\" frameborder=\"0\">");
 Edit26->Text = FastTagsIni->ReadString("Additional", "FrameSetEnd", "</frameset>");
 Edit27->Text = FastTagsIni->ReadString("Additional", "Frame", "<frame src=\"http://\" name=\"\" noresize=\"noresize\" />");
 Edit28->Text = FastTagsIni->ReadString("Additional", "FrameEnd", "");
 Edit29->Text = FastTagsIni->ReadString("Additional", "IFrame", "<iframe src=\"http://\" name=\"\">");
 Edit30->Text = FastTagsIni->ReadString("Additional", "IFrameEnd", "</iframe>");
 Edit31->Text = FastTagsIni->ReadString("Additional", "CSSDefinition", "<style type=\"text/css\"><!-- body { font-family:Arial; color:#000000; } //-->");
 Edit32->Text = FastTagsIni->ReadString("Additional", "CSSDefinitionEnd", "</style>");

 Edit33->Text = FastTagsIni->ReadString("Format", "Font", "<font size=\"\" color=\"#FF0000\"><b>");
 Edit34->Text = FastTagsIni->ReadString("Format", "FontEnd", "</b></font>");
 Edit35->Text = FastTagsIni->ReadString("Format", "FastFormat", "<span style=\"\" class=\"\">");
 Edit36->Text = FastTagsIni->ReadString("Format", "FastFormatEnd", "</span>");
 Edit37->Text = FastTagsIni->ReadString("Format", "Bold", "<b>");
 Edit38->Text = FastTagsIni->ReadString("Format", "BoldEnd", "</b>");
 Edit39->Text = FastTagsIni->ReadString("Format", "Italic", "<i>");
 Edit40->Text = FastTagsIni->ReadString("Format", "ItalicEnd", "</i>");
 Edit41->Text = FastTagsIni->ReadString("Format", "Left", "<div align=\"left\">");
 Edit42->Text = FastTagsIni->ReadString("Format", "LeftEnd", "</div>");
 Edit43->Text = FastTagsIni->ReadString("Format", "Center", "<div align=\"center\">");
 Edit44->Text = FastTagsIni->ReadString("Format", "CenterEnd", "</div>");
 Edit45->Text = FastTagsIni->ReadString("Format", "Right", "<div align=\"right\">");
 Edit46->Text = FastTagsIni->ReadString("Format", "RightEnd", "</div>");
 Edit47->Text = FastTagsIni->ReadString("Format", "Justify", "<p align=\"justify\">");
 Edit48->Text = FastTagsIni->ReadString("Format", "JustifyEnd", "</p>");

 Edit49->Text = FastTagsIni->ReadString("Tables", "Table", "<table width=\"\" bgcolor=\"#000000\" border=\"0\">");
 Edit50->Text = FastTagsIni->ReadString("Tables", "TableEnd", "</table>");
 Edit51->Text = FastTagsIni->ReadString("Tables", "Row", "<tr>");
 Edit52->Text = FastTagsIni->ReadString("Tables", "RowEnd", "</tr>");
 Edit53->Text = FastTagsIni->ReadString("Tables", "Header", "<th height=\"\" width=\"\" bgcolor=\"#000000\" rowspan=\"\" colspan=\"\">");
 Edit54->Text = FastTagsIni->ReadString("Tables", "HeaderEnd", "</th>");
 Edit55->Text = FastTagsIni->ReadString("Tables", "Data", "<td height=\"\" width=\"\" bgcolor=\"#000000\" rowspan=\"\" colspan=\"\">");
 Edit56->Text = FastTagsIni->ReadString("Tables", "DataEnd", "</td>");
 Edit57->Text = FastTagsIni->ReadString("Tables", "Caption", "<caption align=\"bottom\">");
 Edit58->Text = FastTagsIni->ReadString("Tables", "CaptionEnd", "</caption>");

 Edit59->Text = FastTagsIni->ReadString("Forms", "Form", "<form name=\"\" action=\"MailTo:\" method=\"post\" enctype=\"text/plain\" target=\"\">");
 Edit60->Text = FastTagsIni->ReadString("Forms", "FormEnd", "</form>");
 Edit61->Text = FastTagsIni->ReadString("Forms", "InputText", "<input type=\"text\" name=\"\" size=\"\" maxlength=\"100\" />");
 Edit62->Text = FastTagsIni->ReadString("Forms", "InputTextEnd", "");
 Edit63->Text = FastTagsIni->ReadString("Forms", "Textarea", "<textarea name=\"\" rows=\"\" cols=\"\">");
 Edit64->Text = FastTagsIni->ReadString("Forms", "TextareaEnd", "</textarea>");
 Edit65->Text = FastTagsIni->ReadString("Forms", "Submit", "<input type=\"submit\" value=\"Send!\" />");
 Edit66->Text = FastTagsIni->ReadString("Forms", "SubmitEnd", "");
 Edit67->Text = FastTagsIni->ReadString("Forms", "Password", "<input type=\"password\" name=\"\" size=\"\" maxlength=\"\" />");
 Edit68->Text = FastTagsIni->ReadString("Forms", "PasswordEnd", "");
 Edit69->Text = FastTagsIni->ReadString("Forms", "Hidden", "<input type=\"hidden\" name=\"\" value=\"\" />");
 Edit70->Text = FastTagsIni->ReadString("Forms", "HiddenEnd", "");
 Edit71->Text = FastTagsIni->ReadString("Forms", "Checkbox", "<input type=\"radio\" name=\"\" value=\"\" checked=\"checked\" />");
 Edit72->Text = FastTagsIni->ReadString("Forms", "CheckboxEnd", "");
 Edit73->Text = FastTagsIni->ReadString("Forms", "Radiobutton", "<input type=\"checkbox\" name=\"\" value=\"\" checked=\"checked\" />");
 Edit74->Text = FastTagsIni->ReadString("Forms", "RadiobuttonEnd", "");
 Edit75->Text = FastTagsIni->ReadString("Forms", "Select", "<select name=\"\" size=\"\" multiple=\"multiple\">");
 Edit76->Text = FastTagsIni->ReadString("Forms", "SelectEnd", "</select>");
 Edit77->Text = FastTagsIni->ReadString("Forms", "Option", "<option value=\"\">");
 Edit78->Text = FastTagsIni->ReadString("Forms", "OptionEnd", "</option>");
 Edit79->Text = FastTagsIni->ReadString("Forms", "Button", "<input type=\"button\" name=\"\" value=\"\" />");
 Edit80->Text = FastTagsIni->ReadString("Forms", "ButtonEnd", "");

 delete FastTagsIni;
}
//---------------------------------------------------------------------------

void __fastcall TFastTag::FormClose(TObject *Sender, TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TFastTag::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_fasttag.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TFastTag::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TFastTag::BitBtn1Click(TObject *Sender)
{
 TIniFile* FastTagsIni = new TIniFile(Hauptformular->program_dir + "Storage!\\fasttag.ini");

 FastTagsIni->WriteString("Common", "Body", Edit1->Text);
 FastTagsIni->WriteString("Common", "BodyEnd", Edit2->Text);
 FastTagsIni->WriteString("Common", "Paragraph", Edit3->Text);
 FastTagsIni->WriteString("Common", "ParagraphEnd", Edit4->Text);
 FastTagsIni->WriteString("Common", "Break", Edit5->Text);
 FastTagsIni->WriteString("Common", "BreakEnd", Edit6->Text);
 FastTagsIni->WriteString("Common", "Hyperlink", Edit7->Text);
 FastTagsIni->WriteString("Common", "HyperlinkEnd", Edit8->Text);
 FastTagsIni->WriteString("Common", "Image", Edit9->Text);
 FastTagsIni->WriteString("Common", "ImageEnd", Edit10->Text);
 FastTagsIni->WriteString("Common", "Rule", Edit11->Text);
 FastTagsIni->WriteString("Common", "RuleEnd", Edit12->Text);
 FastTagsIni->WriteString("Common", "Object", Edit13->Text);
 FastTagsIni->WriteString("Common", "ObjectEnd", Edit14->Text);
 FastTagsIni->WriteString("Common", "Meta", Edit15->Text);
 FastTagsIni->WriteString("Common", "MetaEnd", Edit16->Text);
 FastTagsIni->WriteString("Common", "List", Edit17->Text);
 FastTagsIni->WriteString("Common", "ListEnd", Edit18->Text);
 FastTagsIni->WriteString("Common", "ListItem", Edit19->Text);
 FastTagsIni->WriteString("Common", "ListItemEnd", Edit20->Text);

 FastTagsIni->WriteString("Additional", "eMail", Edit21->Text);
 FastTagsIni->WriteString("Additional", "eMailEnd", Edit22->Text);
 FastTagsIni->WriteString("Additional", "Anchor", Edit23->Text);
 FastTagsIni->WriteString("Additional", "AnchorEnd", Edit24->Text);
 FastTagsIni->WriteString("Additional", "FrameSet", Edit25->Text);
 FastTagsIni->WriteString("Additional", "FrameSetEnd", Edit26->Text);
 FastTagsIni->WriteString("Additional", "Frame", Edit27->Text);
 FastTagsIni->WriteString("Additional", "FrameEnd", Edit28->Text);
 FastTagsIni->WriteString("Additional", "IFrame", Edit29->Text);
 FastTagsIni->WriteString("Additional", "IFrameEnd", Edit30->Text);
 FastTagsIni->WriteString("Additional", "CSSDefinition", Edit31->Text);
 FastTagsIni->WriteString("Additional", "CSSDefinitionEnd", Edit32->Text);

 FastTagsIni->WriteString("Format", "Font", Edit33->Text);
 FastTagsIni->WriteString("Format", "FontEnd", Edit34->Text);
 FastTagsIni->WriteString("Format", "FastFormat", Edit35->Text);
 FastTagsIni->WriteString("Format", "FastFormatEnd", Edit36->Text);
 FastTagsIni->WriteString("Format", "Bold", Edit37->Text);
 FastTagsIni->WriteString("Format", "BoldEnd", Edit38->Text);
 FastTagsIni->WriteString("Format", "Italic", Edit39->Text);
 FastTagsIni->WriteString("Format", "ItalicEnd", Edit40->Text);
 FastTagsIni->WriteString("Format", "Left", Edit41->Text);
 FastTagsIni->WriteString("Format", "LeftEnd", Edit42->Text);
 FastTagsIni->WriteString("Format", "Center", Edit43->Text);
 FastTagsIni->WriteString("Format", "CenterEnd", Edit44->Text);
 FastTagsIni->WriteString("Format", "Right", Edit45->Text);
 FastTagsIni->WriteString("Format", "RightEnd", Edit46->Text);
 FastTagsIni->WriteString("Format", "Justify", Edit47->Text);
 FastTagsIni->WriteString("Format", "JustifyEnd", Edit48->Text);

 FastTagsIni->WriteString("Tables", "Table", Edit49->Text);
 FastTagsIni->WriteString("Tables", "TableEnd", Edit50->Text);
 FastTagsIni->WriteString("Tables", "Row", Edit51->Text);
 FastTagsIni->WriteString("Tables", "RowEnd", Edit52->Text);
 FastTagsIni->WriteString("Tables", "Header", Edit53->Text);
 FastTagsIni->WriteString("Tables", "HeaderEnd", Edit54->Text);
 FastTagsIni->WriteString("Tables", "Data", Edit55->Text);
 FastTagsIni->WriteString("Tables", "DataEnd", Edit56->Text);
 FastTagsIni->WriteString("Tables", "Caption", Edit57->Text);
 FastTagsIni->WriteString("Tables", "CaptionEnd", Edit58->Text);

 FastTagsIni->WriteString("Forms", "Form", Edit59->Text);
 FastTagsIni->WriteString("Forms", "FormEnd", Edit60->Text);
 FastTagsIni->WriteString("Forms", "InputText", Edit61->Text);
 FastTagsIni->WriteString("Forms", "InputTextEnd", Edit62->Text);
 FastTagsIni->WriteString("Forms", "Textarea", Edit63->Text);
 FastTagsIni->WriteString("Forms", "TextareaEnd", Edit64->Text);
 FastTagsIni->WriteString("Forms", "Submit", Edit65->Text);
 FastTagsIni->WriteString("Forms", "SubmitEnd", Edit66->Text);
 FastTagsIni->WriteString("Forms", "Password", Edit67->Text);
 FastTagsIni->WriteString("Forms", "PasswordEnd", Edit68->Text);
 FastTagsIni->WriteString("Forms", "Hidden", Edit69->Text);
 FastTagsIni->WriteString("Forms", "HiddenEnd", Edit70->Text);
 FastTagsIni->WriteString("Forms", "Checkbox", Edit71->Text);
 FastTagsIni->WriteString("Forms", "CheckboxEnd", Edit72->Text);
 FastTagsIni->WriteString("Forms", "Radiobutton", Edit73->Text);
 FastTagsIni->WriteString("Forms", "RadiobuttonEnd", Edit74->Text);
 FastTagsIni->WriteString("Forms", "Select", Edit75->Text);
 FastTagsIni->WriteString("Forms", "SelectEnd", Edit76->Text);
 FastTagsIni->WriteString("Forms", "Option", Edit77->Text);
 FastTagsIni->WriteString("Forms", "OptionEnd", Edit78->Text);
 FastTagsIni->WriteString("Forms", "Button", Edit79->Text);
 FastTagsIni->WriteString("Forms", "ButtonEnd", Edit80->Text);

 delete FastTagsIni;

 Close();
}
//---------------------------------------------------------------------------

