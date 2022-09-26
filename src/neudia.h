//---------------------------------------------------------------------------
#ifndef neudiaH
#define neudiaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TNeu : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TTabSheet *TabSheet2;
        TListView *Vorlagen;
        TPanel *Panel2;
        TListView *Assistenten;
        TPopupMenu *PopupMenu1;
        TPopupMenu *PopupMenu2;
        TMenuItem *Lschen1;
        TMenuItem *Lschen2;
        TLabel *Pfeil;
        TLabel *Label1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall PopupMenu2Popup(TObject *Sender);
        void __fastcall Lschen1Click(TObject *Sender);
        void __fastcall Lschen2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TNeu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNeu *Neu;
//---------------------------------------------------------------------------
#endif
