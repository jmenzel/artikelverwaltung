#include "updatedaemon.h"
#include "mainwindow.h"


UpdateDaemon::UpdateDaemon(MainWindow *parent)
{
	this->main = parent;
	this->db = main->getDBManageObject();
	this->conf = main->getConfigManageObject();
	
	if ( this->Create() != wxTHREAD_NO_ERROR )
    {
		cerr << "Konnte Updater nicht Starten" << endl;
	}
	else
	{
		//Thread Starten
		this->Run();
	}
}

UpdateDaemon::~UpdateDaemon()
{
}

void UpdateDaemon::OnExit()
{
	
}


void *UpdateDaemon::Entry()
{
	int counter = 1;
	for(;;)
	{
		//GUI Thread reservieren
		//wxMutexGuiEnter();
		
		//Prüfen, ob eine Verbindung zur Datenbank besteht
		if(db->IsConnected())
		{
			//Wenn die GUI noch gesperrt ist, entsperre sie jetzt
			if(this->main->IsLocked())
			{
				this->main->Unlock();
			}
			
			//Inaktive Datenbankverbindungen beenden
			this->db->CheckDBIdleTime();
			
			//Testausgabe - Anzahl der Datenbankverbindugnen und Anzahl Schleifendurchlauf
			wxString msg = wxT("");
			msg << counter;
			msg << wxT(". durchlauf - ");
			msg << db->getCountConnections();
			msg << wxT(" offene Verbindungen");
			
			wxMutexGuiEnter();
			main->SetStatusText(msg);
			wxMutexGuiLeave();
		}
		else
		{
			//Wenn die GUI noch nicht gesperrt ist, dann sperre sie jetzt
			if(!this->main->IsLocked())
			{
				this->main->Lock();
			}
			
			//Sind noch Handles da, dann beenden
			if(db->getCountConnections() > 0)
			{
				db->CloseConnection();
			}
			
			//Versuchen, eine Verbindung zur Datenbank aufzubauen
			if(!db->Connect())
			{
				wxMutexGuiEnter();
				
				/** 
				 * Wenn keine Verbindung zur DB besteht, SettingsPanel
				 * anzeigen, um DBParameter zu ändern
				 */
				if(main->getSettingsPanelObject() != NULL)
				{
					main->getSettingsPanelObject()->Show(true);
				}
				
				main->SetStatusText(wxT("Unable to connect to database"));
				wxMutexGuiLeave();
			}
			else
			{
				wxMutexGuiEnter();
				main->SetStatusText(wxT("Connected to Database"));
				wxMutexGuiLeave();
			}
		}
		//wxMutexGuiLeave();
		
		//cerr << "Ich Laufe zum " << counter << " mal" << endl;
		++counter;
		
		//Bis zum nächsten durch lauf 2 Sekunden warten
		this->Sleep(2000);
	}
}