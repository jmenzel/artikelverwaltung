#ifndef __artikellieferantconnect__
#define __artikellieferantconnect__

#include <vector>
#include <wx/wx.h>
#include <wx/valtext.h>
#include <wx/calctrl.h>

//Vorwärtsdeklarationen
class MainWindow;
//class ArtikelDetail;

#include "callback.h"
#include "dbcommand.h"
//#include "lieferantadd.h"

using namespace std;

/**
 * Die Klasse ArtikelLieferantConnect erbt von wxFrame und ist ein eigenständiges Fenster.
 * Sie dient zum verknüpfen von Artikeln mit Lieferanten - Ausgangspunkt ist der Artikel. 
 * Es können LieferantAdd Objekte von dieser Maske aus erstellt werden
 */
class ArtikelLieferantConnect : public wxFrame
{

	public:
		/**
		 * Erstellt ein ArtikelLieferantConnect Objekt
		 * @param MainWindow *parent - Zeiger auf MainWindow Objekt
		 * @param wxPoint m_position - Position des Aufrufenden Frames
		 * @param int artikelId - ID des Artikels
		 */
        ArtikelLieferantConnect(MainWindow *parent, wxPoint m_position, int artikelId);

		/**
		 * Erstellt ein ArtikelLieferantConnect Objekt
		 * @param MainWindow *parent - Zeiger auf MainWindow Objekt
		 * @param CallbackBase &caller_update - Referenz auf eine Callback-Funktion
		 * @param wxPoint m_position - Position des Aufrufenden Frames
		 * @param int artikelId - ID des Artikels
		 */
        ArtikelLieferantConnect(MainWindow *parent, CallbackBase &caller_update, wxPoint m_position, int artikelId);
        ~ArtikelLieferantConnect();

    private:
        //Attribute
        wxPanel *panel;
        
        wxStaticText *tlabel_nr;
        wxStaticText *tlabel_preis;
        wxStaticText *tlabel_hersteller;
        wxStaticText *tlabel_ek_preis;
        wxStaticText *tlabel_vh_date;
        wxStaticText *tlabel_lieferant;
        
        wxTextCtrl *tfield_artikelnummer;
        wxTextCtrl *tfield_artikel_vk_preis;
        wxTextCtrl *tfield_artikel_hersteller;
        wxTextCtrl *tfield_lieferant_search;
        wxTextCtrl *tfield_artikel_ek_preis;
        
        wxCalendarCtrl *cal_vh_date;
        
        wxCheckListBox *chklist_lieferantBox;
        wxArrayInt arr_db_list;
        wxArrayString arr_lieferant;
        wxArrayString val_preis;
        wxTextValidator *val_tfield_preis;
        
        wxButton *button_lieferant_add;
        wxButton *button_save;
        wxButton *button_abort;
        
		//Artikel ID
        int artId;
		
		//Zuletzt selektiertes Item der Liste
        int lastSelectedItem;
        
		//Aufruf aus MainWindow oder anderem Frame?
        bool parent_check;
        
        //Zeiger auf Objekte
        MainWindow *main;
        DBCommand *db;
        CallbackBase *update;
        
        DECLARE_EVENT_TABLE()
        
		//IDs der GUI-Elemente
        enum
        {
            ID_PANEL,
            ID_TLABELNR,
            ID_TLABELBESCHREIBUNG,
            ID_TLABELPREIS,
            ID_TLABELHERSTELLER,
            ID_TLABELLIEFERANT,
            ID_TLABELEKPREIS,
            ID_TLABELVHDATE,
            ID_TFIELDARTIKELNUMMER,
            ID_TFIELDARTIKELVKPREIS,
            ID_TFIELDARTIKELHERSTELLER,
            ID_TFIELDARTIKELEKPREIS,
            ID_CALVHDATE,
            ID_CHKLISTLIEFERANTBOX,
            ID_TFIELDLIEFERANTSEARCH,
            ID_BUTTONLIEFERANTADD,
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
		 * @param vector< vector < wxString > > data - Daten des Artikels
		 */
        void FillArtikelData(vector< vector< wxString > > data);
		
		/**
		 * Übergibt die Daten der Vektoren an die wxCheckListBox "chklist_lieferantBox"
		 * @param vector< vector < wxString > > data - Daten der Lieferanten
		 */
        void FillChkListLieferant(vector< vector< wxString > > data);
		
		/**
		 * Überprüft die Eingabefelder und aktiviert den Button "button_save".
		 */
        void EnableButtonSave();
		
		/**
		 * Reagiert auf die Selektion eines Eintrages in der wxCheckListBox "chklist_lieferantBox".
		 * Stellt sicher, das immer nur ein Eintrag selektiert ist. Setzt die Variable lastSelectedItem
		 */
        void EventOnClickChkListBox(wxCommandEvent &event);
		
		/**
		 * Reagiert auf Texteingabe im wxTextCtrl "tfield_lieferant_search". Ruft db->getLieferantBySearch
		 * auf und übergibt die Texteingabe sowie "FillChkListLieferant" als Callback
		 */
        void EventTextChangedLieferantSearch(wxCommandEvent &event);
		
		/**
		 * Reagiert auf Texteingabe im wxTextCtrl "tfield_artikel_ek_preis". Überprüft ob das Textfeld
		 * leer ist und aktiviert/deaktivert den Button "button_save"
		 */
        void EventTextChangedArtikelEKPreis(wxCommandEvent &event);
		
		/**
		 * Reagiert auf drücken des Buttons "button_lieferant_add". Erstellt
		 * ein neues LieferantAdd Objekt
		 */
        void EventOnClickLieferantAdd(wxCommandEvent &event);
		
		/**
		 * Reagiert auf drücken des Buttons "button_save". Ruft db->addNewLiefert auf,
		 * übergibt die Werte der Eingabemaske.
		 * Ruft Callback auf.
		 * Erstellt neues ArtikelLieferantConnect Objekt
		 */
        void EventOnClickSaveButton(wxCommandEvent &event);
		
		/**
		 * Reagiert auf drücken des Buttons "button_abort". Überprüft ob Eingaben vollständig.
		 * Wenn ja -> ruft db->addNewLiefert auf, übergibt die Werte der Eingabemaske, 
		 * Ruft Callback auf, Beendet das Frame
		 * Wenn nein -> Beendet das Frame
		 */
        void EventOnClickAbortButton(wxCommandEvent &event);
};
#endif // __artikellieferantconnect__
