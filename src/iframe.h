//---------------------------------------------------------------------------
#ifndef iframeH
#define iframeH
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
class TEingebettetesFrame : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBevel *Bevel1;
        TSpeedButton *SpeedButton7;
        TLabel *Label1;
        TLabel *Label11;
        TEdit *Source1;
        TEdit *Name1;
        TTabSheet *TabSheet3;
        TPanel *Panel2;
        TLabel *Label13;
        TLabel *Label10;
        TLabel *Label15;
        TLabel *Label8;
        TLabel *Label14;
        TLabel *Label12;
        TBevel *Bevel2;
        TUpDown *LinksRechts1;
        TEdit *Edit1;
        TCheckBox *CheckAbstandLinks1;
        TUpDown *ObenUnten1;
        TEdit *Edit2;
        TCheckBox *CheckAbstandOben1;
        TUpDown *Rand1;
        TEdit *Edit3;
        TCheckBox *CheckRand1;
        TTabSheet *TabSheet2;
        TPanel *Panel6;
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
        TOpenDialog *OeffnenDialog;
        TComboBox *ComboScrollbalken1;
        TLabel *Label6;
        TComboBox *ComboBox1;
        TLabel *Label7;
        TLabel *Label9;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TUpDown *UpDown2;
        TEdit *Edit6;
        TUpDown *UpDown1;
        TEdit *Edit5;
        TComboBox *ComboBox2;
        TBevel *Bevel3;
        TBevel *Bevel4;
        TComboBox *ComboBox3;
        TLabel *Label16;
        void __fastcall SpeedButton7Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall CheckRand1Click(TObject *Sender);
        void __fastcall CheckAbstandLinks1Click(TObject *Sender);
        void __fastcall CheckAbstandOben1Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TEingebettetesFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEingebettetesFrame *EingebettetesFrame;
//---------------------------------------------------------------------------
#endif
