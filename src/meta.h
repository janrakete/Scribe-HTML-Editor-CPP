//---------------------------------------------------------------------------
#ifndef metaH
#define metaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMetatag : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TBevel *Bevel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TLabel *Label1;
        TComboBox *ComboBox1;
        TLabel *Label2;
        TEdit *Edit1;
        TLabel *Label3;
        TEdit *Edit2;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TMetatag(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMetatag *Metatag;
//---------------------------------------------------------------------------
#endif
