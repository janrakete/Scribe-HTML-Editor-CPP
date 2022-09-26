//---------------------------------------------------------------------------
#ifndef includeH
#define includeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TIncludeDatei : public TForm
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
        TListView *ListView1;
        TToolBar *ToolBar2;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TListBox *Verzeichnisse;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ListView1Click(TObject *Sender);
        void __fastcall ToolButton4Click(TObject *Sender);
        void __fastcall ToolButton5Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TIncludeDatei(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TIncludeDatei *IncludeDatei;
//---------------------------------------------------------------------------
#endif
