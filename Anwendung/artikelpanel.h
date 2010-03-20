#ifndef __artikelpanel__
#define __artikelpanel__

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>

//Vorwärtsdeklarationen
class MainWindow;

#include "callback.h"
#include "dbcommand.h"

#include "artikeladd.h"
#include "artikeledit.h"
#include "artikeldetail.h"
#include "artikellieferantconnect.h"

using namespace std;

/**
 * Die Klasse ArtikelPanel erbt von wxPanel und wird innerhaln vom MainWindow angezeigt.
 * Sie dient zur Anzeige aller Artikel. Ausgangspunkt für Operationen mit Artikeln.
 */
class ArtikelPanel : public wxPanel
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
	ArtikelPanel(MainWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("panel"));
    
    //Methoden
	/**
	 * Sucht nach "seq" in den Artikeln.
	 * Ruft db->getArtikelBySearch und übergibt FillListArtikel als Callback-Funktion und "seq"
	 * @param wxString seq - Suchwert
	 */
    void SearchArtikel(wxString seq);
	
	/**
	 * Löscht den ausgewählten Artikel und die verknüpften Daten
	 * in der Tabelle liefert
	 * Ruft db->deleteLiefertByArtikelId auf und übergibt die Artikel ID
	 * Ruft db->deleteArtikelById auf und übergibt die Artikel ID
	 * Aktulisiert die Ansicht des ArtikelPanels
	 */
    void DeleteSelectedItem();
    
private:
    //Attribute
    wxListCtrl *listArtikel;
	
	//Zuletzt selektierter Eintrag in der Liste
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
        ID_LISTARTIKEL,
        ID_CONTEXTARTIKELLIEFERANTCONNECT,
        ID_CONTEXTARTIKELDELETE,
        ID_CONTEXTARTIKELADD,
        ID_CONTEXTARTIKELDETAIL,
        ID_CONTEXTARTIKELEDIT
    };
    
    DECLARE_EVENT_TABLE()
      
    //Methoden
	/**
	 * Übergibt die Daten der Vektoren an die wxListCtrl "listArtikel"
	 * @param vector< vector < wxString > > sqlReturn - Daten der Artikel
	 */
    void FillListArtikel(vector< vector< wxString > > sqlReturn);

    
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
	 * Reagiert auf PopUp-Menü Eintrag "Lieferant zuweisen" und erstellt ein
	 * ArtikelLieferantConnect Objekt
	 */
    void EventHandleMenuArtikelLieferantConnect(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Artikel löschen" und ruft "DeleteSelectedItem()" auf
	 */
    void EventHandleMenuArtikelDelete(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Artikel anlegen" und erstellt ein
	 * ArtikelAdd Objekt
	 */
    void EventHandleMenuArtikelAdd(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Artikeldetails" und erstellt ein
	 * ArtikelDetail Objekt
	 */
    void EventHandleMenuArtikelDetail(wxCommandEvent &event);
	
	/**
	 * Reagiert auf PopUp-Menü Eintrag "Artikel bearbeiten" und erstellt ein
	 * ArtikelEdit Objekt
	 */
    void EventHandleMenuArtikelEdit(wxCommandEvent &event);
};
#endif // __artikelpanel__
