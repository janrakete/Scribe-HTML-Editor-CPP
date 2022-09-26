//---------------------------------------------------------------------------
#ifndef incaktH
#define incaktH
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
class TIncludesAktualisieren : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label7;
        TLabel *Label10;
        TLabel *Label11;
        TBevel *Bevel3;
        TComboBox *ComboBox4;
        TEdit *Edit2;
        TCheckBox *CheckBox5;
        TProgressBar *ProgressBar1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TListBox *Verzeichnisse;
        TFileListBox *Dateien;
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ComboBox4Change(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TIncludesAktualisieren(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TIncludesAktualisieren *IncludesAktualisieren;
//---------------------------------------------------------------------------
#endif
