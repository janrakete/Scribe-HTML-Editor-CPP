//---------------------------------------------------------------------------
#ifndef probackH
#define probackH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "Bffolder.h"
#include <Dialogs.hpp>
#include "cabfiles.hpp"
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TProjektBackup : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TBevel *Bevel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TLabel *Pfeil;
        TComboBox *ComboBox1;
        TLabel *Label2;
        TComboBox *ComboBox2;
        TLabel *Label3;
        TBevel *Bevel2;
        TEdit *Edit1;
        TLabel *Label4;
        TSpeedButton *SpeedButton1;
        TEdit *Edit2;
        TBevel *Bevel3;
        TProgressBar *ProgressBar1;
        TSpeedButton *SpeedButton2;
        TBffolder *Bffolder1;
        TCABFile *CABFile1;
        TListBox *Verzeichnisse;
        TFileListBox *TempDateilistBox;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ComboBox2Change(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall CABFile1OverWriteFile(TObject *Sender,
          AnsiString FileName, bool &Allow);
        void __fastcall CABFile1DecompressProgress(TObject *Sender,
          AnsiString FileName, int pos, int tot);
        void __fastcall CABFile1CompressProgress(TObject *Sender, int pos,
          int tot);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall Bffolder1SelectionChanged(TObject *Sender,
          AnsiString NewSel);
private:	// Anwenderdeklarationen
        TStrings* StrLstDateien;
public:		// Anwenderdeklarationen
        __fastcall TProjektBackup(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProjektBackup *ProjektBackup;
//---------------------------------------------------------------------------
#endif
