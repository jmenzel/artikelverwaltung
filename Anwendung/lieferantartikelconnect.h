#ifndef __lieferantartikelconnect__
#define __lieferantartikelconnect__

#include <vector>
#include <wx/wx.h>
#include <wx/valtext.h>
#include <wx/calctrl.h>
#include <wx/listctrl.h>

//Vorwärtsdeklarationen
class MainWindow;

#include "callback.h"
#include "dbcommand.h"
#include "artikeldetail.h"

using namespace std;

/**
 * Die Klasse LieferantArtikelConnect erbt von wxFrame und ist ein eigenständiges Fenster.
 * Sie dient zum verknüpfen von Artikeln mit Lieferanten - Ausgangspunkt ist der Lieferant. 
 * Es können ArtikelAdd Objekte von dieser Maske aus erstellt werden
 */
class LieferantArtikelConnect  : public wxFrame
{
	public:
		/**
		 * Erstellt ein LieferantArtikelConnect Objekt
		 * @param MainWindow *parent - Zeiger auf MainWindow Objekt
		 * @param wxPoint m_position - Position des Aufrufenden Frames
		 * @param int lieferantId - ID des Lieferanten
		 */
        LieferantArtikelConnect(MainWindow *parent, wxPoint m_position, int lieferantId);
		
		/**
		 * Erstellt ein LieferantArtikelConnect Objekt
		 * @param MainWindow *parent - Zeiger auf MainWindow Objekt
		 * @param CallbackBase &caller_update - Referenz auf eine Callback-Funktion
		 * @param wxPoint m_position - Position des Aufrufenden Frames
		 * @param int lieferantId - ID des Lieferanten
		 */
        LieferantArtikelConnect(MainWindow *parent, CallbackBase &caller_update, wxPoint m_position, int lieferantId);
        ~LieferantArtikelConnect();
		    
    private:
        //Attribute
        wxPanel *panel;
        
        wxStaticText *tlabel_name;
        wxStaticText *tlabel_plzOrt;
        wxStaticText *tlabel_email;
        wxStaticText *tlabel_ek_preis;
        wxStaticText *tlabel_vh_date;
        wxStaticText *tlabel_artikel;
        
        wxTextCtrl *tfield_name;
        wxTextCtrl *tfield_plz;
        wxTextCtrl *tfield_ort;
        wxTextCtrl *tfield_email;
        wxTextCtrl *tfield_ek_preis;
        wxTextCtrl *tfield_artikel_search;
        
        wxCalendarCtrl *cal_vh_date;
        
		//Arrays
		wxArrayInt arr_db_list;
        wxArrayString arr_artikel;
        wxArrayString val_preis;
        
        wxTextValidator *val_tfield_preis;
        
        wxButton *button_artikel_add;
        wxButton *button_save;
        wxButton *button_abort;
		
        wxListCtrl *listArtikel;
		
		//Lieferanten ID
        int lId;
		
		//Zuletzt selektiertes Item der Liste
		int lastSelectedItem;
		
		//Anzahl der Spalten
        unsigned short listColumnCount;
        
		//Aufruf aus MainWindow oder anderem Frame?
        bool parent_check;
              
        //Zeiger auf andere Objekte
        MainWindow *main;
        DBCommand *db;
        CallbackBase *update;
        
        DECLARE_EVENT_TABLE()
        
		//IDs der GUI-Elemente
        enum
        {
            ID_PANEL,
            ID_TLABELLIEFERANTNAME,
            ID_TLABELLIEFERANTPLZORT,
            ID_TLABELLIEFERANTEMAIL,
            ID_TLABELLIEFERANTEKPREIS,
            ID_TLABELLIEFERANTVHDATE,
            ID_TLABELLIEFERANTARTIKEL,
            ID_TFIELDLIEFERANTNAME,
            ID_TFIELDLIEFERANTPLZ,
            ID_TFIELDLIEFERANTORT,
            ID_TFIELDLIEFERANTEMAIL,
            ID_TFIELDEKPREIS,
            ID_TFIELDARTIKELSEARCH,
            ID_CALVHDATE,
            ID_CHKLISTARTIKEL,
			ID_LISTARTIKEL,
            ID_BUTTONARTIKELADD,
            ID_BUTTONSAVE,
            ID_BUTTONABORT
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
        void FillLieferantData(vector< vector< wxString > > data);
		
		/**
		 * Übergibt die Daten der Vektoren an die wxListCtrl "listArtikel"
		 * @param vector< vector < wxString > > data - Daten der Artikel
		 */
		void FillListArtikel(vector< vector< wxString > > data);
		
		/**
		 * Überprüft die Eingabefelder und aktiviert den Button "button_save".
		 */
        void EnableButtonSave();
		
		//Event-Handler
		
		/**
		 * Reagiert auf Texteingabe im wxTextCtrl "tfield_artikel_search". Ruft db->getArtikelBySearch
		 * auf und übergibt die Texteingabe sowie "FillListArtikel" als Callback
		 */
		void EventTextChangedArtikelSearch(wxCommandEvent &event);
		
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
		 * 
		 * Auskommentiert, da aus dem Artikeldetail das Gegenstück zu LieferantArtikelConnect aufgerufen
		 * werden kann (ArtikelLieferantConnect).
		 */
		//void EventListItemActivated(wxListEvent &event);
		
		/**
		 * Reagiert auf Texteingabe im wxTextCtrl "tfield_ek_preis". Überprüft ob das Textfeld
		 * leer ist und aktiviert/deaktivert den Button "button_save"
		 */
		void EventTextChangedArtikelEKPreis(wxCommandEvent &event);
		
		/**
		 * Reagiert auf drücken des Buttons "button_save". Ruft db->addNewLiefert auf,
		 * übergibt die Werte der Eingabemaske.
		 * Ruft Callback auf.
		 * Erstellt neues LieferantArtikelConnect Objekt
		 */
        void EventOnClickSaveButton(wxCommandEvent &event);
		
		/**
		 * Reagiert auf drücken des Buttons "button_abort". Überprüft ob Eingaben vollständig.
		 * Wenn ja -> ruft db->addNewLiefert auf, übergibt die Werte der Eingabemaske, 
		 * Ruft Callback auf, Beendet das Frame
		 * Wenn nein -> Beendet das Frame
		 */
        void EventOnClickAbortButton(wxCommandEvent &event);
		
		/**
		 * Reagiert auf drücken des Buttons "button_artikel_add". Erstellt
		 * ein neues ArtikelAdd Objekt
		 */
		void EventOnClickArtikelAdd(wxCommandEvent &event);

};
#endif // __lieferantartikelconnect__
