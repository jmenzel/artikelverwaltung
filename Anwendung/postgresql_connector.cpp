#include "postgresql_connector.h"
PostgreSQL_Connector::PostgreSQL_Connector() 
{
	this->setLastAction();
}

PostgreSQL_Connector::PostgreSQL_Connector(const PostgreSQL_Connector& orig) 
{
}

PostgreSQL_Connector::PostgreSQL_Connector(char const *m_database, char const *m_host, char const *m_user, char const *m_password) 
{
    this->database = m_database;
    this->host = m_host;
    this->user = m_user;
    this->password = m_password;
    this->setLastAction();
}

PostgreSQL_Connector::PostgreSQL_Connector(char const *m_database, char const *m_host, char const *m_user, char const *m_password, bool connectToDB) 
{
    this->database = m_database;
    this->host = m_host;
    this->user = m_user;
    this->password = m_password;
	
    this->setLastAction();
    
    if(connectToDB)
    {
        this->connect();
    }
    
    if(!this->checkConnectionData())
    {
        this->~PostgreSQL_Connector();
    }
}

PostgreSQL_Connector::PostgreSQL_Connector(char const *m_database, char const *m_host, char const *m_user, char const *m_password, bool connectToDB, unsigned short id) 
{
    this->database = m_database;
    this->host = m_host;
    this->user = m_user;
    this->password = m_password;
	
    this->setLastAction();
    
    if(connectToDB)
    {
        this->connect();
    }
	
	this->name = wxT("DBCon ");
	this->name << id;
}

PostgreSQL_Connector::~PostgreSQL_Connector() 
{

}   

bool PostgreSQL_Connector::checkConnectionData(void)
{
    //Prüfen ob relevante Daten gesetzt sind
    return (this->database == "" || this->host == "" || this->user == "") ? false : true;
}

