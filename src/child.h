//---------------------------------------------------------------------------
#ifndef childH
#define childH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Plusmemo.hpp"
#include <Graphics.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include "PlusGutter.hpp"
//---------------------------------------------------------------------------
class TKindFormular : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TPlusMemo *Textfeld;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TSpeedButton *SpeedButton1;
        TLabel *Title;
        TPopupMenu *TextfeldMenu;
        TMenuItem *Seiteschlieen1;
        TPlusGutter *Zeilennummern;
        TLabel *FTPProfil;
        TMenuItem *Tagbearbeiten1;
        TMenuItem *Tagentfernen1;
        TMenuItem *N1;
        TMenuItem *StyleSheets1;
        TMenuItem *JavaScriptEreignisse1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *Stichwort1;
        TMenuItem *Ausschneiden1;
        TMenuItem *Kopieren1;
        TMenuItem *Einfgen1;
        TMenuItem *Lschen1;
        TMenuItem *N4;
        TMenuItem *Markierung1;
        TMenuItem *N5;
        TMenuItem *onAbort1;
        TMenuItem *onBlur1;
        TMenuItem *onChange1;
        TMenuItem *onClick1;
        TMenuItem *onDblClick1;
        TMenuItem *onError1;
        TMenuItem *onFocus1;
        TMenuItem *onKeydown1;
        TMenuItem *onKeypress1;
        TMenuItem *onKeyup1;
        TMenuItem *onLoad1;
        TMenuItem *onMousedown1;
        TMenuItem *onMousemove1;
        TMenuItem *onMouseout1;
        TMenuItem *onMouseover1;
        TMenuItem *onMouseup1;
        TMenuItem *onReset1;
        TMenuItem *onSelect1;
        TMenuItem *onSubmit1;
        TMenuItem *onUnload1;
        TMenuItem *Style1;
        TMenuItem *N6;
        TMenuItem *ID1;
        TMenuItem *Class1;
        TMenuItem *Title1;
        TMenuItem *AlsKommentar1;
        TMenuItem *N7;
        TMenuItem *Zeilenumbrcheanhngen1;
        TMenuItem *N8;
        TMenuItem *InTabelleumwandeln1;
        TMenuItem *InListeumwandeln1;
        TMenuItem *N9;
        TMenuItem *InGrossbuchstaben1;
        TMenuItem *InKleinbuchstaben1;
        TMenuItem *N10;
        TMenuItem *AlleTagsentfernen1;
        TMenuItem *Sonderzeichenumwandeln1;
        TMenuItem *N11;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall TextfeldMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Seiteschlieen1Click(TObject *Sender);
        void __fastcall TextfeldChange(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall TextfeldKeyPress(TObject *Sender, char &Key);
        void __fastcall TextfeldDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall TextfeldDragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
        void __fastcall TextfeldKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall onAbort1Click(TObject *Sender);
        void __fastcall onBlur1Click(TObject *Sender);
        void __fastcall onChange1Click(TObject *Sender);
        void __fastcall onClick1Click(TObject *Sender);
        void __fastcall onDblClick1Click(TObject *Sender);
        void __fastcall onError1Click(TObject *Sender);
        void __fastcall onFocus1Click(TObject *Sender);
        void __fastcall onKeydown1Click(TObject *Sender);
        void __fastcall onKeypress1Click(TObject *Sender);
        void __fastcall onKeyup1Click(TObject *Sender);
        void __fastcall onLoad1Click(TObject *Sender);
        void __fastcall onMousedown1Click(TObject *Sender);
        void __fastcall onMousemove1Click(TObject *Sender);
        void __fastcall onMouseout1Click(TObject *Sender);
        void __fastcall onMouseover1Click(TObject *Sender);
        void __fastcall onMouseup1Click(TObject *Sender);
        void __fastcall onReset1Click(TObject *Sender);
        void __fastcall onSelect1Click(TObject *Sender);
        void __fastcall onSubmit1Click(TObject *Sender);
        void __fastcall onUnload1Click(TObject *Sender);
        void __fastcall TextfeldMenuPopup(TObject *Sender);
        void __fastcall AlsKommentar1Click(TObject *Sender);
        void __fastcall InGrossbuchstaben1Click(TObject *Sender);
        void __fastcall InKleinbuchstaben1Click(TObject *Sender);
        void __fastcall Class1Click(TObject *Sender);
        void __fastcall ID1Click(TObject *Sender);
        void __fastcall Title1Click(TObject *Sender);
        void __fastcall Ausschneiden1Click(TObject *Sender);
        void __fastcall Kopieren1Click(TObject *Sender);
        void __fastcall Einfgen1Click(TObject *Sender);
        void __fastcall Lschen1Click(TObject *Sender);
        void __fastcall Tagentfernen1Click(TObject *Sender);
        void __fastcall Zeilenumbrcheanhngen1Click(TObject *Sender);
        void __fastcall InListeumwandeln1Click(TObject *Sender);
        void __fastcall AlleTagsentfernen1Click(TObject *Sender);
        void __fastcall InTabelleumwandeln1Click(TObject *Sender);
        void __fastcall Style1Click(TObject *Sender);
        void __fastcall Tagbearbeiten1Click(TObject *Sender);
        void __fastcall Stichwort1Click(TObject *Sender);
        void __fastcall Sonderzeichenumwandeln1Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TKindFormular(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKindFormular *KindFormular;
//---------------------------------------------------------------------------
#endif
