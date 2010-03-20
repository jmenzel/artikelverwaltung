#ifndef __mainwindow__
#define __mainwindow__

#include <wx/wx.h>
#include <wx/string.h>
#include <wx/progdlg.h>
#include <wx/tglbtn.h>
#include <wx/thread.h>

#include <wx/config.h>
#include <wx/confbase.h>

//GUI Klassen
#include "artikelpanel.h"
#include "artikeladd.h"

#include "lieferantpanel.h"
#include "lieferantadd.h"

#include "herstellerpanel.h"
#include "herstelleradd.h"

#include "settingspanel.h"

//Anwendung Klassen
#include "updatedaemon.h"
#include "dbconnectionmanager.h"

//Datenhaltung Klassen
#include "configurationmanager.h"

class Artikelverwaltung : public wxApp
{
    public: virtual bool OnInit();
};

using namespace std;

/**
 * Die Klasse MainWindow erbt von wxFrame und ist das Haupt-Frame der Anwendung. Hier werden 
 * weitere Klassen instanziiert und der Inhalt präsentiert.
 */
class MainWindow : public wxFrame
{

public:
	///Konstruktor der Klasse MainWindow
	/**
	 * MainWindow Konstruktor
	 * const wxChar *title 	- Titel des Frames
	 * int xpos				- Position auf der X-Achse
	 * int ypos				- Position auf der Y-Achse
	 * int width			- Breite des Frames
	 * int height			- höhe des Frames
	 */
	MainWindow(const wxChar *title, int xpos, int ypos, int width, int height);
	~MainWindow();
    
    //Attribute
    wxTextCtrl *tfield_searchBox;
    wxButton *button_removeObject;
    wxButton *button_addObject;
    
	//Eventhandler
	/**
	 * Zeigt das ArtikelPanel an und deaktiviert
	 * das LieferantPanel, HerstellerPanel, SettingsPanel
	 */
	void EventOnClickTButtonArtikel( wxCommandEvent &event );
	
	/**
	 * Zeigt das LieferantPanel an und deaktiviert
	 * das ArtikelPanel, HerstellerPanel, SettingsPanel
	 */
    void EventOnClickTButtonLieferant( wxCommandEvent &event );
	
	/**
	 * Zeigt das HerstellerPanel an und deaktiviert
	 * das LieferantPanel, HerstellerPanel, SettingsPanel
	 */
    void EventOnClickTButtonHersteller( wxCommandEvent &event );
	
	/**
	 * Übergibt den eigegeben Text an die Suchfunktion des
	 * aktivierten Panels (ArtikelPanel, LieferantPanel oder HerstellerPanel)
	 */
    void EventTextChangedSearchBox(wxCommandEvent &event);
	
	/**
	 * Ruft die Funktion DeleteSelectedItem() des aktivierten Panels
	 * auf (ArtikelPanel, LieferantPanel oder HerstellerPanel)
	 */
    void EventOnClickButtonRemoveObject(wxCommandEvent &event);
	
	/**
	 * Instanziiert die Anlegen - Frames des aktivierten Panels
	 * (ArtikelPanel, LieferantPanel oder HerstellerPanel) - 
	 * new ArtikelAdd(this), new LieferantAdd(this), new HerstellerAdd(this)
	 */
    void EventOnClickButtonAddObject(wxCommandEvent &event);
	
	/**
	 * Reagiert auf den Rechtsklick im MainWindow und erzeugt
	 * ein PopUp-Menü
	 */
    void EventHandleContextMenu(wxContextMenuEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Einstellungen" und aktiviert
	 * das SettingsPanel. Die Panels ArtikelPanel, LieferantPanel und 
	 * HerstellerPanel werden deaktiviert
	 */
	void EventHandleMenuSettings(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Beenden" und beendet das
	 * Programm
	 */
	void EventHandleMenuClose(wxCommandEvent &event);
	

	/**
	 * Gibt einen Zeiger auf das Objekt
	 * der Klasse DBConnectionManager
	 * @return DBConnectionManager *object
	 */
    DBConnectionManager *getDBManageObject();
	
	/**
	 * Gibt einen Zeiger auf das Objekt
	 * der Klasse ConfigurationManager
	 * @return ConfigurationManager *object
	 */
	ConfigurationManager *getConfigManageObject();
	
	/**
	 * Gibt einen Zeiger auf das Objekt
	 * der Klasse ArtikelPanel
	 * @return ArtikelPanel *object
	 */
    ArtikelPanel *getArtikelPanelObject();
	
	/**
	 * Gibt einen Zeiger auf das Objekt
	 * der Klasse LieferantPanel
	 * @return LieferantPanel *object
	 */
    LieferantPanel *getLieferantPanelObject();
	
	/**
	 * Gibt einen Zeiger auf das Objekt
	 * der Klasse HerstellerPanel
	 * @return HerstellerPanel *object
	 */
    HerstellerPanel *getHerstellerPanelObject();
	
	/**
	 * Gibt einen Zeiger auf das Objekt
	 * der Klasse SettingsPanel
	 * @return SettingsPanel *object
	 */
	SettingsPanel *getSettingsPanelObject();
	
	/**
	 * Sperrt die Anwendung und die instanziierten Panel Objecte.
	 */
	void Lock();
	
	/**
	 * Entsperrt die Anwendung und aktiviert / instanziiert die
	 * Panel Objecte
	 */
	void Unlock();
	
	/**
	 * Gibt zurück, ob die Andwendung gerade gesperrt ist.
	 * @return bool islocked (true | false)
	 */
	bool IsLocked();
	
private:
    //Attribute
	wxPanel *top_panel;
    
	wxToggleButton *tbutton_artikel;
	wxToggleButton *tbutton_lieferant;
	wxToggleButton *tbutton_hersteller;
	
	bool locked;
	    
    //GUI-Element IDs
	enum
	{
		ID_PANELTOP,
		ID_PANELMAIN,
		ID_TBUTTONARTIKEL,
		ID_TBUTTONLIEFERANT,
		ID_TBUTTONHERSTELLER,
		ID_TFIELDSEARCHBOX,
        ID_BUTTONREMOVE,
        ID_BUTTONADD,
		ID_CONTEXTSETTINGS,
		ID_CONTEXTCLOSE
	};
	
	DECLARE_EVENT_TABLE()
    	
	//GUI-Objekte
    ArtikelPanel *artikel_panel;
    LieferantPanel *lieferant_panel;
    HerstellerPanel *hersteller_panel;
	SettingsPanel *settings_panel;
	
    //Anwendung-Objekte
    DBConnectionManager *db;
	UpdateDaemon *updater;
    
    //Datenhaltung-Objekte
    ConfigurationManager *config;
	
	//Methoden
	void CreateContentPanels();
};
#endif // __mainwindow__
