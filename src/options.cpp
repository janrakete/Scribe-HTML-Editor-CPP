//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "options.h"
#include "child.h"
#include "hilfed.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Plusmemo"
#pragma link "Bffolder"
#pragma link "ExtHilit"
#pragma resource "*.dfm"
TOptionen *Optionen;

//---------------------------
// Eigene Funktionen - Anfang
//---------------------------
void __fastcall TOptionen::EditorColorCode()
{
 //---------------------
 // Coloriert die Syntax
 //---------------------
 TWordOptions Worter;
 TExtFontStyles Styles;
 ExtHighlighter1->StartStopKeys->Clear();
 ExtHighlighter1->Keywords->Clear();
 ExtHighlighter2->StartStopKeys->Clear();
 ExtHighlighter2->Keywords->Clear();
 ExtHighlighter3->StartStopKeys->Clear();
 ExtHighlighter3->Keywords->Clear();
 ExtHighlighter4->StartStopKeys->Clear();
 ExtHighlighter4->Keywords->Clear();

 if (temp_syntax_bold_links)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_links)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter1->StartStopKeys->AddExStartStopKey("<a", ">", Worter, Styles, 3, 0, 1, crDefault, PlusMemo2->Color, temp_syntax_color_links, true);
 ExtHighlighter1->StartStopKeys->AddExStartStopKey("</a", ">", Worter, Styles, 4, 0, 1, crDefault, PlusMemo2->Color, temp_syntax_color_links, true);

 if (temp_syntax_bold_linkattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_linkattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter1->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 5, 3, 1, crDefault, PlusMemo2->Color, temp_syntax_color_linkattrs, true);

 if (temp_syntax_bold_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter1->StartStopKeys->AddExStartStopKey("<!--", "-->", Worter, Styles, 6, 0, 1, crDefault, PlusMemo2->Color, temp_syntax_color_comments, false);

 if (temp_syntax_bold_specialchars)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_specialchars)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter1->StartStopKeys->AddExStartStopKey("&", ";", Worter, Styles, 7, 0, 1, crDefault, PlusMemo2->Color, temp_syntax_color_specialchars, true);

 if (temp_syntax_bold_tables)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_tables)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter1->StartStopKeys->AddExStartStopKey("<table", ">", Worter, Styles, 12, 0, 1, crDefault, PlusMemo2->Color, temp_syntax_color_tables, true);

 if (temp_syntax_bold_tableattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_tableattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter1->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 13, 12, 1, crDefault, PlusMemo2->Color, temp_syntax_color_tableattrs, true);

 if (temp_syntax_bold_tags)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_tags)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter1->StartStopKeys->AddExStartStopKey("<", ">", Worter, Styles, 1, 0, 0, crDefault, PlusMemo2->Color, temp_syntax_color_tags, true);

 if (temp_syntax_bold_attributes)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_attributes)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter1->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 2, 1, 0, crDefault, PlusMemo2->Color, temp_syntax_color_attributes, true);

 if (temp_syntax_bold_styles)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_styles)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter2->StartStopKeys->AddExStartStopKey("<script", "</script>", Worter, Styles, 8, 0, 1, crDefault, PlusMemo2->Color, temp_syntax_color_styles, false);

 if (temp_syntax_bold_styleattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_styleattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter2->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 9, 8, 1, crDefault, PlusMemo2->Color, temp_syntax_color_styleattrs, true);

 if (temp_syntax_bold_stylecomments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_stylecomments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter2->StartStopKeys->AddExStartStopKey("<!--", "-->", Worter, Styles, 10, 8, 1, crDefault, PlusMemo2->Color, temp_syntax_color_stylecomments, false);

 if (temp_syntax_bold_javascript)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_javascript)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter2->Keywords->AddExtKeyWord("function", TWordOptions(), Styles, 112, 10, 0, crDefault, PlusMemo2->Color, temp_syntax_color_javascript);

 if (temp_syntax_bold_php_area)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_php_area)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter3->StartStopKeys->AddExStartStopKey("<?", "?>", Worter, Styles, 61, 0, 0, crDefault, PlusMemo2->Color, temp_syntax_color_php_area, false);

 if (temp_syntax_bold_php_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_php_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter3->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 62, 61, 0, crDefault, PlusMemo2->Color, temp_syntax_color_php_comments, false);
 ExtHighlighter3->StartStopKeys->AddExStartStopKey("//", "", Worter, Styles, 62, 61, 0, crDefault, PlusMemo2->Color, temp_syntax_color_php_comments, true);

 if (temp_syntax_bold_php_keywords)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_php_keywords)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter3->Keywords->AddExtKeyWord("if", TWordOptions() << woWholeWordsOnly << woMatchCase, Styles, 63, 61, 0, crDefault, PlusMemo2->Color, temp_syntax_color_php_keywords);

 if (temp_syntax_bold_sql_functions)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_sql_functions)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter3->Keywords->AddExtKeyWord("mysql_connect", TWordOptions() << woMatchCase, Styles, 66, 61, 0, crDefault, PlusMemo2->Color, temp_syntax_color_sql_functions);

 if (temp_syntax_bold_php_attrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_php_attrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter3->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 67, 61, 0, crDefault, PlusMemo2->Color, temp_syntax_color_php_attrs, true);

 if (temp_syntax_bold_css_attrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_css_attrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter4->StartStopKeys->AddExStartStopKey("{", "}", Worter, Styles, 1, 0, 0, crDefault, PlusMemo2->Color, temp_syntax_color_css_attrs, false);

 if (temp_syntax_bold_css_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_css_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter4->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 2, 0, 1, crDefault, PlusMemo2->Color, temp_syntax_color_css_comments, false);

 if (temp_syntax_bold_css_chars)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_css_chars)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter4->Keywords->AddExtKeyWord("{", TWordOptions(), Styles, 3, 1, 1, crDefault, PlusMemo2->Color, temp_syntax_color_css_chars);
 ExtHighlighter4->Keywords->AddExtKeyWord("}", TWordOptions(), Styles, 4, 1, 1, crDefault, PlusMemo2->Color, temp_syntax_color_css_chars);
 ExtHighlighter4->Keywords->AddExtKeyWord(";", TWordOptions(), Styles, 5, 1, 1, crDefault, PlusMemo2->Color, temp_syntax_color_css_chars);
 ExtHighlighter4->Keywords->AddExtKeyWord(":", TWordOptions(), Styles, 6, 1, 1, crDefault, PlusMemo2->Color, temp_syntax_color_css_chars);

 if (temp_syntax_bold_css_strings)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_css_strings)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter4->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 7, 1, 2, crDefault, PlusMemo2->Color, temp_syntax_color_css_strings, true);

 if (temp_syntax_bold_css_tags)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (temp_syntax_italic_css_tags)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 ExtHighlighter4->Keywords->AddExtKeyWord("div", TWordOptions(), Styles, 8, 0, 0, crDefault, PlusMemo2->Color, temp_syntax_color_css_tags);

 PlusMemo2->ReApplyKeywords();
}
//-------------------------
// Eigene Funktionen - Ende
//-------------------------
//---------------------------------------------------------------------------

