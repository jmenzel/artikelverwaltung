#ifndef __lieferantdetail__
#define __lieferantdetail__

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
 * Die Klasse LieferantDetail erbt von wxFrame und ist ein eigenständiges Fenster.
 * Es stellt alle Eigenschaften eines Lieferanten anhand der ID dar.
 * Es zeigt ebenfalls alle Einträge aus der Tabelle liefert zu der ID an.
 * Die Klasse LieferantDetail ist einer der Ausgangspunkte um eine Verknüpfung zwischen
 * Lieferant und Artikel herzustellen.
 */
class LieferantDetail : public wxFrame
{

	public:
		/**
		 * @param MainWindow* parent - Zeiger auf MainWindowobjekt
		 * @param unsigned int lieferantId - ID des Lieferanten
		 */
		LieferantDetail(MainWindow *parent, unsigned int lieferantId);
		~LieferantDetail();
	private:
		//Attribute
		wxPanel *panel;
		
		wxStaticText *tlabel_name;
		wxStaticText *tlabel_strasse;
		wxStaticText *tlabel_plzOrt;
		wxStaticText *tlabel_telefon;
		wxStaticText *tlabel_telefax;
		wxStaticText *tlabel_email;
		wxStaticText *tlabel_createdate;
		
		wxTextCtrl *tfield_name;
		wxTextCtrl *tfield_strasse;
		wxTextCtrl *tfield_plz;
		wxTextCtrl *tfield_ort;
		wxTextCtrl *tfield_telefon;
		wxTextCtrl *tfield_telefax;
		wxTextCtrl *tfield_email;
		wxTextCtrl *tfield_createdate;
		
		wxTextCtrl *tfield_searchLiefert;
		
        wxListCtrl *listArtikelLieferant;
        
        wxButton *button_addLiefert;
        wxButton *button_deleteLiefert;

		wxDateTime *createDate;

        //Arrays
        wxArrayInt arr_db_list;
		
		//Zeiger auf Objekte
		MainWindow *main;
        DBCommand *db;
		
		//Zuletzt ausgewähltes Item der Liste
		int lastSelectedItem;
		
		//Anzahl der Spalten
        unsigned short listColumnCount;
		
		//Lieferant ID
		unsigned int lId;
		
		DECLARE_EVENT_TABLE()
		
		//IDs der GUI-Elemente
		enum
		{
			ID_PANEL,
			ID_TLABELNAME,
			ID_TLABELSTRASSE,
			ID_TLABELPLZORT,
			ID_TLABELTELEFON,
			ID_TLABELTELEFAX,
			ID_TLABELEMAIL,
			ID_TLABELCREATEDATE,
			ID_TFIELDNAME,
			ID_TFIELDSTRASSE,
			ID_TFIELDPLZ,
			ID_TFIELDORT,
			ID_TFIELDTELEFON,
			ID_TFIELDTELEFAX,
			ID_TFIELDEMAIL,
			ID_TFIELDCREATEDATE,
			ID_TFIELDSEARCHLIEFERT,
            ID_LISTARTIKELLIEFERANT,
            ID_BUTTONADDLIEFERT,
            ID_BUTTONDELETELIEFERT
		};
		
		
		//Methoden
		/**
		 * Instanziiert die GUI-Elemente
		 */
		void Initialize();
		
		/**
		 * Läd die Daten aus der DB
		 */
		void Update();
		
		/**
		 * Übergibt die Daten der Vektoren an die Textfelder
		 * @param vector< vector < wxString > > data - Daten des Lieferanten
		 */
		void FillLieferantData(vector< vector < wxString > > data);
		
		/**
		 * Übergibt die Daten der Vektoren an die wxListCtrl "listArtikelLieferant"
		 * @param vector< vector < wxString > > data - Daten des Tabelle "liefert"
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
		 * Erstellt ein neues LieferantArtikelConnect Objekt
		 */
        void EventOnClickAddLiefertButton(wxCommandEvent &event);
		
		/**
		 * Reagiert auf den "button_deleteLiefert" Button
		 * Löscht den Artikel in lastSelectedItem
		 */
        void EventOnClickDeleteLiefertButton(wxCommandEvent &event);
};
#endif // __lieferantdetail__
