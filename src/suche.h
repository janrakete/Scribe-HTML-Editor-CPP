//---------------------------------------------------------------------------
#ifndef sucheH
#define sucheH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TSuchen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TPanel *Panel2;
        TPanel *Panel3;
        TLabel *Label6;
        TBevel *Bevel2;
        TLabel *Label7;
        TComboBox *ComboBox4;
        TLabel *Label8;
        TCheckBox *CheckBox3;
        TBevel *Bevel3;
        TLabel *Label10;
        TEdit *Edit2;
        TLabel *Label11;
        TCheckBox *CheckBox5;
        TListView *ListView1;
        TProgressBar *ProgressBar1;
        TListBox *ListBox1;
        TMemo *SuchenMemo;
        TMemo *ErsetzenMemo;
        TLabel *Label1;
        TCheckBox *CheckBox1;
        TBevel *Bevel1;
        TBitBtn *BitBtn3;
        TListBox *ListBox2;
        TListBox *Verzeichnisse;
        TFileListBox *Dateien;
        TLabel *Pfeil;
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall ComboBox4Change(TObject *Sender);
        void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall ListView1DblClick(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TSuchen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSuchen *Suchen;
//---------------------------------------------------------------------------
#endif
