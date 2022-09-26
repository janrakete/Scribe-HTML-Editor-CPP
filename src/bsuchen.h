//---------------------------------------------------------------------------
#ifndef bsuchenH
#define bsuchenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TBrowserSuchen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBevel *Bevel1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn1;
        TLabel *Label1;
        TListBox *Titel;
        TLabel *Label2;
        TListBox *List;
        TListBox *Pfad;
        TLabel *Label3;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TBrowserSuchen(TComponent* Owner);
        void __fastcall BrowserSearch(String, String, String, String);
};
//---------------------------------------------------------------------------
extern PACKAGE TBrowserSuchen *BrowserSuchen;
//---------------------------------------------------------------------------
#endif
