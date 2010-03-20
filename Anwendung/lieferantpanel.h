#ifndef __lieferantpanel__
#define __lieferantpanel__

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>

//Vorwärtsdeklarationen
class MainWindow;

#include "callback.h"
#include "dbcommand.h"
//#include "dbconnectionmanager.h"

#include "lieferantdetail.h"
#include "lieferantedit.h"
#include "lieferantartikelconnect.h"

using namespace std;

/**
 * Die Klasse LieferantPanel erbt von wxPanel und wird innerhaln vom MainWindow angezeigt.
 * Sie dient zur Anzeige aller Lieferanten. Ausgangspunkt für Operationen mit Lieferanten.
 */
class LieferantPanel : public wxPanel
{

public:
	/**
	 * @param MainWindow *parent - Zeiger auf MainWindow Objekt
	 * @param WindowID id = wxID_ANY - ID des Frames [Default wxID_ANY]
	 * @param const wxPoint& pos = wxDefaultPosition - Position im Frame [Default wxDefaultPosition]
	 * @param const wxSize& size = wxDefaultSize - Größe des Panels [Default wxDefaultSize]
	 * @param long style = wxTAB_TRAVERSAL - Style des Panels [Default wxTAB_TRAVERSAL]
	 * @param const wxString& name = wxT("panel") - Name des Panels [Default panel]
	 */
	LieferantPanel(MainWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("panel"));
    
    //Methoden
	/**
	 * Sucht nach "seq" in den Lieferanten.
	 * Ruft db->getLieferantBySearch und übergibt FillListLieferant als Callback-Funktion und "seq"
	 * @param wxString seq - Suchwert
	 */
    void SearchLieferant(wxString seq);
	
	/**
	 * Löscht den ausgewählten Hersteller und die verknüpften Daten
	 * in der Tabelle Liefert
	 * Ruft db->deleteLiefertByLieferantId auf und übergibt die Lieferant ID
	 * Ruft db->deleteLieferantById auf und übergibt die Lieferant ID
	 * Aktulisiert die Ansicht des LieferantPanels
	 */
    void DeleteSelectedItem();

private:
   //Attribute
    wxListCtrl *listLieferant;
	
	//Zuletzt selektiertes Item der Liste
    int lastSelectedItem;
	
	//Anzahl der Spalten
    unsigned short listColumnCount;
    
    //Arrays
    wxArrayInt arr_db_list;
    
	//Zeiger auf Objekte
    DBCommand *db;
    MainWindow *main;
    
	//Ids der GUI-Elemente
    enum
    {
        ID_LISTLIEFERANT,
		ID_CONTEXTLIEFERANTDETAILS,
		ID_CONTEXTLIEFERANTEDIT,
        ID_CONTEXTLIEFERANTARTIKELCONNECT,
        ID_CONTEXTLIEFERANTDELETE,
        ID_CONTEXTLIEFERANTADD
    };
    
    DECLARE_EVENT_TABLE()
      
    //Methoden
	/**
	 * Übergibt die Daten der Vektoren an die wxListCtrl "listLieferant"
	 * @param vector< vector < wxString > > sqlReturn - Daten der Lieferanten
	 */
    void FillListLieferant(vector< vector< wxString > > sqlReturn);
	
	    
     //Eventhandler
	 /**
	 * Wird aufgerufen, wenn ein Element in der Liste
	 * selektiert wurde.
	 * Setz die Variable lastSelectedItem für weitere
	 * Verarbeiterungen auf aktuelles Element. 
	 */
    void EventListItemSelected(wxListEvent &event);
	
	/**
	 * Wird aufgerufen, wenn ein Element in der Liste
	 * abgewählt wird. Setzt die Variable lastSelectedItem auf -1.
	 */
    void EventListItemDeselected(wxListEvent &event);
	
	/**
	 * Wird aufgerufen, wenn ein Doppelklick / Entertaste auf ein Element der Liste getätigt wird.
	 * Erstellt ein ArtikelDetail Objekt
	 */
	void EventListItemActivated(wxListEvent &event);
	
	/**
	 * Reagiert auf den Rechtsklick im Panel und erzeugt
	 * ein PopUp-Menü
	 */
    void EventHandleContextMenu(wxContextMenuEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Lieferant anlegen" und erstellt ein
	 * LieferantAdd Objekt
	 */
    void EventHandleMenuLieferantAdd(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Lieferant löschen" und ruft "DeleteSelectedItem()" auf
	 */
    void EventHandleMenuLieferantDelete(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Lieferant bearbeiten" und erstellt ein
	 * LieferantEdit Objekt
	 */
	void EventHandleMenuLieferantEdit(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Lieferantdetails" und erstellt ein
	 * LieferantDetail Objekt
	 */
	void EventHandleMenuLieferantDetails(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Artikel zuweisen" und erstellt ein
	 * LieferantArtikelConnect Objekt
	 */
    void EventHandleMenuLieferantArtikelConnect(wxCommandEvent &event);
};
#endif // __lieferantpanel__
