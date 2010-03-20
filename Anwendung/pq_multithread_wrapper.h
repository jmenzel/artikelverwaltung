#ifndef __pq_multithread_wrapper__
#define __pq_multithread_wrapper__

#include "callbackbase.h"
#include "dbconnectionmanager.h"

#include <wx/wx.h>
#include <wx/thread.h>

/**
 * Die Klasse PQ_Multithread_Wrapper kapselt anfragen an die Datenbank in einen eigenen Thread
 * und gibt die Antwort an eine Callback-Funktion
 */
class PQ_Multithread_Wrapper : public wxThread
{
public:    
	/**
	 * Erstellt ein neues PQ_Multithread_Wrapper Objekt
	 * @param PostgreSQL_Connector *ps - Zeiger auf die Datenbankverbindung
	 * @param wxString &sql_command - Referenz des SQL-Statements
	 * @param CallbackBase &cb - Referenz auf Callback-Funktion
	 */
    PQ_Multithread_Wrapper(PostgreSQL_Connector *ps, wxString &sql_command, CallbackBase &cb);
        
    /**
	 * Hier wird der Thread gestartet, der Befehĺ wird an die DB gesendet und die
	 * Callback Funktion wird aufgerufen
	 */
    virtual void *Entry();

    /**
	 * Wenn der Thread beendet wird, gehts hier hinein
	 */
    virtual void OnExit();
    
private:
    wxString s;
    PostgreSQL_Connector *ps;
 
    CallbackBase *m_pcb;

};
#endif // __pq_multithread_wrapper__
