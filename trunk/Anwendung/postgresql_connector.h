#ifndef __postgresql_connector__
#define __postgresql_connector__

#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <wx/wx.h>
#include <time.h>


#ifdef __WIN32__
	#include "vc8\include\libpq-fe.h"
#else
   #include <postgresql/libpq-fe.h>
#endif


using namespace std;

/**
 * Die Klasse PostgreSQL_Connector bietet eine ObjektOrientierte Schnittstelle zur
 * C-Api von PostgreSQL und implementiert wxWidgets Funktionalität
 */

class PostgreSQL_Connector 
{
public:
    PostgreSQL_Connector();
    PostgreSQL_Connector(const PostgreSQL_Connector& orig);
    PostgreSQL_Connector(char const *database, char const *host, char const *user, char const *password);
    PostgreSQL_Connector(char const *database, char const *host, char const *user, char const *password, bool connect);
	PostgreSQL_Connector(char const *database, char const *host, char const *user, char const *password, bool connect, unsigned short id);
    virtual ~PostgreSQL_Connector();

    //Setter Methoden
	/**
	 * Setzt den Datenbanknamen
	 * @param string dbName - Name der Datenbank
	 */
    void setDatabase(string dbName);
	
	/**
	 * Setzt die Datenbank IP-Adresse
	 * @param string hostIP - IP-Adresse der Datenbank
	 */
    void setHost(string hostIP);
	
	/**
	 * Setzt den Datenbank User
	 * @param string userName - User der Datenbank
	 */
    void setUser(string userName);
	
	/**
	 * Setzt das Datenbank Passwort
	 * @param string password - Passwort des Datenbankbenutzers
	 */
    void setPassword(string password);
    
	/**
	 * Verbindung zur Datenbank herstellen
	 */
    bool connect();
	
	/**
	 * Prüfen, ob eine Verbindung zur Datenbank besteht
	 * @return bool isConnected (True | False)
	 */
    bool isConnected();
	
	/**
	 * Prüfen, ob Verbindung in Benutzung ist
	 * @return bool isBusy (True | False)
	 */
    bool isBusy();
	
	/**
	 * Prüfen, ob die Verbindung durch einen Thread geperrt ist
	 * @return isLocked (True | False)
	 */
	bool isLocked();
	
	/**
	 * Die Verbindung für diesen Thread sperren
	 */
	void lock();
	
	/**
	 * Sperre der Verbindung aufheben
	 */
	void unlock();
	
	/**
	 * Gibt die Anzahl der Sekunden seid der letzten Aktion zurück
	 * @return unsigned int idleTimeInSek - Anzahl Sekunden der Inaktivität
	 */
    unsigned int getIdleTime();
    
	/**
	 * Führt einen Befehlt auf der Datenbank auf und speichert das Resultset in der
	 * vector - Referenz
	 * @param string sqlStatement - Das SQL-Statement
	 * @param vector< vector<string> > &result - Referenz auf Speicher-Vektor
	 * @return status - Status der Abfrage
	 */
    int runCommand(string sqlStatement, vector< vector<string> > &result);
	
	/**
	 * Führt einen Befehlt auf der Datenbank auf und speichert das Resultset in der
	 * vector - Referenz
	 * @param wxString sqlStatement - Das SQL-Statement
	 * @param vector< vector<wxString> > &result - Referenz auf Speicher-Vektor
	 * @return status - Status der Abfrage
	 */
    int runCommand(wxString sqlStatement, vector< vector<wxString> > &result);
	
	/**
	 * Führt einen Befehlt auf der Datenbank auf und speichert das Resultset in der
	 * vector - Referenz
	 * @param wxString sqlStatement - Das SQL-Statement
	 * @param vector< vector<wxString> > *result - Zeiger auf Speicher-Vektor
	 * @return status - Status der Abfrage
	 */
    int runCommand(wxString sqlStatement, vector< vector<wxString> > *result);
	
	/**
	 * Führt einen Befehlt auf der Datenbank auf und gibt den Status der Abfrage zurück
	 * @param wxString sqlStatement - Das SQL-Statement
	 * @param bool DEBUG - DEBUG Flag - Wenn True, wird Status des Abfrage in StandartErrorStream geschríeben
	 * @return status - Status der Abfrage
	 */
    int runCommand(string sqlStatement, bool DEBUG);
	
	/**
	 * Führt einen Befehlt auf der Datenbank auf und gibt den Status der Abfrage zurück
	 * @param wxString sqlStatement - Das SQL-Statement
	 * @return status - Status der Abfrage
	 */
    int runCommand(wxString sqlStatements);
	
	/**
	 * Der Name der Verbindung
	 */
	wxString name;
private:
    //Attribute
    PGconn *conn;
    
    string database;
    string host;
    string user;
    string password;
    
    bool busy;
    unsigned int lastAction;
	bool thread_lock;
		
    //Methoden
    void setLastAction();
    bool checkConnectionData();
    
    /*
    char *database;
    char *host;
    char *user;
    char *password;
    */
};
#endif // __postgresql_connector__
