//---------------------------------------------------------------------------
#ifndef listediaH
#define listediaH
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
class TListe : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TBevel *Bevel1;
        TTabSheet *TabSheet2;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TSpeedButton *SpeedButton1;
        TEdit *CssStyle;
        TEdit *CssID;
        TEdit *CssClass;
        TEdit *CssTitle;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TComboBox *ComboBox2;
        TTabSheet *TabSheet3;
        TPanel *Panel2;
        TListBox *ListBox1;
        TLabel *Label6;
        TEdit *Edit1;
        TToolBar *ToolBar2;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TBevel *Bevel2;
        TLabel *Label7;
        TComboBox *ComboBox1;
        TLabel *Label8;
        TUpDown *UpDown3;
        TEdit *Edit7;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TLabel *Item1;
        TLabel *Item2;
        TLabel *Item3;
        TLabel *Item4;
        TLabel *Item5;
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall ListBox1DragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
        void __fastcall ListBox1DragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall ToolButton5Click(TObject *Sender);
        void __fastcall ToolButton4Click(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall ComboBox2Change(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
private:	// Anwenderdeklarationen
        int item_index;
        String end_tag;
public:		// Anwenderdeklarationen
        __fastcall TListe(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TListe *Liste;
//---------------------------------------------------------------------------
#endif
