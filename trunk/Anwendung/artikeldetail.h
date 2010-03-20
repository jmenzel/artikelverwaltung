#ifndef __artikeldetail__
#define __artikeldetail__

#include <wx/wx.h>
#include <vector>
#include <wx/listctrl.h>
#include <wx/datetime.h>

//Vorwärtsdeklarationen
class MainWindow;

#include "callback.h"
#include "dbcommand.h"
#include "artikellieferantconnect.h"

using namespace std;

/**
 * Die Klasse ArtikelDetail erbt von wxFrame und ist ein eigenständiges Fenster.
 * Es zeigt alle Eigenschaften eines Artikels anhand der ID.
 * Es zeigt ebenfalls alle Einträge aus der Tabelle liefert zu der ID an.
 * Die Klasse ArtikelDetails ist einer der Ausgangspunkte um eine Verknüpfung zwischen
 * Artikel und Lieferant herzustellen.
 */
class ArtikelDetail : public wxFrame
{

	public:
		/**
		 * @param MainWindow* parent - Zeiger auf MainWindowobjekt
		 * @param unsigned int artikelId - ID des Artikels
		 */
        ArtikelDetail(MainWindow* parent, unsigned int artikelId);
        ~ArtikelDetail();
	
		/**
		 * Läd alle Daten neu.
		 */
        void Update();
        
	private:
		MainWindow *main;
        DBCommand *db;
        
        unsigned int artId;
        
        //Attribute
        wxPanel *panel;
        
        wxStaticText *tlabel_artNr;
        wxStaticText *tlabel_artVKPreis;
        wxStaticText *tlabel_artBeschreibung;
        wxStaticText *tlabel_artHersteller;
        wxStaticText *tlabel_artCreateDate;
        
        wxTextCtrl *tfield_artNr;
        wxTextCtrl *tfield_artVKPreis;
        wxTextCtrl *tfield_artBeschreibung;
        wxTextCtrl *tfield_artHersteller;
        wxTextCtrl *tfield_artCreateDate;
        wxTextCtrl *tfield_searchLiefert;
        
        wxListCtrl *listArtikelLieferant;
        
        wxButton *button_addLiefert;
        wxButton *button_deleteLiefert;
		
		wxDateTime *createDate;
        
		//Zuletzt ausgewähltes Item der Liste
        int lastSelectedItem;
		
		//Anzahl der Spalten
        unsigned short listColumnCount;
        
        //Arrays
        wxArrayInt arr_db_list;
        
        DECLARE_EVENT_TABLE()
        
		//IDs der GUI-Elemente
        enum
        {
            ID_PANEL,
            ID_TLABELARTNR,
            ID_TLABELARTVKPREIS,
            ID_TLABELARTBESCHREIBUNG,
            ID_TLABELARTHERSTELLER,
            ID_TLABELARTCREATEDATE,
            ID_TFIELDARTNR,
            ID_TFIELDARTVKPREIS,
            ID_TFIELDARTBESCHREIBUNG,
            ID_TFIELDARTHERSTELLER,
            ID_TFIELDARTCREATEDATE,
            ID_TFIELDSEARCHLIEFERT,
            ID_LISTARTIKELLIEFERANT,
            ID_BUTTONADDLIEFERT,
            ID_BUTTONDELETELIEFERT
        };
        
        //Methoden
		/**
		 * Stellt die Daten aus den Vektoren in den Textfeldern dar;
		 * @param vector< vector< wxString > > data - Enhält die Daten des Artikels
		 */
        void FillArtikelData(vector< vector < wxString > > data);
		
		/**
		 * Stellt die Daten aus den Vektoren in der wxListCtrl "listArtikelLieferant" dar;
		 * @param vector< vector< wxString > > data - Enhält die Daten der Tabelle liefert
		 */
        void FillArtikelLieferantList(vector< vector< wxString > > data);
		
		/**
		 * Wird auf gerufen, wenn in die Suchbox Text eingegeben wird.
		 * Aktualisiert die Liste mit den ArtikelLieferanten
		 * verknüpfungen.
		 */
        void EventTextChangedLiefertSearch(wxCommandEvent &event);
		
		/**
		 * Wird aufgerufen, wenn ein Element in der Liste
		 * selektiert wurde.
		 * Setz die Variable lastSelectedItem für weitere
		 * Verarbeiterungen auf aktuelles Element. Aktiviert den "button_deleteLiefert"
		 * Button
		 */
        void EventListItemSelected(wxListEvent &event);
		
		/**
		 * Wird aufgerufen, wenn ein Element in der Liste
		 * abgewählt wird. Setzt die Variable lastSelectedItem auf -1.
		 * Deaktivert den "button_deleteLiefert" Button
		 */
        void EventListItemDeselected(wxListEvent &event);
		
		/**
		 * Reagiert auf den "button_addLiefert" Button
		 * Erstellt ein neues ArtikelLieferantConnect Objekt
		 */
        void EventOnClickAddLiefertButton(wxCommandEvent &event);
		
		/**
		 * Reagiert auf den "button_deleteLiefert" Button
		 * Löscht den Artikel in lastSelectedItem
		 */
        void EventOnClickDeleteLiefertButton(wxCommandEvent &event);

};
#endif // __artikeldetail__
