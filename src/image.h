//---------------------------------------------------------------------------
#ifndef imageH
#define imageH
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
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TGrafik : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TSpeedButton *SpeedButton2;
        TBevel *Bevel1;
        TEdit *Edit1;
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
        TTabSheet *EventsTabSheet;
        TPanel *Panel4;
        TLabel *Label7;
        TLabel *Label10;
        TBevel *Bevel2;
        TEdit *Edit2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Edit3;
        TEdit *Edit4;
        TLabel *Label6;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *Edit5;
        TCheckBox *CheckBox1;
        TComboBox *ComboBox1;
        TUpDown *UpDown1;
        TComboBox *ComboBox2;
        TUpDown *UpDown2;
        TEdit *Edit6;
        TCheckBox *CheckBox2;
        TLabel *Label13;
        TEdit *Edit7;
        TUpDown *UpDown3;
        TLabel *Label14;
        TSpeedButton *SpeedButton3;
        TOpenPictureDialog *OeffnenDialog;
        TScrollBox *ScrollBox1;
        TImage *Image1;
        TComboBox *ComboBox3;
        TLabel *Label15;
        TShape *Shape2;
        TShape *Shape3;
        TShape *Shape4;
        TShape *Shape5;
        TLabel *Pfeil;
        TBitBtn *BitBtn4;
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TGrafik(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGrafik *Grafik;
//---------------------------------------------------------------------------
#endif
