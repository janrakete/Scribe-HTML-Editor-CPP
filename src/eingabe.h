//---------------------------------------------------------------------------
#ifndef eingabeH
#define eingabeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TEingabefeld : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBevel *Bevel1;
        TLabel *Label1;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Edit3;
        TCheckBox *CheckBox1;
        TEdit *Edit4;
        TTabSheet *TabSheet2;
        TPanel *Yeah;
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
        TEdit *Edit5;
        TLabel *Label11;
        TUpDown *UpDown1;
        TEdit *Edit1;
        TCheckBox *CheckBox2;
        TUpDown *UpDown2;
        TEdit *Edit6;
        TCheckBox *CheckBox3;
        TLabel *Label6;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TBevel *Bevel3;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TEingabefeld(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEingabefeld *Eingabefeld;
//---------------------------------------------------------------------------
#endif
