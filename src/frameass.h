//---------------------------------------------------------------------------
#ifndef frameassH
#define frameassH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFrameAssistent : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
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
        TOpenDialog *OeffnenDialog1;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TTabSheet *TabSheet5;
        TLabel *Label7;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton5;
        TSpeedButton *SpeedButton6;
        TPanel *Panel8;
        TPanel *Panel2;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Source1;
        TEdit *Name1;
        TBevel *Bevel2;
        TImage *Image1;
        TPanel *Panel3;
        TImage *Image2;
        TPanel *Panel4;
        TImage *Image3;
        TImage *UrImage2;
        TImage *UrImage1;
        TImage *UrImage3;
        TImage *UrImage4;
        TSpeedButton *SpeedButton7;
        TOpenDialog *OeffnenDialog2;
        TOpenDialog *OeffnenDialog3;
        TBevel *Bevel1;
        TBevel *Bevel3;
        TLabel *LabelMass1;
        TComboBox *ComboMass1;
        TUpDown *Mass1;
        TEdit *Edit5;
        TLabel *Label1;
        TComboBox *ComboScrollbalken1;
        TLabel *Label6;
        TCheckBox *CheckUnveraenderbar1;
        TBevel *Bevel4;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label14;
        TUpDown *Rand1;
        TEdit *Edit3;
        TCheckBox *CheckRand1;
        TBevel *Bevel5;
        TLabel *Label13;
        TUpDown *LinksRechts1;
        TEdit *Edit1;
        TCheckBox *CheckAbstandLinks1;
        TLabel *Label15;
        TUpDown *ObenUnten1;
        TEdit *Edit2;
        TCheckBox *CheckAbstandOben1;
        TEdit *Source2;
        TLabel *Label16;
        TSpeedButton *SpeedButton2;
        TEdit *Name2;
        TLabel *Label17;
        TBevel *Bevel6;
        TLabel *LabelMass2;
        TEdit *Edit7;
        TUpDown *Mass2;
        TComboBox *ComboMass2;
        TBevel *Bevel7;
        TComboBox *ComboScrollbalken2;
        TLabel *Label19;
        TLabel *Label20;
        TCheckBox *CheckUnveraenderbar2;
        TLabel *Label21;
        TUpDown *LinksRechts2;
        TEdit *Edit8;
        TCheckBox *CheckAbstandLinks2;
        TLabel *Label22;
        TLabel *Label23;
        TCheckBox *CheckAbstandOben2;
        TEdit *Edit9;
        TUpDown *ObenUnten2;
        TLabel *Label24;
        TLabel *Label25;
        TUpDown *Rand2;
        TEdit *Edit10;
        TCheckBox *CheckRand2;
        TLabel *Label26;
        TBevel *Bevel8;
        TEdit *Source3;
        TLabel *Label27;
        TSpeedButton *SpeedButton8;
        TEdit *Name3;
        TLabel *Label28;
        TBevel *Bevel9;
        TLabel *LabelMass3;
        TEdit *Edit13;
        TUpDown *Mass3;
        TComboBox *ComboMass3;
        TBevel *Bevel10;
        TComboBox *ComboScrollbalken3;
        TLabel *Label30;
        TLabel *Label31;
        TCheckBox *CheckUnveraenderbar3;
        TLabel *Label32;
        TUpDown *LinksRechts3;
        TEdit *Edit14;
        TCheckBox *CheckAbstandLinks3;
        TLabel *Label33;
        TLabel *Label34;
        TCheckBox *CheckAbstandOben3;
        TEdit *Edit15;
        TUpDown *ObenUnten3;
        TLabel *Label35;
        TLabel *Label36;
        TUpDown *Rand3;
        TEdit *Edit16;
        TCheckBox *CheckRand3;
        TLabel *Label37;
        TBevel *Bevel11;
        TLabel *Width;
        TLabel *Height;
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall SpeedButton7Click(TObject *Sender);
        void __fastcall ComboMass1Change(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall CheckAbstandLinks1Click(TObject *Sender);
        void __fastcall CheckAbstandOben1Click(TObject *Sender);
        void __fastcall CheckRand1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton8Click(TObject *Sender);
        void __fastcall ComboMass2Change(TObject *Sender);
        void __fastcall ComboMass3Change(TObject *Sender);
        void __fastcall CheckAbstandLinks2Click(TObject *Sender);
        void __fastcall CheckAbstandLinks3Click(TObject *Sender);
        void __fastcall CheckAbstandOben2Click(TObject *Sender);
        void __fastcall CheckAbstandOben3Click(TObject *Sender);
        void __fastcall CheckRand2Click(TObject *Sender);
        void __fastcall CheckRand3Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall PageControl1Change(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TFrameAssistent(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrameAssistent *FrameAssistent;
//---------------------------------------------------------------------------
#endif
