//---------------------------------------------------------------------------
#ifndef openinetH
#define openinetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TOeffnenausdemInternet : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TComboBox *ComboBox1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TShape *Shape1;
        TLabel *Pfeil;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall ComboBox1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall BitBtn3Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TOeffnenausdemInternet(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOeffnenausdemInternet *OeffnenausdemInternet;
//---------------------------------------------------------------------------
#endif
