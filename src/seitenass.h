//---------------------------------------------------------------------------
#ifndef seitenassH
#define seitenassH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSeitenAssistent : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label10;
        TLabel *Label6;
        TEdit *Edit1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBevel *Bevel1;
        TShape *Shape2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit2;
        TEdit *Edit3;
        TLabel *Label4;
        TEdit *Edit4;
        TLabel *Label5;
        TBevel *Bevel2;
        TLabel *Label7;
        TComboBox *ComboBox1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TSeitenAssistent(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSeitenAssistent *SeitenAssistent;
//---------------------------------------------------------------------------
#endif
