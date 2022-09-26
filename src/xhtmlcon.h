//---------------------------------------------------------------------------
#ifndef xhtmlconH
#define xhtmlconH
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
class TXHTMLKonverter : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TBevel *Bevel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TComboBox *ComboBox4;
        TLabel *Label7;
        TEdit *Edit2;
        TLabel *Label10;
        TCheckBox *CheckBox5;
        TLabel *Label11;
        TLabel *Label2;
        TComboBox *ComboBox1;
        TComboBox *ComboBox2;
        TLabel *Label3;
        TComboBox *ComboBox3;
        TLabel *Label4;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TBevel *Bevel2;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TProgressBar *ProgressBar1;
        TBevel *Bevel3;
        TListBox *WerteKlein;
        TListBox *TagsMitSlash;
        TListBox *StandAlones;
        TListBox *Verzeichnisse;
        TFileListBox *Dateien;
        TListBox *SonderzeichenCodesIntern;
        TListBox *SonderzeichenNamesIntern;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ComboBox4Change(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TXHTMLKonverter(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TXHTMLKonverter *XHTMLKonverter;
//---------------------------------------------------------------------------
#endif
