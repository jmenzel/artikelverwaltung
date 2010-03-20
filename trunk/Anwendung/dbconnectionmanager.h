#ifndef __dbconnectionmanager__
#define __dbconnectionmanager__

//Allgemeine Klassen
#include <wx/wx.h>
#include <vector>

//Eigene Klassen
#include "postgresql_connector.h"
#include "pq_multithread_wrapper.h"
#include "callbackbase.h"

/**
 * Die Klasse DBConnectionManager erstellt und verwaltet die Verbindungen zur Datenbank.
 * Sie gibt Threadsicher Datenbankverbindungen aus dem Pool an den Anfragenden und erstellt neue
 * Datenbankverbindungen, wenn keine freie Verbindung zur Verfügung steht. Nicht mehr benötigte
 * Verbindungen können über CheckDBIdleTime() beendet werden.
 */
class DBConnectionManager
{
public:
    //Funktionen
	/**
	 * Erstellt ein DBConnectionManager Objekt
	 */
    DBConnectionManager();

    ~DBConnectionManager();
    
	/**
	 * Setzt die Datenbankparameter für die Verbindung zur Datenbank
	 * @param wxString &db_ipadress - IP Adresse der Datenbank
	 * @param wxString &db_name - Der Name der Datenbank
	 * @param wxString &db_user - Der Name des Benuzter
	 * @param wxString &db_password - Das Passwort des Benutzers
	 */
    void SetDBData(wxString &db_ipadress, wxString &db_name, wxString &db_user, wxString &db_password);
    
	/**
	 * Erstellt n Verbindungen zur Datenbank. n = MinDBHandles
	 */
	bool Connect();
	
	/**
	 * Führt ein Befehl auf der Datenbank aus und gibt das Resultset zurück
	 * @param wxString sqlCommand - Das SQL Statement
	 * @return vector< vector< wxString > > - Resultset des SQL Statements
	 */
    vector< vector< wxString > > DBRunCommand( wxString sqlCommand );
	
	/**
	 * Führt einen Befehl auf der Datenbank in einem eigenen Thread aus und
	 * gibt das Resultset an die übergebene CallbakBase Referenz
	 * @param wxString sqlCommand - Das SQL Statement
	 * @param CallbackBase &cb - Referenz auf die Callback-Funktion
	 * @result unsigned short threadCreated - 1 Error: Thread konnte nicht gestartet werden
	 * @result unsigned short threadCreated - 0 Okay: Thread wurde gestartet
	 */
    unsigned short DBRunCommand( wxString sqlCommand, CallbackBase &cb );
	
	/**
	 * Führt einen Befehl auf der Datenbank aus und gibt zurück ob der Befehl
	 * erfolgreich ausgeführt wurde oder nicht.
	 * @param wxString sqlCommand - Das SQL Statement
	 * @result unsigned short QueryOkay - 1 Error: Befehl nicht erfolgreich ausgeführt
	 * @result unsigned short QueryOkay - 0 Okay: Befehl erfolgreich ausgeführt
	 */
	unsigned int DBRunCommandTest( wxString sqlCommand );
	
	/**
	 * Gibt die Anzahl der offenen Datenbankverbindungen zurück
	 * @return unsigned short countConnection
	 */
    unsigned short getCountConnections();
	
	/**
	 * Überprüft die Datenbankverbindgen auf inaktivität und beendet die Verbindungen, bei
	 * denen die IdleTime größer IdleTimeLimit. Wird nur ausgeführt wenn AnzahlVerbindungen größer
	 * MinDBHandles
	 */
	void CheckDBIdleTime();
	
	/**
	 * Gibt zurück, ob eine Verbindung zur Datenbank besteht
	 * @return bool isConnected (True | False)
	 */ 
	bool IsConnected();
	
	/**
	 * Beendet alle Verbindgungen zur Datenbank
	 */
	void CloseConnection();
private:
    //Attribute
    unsigned short MinDBHandles;
    unsigned short MaxDBHandles;
    unsigned short IdleTimeLimit;
	
	unsigned short handleCounter;
    
    wxString database;
    wxString host;
    wxString user;
    wxString password;
    
    vector< PostgreSQL_Connector* > DBHandleList;
            
    //Methoden
	/**
	 * Erstellt eine neue Verbindung zur Datenbank. Wird nur ausgeführt, 
	 * wenn AnzahlVerbindung kleiner MaxDBHandles
	 */
    void CreateNewDBHandle();
	
	/**
	 * Gibt eine freie Datenbankverbindung aus dem Pool zurück
	 * @return PostgreSQL_Connector* - Zeiger auf Datenbankverbindung
	 */
    PostgreSQL_Connector* GetDBHandle();
    
};
#endif // __dbconnectionmanager__
