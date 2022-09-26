//---------------------------------------------------------------------------
#ifndef zeilediaH
#define zeilediaH
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
class TZeile : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TBevel *Bevel1;
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
        TLabel *Pfeil;
        TBitBtn *BitBtn3;
        TLabel *Label6;
        TLabel *Label7;
        TComboBox *ComboBox3;
        TComboBox *ComboBox1;
        TCheckBox *CheckBox3;
        TSpeedButton *SpeedButton4;
        TColorDialog *ColorDialog1;
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TZeile(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TZeile *Zeile;
//---------------------------------------------------------------------------
#endif
