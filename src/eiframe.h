//---------------------------------------------------------------------------
#ifndef eiframeH
#define eiframeH
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
class TEinzelnerFrame : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBevel *Bevel1;
        TTabSheet *TabSheet3;
        TPanel *Panel2;
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
        TPanel *Panel6;
        TEdit *Source1;
        TSpeedButton *SpeedButton7;
        TEdit *Name1;
        TLabel *Label1;
        TComboBox *ComboScrollbalken1;
        TLabel *Label6;
        TLabel *Label7;
        TCheckBox *CheckUnveraenderbar1;
        TLabel *Label11;
        TLabel *Label13;
        TUpDown *LinksRechts1;
        TEdit *Edit1;
        TCheckBox *CheckAbstandLinks1;
        TLabel *Label10;
        TLabel *Label15;
        TUpDown *ObenUnten1;
        TEdit *Edit2;
        TCheckBox *CheckAbstandOben1;
        TLabel *Label8;
        TLabel *Label14;
        TUpDown *Rand1;
        TEdit *Edit3;
        TCheckBox *CheckRand1;
        TLabel *Label12;
        TBevel *Bevel2;
        TOpenDialog *OeffnenDialog;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall CheckRand1Click(TObject *Sender);
        void __fastcall CheckAbstandLinks1Click(TObject *Sender);
        void __fastcall CheckAbstandOben1Click(TObject *Sender);
        void __fastcall SpeedButton7Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TEinzelnerFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEinzelnerFrame *EinzelnerFrame;
//---------------------------------------------------------------------------
#endif
