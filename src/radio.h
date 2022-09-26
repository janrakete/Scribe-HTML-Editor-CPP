//---------------------------------------------------------------------------
#ifndef radioH
#define radioH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TRadiobutton : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TPageControl *PageControl1;
        TTabSheet *TabSheet2;
        TTabSheet *EventsTab;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TTabSheet *TabSheet1;
        TShape *Shape1;
        TLabel *Pfeil;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TEdit *Edit1;
        TLabel *Label6;
        TEdit *Edit3;
        TLabel *Label1;
        TCheckBox *CheckBox1;
        TLabel *Label8;
        TEdit *Edit4;
        TLabel *Label9;
        TBevel *Bevel1;
        TEdit *CssStyle;
        TEdit *CssID;
        TEdit *CssClass;
        TEdit *CssTitle;
        TLabel *Label5;
        TLabel *Label4;
        TLabel *Label3;
        TLabel *Label2;
        TSpeedButton *SpeedButton1;
        TLabel *Label10;
        TBevel *Bevel2;
        TEdit *Edit2;
        TLabel *Label7;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TRadiobutton(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRadiobutton *Radiobutton;
//---------------------------------------------------------------------------
#endif
