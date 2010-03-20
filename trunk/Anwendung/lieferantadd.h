#ifndef __lieferantadd__
#define __lieferantadd__

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
 * Die Klasse LieferantAdd erbt von wxFrame und ist ein eigenständiges Fenster.
 * Sie dient zum anlegen von Lieferanten
 */

class LieferantAdd : public wxFrame
{

	public:
		/**
		 * @param MainWindow* parent - Zeiger auf MainWindowobjekt
		 */
        LieferantAdd(MainWindow *parent);
		
		/**
		 * @param MainWindow* parent - Zeiger auf MainWindowobjekt
		 * @param CallbackBase &caller_update - Referenz auf Callback-Funktion
		 */
        LieferantAdd(MainWindow *parent, CallbackBase &caller_update);
        
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
		 * Instanziiert die GUI-Elemente
		 */
        void Initialize();
		
        //Event-Handler
		/**
		 * Reagiert auf Texteingabe im wxTextCtrl "tfield_name". Überprüft ob Textfeld
		 * leer. Aktiviert / Deaktiviert den Button "button_save"
		 */
        void EventTextChangedName(wxCommandEvent &event);
		
		/**
		 * Reagiert auf drücken des Buttons "button_save". Ruft db->addNewLieferant auf,
		 * übergibt die Werte der Eingabemaske und bekommt die Id des Datensatzes zurück.
		 * Ruft die Callback-Funktions auf.
		 * Beendet das Frame
		 */
        void EventOnClickButtonSave(wxCommandEvent &event);
};
#endif // __lieferantadd__
