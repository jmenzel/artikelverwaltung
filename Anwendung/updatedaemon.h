#ifndef UPDATEDAEMON_H
#define UPDATEDAEMON_H

#include <wx/wx.h>
#include <wx/thread.h>

//Vorwärtsdeklaration
class MainWindow;

#include "dbconnectionmanager.h"
#include "configurationmanager.h"

/**
 * Der UpdateDaemon läuft, sobald instanziiert, bis zum beenden des Programms
 * im Hintergrund in einem eigenen Thread. Er überprüft die inaktiven Datenbankberbindungen und
 * sperrt die GUI, wenn die Verbindung zur DB verloren geht. Er baut die Verbindung wieder auf,
 * wenn die DB wieder erreichbar ist.
 */
class UpdateDaemon : public wxThread
{

	public:
		/**
		 * Erstellt ein UpdateDaemon Objekt
		 * @param MainWindow *parent - Zeiger auf MainWindow
		 */
		UpdateDaemon(MainWindow *parent);
		~UpdateDaemon();
		
		/**
		 * In einer endlosschleife werden Operationen ausgeführt
		 */
		virtual void *Entry();
		virtual void OnExit();

	private:
		//Zeiger auf Objekte
		MainWindow *main;
		DBConnectionManager *db;
		ConfigurationManager *conf;
};

#endif // UPDATEDAEMON_H
