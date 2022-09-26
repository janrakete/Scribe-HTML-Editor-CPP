//---------------------------------------------------------------------------
#ifndef tipodayH
#define tipodayH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TTippDesTages : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TMemo *TippMemo;
        TLabel *LineCounter;
        TLabel *Label2;
        TSpeedButton *SpeedButton1;
        TLabel *Label1;
        TCheckBox *CheckBox1;
        TShape *Shape2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TTippDesTages(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTippDesTages *TippDesTages;
//---------------------------------------------------------------------------
#endif
