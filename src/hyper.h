//---------------------------------------------------------------------------
#ifndef hyperH
#define hyperH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class THyperlink : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TEdit *Edit1;
        TTabSheet *EventsTabSheet;
        TPanel *Panel4;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TTabSheet *TabSheet2;
        TLabel *Label2;
        TEdit *CssStyle;
        TLabel *Label3;
        TEdit *CssID;
        TLabel *Label4;
        TEdit *CssClass;
        TLabel *Label5;
        TEdit *CssTitle;
        TSpeedButton *SpeedButton1;
        TLabel *Label6;
        TComboBox *ComboBox1;
        TSpeedButton *SpeedButton2;
        TBevel *Bevel1;
        TOpenDialog *OeffnenDialog;
        TLabel *Label7;
        TEdit *Edit2;
        TLabel *Label10;
        TBevel *Bevel2;
        TLabel *Pfeil;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall THyperlink(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THyperlink *Hyperlink;
//---------------------------------------------------------------------------
#endif
