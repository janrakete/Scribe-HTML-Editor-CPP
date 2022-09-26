//---------------------------------------------------------------------------
#ifndef absendenH
#define absendenH
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
//---------------------------------------------------------------------------
class TAbsendenZuruecksetzen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBevel *Bevel1;
        TLabel *Label1;
        TLabel *Label9;
        TEdit *Edit3;
        TEdit *Edit4;
        TTabSheet *TabSheet2;
        TPanel *Yeah;
        TTabSheet *EventsTabSheet;
        TPanel *Panel4;
        TLabel *Label7;
        TLabel *Label10;
        TBevel *Bevel2;
        TEdit *Edit2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TLabel *Label6;
        TComboBox *ComboBox1;
        TCheckBox *CheckBox1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TEdit *CssStyle;
        TSpeedButton *SpeedButton1;
        TEdit *CssClass;
        TLabel *Label4;
        TEdit *CssID;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label5;
        TEdit *CssTitle;
        TOpenPictureDialog *OeffnenDialog;
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TAbsendenZuruecksetzen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAbsendenZuruecksetzen *AbsendenZuruecksetzen;
//---------------------------------------------------------------------------
#endif
