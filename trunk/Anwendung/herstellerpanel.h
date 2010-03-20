#ifndef __herstellerpanel__
#define __herstellerpanel__

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>

//Vorwärtsdeklarationen
class MainWindow;

#include "callback.h"
#include "dbcommand.h"

#include "herstellerdetail.h"
#include "herstelleredit.h"

using namespace std;

/**
 * Die Klasse HerstellerPanel erbt von wxPanel und wird innerhaln vom MainWindow angezeigt.
 * Sie dient zur Anzeige aller Hersteller. Ausgangspunkt für Operationen mit Herstellern.
 */
class HerstellerPanel : public wxPanel
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
	HerstellerPanel(MainWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("panel"));
    
    //Methoden
	/**
	 * Sucht nach "seq" in den Herstellern.
	 * Ruft db->getHerstellerBySearch und übergibt FillListHersteller als Callback-Funktion und "seq"
	 * @param wxString seq - Suchwert
	 */
    void SearchHersteller(wxString seq);
	
	/**
	 * Löscht den ausgewählten Hersteller und die verknüpften Daten
	 * in der Tabelle Artikel sowie Liefert
	 * Ruft db->deleteLiefertByHerstellerId auf und übergibt die Hersteller ID
	 * Ruft db->deleteArtikelByHerstellerId auf und übergibt die Hersteller ID
	 * Ruft db->deleteHerstellerById auf und übergibt die Hersteller ID
	 * Aktulisiert die Ansicht des HerstellerPanels
	 */
    void DeleteSelectedItem();

private:
    //Attribute
    wxListCtrl *listHersteller;
	
	//Zuletzt selektierter Eintrag in der Liste
    int lastSelectedItem;
	
	//Anzahl der Spalten
    unsigned short listColumnCount;
        
    //Arrays
    wxArrayInt arr_db_list;
    
	//Zeiger auf Objekte
    DBCommand *db;
    MainWindow *main;
    	
	//IDs der GUI-Elemente
    enum
    {
        ID_LISTHERSTELLER,
        ID_CONTEXTHERSTELLERDELETE,
        ID_CONTEXTHERSTELLERADD,
        ID_CONTEXTHERSTELLERDETAIL,
        ID_CONTEXTHERSTELLEREDIT
    };
    
    DECLARE_EVENT_TABLE()
    
    //Methoden
	/**
	 * Übergibt die Daten der Vektoren an die wxListCtrl "listHersteller"
	 * @param vector< vector < wxString > > sqlReturn - Daten der Hersteller
	 */
    void FillListHersteller(vector< vector< wxString > > sqlReturn);
	
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
	 * Reagiert auf PopUp-Menü Eintrag "Hersteller löschen" und ruft "DeleteSelectedItem()" auf
	 */
    void EventHandleMenuHerstellerDelete(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Hersteller anlegen" und erstellt ein
	 * HerstellerAdd Objekt
	 */
    void EventHandleMenuHerstellerAdd(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Herstellerdetails" und erstellt ein
	 * HerstellerDetail Objekt
	 */
    void EventHandleMenuHerstellerDetail(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Hersteller bearbeiten" und erstellt ein
	 * HerstellerEdit Objekt
	 */
    void EventHandleMenuHerstellerEdit(wxCommandEvent &event);
};
#endif // __herstellerpanel__
