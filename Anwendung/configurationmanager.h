#ifndef __configurationmanager__
#define __configurationmanager__

#include <wx/wx.h>
#include <wx/config.h>

/**
 * Die Klasse ConfigurationManager erbt von wxConfig. Sie stellt Funktionalitäten
 * bereit, Konfigurationsparameter dauerhaft zu speichern.
 */

class ConfigurationManager : public wxConfig
{

	public:
		/**
		 * Erstellt ein ConfigurationManager Objekt. 
		 * Prüft, ob eine Konfigurationsdatei existiert und legt eine
		 * leere Konfiguration an, wenn keine existiert
		 * @param wxString applicationName - Name des Programms
		 */
        ConfigurationManager(wxString applicationName);
        ~ConfigurationManager();
        
        //Getter
		/**
		 * Gibt die Datenbank IP-Adresse zurück
		 * @return wxString &db_ipadress;
		 */
        wxString &GetDBIPAdress();
		
		/**
		 * Gibt den Datenbank Namen zurück
		 * @return wxString &db_name
		 */
        wxString &GetDBName();
		
		/**
		 * Gibt den Datenbank Benutzernamen zurück
		 * @return wxString &db_user
		 */
        wxString &GetDBUser();
		
		/**
		 * Gibt das Datenbank Benutzerpasswort zrück
		 * @return wxString &db_password
		 */
        wxString &GetDBPassword();
        
        //Setter
		/**
		 * Setzt die Datenbank IP-Adresse
		 * @param wxString newDBIPAdress
		 */
        void SetDBIPAdress(wxString newDBIPAdress);
		
		/**
		 * Setzt den Datenbank Namen
		 * @param wxString newDBName
		 */
        void SetDBName(wxString newDBName);
		
		/**
		 * Setzt den Datenbank Benutzernamen
		 * @param wxString newDBUser
		 */
        void SetDBUser(wxString newDBUser);
		
		/**
		 * Setzt das Datenbank Benutzerpasswort
		 * @param wxString newDBPassword
		 */
        void SetDBPassword(wxString newDBPassword);
        
		/**
		 * Läd die Konfiguration aus der Datei
		 */
        void LoadConfig();
		
		/**
		 * Speichert die Konfiguration in der Datei
		 */
        void SaveConfig();
		
		/**
		 * Prüft ob eine Konfigurationsdatei existiert
		 */
        bool CheckConfigExists();
        
	private:
		//Attribute
        wxString db_ipadress;
        wxString db_name;
        wxString db_user;
        wxString db_password;

};
#endif // __configurationmanager__
