//---------------------------------------------------------------------------
#ifndef optionsH
#define optionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include "Plusmemo.hpp"
#include <Graphics.hpp>
#include "Bffolder.h"
#include "ExtHilit.hpp"
//---------------------------------------------------------------------------
class TOptionen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TTabSheet *TabSheet5;
        TTabSheet *TabSheet6;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TLabel *Label1;
        TComboBox *ComboBox1;
        TLabel *Label2;
        TEdit *Edit1;
        TUpDown *UpDown1;
        TBevel *Bevel1;
        TCheckBox *CheckBox1;
        TLabel *Label4;
        TEdit *Edit2;
        TUpDown *UpDown2;
        TLabel *Label5;
        TBevel *Bevel2;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TBevel *Bevel3;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TEdit *Edit3;
        TEdit *Edit4;
        TBevel *Bevel4;
        TSpeedButton *SpeedButton1;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TEdit *Edit5;
        TSpeedButton *SpeedButton2;
        TEdit *Edit6;
        TBevel *Bevel5;
        TLabel *Label15;
        TLabel *Label16;
        TEdit *Edit7;
        TEdit *Edit8;
        TSpeedButton *SpeedButton3;
        TLabel *Label17;
        TLabel *Label21;
        TEdit *Edit9;
        TBevel *Bevel6;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label24;
        TLabel *Label25;
        TLabel *Label26;
        TEdit *Edit10;
        TEdit *Edit11;
        TEdit *Edit12;
        TEdit *Edit13;
        TEdit *Edit14;
        TLabel *Label27;
        TOpenDialog *OpenDialog1;
        TOpenDialog *OpenDialog2;
        TOpenDialog *OpenDialog3;
        TCheckBox *CheckBox12;
        TCheckBox *CheckBox13;
        TListBox *ListBox1;
        TPlusMemo *PlusMemo2;
        TComboBox *ComboBox5;
        TLabel *Label3;
        TComboBox *ComboBox2;
        TCheckBox *CheckBox5;
        TBevel *Bevel7;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *Edit15;
        TEdit *Edit16;
        TBevel *Bevel8;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton5;
        TBffolder *Bffolder1;
        TBffolder *Bffolder2;
        TLabel *Label8;
        TLabel *Label18;
        TComboBox *ComboBox3;
        TLabel *Label19;
        TUpDown *UpDown3;
        TEdit *Edit17;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox8;
        TBevel *Bevel10;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TBevel *Bevel11;
        TCheckBox *CheckBox11;
        TBevel *Bevel12;
        TCheckBox *CheckBox14;
        TListBox *XHTML;
        TListBox *JavaScript;
        TListBox *PHP;
        TListBox *CSS;
        TExtHighlighter *ExtHighlighter1;
        TExtHighlighter *ExtHighlighter2;
        TExtHighlighter *ExtHighlighter3;
        TExtHighlighter *ExtHighlighter4;
        TBevel *Bevel13;
        TSpeedButton *SpeedButton6;
        TColorDialog *ColorDialog1;
        TBevel *Bevel14;
        TCheckBox *CheckBox15;
        TCheckBox *CheckBox16;
        TEdit *Edit18;
        TCheckBox *CheckBox7;
        TLabel *Label20;
        TBevel *Bevel15;
        TBevel *Bevel9;
        TCheckBox *CheckBox17;
        TLabel *Label28;
        TSpeedButton *SpeedButton7;
        TColorDialog *ColorDialog2;
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall Bffolder1SelectionChanged(TObject *Sender,
          AnsiString NewSel);
        void __fastcall Bffolder2SelectionChanged(TObject *Sender,
          AnsiString NewSel);
        void __fastcall CheckBox7Click(TObject *Sender);
        void __fastcall ComboBox5Change(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall PlusMemo2Click(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall CheckBox12Click(TObject *Sender);
        void __fastcall CheckBox13Click(TObject *Sender);
        void __fastcall SpeedButton7Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TOptionen(TComponent* Owner);
        void __fastcall EditorColorCode();
        TColor temp_syntax_color_tags;
        TColor temp_syntax_color_attributes;
        TColor temp_syntax_color_links;
        TColor temp_syntax_color_linkattrs;
        TColor temp_syntax_color_comments;
        TColor temp_syntax_color_styles;
        TColor temp_syntax_color_styleattrs;
        TColor temp_syntax_color_stylecomments;
        TColor temp_syntax_color_javascript;
        TColor temp_syntax_color_tables;
        TColor temp_syntax_color_tableattrs;
        TColor temp_syntax_color_specialchars;
        TColor temp_syntax_color_php_area;
        TColor temp_syntax_color_php_comments;
        TColor temp_syntax_color_php_keywords;
        TColor temp_syntax_color_php_attrs;
        TColor temp_syntax_color_sql_functions;
        TColor temp_syntax_color_css_comments;
        TColor temp_syntax_color_css_strings;
        TColor temp_syntax_color_css_chars;
        TColor temp_syntax_color_css_tags;
        TColor temp_syntax_color_css_attrs;
        bool temp_syntax_bold_tags;
        bool temp_syntax_bold_attributes;
        bool temp_syntax_bold_links;
        bool temp_syntax_bold_linkattrs;
        bool temp_syntax_bold_comments;
        bool temp_syntax_bold_styles;
        bool temp_syntax_bold_styleattrs;
        bool temp_syntax_bold_stylecomments;
        bool temp_syntax_bold_javascript;
        bool temp_syntax_bold_tables;
        bool temp_syntax_bold_tableattrs;
        bool temp_syntax_bold_specialchars;
        bool temp_syntax_bold_php_area;
        bool temp_syntax_bold_php_comments;
        bool temp_syntax_bold_php_keywords;
        bool temp_syntax_bold_php_attrs;
        bool temp_syntax_bold_sql_functions;
        bool temp_syntax_bold_css_comments;
        bool temp_syntax_bold_css_strings;
        bool temp_syntax_bold_css_chars;
        bool temp_syntax_bold_css_tags;
        bool temp_syntax_bold_css_attrs;
        bool temp_syntax_italic_tags;
        bool temp_syntax_italic_attributes;
        bool temp_syntax_italic_links;
        bool temp_syntax_italic_linkattrs;
        bool temp_syntax_italic_comments;
        bool temp_syntax_italic_styles;
        bool temp_syntax_italic_styleattrs;
        bool temp_syntax_italic_stylecomments;
        bool temp_syntax_italic_javascript;
        bool temp_syntax_italic_tables;
        bool temp_syntax_italic_tableattrs;
        bool temp_syntax_italic_specialchars;
        bool temp_syntax_italic_php_area;
        bool temp_syntax_italic_php_comments;
        bool temp_syntax_italic_php_keywords;
        bool temp_syntax_italic_php_attrs;
        bool temp_syntax_italic_sql_functions;
        bool temp_syntax_italic_css_comments;
        bool temp_syntax_italic_css_strings;
        bool temp_syntax_italic_css_chars;
        bool temp_syntax_italic_css_tags;
        bool temp_syntax_italic_css_attrs;
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionen *Optionen;
//---------------------------------------------------------------------------
#endif
