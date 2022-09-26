//---------------------------------------------------------------------------
#ifndef infoH
#define infoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "credits.hpp"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TInfoDialog : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TScrollingCredits *ScrollingCredits1;
        TLabel *Label1;
        TSpeedButton *SpeedButton1;
        TShape *Shape1;
        TShape *Shape2;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall Shape1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TInfoDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInfoDialog *InfoDialog;
//---------------------------------------------------------------------------
#endif
