//---------------------------------------------------------------------------
#ifndef addluniH
#define addluniH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAddLangUniDialog : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TAddLangUniDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAddLangUniDialog *AddLangUniDialog;
//---------------------------------------------------------------------------
#endif
