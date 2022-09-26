//---------------------------------------------------------------------------
#ifndef ftpprofiH
#define ftpprofiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFTPProfile : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TShape *Shape1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TLabel *Label1;
        TEdit *Profilname;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TPanel *Panel2;
        TListView *Profile;
        TPopupMenu *PopupMenu1;
        TMenuItem *Lschen1;
        TBevel *Bevel1;
        TLabel *Label2;
        TEdit *Server;
        TLabel *Label3;
        TEdit *Username;
        TLabel *Label4;
        TEdit *Password;
        TBevel *Bevel2;
        TLabel *Label5;
        TCheckBox *Passive;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TPanel *Panel3;
        TPanel *Panel4;
        TLabel *Label6;
        TEdit *Account;
        TLabel *Label7;
        TEdit *Port;
        TLabel *Label8;
        TComboBox *TransferMode;
        TLabel *Label9;
        TEdit *Retries;
        TUpDown *RetriesController;
        TBevel *Bevel3;
        TBevel *Bevel4;
        TLabel *Label10;
        TEdit *ProxyServer;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *ProxyUsername;
        TEdit *ProxyPassword;
        TBevel *Bevel5;
        TLabel *Label13;
        TEdit *ProxyPort;
        TBevel *Bevel6;
        TLabel *Label14;
        TComboBox *ProxyType;
        TLabel *Pfeil;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall ProfileClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall Lschen1Click(TObject *Sender);
private:	// Anwenderdeklarationen
public:		// Anwenderdeklarationen
        __fastcall TFTPProfile(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFTPProfile *FTPProfile;
//---------------------------------------------------------------------------
#endif
