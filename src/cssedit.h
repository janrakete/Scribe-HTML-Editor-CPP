//---------------------------------------------------------------------------
#ifndef csseditH
#define csseditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include "Plusmemo.hpp"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <Graphics.hpp>
#include "ExtHilit.hpp"
#include "PMSupport.hpp"
//---------------------------------------------------------------------------
class TStyleSheetEditor : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TControlBar *ControlBar1;
        TToolBar *MenuLeiste;
        TToolButton *ToolButton5;
        TToolButton *ToolButton6;
        TToolButton *ToolButton11;
        TPopupMenu *BearbeitenMenu;
        TMenuItem *Rckgngig1;
        TMenuItem *Widerrufen1;
        TMenuItem *N7;
        TMenuItem *Ausschneiden1;
        TMenuItem *Kopieren1;
        TMenuItem *Einfgen1;
        TMenuItem *Lschen1;
        TMenuItem *N8;
        TMenuItem *Allesmarkieren1;
        TMenuItem *N9;
        TMenuItem *AlsKommentar1;
        TStatusBar *StatusBar1;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton7;
        TToolButton *ToolButton8;
        TToolButton *ToolButton9;
        TToolButton *ToolButton10;
        TToolButton *ToolButton12;
        TToolButton *ToolButton14;
        TToolButton *ToolButton15;
        TPopupMenu *StyleMenu;
        TMenuItem *Neu1;
        TMenuItem *N1;
        TMenuItem *ffnen1;
        TMenuItem *N2;
        TMenuItem *Speichern1;
        TMenuItem *Speichernunter1;
        TMenuItem *N6;
        TMenuItem *Beenden1;
        TPanel *Panel1;
        TSplitter *Splitter1;
        TPanel *Panel2;
        TPlusMemo *Stylefeld;
        TComboBox *ComboBox1;
        TBevel *Bevel1;
        TToolBar *ToolBar2;
        TToolButton *ToolButton13;
        TToolButton *ToolButton16;
        TShape *Shape1;
        TComboBox *ComboBox2;
        TShape *Shape2;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TShape *Shape3;
        TLabel *Label1;
        TBitBtn *BitBtn1;
        TToolBar *ToolBar3;
        TToolButton *ToolButton17;
        TToolButton *ToolButton18;
        TToolButton *ToolButton19;
        TToolButton *ToolButton20;
        TToolButton *ToolButton21;
        TToolButton *ToolButton22;
        TToolButton *ToolButton23;
        TToolButton *ToolButton24;
        TToolButton *ToolButton25;
        TToolButton *ToolButton26;
        TMenuItem *StyleS1;
        TMenuItem *Abbrechen1;
        TMenuItem *N3;
        TPopupMenu *PopupMenu1;
        TMenuItem *Ausschneiden2;
        TMenuItem *Kopieren2;
        TMenuItem *Einfgen2;
        TMenuItem *Lschen2;
        TMenuItem *N4;
        TMenuItem *AlsKommentar2;
        TSpeedButton *SpeedButton4;
        TComboBox *ComboBox5;
        TColorDialog *ColorDialog1;
        TStringGrid *StringGrid1;
        TPlusMemo *TempMemo;
        TOpenDialog *OeffnenDialog;
        TSaveDialog *SpeichernunterDialog;
        TExtHighlighter *StylefeldHighlighter;
        void __fastcall ToolButton11Click(TObject *Sender);
        void __fastcall Splitter1CanResize(TObject *Sender, int &NewSize,
          bool &Accept);
        void __fastcall Neu1Click(TObject *Sender);
        void __fastcall ffnen1Click(TObject *Sender);
        void __fastcall Speichern1Click(TObject *Sender);
        void __fastcall Speichernunter1Click(TObject *Sender);
        void __fastcall Beenden1Click(TObject *Sender);
        void __fastcall StyleS1Click(TObject *Sender);
        void __fastcall Abbrechen1Click(TObject *Sender);
        void __fastcall Rckgngig1Click(TObject *Sender);
        void __fastcall Widerrufen1Click(TObject *Sender);
        void __fastcall Ausschneiden1Click(TObject *Sender);
        void __fastcall Kopieren1Click(TObject *Sender);
        void __fastcall Einfgen1Click(TObject *Sender);
        void __fastcall Lschen1Click(TObject *Sender);
        void __fastcall Allesmarkieren1Click(TObject *Sender);
        void __fastcall AlsKommentar1Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall StylefeldMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall BearbeitenMenuPopup(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ToolButton13Click(TObject *Sender);
        void __fastcall ToolButton16Click(TObject *Sender);
        void __fastcall ComboBox2Change(TObject *Sender);
        void __fastcall StylefeldChange(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall StylefeldClick(TObject *Sender);
        void __fastcall ComboBox5Click(TObject *Sender);
        void __fastcall ComboBox3Click(TObject *Sender);
        void __fastcall ComboBox4Click(TObject *Sender);
        void __fastcall ComboBox3Change(TObject *Sender);
        void __fastcall ComboBox4KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ComboBox5KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ComboBox3KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Anwenderdeklarationen
        int MinZ;
        int MaxZ;
        int carriage;
public:		// Anwenderdeklarationen
        __fastcall TStyleSheetEditor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStyleSheetEditor *StyleSheetEditor;
//---------------------------------------------------------------------------
#endif
  