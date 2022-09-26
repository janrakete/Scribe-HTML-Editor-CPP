//---------------------------------------------------------------------------
#ifndef frameberH
#define frameberH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrameBereich : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label6;
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
        TPanel *Panel5;
        TLabel *Label8;
        TEdit *Edit3;
        TBevel *Bevel1;
        TEdit *Edit1;
        TComboBox *ComboBox1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TFrameBereich(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrameBereich *FrameBereich;
//---------------------------------------------------------------------------
#endif
