//---------------------------------------------------------------------------
#ifndef ibrowseH
#define ibrowseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TInternerBrowser : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TPanel *Panel1;
        TControlBar *ControlBar1;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TToolButton *ToolButton6;
        TStatusBar *StatusBar1;
        TToolBar *ToolBar2;
        TToolButton *ToolButton7;
        TPopupMenu *PopupMenu1;
        TMenuItem *N640x4801;
        TMenuItem *N800x6001;
        TMenuItem *N1024x7681;
        TLabel *Ursprung;
        TMenuItem *N320x2401;
        TToolButton *ToolButton8;
        TToolButton *ToolButton9;
        TOpenDialog *OeffnenDialog;
        TEdit *Edit1;
        TToolButton *ToolButton10;
        TToolButton *ToolButton11;
        TActionList *ShortCutDummy;
        TAction *Action1;
        TAction *Action2;
        void __fastcall ToolButton5Click(TObject *Sender);
        void __fastcall ToolButton6Click(TObject *Sender);
        void __fastcall N640x4801Click(TObject *Sender);
        void __fastcall N800x6001Click(TObject *Sender);
        void __fastcall N1024x7681Click(TObject *Sender);
        void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall N320x2401Click(TObject *Sender);
        void __fastcall ToolButton9Click(TObject *Sender);
        void __fastcall ToolButton3Click(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ToolButton11Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Action1Execute(TObject *Sender);
        void __fastcall Action2Execute(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TInternerBrowser(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInternerBrowser *InternerBrowser;
//---------------------------------------------------------------------------
#endif
