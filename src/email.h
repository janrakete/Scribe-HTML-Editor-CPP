//---------------------------------------------------------------------------
#ifndef emailH
#define emailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TEmailVerweis : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TEdit *Edit1;
        TTabSheet *TabSheet2;
        TPanel *Panel5;
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
        TCheckBox *CheckBox1;
        TLabel *Pfeil;
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TEmailVerweis(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEmailVerweis *EmailVerweis;
//---------------------------------------------------------------------------
#endif