__fastcall TOptionen::TOptionen(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOptionen::BitBtn3Click(TObject *Sender)
{
 Hauptformular->HelpShow(this, "dialog_options.html", true);
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::BitBtn1Click(TObject *Sender)
{
 Hauptformular->standard_template = ComboBox2->Text;
 Hauptformular->editor_font_face = ComboBox1->Text;
 Hauptformular->editor_font_size = UpDown1->Position;
 Hauptformular->textarea_convert_special_chars = CheckBox3->Checked;
 Hauptformular->textarea_tabstops = UpDown2->Position;
 Hauptformular->textarea_save_files_in_unix = CheckBox1->Checked;
 Hauptformular->textarea_print_plaintext = CheckBox2->Checked;
 Hauptformular->editor_xhtml_mode = CheckBox4->Checked;

 Hauptformular->browser_path_1 = Edit3->Text;
 Hauptformular->browser_desc_1 = Edit4->Text;
 Hauptformular->browser_path_2 = Edit5->Text;
 Hauptformular->browser_desc_2 = Edit6->Text;
 Hauptformular->browser_path_3 = Edit7->Text;
 Hauptformular->browser_desc_3 = Edit8->Text;

 Hauptformular->documents_extension = Edit9->Text;
 Hauptformular->docfile_extensions = Edit10->Text;
 Hauptformular->graphicfile_extensions = Edit11->Text;
 Hauptformular->multimediafile_extensions = Edit12->Text;
 Hauptformular->cssfile_extensions = Edit13->Text;
 Hauptformular->javascriptfile_extensions = Edit14->Text;

 Hauptformular->editor_file_at_start = CheckBox5->Checked;
 Hauptformular->includes_dir = Edit16->Text;
 Hauptformular->help_size = UpDown3->Position;
 Hauptformular->help_dock_window = CheckBox6->Checked;
 if (ComboBox3->ItemIndex == 0)
  Hauptformular->help_align == "top";
 else if (ComboBox3->ItemIndex == 1)
  Hauptformular->help_align = "right";
 else if (ComboBox3->ItemIndex == 2)
  Hauptformular->help_align = "bottom";
 else if (ComboBox3->ItemIndex == 3)
  Hauptformular->help_align = "left";

 Hauptformular->localhost_use = CheckBox7->Checked;
 String last_char = Edit18->Text.AnsiLastChar();
 if (last_char == "/")
  Hauptformular->localhost_adress = Edit18->Text;
 else
  Hauptformular->localhost_adress = Edit18->Text + "/";
 Hauptformular->editor_show_tip = CheckBox8->Checked;
 Hauptformular->tag_auto_complete = CheckBox9->Checked;
 Hauptformular->tag_automatic_position = CheckBox10->Checked;
 Hauptformular->directftp_connect_at_start = CheckBox11->Checked;
 Hauptformular->use_topstyle = CheckBox14->Checked;
 Hauptformular->directftp_show_menue = CheckBox16->Checked;

 if (CheckBox17->Checked)
  Hauptformular->directftp_check_connection = false;
 else
  Hauptformular->directftp_check_connection = true;

 if (CheckBox15->Checked)
  Hauptformular->browser_confirm_save = false;
 else
  Hauptformular->browser_confirm_save = true;

 String temp_project = Edit15->Text;
 TIniFile* Einstellungen = new TIniFile(Hauptformular->program_dir + "Storage!\\settings.ini");
 Einstellungen->WriteString("Others", "ProjectDir", temp_project);
 delete Einstellungen;
 if (Hauptformular->project_dir == temp_project)
  1 == 1;
 else
  Application->MessageBox(Hauptformular->SprachenWaehler->GetString(84).c_str(), "Scribe!", MB_OK + MB_DEFBUTTON1 + MB_ICONINFORMATION);

 Hauptformular->editor_background_color = PlusMemo2->Color;

 Hauptformular->syntax_color_tags = temp_syntax_color_tags;
 Hauptformular->syntax_color_attributes = temp_syntax_color_attributes;
 Hauptformular->syntax_color_links = temp_syntax_color_links;
 Hauptformular->syntax_color_linkattrs = temp_syntax_color_linkattrs;
 Hauptformular->syntax_color_comments = temp_syntax_color_comments;
 Hauptformular->syntax_color_styles = temp_syntax_color_styles;
 Hauptformular->syntax_color_styleattrs = temp_syntax_color_styleattrs;
 Hauptformular->syntax_color_stylecomments = temp_syntax_color_stylecomments;
 Hauptformular->syntax_color_javascript = temp_syntax_color_javascript;
 Hauptformular->syntax_color_tables = temp_syntax_color_tables;
 Hauptformular->syntax_color_tableattrs = temp_syntax_color_tableattrs;
 Hauptformular->syntax_color_specialchars = temp_syntax_color_specialchars;
 Hauptformular->syntax_color_php_area = temp_syntax_color_php_area;
 Hauptformular->syntax_color_php_comments = temp_syntax_color_php_comments;
 Hauptformular->syntax_color_php_keywords = temp_syntax_color_php_keywords;
 Hauptformular->syntax_color_php_attrs = temp_syntax_color_php_attrs;
 Hauptformular->syntax_color_sql_functions = temp_syntax_color_sql_functions;
 Hauptformular->syntax_color_css_comments = temp_syntax_color_css_comments;
 Hauptformular->syntax_color_css_strings = temp_syntax_color_css_strings;
 Hauptformular->syntax_color_css_chars = temp_syntax_color_css_chars;
 Hauptformular->syntax_color_css_tags = temp_syntax_color_css_tags;
 Hauptformular->syntax_color_css_attrs = temp_syntax_color_css_attrs;
 Hauptformular->syntax_bold_tags = temp_syntax_bold_tags;
 Hauptformular->syntax_bold_attributes = temp_syntax_bold_attributes;
 Hauptformular->syntax_bold_links = temp_syntax_bold_links;
 Hauptformular->syntax_bold_linkattrs = temp_syntax_bold_linkattrs;
 Hauptformular->syntax_bold_comments = temp_syntax_bold_comments;
 Hauptformular->syntax_bold_styles = temp_syntax_bold_styles;
 Hauptformular->syntax_bold_styleattrs = temp_syntax_bold_styleattrs;
 Hauptformular->syntax_bold_stylecomments = temp_syntax_bold_stylecomments;
 Hauptformular->syntax_bold_javascript = temp_syntax_bold_javascript;
 Hauptformular->syntax_bold_tables = temp_syntax_bold_tables;
 Hauptformular->syntax_bold_tableattrs = temp_syntax_bold_tableattrs;
 Hauptformular->syntax_bold_specialchars = temp_syntax_bold_specialchars;
 Hauptformular->syntax_bold_php_area = temp_syntax_bold_php_area;
 Hauptformular->syntax_bold_php_comments = temp_syntax_bold_php_comments;
 Hauptformular->syntax_bold_php_keywords = temp_syntax_bold_php_keywords;
 Hauptformular->syntax_bold_php_attrs = temp_syntax_bold_php_attrs;
 Hauptformular->syntax_bold_sql_functions = temp_syntax_bold_sql_functions;
 Hauptformular->syntax_bold_css_comments = temp_syntax_bold_css_comments;
 Hauptformular->syntax_bold_css_strings = temp_syntax_bold_css_strings;
 Hauptformular->syntax_bold_css_chars = temp_syntax_bold_css_chars;
 Hauptformular->syntax_bold_css_tags = temp_syntax_bold_css_tags;
 Hauptformular->syntax_bold_css_attrs = temp_syntax_bold_css_attrs;
 Hauptformular->syntax_italic_tags = temp_syntax_italic_tags;
 Hauptformular->syntax_italic_attributes = temp_syntax_italic_attributes;
 Hauptformular->syntax_italic_links = temp_syntax_italic_links;
 Hauptformular->syntax_italic_linkattrs = temp_syntax_italic_linkattrs;
 Hauptformular->syntax_italic_comments = temp_syntax_italic_comments;
 Hauptformular->syntax_italic_styles = temp_syntax_italic_styles;
 Hauptformular->syntax_italic_styleattrs = temp_syntax_italic_styleattrs;
 Hauptformular->syntax_italic_stylecomments = temp_syntax_italic_stylecomments;
 Hauptformular->syntax_italic_javascript = temp_syntax_italic_javascript;
 Hauptformular->syntax_italic_tables = temp_syntax_italic_tables;
 Hauptformular->syntax_italic_tableattrs = temp_syntax_italic_tableattrs;
 Hauptformular->syntax_italic_specialchars = temp_syntax_italic_specialchars;
 Hauptformular->syntax_italic_php_area = temp_syntax_italic_php_area;
 Hauptformular->syntax_italic_php_comments = temp_syntax_italic_php_comments;
 Hauptformular->syntax_italic_php_keywords = temp_syntax_italic_php_keywords;
 Hauptformular->syntax_italic_php_attrs = temp_syntax_italic_php_attrs;
 Hauptformular->syntax_italic_sql_functions = temp_syntax_italic_sql_functions;
 Hauptformular->syntax_italic_css_comments = temp_syntax_italic_css_comments;
 Hauptformular->syntax_italic_css_strings = temp_syntax_italic_css_strings;
 Hauptformular->syntax_italic_css_chars = temp_syntax_italic_css_chars;
 Hauptformular->syntax_italic_css_tags = temp_syntax_italic_css_tags;
 Hauptformular->syntax_italic_css_attrs = temp_syntax_italic_css_attrs;

 // Schema aufbauen
 TWordOptions Worter;
 TExtFontStyles Styles;
 Hauptformular->TextfeldHighlighter->StartStopKeys->Clear();
 Hauptformular->TextfeldHighlighter->Keywords->Clear();

 if (Hauptformular->syntax_bold_links)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_links)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<a", ">", Worter, Styles, 3, 0, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_links, true);
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("</a", ">", Worter, Styles, 4, 0, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_links, true);

 if (Hauptformular->syntax_bold_linkattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_linkattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 5, 3, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_linkattrs, true);

 if (Hauptformular->syntax_bold_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<!--", "-->", Worter, Styles, 6, 0, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_comments, false);

 if (Hauptformular->syntax_bold_specialchars)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_specialchars)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("&", ";", Worter, Styles, 7, 0, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_specialchars, true);

 if (Hauptformular->syntax_bold_styles)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_styles)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<script", "</script>", Worter, Styles, 8, 0, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_styles, false);

 if (Hauptformular->syntax_bold_styleattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_styleattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 9, 8, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_styleattrs, true);

 if (Hauptformular->syntax_bold_stylecomments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_stylecomments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<!--", "-->", Worter, Styles, 10, 8, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_stylecomments, false);

 if (Hauptformular->syntax_bold_styles)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_styles)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<style", "</style>", Worter, Styles, 14, 0, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_styles, false);

 if (Hauptformular->syntax_bold_styleattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_styleattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 15, 14, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_styleattrs, true);

 if (Hauptformular->syntax_bold_css_tags)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_css_tags)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<!--", "-->", Worter, Styles, 16, 14, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_css_tags, false);

 if (Hauptformular->syntax_bold_css_attrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_css_attrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("{", "}", Worter, Styles, 81, 16, 0, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_css_attrs, false);

 if (Hauptformular->syntax_bold_css_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_css_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 82, 16, 2, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_css_comments, false);

 if (Hauptformular->syntax_bold_css_chars)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_css_chars)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord("{", TWordOptions(), Styles, 83, 81, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_css_chars);
 Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord("}", TWordOptions(), Styles, 84, 81, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_css_chars);
 Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord(";", TWordOptions(), Styles, 85, 81, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_css_chars);
 Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord(":", TWordOptions(), Styles, 86, 81, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_css_chars);

 if (Hauptformular->syntax_bold_css_strings)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_css_strings)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 87, 81, 2, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_css_strings, true);

 if (Hauptformular->syntax_bold_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 23, 10, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_comments, true);
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 24, 16, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_comments, true);

 Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord("{", Worter, TExtFontStyles() << fsBold, 17, 14, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_styles);
 Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord("}", Worter, TExtFontStyles() << fsBold, 17, 14, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_styles);
 Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord("{", Worter, TExtFontStyles() << fsBold, 18, 16, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_stylecomments);
 Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord("}", Worter, TExtFontStyles() << fsBold, 18, 16, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_stylecomments);

 if (Hauptformular->syntax_bold_tables)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_tables)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 for (int i = 0; i < Hauptformular->TabellenSyntax->Items->Count; i++)
  Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey(Hauptformular->TabellenSyntax->Items->Strings[i], ">", Worter, Styles, 12, 0, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_tables, true);

 if (Hauptformular->syntax_bold_tableattrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_tableattrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 13, 12, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_tableattrs, true);

 if (Hauptformular->syntax_bold_javascript)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_javascript)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 for (int i = 0; i < Hauptformular->JavaScriptSyntax->Items->Count; i++)
  Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord(Hauptformular->JavaScriptSyntax->Items->Strings[i], TWordOptions() << woWholeWordsOnly << woMatchCase, Styles, 11, 10, 0, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_javascript);

 if (Hauptformular->syntax_bold_php_area)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_php_area)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<?", "?>", Worter, Styles, 61, 0, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_php_area, false);

 if (Hauptformular->syntax_bold_php_comments)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_php_comments)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("/*", "*/", Worter, Styles, 62, 61, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_php_comments, false);
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("//", "", Worter, Styles, 62, 61, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_php_comments, true);

 if (Hauptformular->syntax_bold_php_keywords)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_php_keywords)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 for (int i = 0; i < Hauptformular->PHPKeywordsSyntax->Items->Count; i++)
  Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord(Hauptformular->PHPKeywordsSyntax->Items->Strings[i], TWordOptions() << woWholeWordsOnly << woMatchCase, Styles, 63, 61, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_php_keywords);

 if (Hauptformular->syntax_bold_sql_functions)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_sql_functions)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 for (int i = 0; i < Hauptformular->MySQLSyntax->Items->Count; i++)
  Hauptformular->TextfeldHighlighter->Keywords->AddExtKeyWord(Hauptformular->MySQLSyntax->Items->Strings[i], TWordOptions() << woWholeWordsOnly << woMatchCase, Styles, 66, 61, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_sql_functions);

 if (Hauptformular->syntax_bold_php_attrs)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_php_attrs)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 67, 61, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_php_attrs, true);
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("'", "'", Worter, Styles, 71, 61, 1, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_php_attrs, true);

 if (Hauptformular->syntax_bold_tags)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_tags)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("<", ">", Worter, Styles, 1, 0, 0, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_tags, true);

 if (Hauptformular->syntax_bold_attributes)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_attributes)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\"", "\"", Worter, Styles, 2, 1, 0, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_attributes, true);

 if (Hauptformular->syntax_bold_attributes)
  Styles << fsBold;
 else
  Styles >> fsBold;
 if (Hauptformular->syntax_italic_attributes)
  Styles << fsItalic;
 else
  Styles >> fsItalic;
 Hauptformular->TextfeldHighlighter->StartStopKeys->AddExStartStopKey("\\\"", "\\\"", Worter, Styles, 352, 1, 0, crDefault, PlusMemo2->Color, Hauptformular->syntax_color_attributes, true);

 int mdis_count = Hauptformular->MDIChildCount;
 for (int i = 0; i < mdis_count; i++)
  Hauptformular->MDIChildren[i]->OnShow(Sender);

 Hauptformular->FileFillList(Hauptformular->DateimanagerTemp, Hauptformular->DateimanagerListe);
 Hauptformular->FileFillList(Hauptformular->ProjektmanagerTemp, Hauptformular->ProjekteListe);
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::FormClose(TObject *Sender, TCloseAction &Action)
{
 if ((Hilfe->Visible) && (!Hilfe->ControlBar1->Visible))
  Hilfe->Close();
 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::FormShow(TObject *Sender)
{
 Hauptformular->TempDateilistBox->Directory = Hauptformular->program_dir + "Storage!\\Templates";
 Hauptformular->TempDateilistBox->Mask = "*.sct";
 Hauptformular->TempDateilistBox->Update();

 for (int i = 0; i < Hauptformular->TempDateilistBox->Items->Count; i++)
  ComboBox2->Items->Add(Hauptformular->ReplaceString(Hauptformular->TempDateilistBox->Items->Strings[i], ".sct", "", false, true));
 ComboBox2->Text = Hauptformular->standard_template;

 ComboBox1->Items = Screen->Fonts;
 ComboBox1->Text = Hauptformular->editor_font_face;
 UpDown1->Position = Hauptformular->editor_font_size;
 CheckBox3->Checked = Hauptformular->textarea_convert_special_chars;
 UpDown2->Position = Hauptformular->textarea_tabstops;
 CheckBox1->Checked = Hauptformular->textarea_save_files_in_unix;
 CheckBox2->Checked = Hauptformular->textarea_print_plaintext;
 CheckBox4->Checked = Hauptformular->editor_xhtml_mode;

 Edit3->Text = Hauptformular->browser_path_1;
 Edit4->Text = Hauptformular->browser_desc_1;
 Edit5->Text = Hauptformular->browser_path_2;
 Edit6->Text = Hauptformular->browser_desc_2;
 Edit7->Text = Hauptformular->browser_path_3;
 Edit8->Text = Hauptformular->browser_desc_3;

 Edit9->Text = Hauptformular->documents_extension;
 Edit10->Text = Hauptformular->docfile_extensions;
 Edit11->Text = Hauptformular->graphicfile_extensions;
 Edit12->Text = Hauptformular->multimediafile_extensions;
 Edit13->Text = Hauptformular->cssfile_extensions;
 Edit14->Text = Hauptformular->javascriptfile_extensions;

 CheckBox5->Checked = Hauptformular->editor_file_at_start;
 Edit15->Text = Hauptformular->project_dir;
 Edit16->Text = Hauptformular->includes_dir;
 UpDown3->Position = Hauptformular->help_size;
 CheckBox6->Checked = Hauptformular->help_dock_window;
 if (Hauptformular->help_align == "top")
  ComboBox3->ItemIndex = 0;
 else if (Hauptformular->help_align == "right")
  ComboBox3->ItemIndex = 1;
 else if (Hauptformular->help_align == "bottom")
  ComboBox3->ItemIndex = 2;
 else if (Hauptformular->help_align == "left")
  ComboBox3->ItemIndex = 3;

 CheckBox7->Checked = Hauptformular->localhost_use;
 Edit18->Text = Hauptformular->localhost_adress;
 CheckBox8->Checked = Hauptformular->editor_show_tip;
 CheckBox9->Checked = Hauptformular->tag_auto_complete;
 CheckBox10->Checked = Hauptformular->tag_automatic_position;
 CheckBox11->Checked = Hauptformular->directftp_connect_at_start;
 CheckBox14->Checked = Hauptformular->use_topstyle;
 CheckBox16->Checked = Hauptformular->directftp_show_menue;

 if (Hauptformular->directftp_check_connection)
  CheckBox17->Checked = false;
 else
  CheckBox17->Checked = true;

 if (Hauptformular->browser_confirm_save)
  CheckBox15->Checked = false;
 else
  CheckBox15->Checked = true;

 PlusMemo2->Color = Hauptformular->editor_background_color;
 Hauptformular->ColorAssignColorToButton(SpeedButton7, Hauptformular->editor_background_color, ColorDialog2);

 temp_syntax_color_tags = Hauptformular->syntax_color_tags;
 temp_syntax_color_attributes = Hauptformular->syntax_color_attributes;
 temp_syntax_color_links = Hauptformular->syntax_color_links;
 temp_syntax_color_linkattrs = Hauptformular->syntax_color_linkattrs;
 temp_syntax_color_comments = Hauptformular->syntax_color_comments;
 temp_syntax_color_styles = Hauptformular->syntax_color_styles;
 temp_syntax_color_styleattrs = Hauptformular->syntax_color_styleattrs;
 temp_syntax_color_stylecomments = Hauptformular->syntax_color_stylecomments;
 temp_syntax_color_javascript = Hauptformular->syntax_color_javascript;
 temp_syntax_color_tables = Hauptformular->syntax_color_tables;
 temp_syntax_color_tableattrs = Hauptformular->syntax_color_tableattrs;
 temp_syntax_color_specialchars = Hauptformular->syntax_color_specialchars;
 temp_syntax_color_php_area = Hauptformular->syntax_color_php_area;
 temp_syntax_color_php_comments = Hauptformular->syntax_color_php_comments;
 temp_syntax_color_php_keywords = Hauptformular->syntax_color_php_keywords;
 temp_syntax_color_php_attrs = Hauptformular->syntax_color_php_attrs;
 temp_syntax_color_sql_functions = Hauptformular->syntax_color_sql_functions;
 temp_syntax_color_css_comments = Hauptformular->syntax_color_css_comments;
 temp_syntax_color_css_strings = Hauptformular->syntax_color_css_strings;
 temp_syntax_color_css_chars = Hauptformular->syntax_color_css_chars;
 temp_syntax_color_css_tags = Hauptformular->syntax_color_css_tags;
 temp_syntax_color_css_attrs = Hauptformular->syntax_color_css_attrs;
 temp_syntax_bold_tags = Hauptformular->syntax_bold_tags;
 temp_syntax_bold_attributes = Hauptformular->syntax_bold_attributes;
 temp_syntax_bold_links = Hauptformular->syntax_bold_links;
 temp_syntax_bold_linkattrs = Hauptformular->syntax_bold_linkattrs;
 temp_syntax_bold_comments = Hauptformular->syntax_bold_comments;
 temp_syntax_bold_styles = Hauptformular->syntax_bold_styles;
 temp_syntax_bold_styleattrs = Hauptformular->syntax_bold_styleattrs;
 temp_syntax_bold_stylecomments = Hauptformular->syntax_bold_stylecomments;
 temp_syntax_bold_javascript = Hauptformular->syntax_bold_javascript;
 temp_syntax_bold_tables = Hauptformular->syntax_bold_tables;
 temp_syntax_bold_tableattrs = Hauptformular->syntax_bold_tableattrs;
 temp_syntax_bold_specialchars = Hauptformular->syntax_bold_specialchars;
 temp_syntax_bold_php_area = Hauptformular->syntax_bold_php_area;
 temp_syntax_bold_php_comments = Hauptformular->syntax_bold_php_comments;
 temp_syntax_bold_php_keywords = Hauptformular->syntax_bold_php_keywords;
 temp_syntax_bold_php_attrs = Hauptformular->syntax_bold_php_attrs;
 temp_syntax_bold_sql_functions = Hauptformular->syntax_bold_sql_functions;
 temp_syntax_bold_css_comments = Hauptformular->syntax_bold_css_comments;
 temp_syntax_bold_css_strings = Hauptformular->syntax_bold_css_strings;
 temp_syntax_bold_css_chars = Hauptformular->syntax_bold_css_chars;
 temp_syntax_bold_css_tags = Hauptformular->syntax_bold_css_tags;
 temp_syntax_bold_css_attrs = Hauptformular->syntax_bold_css_attrs;
 temp_syntax_italic_tags = Hauptformular->syntax_italic_tags;
 temp_syntax_italic_attributes = Hauptformular->syntax_italic_attributes;
 temp_syntax_italic_links = Hauptformular->syntax_italic_links;
 temp_syntax_italic_linkattrs = Hauptformular->syntax_italic_linkattrs;
 temp_syntax_italic_comments = Hauptformular->syntax_italic_comments;
 temp_syntax_italic_styles = Hauptformular->syntax_italic_styles;
 temp_syntax_italic_styleattrs = Hauptformular->syntax_italic_styleattrs;
 temp_syntax_italic_stylecomments = Hauptformular->syntax_italic_stylecomments;
 temp_syntax_italic_javascript = Hauptformular->syntax_italic_javascript;
 temp_syntax_italic_tables = Hauptformular->syntax_italic_tables;
 temp_syntax_italic_tableattrs = Hauptformular->syntax_italic_tableattrs;
 temp_syntax_italic_specialchars = Hauptformular->syntax_italic_specialchars;
 temp_syntax_italic_php_area = Hauptformular->syntax_italic_php_area;
 temp_syntax_italic_php_comments = Hauptformular->syntax_italic_php_comments;
 temp_syntax_italic_php_keywords = Hauptformular->syntax_italic_php_keywords;
 temp_syntax_italic_php_attrs = Hauptformular->syntax_italic_php_attrs;
 temp_syntax_italic_sql_functions = Hauptformular->syntax_italic_sql_functions;
 temp_syntax_italic_css_comments = Hauptformular->syntax_italic_css_comments;
 temp_syntax_italic_css_strings = Hauptformular->syntax_italic_css_strings;
 temp_syntax_italic_css_chars = Hauptformular->syntax_italic_css_chars;
 temp_syntax_italic_css_tags = Hauptformular->syntax_italic_css_tags;
 temp_syntax_italic_css_attrs = Hauptformular->syntax_italic_css_attrs;

 ComboBox5->ItemIndex = 0;
 ComboBox5Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::SpeedButton1Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(58);
 filter_temp = filter_temp + " (*.exe,*.bat,*.com)|*.exe;*.bat;*.com";
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OpenDialog1->Filter = filter_gesamt;
 OpenDialog1->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OpenDialog1->Execute())
 {
  Edit3->Text = OpenDialog1->FileName;
  Edit4->Text = ExtractFileName(OpenDialog1->FileName);
 }
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::SpeedButton2Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(58);
 filter_temp = filter_temp + " (*.exe,*.bat,*.com)|*.exe;*.bat;*.com";
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OpenDialog2->Filter = filter_gesamt;
 OpenDialog2->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OpenDialog2->Execute())
 {
  Edit5->Text = OpenDialog2->FileName;
  Edit6->Text = ExtractFileName(OpenDialog2->FileName);
 }
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::SpeedButton3Click(TObject *Sender)
{
 String filter_gesamt = "";
 String filter_temp = "";

 filter_temp = Hauptformular->SprachenWaehler->GetString(58);
 filter_temp = filter_temp + " (*.exe,*.bat,*.com)|*.exe;*.bat;*.com";
 filter_gesamt = filter_gesamt + filter_temp + "|";

 filter_temp = Hauptformular->SprachenWaehler->GetString(8);
 filter_temp = filter_temp + " (*.*)|*.*";
 filter_gesamt = filter_gesamt + filter_temp;

 OpenDialog3->Filter = filter_gesamt;
 OpenDialog3->Title = Hauptformular->ReplaceString(Hauptformular->ffnen1->Caption, "&", "", false, true);

 if (OpenDialog3->Execute())
 {
  Edit7->Text = OpenDialog3->FileName;
  Edit8->Text = ExtractFileName(OpenDialog3->FileName);
 }
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::SpeedButton5Click(TObject *Sender)
{
 Bffolder2->Caption = Hauptformular->SprachenWaehler->GetString(69);
 Bffolder2->Title = Hauptformular->SprachenWaehler->GetString(70);
 Bffolder2->SelectedDir = Edit16->Text;
 if (Bffolder2->Execute())
  Edit16->Text = Bffolder2->SelectedDir + "\\";
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::SpeedButton4Click(TObject *Sender)
{
 Bffolder1->Caption = Hauptformular->SprachenWaehler->GetString(69);
 Bffolder1->Title = Hauptformular->SprachenWaehler->GetString(70);
 Bffolder1->SelectedDir = Edit15->Text;
 if (Bffolder1->Execute())
  Edit15->Text = Bffolder1->SelectedDir + "\\";
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::Bffolder1SelectionChanged(TObject *Sender,
      AnsiString NewSel)
{
 Bffolder1->StatusText = NewSel;        
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::Bffolder2SelectionChanged(TObject *Sender,
      AnsiString NewSel)
{
 Bffolder2->StatusText = NewSel;        
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::CheckBox7Click(TObject *Sender)
{
 if (CheckBox7->Checked)
 {
  Edit18->Color = clWindow;
  Edit18->Enabled = true;
 }
 else
 {
  Edit18->Color = clBtnFace;
  Edit18->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::ComboBox5Change(TObject *Sender)
{
 if (ComboBox5->ItemIndex == 0)
 {
  PlusMemo2->Lines->Clear();
  PlusMemo2->Lines->Strings[0] = Hauptformular->ReplaceString(Hauptformular->SprachenWaehler->GetString(85), "$T", "\r\n", true, false);
  PlusMemo2->Highlighter = ExtHighlighter1;
  ListBox1->Items = XHTML->Items;
  EditorColorCode();
 }
 else if (ComboBox5->ItemIndex == 1)
 {
  PlusMemo2->Lines->Clear();
  PlusMemo2->Lines->Strings[0] = Hauptformular->ReplaceString(Hauptformular->SprachenWaehler->GetString(86), "$T", "\r\n", true, false);
  PlusMemo2->Highlighter = ExtHighlighter2;
  ListBox1->Items = JavaScript->Items;
  EditorColorCode();
 }
 else if (ComboBox5->ItemIndex == 2)
 {
  PlusMemo2->Lines->Clear();
  PlusMemo2->Lines->Strings[0] = Hauptformular->ReplaceString(Hauptformular->SprachenWaehler->GetString(87), "$T", "\r\n", true, false);
  PlusMemo2->Highlighter = ExtHighlighter3;
  ListBox1->Items = PHP->Items;
  EditorColorCode();
 }
 else if (ComboBox5->ItemIndex == 3)
 {
  PlusMemo2->Lines->Clear();
  PlusMemo2->Lines->Strings[0] = Hauptformular->ReplaceString(Hauptformular->SprachenWaehler->GetString(88), "$T", "\r\n", true, false);
  PlusMemo2->Highlighter = ExtHighlighter4;
  ListBox1->Items = CSS->Items;
  EditorColorCode();
 }
}
//---------------------------------------------------------------------------


void __fastcall TOptionen::SpeedButton6Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog1);
 if (ColorDialog1->Execute())
 {
  Hauptformular->ColorButton(SpeedButton6, ColorDialog1->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog1);

  if (ComboBox5->ItemIndex == 0)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_color_tags = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_color_attributes = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_color_links = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_color_linkattrs = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_color_tables = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 5)
    temp_syntax_color_tableattrs = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 6)
    temp_syntax_color_comments = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 7)
    temp_syntax_color_specialchars = ColorDialog1->Color;
  }
  else if (ComboBox5->ItemIndex == 1)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_color_styles = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_color_styleattrs = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_color_stylecomments = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_color_javascript = ColorDialog1->Color;
  }
  else if (ComboBox5->ItemIndex == 2)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_color_php_area = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_color_php_comments = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_color_php_keywords = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_color_php_attrs = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_color_sql_functions = ColorDialog1->Color;
  }
  else if (ComboBox5->ItemIndex == 3)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_color_css_chars = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_color_css_strings = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_color_css_comments = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_color_css_attrs = ColorDialog1->Color;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_color_css_tags = ColorDialog1->Color;
  }
  EditorColorCode();
 }
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::PlusMemo2Click(TObject *Sender)
{
 if (ComboBox5->ItemIndex == 0)
 {
  if (PlusMemo2->SelStart >= 0 && PlusMemo2->SelStart <= 18)
   ListBox1->ItemIndex = 6;
  else if (PlusMemo2->SelStart >= 20 && PlusMemo2->SelStart <= 29)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 30 && PlusMemo2->SelStart <= 34)
   ListBox1->ItemIndex = 1;
  else if (PlusMemo2->SelStart >= 35 && PlusMemo2->SelStart <= 36)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 38 && PlusMemo2->SelStart <= 56)
   ListBox1->ItemIndex = 4;
  else if (PlusMemo2->SelStart >= 57 && PlusMemo2->SelStart <= 64)
   ListBox1->ItemIndex = 5;
  else if (PlusMemo2->SelStart >= 65 && PlusMemo2->SelStart <= 66)
   ListBox1->ItemIndex = 4;
  else if (PlusMemo2->SelStart >= 68 && PlusMemo2->SelStart <= 76)
   ListBox1->ItemIndex = 2;
  else if (PlusMemo2->SelStart >= 77 && PlusMemo2->SelStart <= 86)
   ListBox1->ItemIndex = 3;
  else if (PlusMemo2->SelStart >= 87 && PlusMemo2->SelStart <= 88)
   ListBox1->ItemIndex = 2;
  else if (PlusMemo2->SelStart >= 90 && PlusMemo2->SelStart <= 96)
   ListBox1->ItemIndex = 7;
 }
 else if (ComboBox5->ItemIndex == 1)
 {
  if (PlusMemo2->SelStart >= 0 && PlusMemo2->SelStart <= 17)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 18 && PlusMemo2->SelStart <= 28)
   ListBox1->ItemIndex = 1;
  else if (PlusMemo2->SelStart >= 29 && PlusMemo2->SelStart <= 30)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 32 && PlusMemo2->SelStart <= 37)
   ListBox1->ItemIndex = 2;
  else if (PlusMemo2->SelStart >= 38 && PlusMemo2->SelStart <= 44)
   ListBox1->ItemIndex = 3;
  else if (PlusMemo2->SelStart >= 45 && PlusMemo2->SelStart <= 54)
   ListBox1->ItemIndex = 2;
  else if (PlusMemo2->SelStart >= 56 && PlusMemo2->SelStart <= 65)
   ListBox1->ItemIndex = 0;
 }
 else if (ComboBox5->ItemIndex == 2)
 {
  if (PlusMemo2->SelStart >= 0 && PlusMemo2->SelStart <= 5)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 75 && PlusMemo2->SelStart <= 80)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 45 && PlusMemo2->SelStart <= 53)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart == 27)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 7 && PlusMemo2->SelStart <= 22)
   ListBox1->ItemIndex = 1;
  else if (PlusMemo2->SelStart >= 24 && PlusMemo2->SelStart <= 26)
   ListBox1->ItemIndex = 2;
  else if (PlusMemo2->SelStart >= 28 && PlusMemo2->SelStart <= 34)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 54 && PlusMemo2->SelStart <= 66)
   ListBox1->ItemIndex = 4;
  else if (PlusMemo2->SelStart >= 35 && PlusMemo2->SelStart <= 44)
   ListBox1->ItemIndex = 3;
  else if (PlusMemo2->SelStart >= 67 && PlusMemo2->SelStart <= 74)
   ListBox1->ItemIndex = 3;
 }
 else if (ComboBox5->ItemIndex == 3)
 {
  if (PlusMemo2->SelStart >= 0 && PlusMemo2->SelStart <= 15)
   ListBox1->ItemIndex = 2;
  else if (PlusMemo2->SelStart >= 21 && PlusMemo2->SelStart <= 22)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 33 && PlusMemo2->SelStart <= 34)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 40 && PlusMemo2->SelStart <= 41)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 60 && PlusMemo2->SelStart <= 61)
   ListBox1->ItemIndex = 0;
  else if (PlusMemo2->SelStart >= 72 && PlusMemo2->SelStart <= 73)
   ListBox1->ItemIndex = 0;
  else  if (PlusMemo2->SelStart >= 62 && PlusMemo2->SelStart <= 71)
   ListBox1->ItemIndex = 1;
  else  if (PlusMemo2->SelStart >= 17 && PlusMemo2->SelStart <= 20)
   ListBox1->ItemIndex = 4;
  else  if (PlusMemo2->SelStart >= 23 && PlusMemo2->SelStart <= 32)
   ListBox1->ItemIndex = 3;
  else  if (PlusMemo2->SelStart >= 35 && PlusMemo2->SelStart <= 39)
   ListBox1->ItemIndex = 3;
  else  if (PlusMemo2->SelStart >= 49 && PlusMemo2->SelStart <= 59)
   ListBox1->ItemIndex = 3;
 }
 ListBox1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::ListBox1Click(TObject *Sender)
{
 if (ListBox1->ItemIndex > - 1)
 {
  if (ComboBox5->ItemIndex == 0)
  {
   if (ListBox1->ItemIndex == 0)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_tags, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_tags;
    CheckBox13->Checked = temp_syntax_italic_tags;
   }
   else if (ListBox1->ItemIndex == 1)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_attributes, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_attributes;
    CheckBox13->Checked = temp_syntax_italic_attributes;
   }
   else if (ListBox1->ItemIndex == 2)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_links, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_links;
    CheckBox13->Checked = temp_syntax_italic_links;
   }
   else if (ListBox1->ItemIndex == 3)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_linkattrs, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_linkattrs;
    CheckBox13->Checked = temp_syntax_italic_linkattrs;
   }
   else if (ListBox1->ItemIndex == 4)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_tables, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_tables;
    CheckBox13->Checked = temp_syntax_italic_tables;
   }
   else if (ListBox1->ItemIndex == 5)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_tableattrs, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_tableattrs;
    CheckBox13->Checked = temp_syntax_italic_tableattrs;
   }
   else if (ListBox1->ItemIndex == 6)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_comments, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_comments;
    CheckBox13->Checked = temp_syntax_italic_comments;
   }
   else if (ListBox1->ItemIndex == 7)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_specialchars, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_specialchars;
    CheckBox13->Checked = temp_syntax_italic_specialchars;
   }
  }
  else if (ComboBox5->ItemIndex == 1)
  {
   if (ListBox1->ItemIndex == 0)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_styles, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_styles;
    CheckBox13->Checked = temp_syntax_italic_styles;
   }
   else if (ListBox1->ItemIndex == 1)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_styleattrs, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_styleattrs;
    CheckBox13->Checked = temp_syntax_italic_styleattrs;
   }
   else if (ListBox1->ItemIndex == 2)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_stylecomments, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_stylecomments;
    CheckBox13->Checked = temp_syntax_italic_stylecomments;
   }
   else if (ListBox1->ItemIndex == 3)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_javascript, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_javascript;
    CheckBox13->Checked = temp_syntax_italic_javascript;
   }
  }
  else if (ComboBox5->ItemIndex == 2)
  {
   if (ListBox1->ItemIndex == 0)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_php_area, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_php_area;
    CheckBox13->Checked = temp_syntax_italic_php_area;
   }
   else if (ListBox1->ItemIndex == 1)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_php_comments, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_php_comments;
    CheckBox13->Checked = temp_syntax_italic_php_comments;
   }
   else if (ListBox1->ItemIndex == 2)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_php_keywords, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_php_keywords;
    CheckBox13->Checked = temp_syntax_italic_php_keywords;
   }
   else if (ListBox1->ItemIndex == 3)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_php_attrs, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_php_attrs;
    CheckBox13->Checked = temp_syntax_italic_php_attrs;
   }
   else if (ListBox1->ItemIndex == 4)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_sql_functions, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_sql_functions;
    CheckBox13->Checked = temp_syntax_italic_sql_functions;
   }
  }
  else if (ComboBox5->ItemIndex == 3)
  {
   if (ListBox1->ItemIndex == 0)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_css_chars, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_css_chars;
    CheckBox13->Checked = temp_syntax_italic_css_chars;
   }
   else if (ListBox1->ItemIndex == 1)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_css_strings, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_css_strings;
    CheckBox13->Checked = temp_syntax_italic_css_strings;
   }
   else if (ListBox1->ItemIndex == 2)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_css_comments, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_css_comments;
    CheckBox13->Checked = temp_syntax_italic_css_comments;
   }
   else if (ListBox1->ItemIndex == 3)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_css_attrs, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_css_attrs;
    CheckBox13->Checked = temp_syntax_italic_css_attrs;
   }
   else if (ListBox1->ItemIndex == 4)
   {
    Hauptformular->ColorAssignColorToButton(SpeedButton6, temp_syntax_color_css_tags, ColorDialog1);
    CheckBox12->Checked = temp_syntax_bold_css_tags;
    CheckBox13->Checked = temp_syntax_italic_css_tags;
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::CheckBox12Click(TObject *Sender)
{
 if (ComboBox5->ItemIndex == 0)
 {
  if (CheckBox12->Checked)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_bold_tags = true;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_bold_attributes = true;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_bold_links = true;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_bold_linkattrs = true;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_bold_tables = true;
   else if (ListBox1->ItemIndex == 5)
    temp_syntax_bold_tableattrs = true;
   else if (ListBox1->ItemIndex == 6)
    temp_syntax_bold_comments = true;
   else if (ListBox1->ItemIndex == 7)
    temp_syntax_bold_specialchars = true;
  }
  else
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_bold_tags = false;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_bold_attributes = false;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_bold_links = false;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_bold_linkattrs = false;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_bold_tables = false;
   else if (ListBox1->ItemIndex == 5)
    temp_syntax_bold_tableattrs = false;
   else if (ListBox1->ItemIndex == 6)
    temp_syntax_bold_comments = false;
   else if (ListBox1->ItemIndex == 7)
    temp_syntax_bold_specialchars = false;
  }
 }
 else if (ComboBox5->ItemIndex == 1)
 {
  if (CheckBox12->Checked)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_bold_styles = true;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_bold_styleattrs = true;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_bold_stylecomments = true;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_bold_javascript = true;
  }
  else
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_bold_styles = false;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_bold_styleattrs = false;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_bold_stylecomments = false;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_bold_javascript = false;
  }
 }
 else if (ComboBox5->ItemIndex == 2)
 {
  if (CheckBox12->Checked)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_bold_php_area = true;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_bold_php_comments = true;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_bold_php_keywords = true;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_bold_php_attrs = true;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_bold_sql_functions = true;
  }
  else
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_bold_php_area = false;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_bold_php_comments = false;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_bold_php_keywords = false;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_bold_php_attrs = false;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_bold_sql_functions = false;
  }
 }
 else if (ComboBox5->ItemIndex == 3)
 {
  if (CheckBox12->Checked)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_bold_css_chars = true;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_bold_css_strings = true;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_bold_css_comments = true;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_bold_css_attrs = true;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_bold_css_tags = true;
  }
  else
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_bold_css_chars = false;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_bold_css_strings = false;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_bold_css_comments = false;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_bold_css_attrs = false;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_bold_css_tags = false;
  }
 }
 EditorColorCode();
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::CheckBox13Click(TObject *Sender)
{
 if (ComboBox5->ItemIndex == 0)
 {
  if (CheckBox13->Checked)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_italic_tags = true;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_italic_attributes = true;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_italic_links = true;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_italic_linkattrs = true;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_italic_tables = true;
   else if (ListBox1->ItemIndex == 5)
    temp_syntax_italic_tableattrs = true;
   else if (ListBox1->ItemIndex == 6)
    temp_syntax_italic_comments = true;
   else if (ListBox1->ItemIndex == 7)
    temp_syntax_italic_specialchars = true;
  }
  else
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_italic_tags = false;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_italic_attributes = false;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_italic_links = false;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_italic_linkattrs = false;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_italic_tables = false;
   else if (ListBox1->ItemIndex == 5)
    temp_syntax_italic_tableattrs = false;
   else if (ListBox1->ItemIndex == 6)
    temp_syntax_italic_comments = false;
   else if (ListBox1->ItemIndex == 7)
    temp_syntax_italic_specialchars = false;
  }
 }
 else if (ComboBox5->ItemIndex == 1)
 {
  if (CheckBox13->Checked)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_italic_styles = true;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_italic_styleattrs = true;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_italic_stylecomments = true;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_italic_javascript = true;
  }
  else
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_italic_styles = false;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_italic_styleattrs = false;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_italic_stylecomments = false;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_italic_javascript = false;
  }
 }
 else if (ComboBox5->ItemIndex == 2)
 {
  if (CheckBox13->Checked)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_italic_php_area = true;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_italic_php_comments = true;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_italic_php_keywords = true;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_italic_php_attrs = true;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_italic_sql_functions = true;
  }
  else
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_italic_php_area = false;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_italic_php_comments = false;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_italic_php_keywords = false;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_italic_php_attrs = false;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_italic_sql_functions = false;
  }
 }
 else if (ComboBox5->ItemIndex == 3)
 {
  if (CheckBox13->Checked)
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_italic_css_chars = true;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_italic_css_strings = true;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_italic_css_comments = true;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_italic_css_attrs = true;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_italic_css_tags = true;
  }
  else
  {
   if (ListBox1->ItemIndex == 0)
    temp_syntax_italic_css_chars = false;
   else if (ListBox1->ItemIndex == 1)
    temp_syntax_italic_css_strings = false;
   else if (ListBox1->ItemIndex == 2)
    temp_syntax_italic_css_comments = false;
   else if (ListBox1->ItemIndex == 3)
    temp_syntax_italic_css_attrs = false;
   else if (ListBox1->ItemIndex == 4)
    temp_syntax_italic_css_tags = false;
  }
 }
 EditorColorCode();
}
//---------------------------------------------------------------------------

void __fastcall TOptionen::SpeedButton7Click(TObject *Sender)
{
 Hauptformular->ColorSetUserDefined(ColorDialog2);
 if (ColorDialog2->Execute())
 {
  Hauptformular->ColorButton(SpeedButton7, ColorDialog2->Color);
  Hauptformular->ColorReadUserDefined(ColorDialog2);
  PlusMemo2->Color = ColorDialog2->Color;
  EditorColorCode();
 }
}
//---------------------------------------------------------------------------

