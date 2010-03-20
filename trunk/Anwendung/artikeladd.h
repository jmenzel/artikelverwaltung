#ifndef __artikeladd__
#define __artikeladd__

#include <wx/wx.h>
#include <wx/valtext.h>
#include <vector>

//Vorwärtsdeklarationen
class MainWindow;

#include "callback.h"
#include "dbcommand.h"
#include "herstelleradd.h"
#include "artikellieferantconnect.h"

using namespace std;

/**
 * Die Klasse ArtikelAdd erbt von wxFrame und ist ein eigenständiges Fenster.
 * Sie dient zum Anlegen eines neuen Artikels. Es können HerstellerAdd Objekte
 * von dieser Maske aus erstellt werden
 */
class ArtikelAdd : public wxFrame
{

	public:
		/**
		 * Erstellt ein ArtikelAdd Objekt
		 * @param MainWindow *parent - Zeiger auf MainWindow Objekt
		 */
        ArtikelAdd(MainWindow *parent);
		
		/**
		 * Erstellt ein ArtikelAdd Objekt
		 * @param MainWindow *parent - Zeiger auf MainWindow Objekt
		 * @param CallbackBase &caller_update - Referenz auf eine Callbackfunktion (CallbackBase Objekt)
		 */
		ArtikelAdd(MainWindow *parent, CallbackBase &caller_update);
        ~ArtikelAdd();
        
    private:
        //Attribute
        wxPanel *panel;
        
        wxStaticText *tlabel_nr;
        wxStaticText *tlabel_beschreibung;
        wxStaticText *tlabel_preis;
        wxStaticText *tlabel_hersteller;
        
        wxTextCtrl *tfield_nr;
        wxTextCtrl *tfield_beschreibung;
        wxTextCtrl *tfield_preis;
        wxTextCtrl *tfield_hersteller_search;
        
        wxCheckListBox *chklist_herstellerBox;
        
        wxArrayString arr_hersteller;
        wxArrayString val_preis;
        wxArrayInt arr_db_list;
        
        wxTextValidator *val_tfield_preis;
        
        wxButton *button_hersteller_add;
        wxButton *button_save;
        
		//Ist die Artikelnummer bereits Validiert?
        bool artikelNrValidated;
		
		//Aufruf aus MainWindow oder anderem Frame?
		bool parent_check;
		
		//Zuletzt ausgewähltes Item der Liste
        int lastSelectedItem;

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
            ID_TFIELDNR,
            ID_TFIELDBESCHREIBUNG,
            ID_TFIELDPREIS,
            ID_CHKLISTHERSTELLERBOX,
            ID_TFIELDHERSTELLERSEARCH,
            ID_BUTTONHERSTELLERADD,
            ID_BUTTONSAVE
        };
        
        //Methoden
		/**
		 * Instanziiert die GUI-Elemente
		 */
		void Initialize();
		
		/**
		 * Übergibt die Daten der Vektoren an die wxCheckListBox "chklist_herstellerBox"
		 * @param vector< vector < wxString > > data - Daten der Hersteller
		 */
        void FillChkListHersteller(vector< vector< wxString > > data);
		
		/**
		 * Stellt dar, ob die Artikel Nummer bereits vergeben ist.
		 * @param vector< vector < wxString > > data - Count(ArtikelNr) = 0 / 1
		 */
        void ValidateUniqueArtikelNr(vector< vector< wxString > > data);
		
		/**
		 * Läd die Daten aus der DB
		 */
        void Update();
		
		/**
		 * Überprüft die Eingabefelder und aktiviert den Button "button_save".
		 */
        void EnableButtonSave();
		
		/**
		 * Reagiert auf die Selektion eines Eintrages in der wxCheckListBox "chklist_herstellerBox".
		 * Stellt sicher, das immer nur ein Eintrag selektiert ist. Setzt die Variable lastSelectedItem
		 */
        void EventOnClickChkListBox(wxCommandEvent &event);
		
		/**
		 * Reagiert auf Texteingabe im wxTextCtrl "tfield_nr". Ruft db->getCountArtikelByNr auf
		 * und übergibt die Texteinhabe sowie "ValidateUniqueArtikelNr" als Callback
		 */
        void EventTextChangedArtikelnummer(wxCommandEvent &event);
		
		/**
		 * Reagiert auf Texteingabe im wxTextCtrl "tfield_hersteller_search". Ruft db->getHerstellerBySearch
		 * auf und übergibt die Texteingabe sowie "FillChkListHersteller" als Callback
		 */
        void EventTextChangedHerstellerSearch(wxCommandEvent &event);
		
		/**
		 * Reagiert auf Texteingabe im wxTextCtrl "tfield_preis". Überprüft ob das Textfeld
		 * leer ist und aktiviert/deaktivert den Button "button_save"
		 */
        void EventTextChangedArtikelPreis(wxCommandEvent &event);
		
		/**
		 * Reagiert auf drücken des Buttons "button_hersteller_add". Erstellt
		 * ein neues HerstellerAdd Objekt
		 */
        void EventOnClickHerstellerAddButton(wxCommandEvent &event);
		
		/**
		 * Reagiert auf drücken des Buttons "button_save". Ruft db->addNewArtikel auf,
		 * übergibt die Werte der Eingabemaske und bekommt die Id des Datensatzes zurück.
		 * Ruft die Callback-Funktions auf.
		 * Erstellt neues ArtikelLieferantConnect Objekt und übergibt die Datensatz Id.
		 */
        void EventOnClickSaveButton(wxCommandEvent &event);
};
#endif // __artikeladd__
