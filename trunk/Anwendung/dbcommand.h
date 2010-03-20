#ifndef __dbcommand__
#define __dbcommand__

#include <wx/string.h>
#include <vector>

#include "callbackbase.h"
#include "dbconnectionmanager.h"

using namespace std;
class DBCommand 
{

	public:
		/**
		 * Erstellt ein DBCommand Objekt
		 * @param DBConnectionManager *dbHandle - Zeiger auf DBConnectionManager Objekt
		 */
		DBCommand(DBConnectionManager *dbHandle);
		~DBCommand();
		
		/**
		 * Führt Befehl über den DBConnectionManager in eigenem Thread 
		 * aus und gibt die Rückgabe an die Callback-Funktion
		 * @param wxString command - Das SQL Statement
		 * @param CallbackBase &cb - Referenz auf Callback-Funktion
		 */
		void run(wxString command, CallbackBase &cb);
		
		/**
		 * Führt Befehl über den DBConnectionManager aus und gibt die Rückgabe an
		 * zurück
		 * @param wxString command - Das SQL Statement
		 * @return vector< vector < wxString > > - Resultset des Statements
		 */
        vector< vector < wxString > > run(wxString command);
		
		/**
		 * Führt Befehl über den DBConnectionManager TestZweig aus und zurück ob der 
		 * Befehl erfolgreich ausgeführt wurde
		 * @param wxString command - Das SQL Statement
		 * @param bool test - identifier TestZweig
		 * @return unsigned short - QueryCode [1-Error | 0-Success]
		 */
        unsigned int run(wxString command, bool test);
             
        //Artikel
        void getAllArtikelValues(CallbackBase &cbHandle);
        void getArtikelBySearch(CallbackBase &cbHandle, wxString &seq);
        void getArtikelById(CallbackBase &cbHandle, unsigned int artId);
        void deleteArtikelById(unsigned int id);
        void deleteArtikelByHerstellerId(unsigned int id);
		void getCountArtikelByNr(CallbackBase &cbHandle, wxString nr);
        int addNewArtikel(wxString artikelNr, wxString preis, wxString beschreibung, int herstellerId);
        void updateArtikelById(unsigned int artId, wxString artikelNr, wxString preis, wxString beschreibung, int herstellerId);
        
        //Lieferant
        void getAllLieferantValues(CallbackBase &cbHandle);
		void getLieferantById(CallbackBase &cbHandle, int lieferantId);
        void getLieferantBySearch(CallbackBase &cbHandle, wxString &seq);
        void deleteLieferantById(unsigned int id);
        int addNewLieferant(wxString name, wxString strasse=wxT(""), wxString plz=wxT(""), wxString ort=wxT(""), wxString telefon=wxT(""), wxString fax=wxT(""), wxString email=wxT(""));
		void updateLieferantById(unsigned int lieferantId, wxString name, wxString strasse=wxT(""), wxString plz=wxT(""), wxString ort=wxT(""), wxString telefon=wxT(""), wxString fax=wxT(""), wxString email=wxT(""));
        
        //Hersteller
        void getAllHerstellerValues(CallbackBase &cbHandle);
		void getHerstellerById(CallbackBase &cbHandle, unsigned int herstellerId);
        void getHerstellerBySearch(CallbackBase &cbHandle, wxString &seq);
        void deleteHerstellerById(unsigned int id);
        int addNewHersteller(wxString name, wxString strasse=wxT(""), wxString plz=wxT(""), wxString ort=wxT(""), wxString telefon=wxT(""), wxString fax=wxT(""), wxString email=wxT(""));
		void updateHerstellerById(unsigned int herstellerId, wxString name, wxString strasse=wxT(""), wxString plz=wxT(""), wxString ort=wxT(""), wxString telefon=wxT(""), wxString fax=wxT(""), wxString email=wxT(""));
        
        //Liefert
        void addNewLiefert(unsigned int artikelId, unsigned int lieferantId, wxString ekPreis, wxString vhdate);
        void deleteLiefertById(unsigned int liefertId);
        void deleteLiefertByArtikelId(unsigned int artId);
        void deleteLiefertByLieferantId(unsigned int lieferantId);
		void deleteLiefertByHerstellerId(unsigned int herstellerId);
        void getArtikelLieferantByArtId(CallbackBase &cbHandle, unsigned int artId);
        void getArtikelLieferantByArtIdBySearch(CallbackBase &cbHandle, unsigned int artId, wxString &seq);
		void getLieferantArtikelByLieferantId(CallbackBase &cbHandle, unsigned int lieferantId);
		void getLieferantArtikelByLieferantIdBySearch(CallbackBase &cbHandle, unsigned int lieferantId, wxString &seq);
		
		//Überprüfung der DBStruktur
		bool checkTableStruktur();
		wxString insertTableStruktur();
	private:
		//Zeiger auf DBConnectionManager
		DBConnectionManager *db;
};
#endif // __dbcommand__
