//---------------------------------------------------------------------------
#ifndef tablewizH
#define tablewizH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TTabellenAssistent : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBevel *Bevel1;
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
        TLabel *Label1;
        TLabel *Label6;
        TUpDown *UpDown3;
        TEdit *Edit7;
        TUpDown *UpDown1;
        TEdit *Edit1;
        TCheckBox *CheckBox2;
        TLabel *Label12;
        TEdit *Edit6;
        TUpDown *UpDown2;
        TComboBox *ComboBox2;
        TComboBox *ComboBox3;
        TLabel *Label15;
        TBevel *Bevel2;
        TLabel *Label7;
        TEdit *Edit2;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TLabel *Label8;
        TSpeedButton *SpeedButton4;
        TColorDialog *ColorDialog1;
        TOpenPictureDialog *OeffnenDialog;
        TBevel *Bevel3;
        TLabel *Label14;
        TUpDown *UpDown4;
        TEdit *Edit3;
        TLabel *Label13;
        TCheckBox *CheckBox1;
        TLabel *Label9;
        TUpDown *UpDown5;
        TEdit *Edit4;
        TCheckBox *CheckBox3;
        TLabel *Label10;
        TUpDown *UpDown6;
        TEdit *Edit5;
        TCheckBox *CheckBox4;
        TLabel *Label11;
        TLabel *Label16;
        TTabSheet *TabSheet3;
        TPanel *Panel2;
        TPanel *Panel3;
        TStringGrid *StringGrid1;
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall CheckBox4Click(TObject *Sender);
        void __fastcall Edit7Change(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TTabellenAssistent(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTabellenAssistent *TabellenAssistent;
//---------------------------------------------------------------------------
#endif
