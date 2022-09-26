//---------------------------------------------------------------------------
#ifndef multimH
#define multimH
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
class TMultimedia : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Label8;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TSpeedButton *SpeedButton2;
        TBevel *Bevel1;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *Edit1;
        TEdit *Edit5;
        TCheckBox *CheckBox1;
        TComboBox *ComboBox1;
        TUpDown *UpDown1;
        TComboBox *ComboBox2;
        TUpDown *UpDown2;
        TEdit *Edit6;
        TCheckBox *CheckBox2;
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
        TOpenDialog *OeffnenDialog;
        TEdit *Edit2;
        TBevel *Bevel2;
        TLabel *Label6;
        TComboBox *ComboBox4;
        TLabel *Label7;
        TTabSheet *TabSheet3;
        TPanel *Panel2;
        TUpDown *UpDown3;
        TComboBox *ComboBox3;
        TLabel *Label14;
        TEdit *Edit7;
        TLabel *Label13;
        TLabel *Label15;
        TBevel *Bevel3;
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TMultimedia(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMultimedia *Multimedia;
//---------------------------------------------------------------------------
#endif
