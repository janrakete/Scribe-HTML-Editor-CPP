//---------------------------------------------------------------------------
#ifndef downloadH
#define downloadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TDownloadzeit : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel2;
        TBevel *Bevel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TListView *Links;
        TProgressBar *ProgressBar1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TBevel *Bevel2;
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *DocumentSize;
        TLabel *LinkedFiles;
        TLabel *Total;
        TLabel *Kbps1;
        TLabel *Kbps2;
        TLabel *Kbps3;
        TListBox *ListBox1;
        TListBox *ListBox2;
        TListBox *Doppelt;
        TFileListBox *FileListBox1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall LinksClick(TObject *Sender);
private:	// Anwenderdeklarationen
        bool abbruch;

public:		// Anwenderdeklarationen
        __fastcall TDownloadzeit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDownloadzeit *Downloadzeit;
//---------------------------------------------------------------------------
#endif
