//---------------------------------------------------------------------------
#ifndef javascrH
#define javascrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TJavaScriptVorlagen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TLabel *Pfeil;
        TPageControl *PageControl1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TLabel *Label10;
        TShape *Shape2;
        TLabel *Label1;
        TShape *Shape3;
        TLabel *Label2;
        TShape *Shape4;
        TLabel *Label3;
        TShape *Shape5;
        TBevel *Bevel1;
        TBevel *Bevel2;
        TBevel *Bevel3;
        TBevel *Bevel4;
        TListView *ListView1;
        TBevel *Bevel5;
        TLabel *Label4;
        TEdit *Edit1;
        TLabel *Label5;
        TEdit *Edit2;
        TLabel *Label6;
        TEdit *Edit3;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton5;
        TOpenPictureDialog *HighlightOeffnenDialog;
        TOpenDialog *HighlightOeffnenDialog2;
        TPopupMenu *PopupMenu2;
        TMenuItem *Entfernen1;
        TBevel *Bevel6;
        TBitBtn *BitBtn4;
        TLabel *Label7;
        TLabel *Label8;
        TEdit *Edit4;
        TBevel *Bevel7;
        TLabel *Label9;
        TSpeedButton *SpeedButton6;
        TEdit *Edit6;
        TLabel *Label11;
        TBevel *Bevel8;
        TBitBtn *BitBtn5;
        TEdit *Edit7;
        TListView *ListView2;
        TPopupMenu *PopupMenu1;
        TMenuItem *MenuItem1;
        TBevel *Bevel9;
        TComboBox *ComboBox1;
        TLabel *Label12;
        TEdit *Edit5;
        TLabel *Label13;
        TEdit *Edit8;
        TEdit *Edit9;
        TLabel *Label14;
        TBevel *Bevel10;
        TLabel *Label15;
        TLabel *Label16;
        TEdit *Edit10;
        TUpDown *UpDown1;
        TEdit *Edit11;
        TLabel *Label17;
        TUpDown *UpDown2;
        TLabel *Label18;
        TEdit *Edit12;
        TLabel *Label19;
        TLabel *Label20;
        TEdit *Edit13;
        TEdit *Edit14;
        TLabel *Label21;
        TBevel *Bevel12;
        TLabel *Label22;
        TLabel *Label23;
        TUpDown *UpDown3;
        TEdit *Edit15;
        TLabel *Label24;
        TLabel *Label25;
        TUpDown *UpDown4;
        TEdit *Edit16;
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall Lschen1Click(TObject *Sender);
        void __fastcall PopupMenu2Popup(TObject *Sender);
        void __fastcall Entfernen1Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall MenuItem1Click(TObject *Sender);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TJavaScriptVorlagen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TJavaScriptVorlagen *JavaScriptVorlagen;
//---------------------------------------------------------------------------
#endif
