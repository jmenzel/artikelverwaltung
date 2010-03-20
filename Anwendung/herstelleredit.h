#ifndef HERSTELLEREDIT_H
#define HERSTELLEREDIT_H

#include <wx/wx.h>
#include <wx/valtext.h>
#include <vector>

//Vorwärtsdeklarationen
class MainWindow;
class CallbackBase;

#include "callback.h"
#include "dbcommand.h"

using namespace std;

/**
 * Die Klasse HerstellerEdit erbt von wxFrame und ist ein eigenständiges Fenster.
 * Sie dient zum bearbeiten von Herstellern
 */
class HerstellerEdit : public wxFrame
{

	public:
		/**
		 * @param MainWindow* parent - Zeiger auf MainWindowobjekt
		 * @param unsigned int herstellerId - ID des Herstellers
		 */
		HerstellerEdit(MainWindow *parent, unsigned int herstellerId);
		~HerstellerEdit();
	
	private:
		//Attribute
        wxPanel *panel;
        
        wxStaticText *tlabel_name;
        wxStaticText *tlabel_strasse;
        wxStaticText *tlabel_plz_ort;
        wxStaticText *tlabel_telefon;
        wxStaticText *tlabel_fax;
        wxStaticText *tlabel_email;
        
        wxTextCtrl *tfield_name;
        wxTextCtrl *tfield_strasse;
        wxTextCtrl *tfield_plz;
        wxTextCtrl *tfield_ort;
        wxTextCtrl *tfield_telefon;
        wxTextCtrl *tfield_fax;
        wxTextCtrl *tfield_email;
        
        wxArrayString arr_val_plz;
        wxArrayString arr_val_telFax;
        wxArrayString arr_val_email;
        
        wxTextValidator *val_tfield_plz;
        wxTextValidator *val_tfield_telFax;
        wxTextValidator *val_tfield_email;
        
        wxButton *button_save;
             
        //Objekte
        DBCommand *db;
        
        //Zeiger auf andere Objekte
        MainWindow *main;
		
		unsigned int hId;
      
        DECLARE_EVENT_TABLE()
        
		//IDs der GUI-Elemente
        enum
        {
            ID_PANEL,
            ID_TLABEL_NAME,
            ID_TLABEL_STRASSE,
            ID_TLABEL_PLZORT,
            ID_TLABEL_TELEFON,
            ID_TLABEL_FAX,
            ID_TLABEL_EMAIL,
            ID_TFIELD_NAME,
            ID_TFIELD_STRASSE,
            ID_TFIELD_PLZ,
            ID_TFIELD_ORT,
            ID_TFIELD_TELEFON,
            ID_TFIELD_FAX,
            ID_TFIELD_EMAIL,
            ID_BUTTON_SAVE
        };
		
		//Methoden
		/**
		 * Übergibt die Daten der Vektoren an die Textfelder
		 * @param vector< vector < wxString > > data - Daten des Hertellers
		 */
		void FillHerstellerData(vector< vector< wxString > > data);
		
		//Event-Handler
		/**
		 * Reagiert auf Texteingabe im wxTextCtrl "tfield_name". Überprüft ob Textfeld
		 * leer. Aktiviert / Deaktiviert den Button "button_save"
		 */
        void EventTextChangedName(wxCommandEvent &event);
		
		/**
		 * Reagiert auf drücken des Buttons "button_save". Ruft db->updateHerstellerById auf,
		 * übergibt die Werte der Eingabemaske.
		 * Aktualisiert die Ansicht im HerstellerPanel.
		 * Erstellt beendet das Frame
		 */
        void EventOnClickButtonSave(wxCommandEvent &event);
};

#endif // HERSTELLEREDIT_H
