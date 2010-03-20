#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <wx/wx.h>

//Vorwärtsdeklarationen
class MainWindow;
#include "dbcommand.h"
#include "configurationmanager.h"
/**
 * Die Klasse SettingsPanel erbt von wxPanel und wird innerhaln vom MainWindow angezeigt.
 * Sie dient zur Eingabe der Konfigurationsparameter.
 */
class SettingsPanel : public wxPanel
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
		SettingsPanel(MainWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("panel"));
		~SettingsPanel();

	private:
	    wxStaticText *tlabel_headline;
		
		wxStaticText *tlabel_dbAdress;
		wxStaticText *tlabel_dbName;
		wxStaticText *tlabel_dbUser;
		wxStaticText *tlabel_dbPassword;
		
		wxTextCtrl *tfield_dbAdress;
		wxTextCtrl *tfield_dbName;
		wxTextCtrl *tfield_dbUser;
		wxTextCtrl *tfield_dbPassword;
		
		wxButton *button_save;
		wxButton *button_checkTableStructure;
		
		//Zeiger auf Objekte
		MainWindow *main;
		ConfigurationManager *config;
		DBCommand *db;
		
		//Ids der GUI-Elemente
		enum
		{
			ID_TLABEL_HEADLINE=20,
			ID_TLABEL_DBADRESS,
			ID_TLABEL_DBNAME,
			ID_TLABEL_DBUSER,
			ID_TLABEL_DBPASSWORD,
			ID_TFIELD_DBADRESS,
			ID_TFIELD_DBNAME,
			ID_TFIELD_DBUSER,
			ID_TFIELD_DBPASSWORD,
			ID_BUTTON_SAVE,
			ID_BUTTON_CHECKTABLESTRUCTURE
		};
		
		DECLARE_EVENT_TABLE()
		
		//Methoden
		/**
		 * Liest über den ConfigurationManager die Datenbankparameter aus der Konfigdatei ein
		 * und übergibt die Daten an die Textfelder.
		 */
		void FillDBConnectionData();
				
		//Event-Handler
		/**
		 * Speichert die eingegenen Daten der Textfelder über den ConfigurationManager in der
		 * Konfigdatei.
		 * Ruft main->getDBManageObject()->CloseConnection() auf um alle Verbindungen zur Datenbank zu
		 * beenden und übergibt mit main->getDBManageObject()->SetDBData() die neuen Daten an das 
		 * DBConnectionManager Objekt
		 */
		void EventOnClickButtonSave(wxCommandEvent &event);
		
		/**
		 * Prüft die TabellenStruktur der Datenbank
		 * Ruft db->checkTableStruktur auf
		 */
		void EventOnClickCheckTableStructure(wxCommandEvent &event);

};

#endif // SETTINGSPANEL_H