#include "configurationmanager.h"

ConfigurationManager::ConfigurationManager(wxString applicationName)
    : wxConfig(applicationName)
{    
	if(this->CheckConfigExists())
	{
		this->LoadConfig();
	}
	else
	{
		//Gibt noch keine Konfig, dann legen wir mal eine an
		this->SetDBIPAdress(wxT(""));
		this->SetDBName(wxT(""));
		this->SetDBUser(wxT(""));
		this->SetDBPassword(wxT(""));
		
		//Leere Konfig Speichern
		this->SaveConfig();
	}
}

ConfigurationManager::~ConfigurationManager()
{
}

void ConfigurationManager::LoadConfig()
{
    this->SetDBIPAdress(this->Read(wxT("/DBConnection/IPAdress"), wxT("")));
    this->SetDBName(this->Read(wxT("/DBConnection/Name"), wxT("")));
    this->SetDBUser(this->Read(wxT("/DBConnection/User"), wxT("")));
    this->SetDBPassword(this->Read(wxT("/DBConnection/Password"), wxT("")));
}

void ConfigurationManager::SaveConfig()
{
    this->SetPath(wxT("/DBConnection"));
    this->Write(wxT("/DBConnection/IPAdress"), this->GetDBIPAdress());
    this->Write(wxT("/DBConnection/Name"), this->GetDBName());
    this->Write(wxT("/DBConnection/User"), this->GetDBUser());
    this->Write(wxT("/DBConnection/Password"), this->GetDBPassword());
    
	//Und ab dafür
    this->Flush();
}

bool ConfigurationManager::CheckConfigExists()
{
	//Wenn mehr als 0 Einträge existieren, dann gibts wohl ne Config
    return (this->GetNumberOfEntries(true) > 0) ? true : false;
}

//Getter
wxString &ConfigurationManager::GetDBIPAdress()
{
    return this->db_ipadress;
}

wxString &ConfigurationManager::GetDBName()
{
    return this->db_name;
}

wxString &ConfigurationManager::GetDBUser()
{
    return this->db_user;
}

wxString &ConfigurationManager::GetDBPassword()
{
    return this->db_password;
}

//Setter
void ConfigurationManager::SetDBIPAdress(wxString newDBIPAdress)
{
    this->db_ipadress = newDBIPAdress;
}

void ConfigurationManager::SetDBName(wxString newDBName)
{
    this->db_name = newDBName;
}

void ConfigurationManager::SetDBUser(wxString newDBUser)
{
    this->db_user = newDBUser;
}

void ConfigurationManager::SetDBPassword(wxString newDBPassword)
{
    this->db_password = newDBPassword;
}