bool PostgreSQL_Connector::isConnected()
{
	//const char* q = "SELECT 1";
	//PQexec(this->conn, q);
	if(PQstatus(this->conn) == CONNECTION_BAD || PQsocket(this->conn) == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//Setter
void PostgreSQL_Connector::setDatabase(std::string dbName)
{
    this->database = dbName;
}

void PostgreSQL_Connector::setHost(std::string hostIP)
{
    this->host = hostIP;
}

void PostgreSQL_Connector::setUser(std::string userName)
{
    this->user = userName;
}

void PostgreSQL_Connector::setPassword(std::string password)
{
    this->password = password;
}

bool PostgreSQL_Connector::connect()
{
    if(this->checkConnectionData() == true)
    {
        string connStr = "dbname=" + this->database + " host="+this->host+" user="+this->user+" password="+this->password;

        this->conn = PQconnectdb(connStr.c_str());
        if(PQstatus(this->conn) == CONNECTION_BAD)
        {
            std::cerr << "unable to connect to the database\n";
            return false;
        }

        return true;
    }
    else
    {
        return false;

    }
}

int PostgreSQL_Connector::runCommand(string sqlStatement, vector< vector <string> > &result)
{
    this->busy = true;
    
    PGresult *res = PQexec(this->conn, sqlStatement.c_str());

    if(PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        cerr << "We did not get any data!";
    }
    else
    {
        cout << "\nDie Anfrage ergab " << PQntuples(res) << " Ergebnisse mit je ";
        cout << PQnfields(res) << " Mengen" << endl;
        for(int row = 0; row < PQntuples(res); ++row)
        {
            vector<string> tmp(PQnfields(res));

            for(int field = 0; field < PQnfields(res); ++field)
            {
                tmp.push_back(PQgetvalue(res, row, field));
            }
            result.push_back(tmp);
        }
    }
    PQclear(res);
    
    this->setLastAction();
    this->busy = false;
	this->thread_lock = false;
    
    return 0;
}

int PostgreSQL_Connector::runCommand(wxString sqlStatement, vector< vector <wxString> > &result)
{
    this->busy = true;
	
	if(this->isConnected())
    {
		
        PGresult *res = PQexec(this->conn, sqlStatement.mb_str(wxConvUTF8));
		
		
		int PQStatus = PQresultStatus(res);
		
		
		switch(PQStatus)
        {
            case PGRES_EMPTY_QUERY:
                cerr << name.mb_str(wxConvUTF8) << " " << "The string sent to the backend was empty." << endl;
                break;
            case PGRES_COMMAND_OK:
                cerr << name.mb_str(wxConvUTF8) << " " << "Successful completion of a command returning no data." << endl;
                break;
            case PGRES_TUPLES_OK:
                cerr << name.mb_str(wxConvUTF8) << " " << "The query successfully executed." << endl;
                break;
            case PGRES_COPY_OUT:
                cerr << name.mb_str(wxConvUTF8) << " " << "Copy Out (from server) data transfer started." << endl;
                break;
            case PGRES_COPY_IN:
                cerr << name.mb_str(wxConvUTF8) << " " << "Copy In (to server) data transfer started." << endl;
                break;
            case PGRES_BAD_RESPONSE:
                cerr << name.mb_str(wxConvUTF8) << " " << "The server's response was not understood." << endl;
                break;
            case PGRES_NONFATAL_ERROR:
                cerr << name.mb_str(wxConvUTF8) << " " << "PGRES_NONFATAL_ERROR" << endl;
                break;
            case PGRES_FATAL_ERROR:
                cerr << name.mb_str(wxConvUTF8) << " " << "PGRES_FATAL_ERROR " << endl;
                break;
            default:
                cerr << name.mb_str(wxConvUTF8) << " " << "Unknown" << endl;
                break;
        }
		
        if(PQStatus != PGRES_TUPLES_OK)
        {
            cerr << name << " " << "No Data returned" << endl;

			this->busy = false;
			this->thread_lock = false;
			PQclear(res);
			return 1;
        }
        else
        {
            for(int row = 0; row < PQntuples(res); ++row)
            {
                vector<wxString> tmp;
                for(int field = 0; field < PQnfields(res); ++field)
                {
                    tmp.push_back(wxString(PQgetvalue(res, row, field), wxConvUTF8));
                }
                result.push_back(tmp);
            }
        }
        PQclear(res);
        
        this->setLastAction();
        this->busy = false;
        this->thread_lock = false;
        return 0;
		//return (PQStatus == PGRES_TUPLES_OK) ? 1 : 0;
    }
    else
    {
		this->busy = false;
        this->thread_lock = false;
		
		cerr << name << " " << "Nicht Verbunden" << endl; 
        return 1;
    }
    
}

int PostgreSQL_Connector::runCommand(wxString sqlStatement, vector< vector <wxString> > *result)
{
    this->busy = true;
    if(this->isConnected())
    {
        PGresult *res = PQexec(this->conn, sqlStatement.mb_str(wxConvUTF8));
		
		
		int PQStatus = PQresultStatus(res);
		switch(PQStatus)
        {
            case PGRES_EMPTY_QUERY:
                cerr << "The string sent to the backend was empty." << endl;
                break;
            case PGRES_COMMAND_OK:
                cerr << "Successful completion of a command returning no data." << endl;
                break;
            case PGRES_TUPLES_OK:
                cerr << "The query successfully executed." << endl;
                break;
            case PGRES_COPY_OUT:
                cerr << "Copy Out (from server) data transfer started." << endl;
                break;
            case PGRES_COPY_IN:
                cerr << "Copy In (to server) data transfer started." << endl;
                break;
            case PGRES_BAD_RESPONSE:
                cerr << "The server's response was not understood." << endl;
                break;
            case PGRES_NONFATAL_ERROR:
                cerr << "PGRES_NONFATAL_ERROR" << endl;
                break;
            case PGRES_FATAL_ERROR:
                cerr << "PGRES_FATAL_ERROR " << endl;
                break;
            default:
                cerr << "Unknown" << endl;
                break;
        }
		
        if(PQStatus != PGRES_TUPLES_OK)
        {
            cerr << name << " " << "Nicht Verbunden" << endl; 
            this->busy = false;
            this->thread_lock = false;
        }
        else
        {
            for(int row = 0; row < PQntuples(res); ++row)
            {

                vector<wxString> tmp;

                for(int field = 0; field < PQnfields(res); ++field)
                {
                    tmp.push_back(wxString(PQgetvalue(res, row, field), wxConvUTF8));
                }
                result->push_back(tmp);
            }
        }
        PQclear(res);
        
        this->setLastAction();
        this->busy = false;
        this->thread_lock = false;
		
        return 0;
    }
    else
    {
		this->busy = false;
        this->thread_lock = false;
        return 1;
    }
    
}

int PostgreSQL_Connector::runCommand(string sqlStatement, bool DEBUG)
{
    this->busy = true;
    
    PGresult *res = PQexec(this->conn, sqlStatement.c_str());

    int PQStatus = PQresultStatus(res);

    if(DEBUG)
    {
        switch(PQStatus)
        {
            case PGRES_EMPTY_QUERY:
                cerr << name << " " << "The string sent to the backend was empty." << endl;
                break;
            case PGRES_COMMAND_OK:
                cerr << name << " " << "Successful completion of a command returning no data." << endl;
                break;
            case PGRES_TUPLES_OK:
                cerr << name << " " << "The query successfully executed." << endl;
                break;
            case PGRES_COPY_OUT:
                cerr << name << " " << "Copy Out (from server) data transfer started." << endl;
                break;
            case PGRES_COPY_IN:
                cerr << name << " " << "Copy In (to server) data transfer started." << endl;
                break;
            case PGRES_BAD_RESPONSE:
                cerr << name << " " << "The server's response was not understood." << endl;
                break;
            case PGRES_NONFATAL_ERROR:
                cerr << name << " " << "PGRES_NONFATAL_ERROR" << endl;
                break;
            case PGRES_FATAL_ERROR:
                cerr << name << " "<< "PGRES_FATAL_ERROR " << endl;
                break;
            default:
                cerr << name << " " << "Unknown" << endl;
                break;
        }
    }

    PQclear(res);
    
    this->setLastAction();
    this->busy = false;
	this->thread_lock = false;
    
    return PQStatus;
}

int PostgreSQL_Connector::runCommand(wxString sqlStatement)
{
    this->busy = true;
    
    PGresult *res = PQexec(this->conn, sqlStatement.mb_str(wxConvUTF8));
    PQclear(res);
    
    this->setLastAction();
    this->busy = false;
    this->thread_lock = false;
    return 0;
}

bool PostgreSQL_Connector::isBusy()
{
    return this->busy;
}

void PostgreSQL_Connector::setLastAction()
{
    this->lastAction = time(0);
}

unsigned int PostgreSQL_Connector::getIdleTime()
{
    if(this->lastAction > 0)
    {
        return (time(0) - this->lastAction);
    }
    else
    {
        return 0;
    }
}

bool PostgreSQL_Connector::isLocked()
{
	return thread_lock;
}

void PostgreSQL_Connector::lock()
{
	thread_lock = true;
}

void PostgreSQL_Connector::unlock()
{
	thread_lock = false;
}