//---------------------------------------------------------------------------
#ifndef grafkataH
#define grafkataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TGrafikKatalog : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBevel *Bevel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TFileListBox *KategorieListe;
        TPanel *Panel4;
        TPanel *Panel2;
        TListView *Kategorien;
        TSplitter *Splitter1;
        TPanel *Panel3;
        TListView *Grafiken;
        TFileListBox *GrafikenListe;
        TScrollBox *ScrollBox1;
        TImage *Image1;
        TLabel *Label3;
        TLabel *Height;
        TLabel *Width;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Size;
        TPopupMenu *PopupMenu1;
        TPopupMenu *PopupMenu2;
        TMenuItem *Lschen1;
        TMenuItem *N1;
        TMenuItem *Lschen2;
        TMenuItem *N2;
        TMenuItem *NeueKategorie1;
        TMenuItem *Hinzufgen1;
        TOpenDialog *OpenDialog1;
        TMenuItem *Umbenennen1;
        TMenuItem *Umbenennen2;
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall KategorienClick(TObject *Sender);
        void __fastcall GrafikenClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall GrafikenDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall KategorienDragOver(TObject *Sender,
          TObject *Source, int X, int Y, TDragState State, bool &Accept);
        void __fastcall KategorienDragDrop(TObject *Sender,
          TObject *Source, int X, int Y);
        void __fastcall KategorienEdited(TObject *Sender, TListItem *Item,
          AnsiString &S);
        void __fastcall GrafikenEdited(TObject *Sender, TListItem *Item,
          AnsiString &S);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall PopupMenu2Popup(TObject *Sender);
        void __fastcall Lschen2Click(TObject *Sender);
        void __fastcall Lschen1Click(TObject *Sender);
        void __fastcall NeueKategorie1Click(TObject *Sender);
        void __fastcall Hinzufgen1Click(TObject *Sender);
        void __fastcall Umbenennen1Click(TObject *Sender);
        void __fastcall Umbenennen2Click(TObject *Sender);
private:	// Anwenderdeklarationen
        String drag_file;

public:		// Anwenderdeklarationen
        __fastcall TGrafikKatalog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGrafikKatalog *GrafikKatalog;
//---------------------------------------------------------------------------
#endif
