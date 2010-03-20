#include "dbconnectionmanager.h"

DBConnectionManager::DBConnectionManager()
{  
    MinDBHandles = 1;
    MaxDBHandles = 6;
    IdleTimeLimit = 45;
	
	handleCounter = 0;
}

DBConnectionManager::~DBConnectionManager()
{
}

void DBConnectionManager::SetDBData(wxString &db_ipadress, wxString &db_name, wxString &db_user, wxString &db_password)
{
    this->host = db_ipadress;
    this->database = db_name;
    this->user = db_user;
    this->password = db_password;
}

bool DBConnectionManager::Connect()
{
	if(host.Length() > 0 && database.Length() > 0 && user.Length() > 0)
	{
		//DB Handles erzeugen
		for(int i = 0; i < MinDBHandles; ++i)
		{
			this->CreateNewDBHandle();
		}
    
		return (DBHandleList.size() > 0) ? true : false;
	}
	else
	{
		return false;
	}
}

/**
 * Erstellt einen neuen DBHandle, sofern das
 * Limit nicht überschritten ist
 */
void DBConnectionManager::CreateNewDBHandle()
{
    if( DBHandleList.size() < MaxDBHandles )
    {
		++handleCounter;
        PostgreSQL_Connector *ps = new PostgreSQL_Connector(database.mb_str(wxConvUTF8), host.mb_str(wxConvUTF8), user.mb_str(wxConvUTF8), password.mb_str(wxConvUTF8), true, handleCounter);
        if(ps->isConnected())
        {
            DBHandleList.push_back(ps);  
        }
    }
}

/**
 * Gibt einen verfügbaren DBHandle zurück, und erstellt,
 * einen neuen, wenn keine Handles verfügbar sind und das
 * Limit noch nicht überschritten ist.
 */
PostgreSQL_Connector* DBConnectionManager::GetDBHandle()
{
    unsigned short counter = 0;
    while(true)
    {
        //this->CheckDBIdleTime();
        
        if(counter >= 20)
        {
			//Und wieder von vorn =)
            counter = 0;
			
			//Immernoch kein Handle frei? Neues erstellen
			this->CreateNewDBHandle();
        }
        
        if(this->DBHandleList.size() > 0)
        {
            for(unsigned short i = 0; i < this->DBHandleList.size(); ++i)
            {
                if(DBHandleList[i])
                {
					if(!DBHandleList[i]->isLocked())
					{
						DBHandleList[i]->lock();
						
						if(DBHandleList[i]->isConnected())
						{
							if(!DBHandleList[i]->isBusy())
							{
								//Alles supi, und ab dafür
								return DBHandleList[i];
							}
						}
						else
						{
							//Na, dem ist wohl schlecht geworden, wech damit
							DBHandleList[i]->~PostgreSQL_Connector();
							DBHandleList.erase(DBHandleList.begin() + i);
							
							//Wir stoppen hier mal lieber, damit die Zählerschleife nicht ins trudeln kommt
							//man weiß ja nie :P
							break;
						}
						DBHandleList[i]->unlock();
					}
                }
            }
        }
        else
        {
            //Kein Handle drin? Eigenartig, dann machen wir mal ein neues auf
            this->CreateNewDBHandle();
        }
        
        ++counter;
    }

}

/**
 * Prüfen, ob mehr als benötigte DBHandles offen sind.
 * Sind mehr als benötigt offen, dann lösche die nicht
 * mehr benötigten Handles;
 */
void DBConnectionManager::CheckDBIdleTime()
{
    if(this->DBHandleList.size() > MinDBHandles)
    {
        while(true)
        {
			//Prüfen, ob noch ein DB Handle in der Liste ist, da sonst eine Endlosschleife produziert wird
			if(this->DBHandleList.size() == 0)
			{
				return;
			}
			
            //PostgreSQL_Connector *ps;
            for(unsigned short i = 0; i < this->DBHandleList.size(); ++i)
            {
                unsigned int akt_idle = DBHandleList[i]->getIdleTime();
                if(akt_idle > this->IdleTimeLimit)
                {
					if(this->DBHandleList.size() > MinDBHandles)
					{
						//Na, dem ist wohl schlecht geworden, wech damit
						DBHandleList[i]->~PostgreSQL_Connector();
						DBHandleList.erase(DBHandleList.begin() + i);
						break;						
					}

                }
                
                if((i + 1) >= this->DBHandleList.size())
                {
                    return;
                }
            }            
        }
    }
}

unsigned short DBConnectionManager::DBRunCommand( wxString sqlCommand, CallbackBase &cb)
{
    PQ_Multithread_Wrapper *thread = new PQ_Multithread_Wrapper(this->GetDBHandle(), sqlCommand, cb);

    if ( thread->Create() != wxTHREAD_NO_ERROR )
    {
		cerr << "Thread konnte nicht gestartet werden - " << sqlCommand << endl;
        wxLogError(wxT("Can't create thread!"));
        return 1;
    }
    thread->Run();
    return 0;
}

vector< vector< wxString > > DBConnectionManager::DBRunCommand( wxString sqlCommand )
{
    std::vector< std::vector < wxString > > result;
    
    this->GetDBHandle()->runCommand(sqlCommand, result);
    return result;
}

unsigned int DBConnectionManager::DBRunCommandTest( wxString sqlCommand )
{
	std::vector< std::vector < wxString > > test;
	return this->GetDBHandle()->runCommand(sqlCommand, test);
}

unsigned short DBConnectionManager::getCountConnections()
{
    return this->DBHandleList.size();
}

bool DBConnectionManager::IsConnected()
{
    if(this->DBHandleList.size() > 0)
    {
		for(unsigned short i = 0; i < this->DBHandleList.size(); ++i)
		{
			if(DBHandleList[i]->isConnected())
			{
				return true;
			}
		}
		return false;
    }
	else
	{
		return false;
	}
}

void DBConnectionManager::CloseConnection()
{
    while(this->DBHandleList.size() > 0)
    {
		for(unsigned short i = 0; i < this->DBHandleList.size(); ++i)
		{
			//Und wech damit
			DBHandleList[i]->~PostgreSQL_Connector();
			DBHandleList.erase(DBHandleList.begin() + i);
			break;
		}
    }
}