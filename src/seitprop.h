//---------------------------------------------------------------------------
#ifndef seitpropH
#define seitpropH
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
class TSeiteneigen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Label8;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TSpeedButton *SpeedButton2;
        TBevel *Bevel1;
        TLabel *Label6;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TSpeedButton *SpeedButton3;
        TLabel *Label15;
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
        TLabel *Label9;
        TEdit *Edit2;
        TEdit *Edit3;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TOpenPictureDialog *OeffnenDialog;
        TBitBtn *BitBtn3;
        TLabel *Pfeil;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton5;
        TSpeedButton *SpeedButton6;
        TSpeedButton *SpeedButton7;
        TSpeedButton *SpeedButton8;
        TPanel *Panel2;
        TColorDialog *ColorDialog1;
        TColorDialog *ColorDialog2;
        TColorDialog *ColorDialog3;
        TColorDialog *ColorDialog4;
        TColorDialog *ColorDialog5;
        TLabel *Label14;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TImage *Image1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall SpeedButton7Click(TObject *Sender);
        void __fastcall SpeedButton8Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TSeiteneigen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSeiteneigen *Seiteneigen;
//---------------------------------------------------------------------------
#endif
