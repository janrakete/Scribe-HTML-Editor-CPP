//---------------------------------------------------------------------------
#ifndef thumbsH
#define thumbsH
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
#include <Menus.hpp>
#include "EnJpgGr.hpp"
#include "EnTransf.hpp"
//---------------------------------------------------------------------------
class TThumbnailGenerator : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TEdit *Edit1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TLabel *Pfeil;
        TTabSheet *TabSheet2;
        TPanel *Panel2;
        TBevel *Bevel1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TBevel *Bevel2;
        TLabel *Label7;
        TLabel *Label8;
        TEdit *Edit2;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TPanel *Panel3;
        TListView *Grafiken;
        TLabel *Label9;
        TLabel *Label10;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TBevel *Bevel3;
        TLabel *Label11;
        TComboBox *ComboBox1;
        TLabel *Label12;
        TEdit *Edit3;
        TTrackBar *TrackBar1;
        TLabel *Label13;
        TLabel *Label14;
        TUpDown *UpDown3;
        TEdit *Edit7;
        TLabel *Label15;
        TUpDown *UpDown1;
        TEdit *Edit4;
        TEdit *Edit5;
        TUpDown *UpDown2;
        TComboBox *ComboBox2;
        TEdit *Edit6;
        TUpDown *UpDown4;
        TComboBox *ComboBox3;
        TEdit *Edit8;
        TComboBox *ComboBox4;
        TComboBox *ComboBox5;
        TBffolder *Bffolder1;
        TBffolder *Bffolder2;
        TSpeedButton *SpeedButton3;
        TOpenDialog *OeffnenDialog;
        TProgressBar *ProgressBar1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Entfernen1;
        TImage *Image1;
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Bffolder1SelectionChanged(TObject *Sender,
          AnsiString NewSel);
        void __fastcall Bffolder2SelectionChanged(TObject *Sender,
          AnsiString NewSel);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall Entfernen1Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TThumbnailGenerator(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TThumbnailGenerator *ThumbnailGenerator;
//---------------------------------------------------------------------------
#endif
