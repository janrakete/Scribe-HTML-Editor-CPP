//---------------------------------------------------------------------------
#ifndef auswahlH
#define auswahlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <CheckLst.hpp>
//---------------------------------------------------------------------------
class TAuswahlliste : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TBevel *Bevel1;
        TLabel *Label8;
        TTabSheet *TabSheet3;
        TPanel *Panel2;
        TLabel *Label6;
        TBevel *Bevel2;
        TEdit *Edit1;
        TToolBar *ToolBar2;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
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
        TEdit *Edit2;
        TUpDown *UpDown1;
        TLabel *Label13;
        TEdit *Edit3;
        TCheckBox *CheckBox2;
        TLabel *Label14;
        TCheckBox *CheckBox1;
        TTabSheet *EventsTabSheet;
        TPanel *Panel4;
        TLabel *Label7;
        TLabel *Label10;
        TBevel *Bevel3;
        TEdit *Edit4;
        TCheckListBox *ListBox1;
        TListBox *ListBox2;
        TEdit *Edit5;
        TLabel *Label9;
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall ToolButton4Click(TObject *Sender);
        void __fastcall ToolButton5Click(TObject *Sender);
        void __fastcall ListBox1DragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall ListBox1DragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
private:	// Anwenderdeklarationen
        int item_index;
public:		// Anwenderdeklarationen
        __fastcall TAuswahlliste(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAuswahlliste *Auswahlliste;
//---------------------------------------------------------------------------
#endif
