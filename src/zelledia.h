//---------------------------------------------------------------------------
#ifndef zellediaH
#define zellediaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TZelle : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBevel *Bevel1;
        TLabel *Label11;
        TLabel *Label12;
        TSpeedButton *SpeedButton4;
        TLabel *Label1;
        TBevel *Bevel2;
        TLabel *Label6;
        TLabel *Label7;
        TComboBox *ComboBox1;
        TComboBox *ComboBox2;
        TUpDown *UpDown2;
        TUpDown *UpDown1;
        TEdit *Edit5;
        TEdit *Edit6;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox3;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TTabSheet *TabSheet3;
        TPanel *Panel2;
        TLabel *Label8;
        TBevel *Bevel3;
        TLabel *Label9;
        TLabel *Label14;
        TLabel *Label10;
        TCheckBox *CheckBox4;
        TEdit *Edit7;
        TUpDown *UpDown3;
        TEdit *Edit1;
        TUpDown *UpDown4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TTabSheet *TabSheet2;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TSpeedButton *SpeedButton1;
        TEdit *CssStyle;
        TEdit *CssID;
        TEdit *CssClass;
        TEdit *CssTitle;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TColorDialog *ColorDialog1;
        TPanel *PPanel6;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall CheckBox5Click(TObject *Sender);
        void __fastcall CheckBox6Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TZelle(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TZelle *Zelle;
//---------------------------------------------------------------------------
#endif
