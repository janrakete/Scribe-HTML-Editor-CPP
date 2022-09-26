//---------------------------------------------------------------------------
#ifndef grapviewH
#define grapviewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGrafikBetrachter : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TScrollBox *ScrollBox1;
        TImage *Image1;
        TShape *Shape1;
        TLabel *Filename;
        TLabel *Height;
        TLabel *Width;
        TLabel *Size;
        TBitBtn *BitBtn4;
        TLabel *AktuelleDatei;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TGrafikBetrachter(TComponent* Owner);
        void __fastcall ShowImage(String);
};
//---------------------------------------------------------------------------
extern PACKAGE TGrafikBetrachter *GrafikBetrachter;
//---------------------------------------------------------------------------
#endif
