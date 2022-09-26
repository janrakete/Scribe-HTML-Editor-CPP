//---------------------------------------------------------------------------
#ifndef ftppassH
#define ftppassH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TDirektesFTPPasswort : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TEdit *Edit1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TLabel *Label2;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TDirektesFTPPasswort(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDirektesFTPPasswort *DirektesFTPPasswort;
//---------------------------------------------------------------------------
#endif
