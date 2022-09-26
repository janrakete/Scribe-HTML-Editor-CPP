//---------------------------------------------------------------------------
#ifndef tableH
#define tableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TTabelle : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label12;
        TLabel *Label15;
        TBevel *Bevel2;
        TLabel *Label7;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TLabel *Label8;
        TSpeedButton *SpeedButton4;
        TCheckBox *CheckBox2;
        TEdit *Edit6;
        TUpDown *UpDown2;
        TComboBox *ComboBox2;
        TComboBox *ComboBox3;
        TEdit *Edit2;
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
        TOpenPictureDialog *OeffnenDialog;
        TTabSheet *TabSheet3;
        TPanel *Panel2;
        TEdit *Edit3;
        TUpDown *UpDown4;
        TLabel *Label14;
        TLabel *Label9;
        TUpDown *UpDown5;
        TEdit *Edit4;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox1;
        TLabel *Label13;
        TLabel *Label11;
        TLabel *Label16;
        TCheckBox *CheckBox4;
        TEdit *Edit5;
        TUpDown *UpDown6;
        TLabel *Label10;
        TBevel *Bevel1;
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall CheckBox4Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TTabelle(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTabelle *Tabelle;
//---------------------------------------------------------------------------
#endif
