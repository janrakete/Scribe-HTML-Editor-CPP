//---------------------------------------------------------------------------
#ifndef welcomeH
#define welcomeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TWillkommen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TShape *Shape2;
        TLabel *Label1;
        TLabel *Label2;
        TBevel *Bevel1;
        TLabel *Label10;
        TLabel *Label3;
        TLabel *Label4;
        TBevel *Bevel2;
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label5;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TEdit *Edit4;
        TEdit *Edit3;
        TLabel *Label6;
        TShape *Shape3;
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TWillkommen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWillkommen *Willkommen;
//---------------------------------------------------------------------------
#endif
