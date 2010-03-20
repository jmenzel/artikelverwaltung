#ifndef HERSTELLERDETAIL_H
#define HERSTELLERDETAIL_H

#include <wx/wx.h>
#include <vector>
#include <wx/listctrl.h>
#include <wx/datetime.h>

//Vorwärtsdeklarationen
class MainWindow;

#include "callback.h"
#include "dbcommand.h"

using namespace std;

/**
 * Die Klasse HerstellerDetail erbt von wxFrame und ist ein eigenständiges Fenster.
 * Es zeigt alle Eigenschaften eines Herstellers anhand der ID dar. 
 */
class HerstellerDetail  : public wxFrame
{

	public:
		/**
		 * @param MainWindow* parent - Zeiger auf MainWindowobjekt
		 * @param unsigned int herstellerId - ID des Herstellers
		 */
		HerstellerDetail(MainWindow* parent, unsigned int herstellerId);
		~HerstellerDetail();

	private:
			//Attribute
			wxPanel *panel;
			
			wxStaticText *tlabel_name;
			wxStaticText *tlabel_strasse;
			wxStaticText *tlabel_plz_ort;
			wxStaticText *tlabel_telefon;
			wxStaticText *tlabel_fax;
			wxStaticText *tlabel_email;
			wxStaticText *tlabel_createDate;
			
			wxTextCtrl *tfield_name;
			wxTextCtrl *tfield_strasse;
			wxTextCtrl *tfield_plz;
			wxTextCtrl *tfield_ort;
			wxTextCtrl *tfield_telefon;
			wxTextCtrl *tfield_fax;
			wxTextCtrl *tfield_email;
			wxTextCtrl *tfield_createDate;
			
			wxButton *button_close;
				 
			wxDateTime *createDate;
			 
			//Zeiger auf Objekte
			MainWindow *main;
			DBCommand *db;
			
			//Hersteller ID
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
				ID_TFIELD_CREATEDATE,
				ID_BUTTON_CLOSE
			};
			
			/**
			 * Stellt die Daten der Vektoren in den Textfeldern dar.
			 * @param vector< vector< wxString > > data - Die Daten des Herstellers
			 */
			void FillHerstellerData(vector< vector< wxString > > data);
			
			/**
			 * Reagiert auf "button_close", beendet das Frame
			 */
			void EventOnClickButtonClose(wxCommandEvent &event);
};

#endif // HERSTELLERDETAIL_H
