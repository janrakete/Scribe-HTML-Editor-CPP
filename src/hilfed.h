//---------------------------------------------------------------------------
#ifndef hilfedH
#define hilfedH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class THilfe : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TPanel *Panel1;
        TControlBar *ControlBar1;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        void __fastcall ToolButton3Click(TObject *Sender);
        void __fastcall ToolButton4Click(TObject *Sender);
        void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall THilfe(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THilfe *Hilfe;
//---------------------------------------------------------------------------
#endif
