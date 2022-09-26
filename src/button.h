//---------------------------------------------------------------------------
#ifndef buttonH
#define buttonH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "Plusmemo.hpp"
//---------------------------------------------------------------------------
class TButtonx : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TBevel *Bevel1;
        TLabel *Label2;
        TEdit *Edit2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TPanel *Panel2;
        TListView *ButtonxListe;
        TPopupMenu *PopupMenu1;
        TMenuItem *Lschen1;
        TPlusMemo *PlusMemo1;
        TLabel *Pfeil;
        TPopupMenu *PopupMenu2;
        TMenuItem *Ausschneiden2;
        TMenuItem *Kopieren2;
        TMenuItem *Einfgen2;
        TMenuItem *Lschen2;
        TMenuItem *N1;
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall ButtonxListeClick(TObject *Sender);
        void __fastcall Lschen1Click(TObject *Sender);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall PopupMenu2Popup(TObject *Sender);
        void __fastcall Ausschneiden2Click(TObject *Sender);
        void __fastcall Kopieren2Click(TObject *Sender);
        void __fastcall Einfgen2Click(TObject *Sender);
        void __fastcall Lschen2Click(TObject *Sender);
        void __fastcall ButtonxListeDragDrop(TObject *Sender,
          TObject *Source, int X, int Y);
        void __fastcall ButtonxListeDragOver(TObject *Sender,
          TObject *Source, int X, int Y, TDragState State, bool &Accept);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TButtonx(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TButtonx *Buttonx;
//---------------------------------------------------------------------------
#endif
