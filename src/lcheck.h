//---------------------------------------------------------------------------
#ifndef lcheckH
#define lcheckH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include "HTTPGet.hpp"

//---------------------------------------------------------------------------
class TLinkUeberpruefung : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel2;
        TLabel *Label7;
        TLabel *Label10;
        TLabel *Label11;
        TBevel *Bevel1;
        TComboBox *ComboBox4;
        TEdit *Edit2;
        TCheckBox *CheckBox5;
        TTabSheet *TabSheet2;
        TPanel *Panel3;
        TListView *ListView1;
        TProgressBar *ProgressBar1;
        TListBox *ListBox1;
        TListBox *ListBox2;
        TListBox *Verzeichnisse;
        TFileListBox *Dateien;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TLabel *Label1;
        TCheckBox *CheckBox1;
        TListBox *Attributes;
        TListBox *ListBox3;
        TFileListBox *FileListBox1;
        THTTPGet *HTTPGet;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall ComboBox4Change(TObject *Sender);
        void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall ListView1DblClick(TObject *Sender);
        void __fastcall HTTPGetProgress(TObject *Sender, int TotalSize,
          int Readed);
        void __fastcall HTTPGetError(TObject *Sender);
private:	// Anwenderdeklarationen
        bool abbruch;
        bool http_success;
public:		// Anwenderdeklarationen
        __fastcall TLinkUeberpruefung(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLinkUeberpruefung *LinkUeberpruefung;
//---------------------------------------------------------------------------
#endif
