//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("scribe.res");
USEFORM("main.cpp", Hauptformular);
USEFORM("addluni.cpp", AddLangUniDialog);
USEFORM("child.cpp", KindFormular);
USELIB("..\..\Cponents\THTTPGet\INET.LIB");
USEFORM("openinet.cpp", OeffnenausdemInternet);
USEFORM("neudia.cpp", Neu);
USEFORM("neuproj.cpp", NeuesProjekt);
USEFORM("info.cpp", InfoDialog);
USEFORM("grapview.cpp", GrafikBetrachter);
USEFORM("suche.cpp", Suchen);
USEFORM("hilfed.cpp", Hilfe);
USEFORM("ibrowse.cpp", InternerBrowser);
USEFORM("ftpprofi.cpp", FTPProfile);
USEFORM("newlink.cpp", NeueVerknuepfung);
USEFORM("tipoday.cpp", TippDesTages);
USEFORM("plugin.cpp", Plugins);
USEFORM("button.cpp", Buttonx);
USEUNIT("gifimage.pas");
USEFORM("hyper.cpp", Hyperlink);
USEFORM("ankerdia.cpp", Anker);
USEFORM("email.cpp", EmailVerweis);
USEFORM("image.cpp", Grafik);
USEFORM("trennli.cpp", Trennlinie);
USEFORM("multim.cpp", Multimedia);
USEFORM("meta.cpp", Metatag);
USEFORM("include.cpp", IncludeDatei);
USEFORM("schriftd.cpp", Schrift);
USEFORM("schnellf.cpp", Schnellformat);
USEFORM("para.cpp", Paragraph);
USEFORM("abschni.cpp", Abschnitt);
USEFORM("listedia.cpp", Liste);
USEFORM("proback.cpp", ProjektBackup);
USEFORM("seitprop.cpp", Seiteneigen);
USEFORM("grafkata.cpp", GrafikKatalog);
USEFORM("thumbs.cpp", ThumbnailGenerator);
USEFORM("tablewiz.cpp", TabellenAssistent);
USEFORM("table.cpp", Tabelle);
USEFORM("zeiledia.cpp", Zeile);
USEFORM("caption.cpp", UeberUnterschrift);
USEFORM("kopfzell.cpp", Kopfzelle);
USEFORM("zelledia.cpp", Zelle);
USEUNIT("..\..\Cponents\TTopStyle\u_TopStyleIntegration.pas");
USEFORM("cssedit.cpp", StyleSheetEditor);
USEFORM("xhtmlcon.cpp", XHTMLKonverter);
USEFORM("incakt.cpp", IncludesAktualisieren);
USEFORM("lcheck.cpp", LinkUeberpruefung);
USEFORM("buttonta.cpp", ButtonTag);
USEFORM("auswahle.cpp", Auswahleintrag);
USEFORM("checkb.cpp", CheckboxTag);
USEFORM("radio.cpp", Radiobutton);
USEFORM("verstfe.cpp", VerstecktesFeld);
USEFORM("eingabe.cpp", Eingabefeld);
USEFORM("password.cpp", Passwortfeld);
USEFORM("textfel.cpp", Textfeld);
USEFORM("absenden.cpp", AbsendenZuruecksetzen);
USEFORM("auswahl.cpp", Auswahlliste);
USEFORM("formula.cpp", Formular);
USEFORM("frameass.cpp", FrameAssistent);
USEFORM("fastta.cpp", FastTag);
USEFORM("frameber.cpp", FrameBereich);
USEFORM("eiframe.cpp", EinzelnerFrame);
USEFORM("iframe.cpp", EingebettetesFrame);
USEFORM("welcome.cpp", Willkommen);
USEFORM("bsuchen.cpp", BrowserSuchen);
USEFORM("seitenass.cpp", SeitenAssistent);
USEFORM("download.cpp", Downloadzeit);
USEFORM("options.cpp", Optionen);
USEFORM("javascr.cpp", JavaScriptVorlagen);
USEFORM("ftpprops.cpp", DirektFTPEigenschaften);
USEFORM("ftppass.cpp", DirektesFTPPasswort);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
         HANDLE MutexHandle = CreateMutex(NULL, TRUE, "ABMUTEX");
         if (WaitForSingleObject(MutexHandle, 0) != WAIT_TIMEOUT)
         {
                 Application->Initialize();
                 Application->Title = "Scribe!";
                 Application->CreateForm(__classid(THauptformular), &Hauptformular);
                 Application->CreateForm(__classid(TSuchen), &Suchen);
                 Application->CreateForm(__classid(THilfe), &Hilfe);
                 Application->CreateForm(__classid(TInternerBrowser), &InternerBrowser);
                 Application->Run();
         }
         else
         {
          HWND hWnd = FindWindow(0, "Scribe!");
          SetForegroundWindow(hWnd);
         }
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
