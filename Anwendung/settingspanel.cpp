#include "settingspanel.h"
#include "mainwindow.h"

//EVENT-Table
BEGIN_EVENT_TABLE( SettingsPanel, wxPanel )
    EVT_BUTTON(ID_BUTTON_SAVE, SettingsPanel::EventOnClickButtonSave)
	EVT_BUTTON(ID_BUTTON_CHECKTABLESTRUCTURE, SettingsPanel::EventOnClickCheckTableStructure)
END_EVENT_TABLE()

SettingsPanel::SettingsPanel(MainWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size , long style, const wxString &name)
    : wxPanel((wxWindow*)parent, id, pos, size, style, name)
{
    this->Show(false);
    main = parent;
	config = main->getConfigManageObject();
	db = new DBCommand(parent->getDBManageObject());
	
	tlabel_headline = new wxStaticText(this, ID_TLABEL_HEADLINE, wxT("Einstellungen"), wxPoint(10, 10), wxSize(-1, -1), wxALIGN_LEFT);
	
	tlabel_dbAdress 	= new wxStaticText(this, ID_TLABEL_DBADRESS, wxT("DB-IPAdresse"), wxPoint(10, 40), wxSize(-1, -1), wxALIGN_LEFT);
	tlabel_dbName 		= new wxStaticText(this, ID_TLABEL_DBNAME, wxT("DB-Name"), wxPoint(10, 70), wxSize(-1, -1), wxALIGN_LEFT);
	tlabel_dbUser  		= new wxStaticText(this, ID_TLABEL_DBUSER, wxT("DB-Benutzer"), wxPoint(10, 100), wxSize(-1, -1), wxALIGN_LEFT);
	tlabel_dbPassword 	= new wxStaticText(this, ID_TLABEL_DBPASSWORD, wxT("DB-Passwort"), wxPoint(10, 130), wxSize(-1, -1), wxALIGN_LEFT);
						  
	tfield_dbAdress		= new wxTextCtrl(this, ID_TFIELD_DBADRESS, wxT(""), wxPoint(190, 37), wxSize(220, -1), wxTE_HT_BELOW);
	tfield_dbName		= new wxTextCtrl(this, ID_TFIELD_DBNAME, wxT(""), wxPoint(190, 67), wxSize(220, -1), wxTE_HT_BELOW);
	tfield_dbUser		= new wxTextCtrl(this, ID_TFIELD_DBUSER, wxT(""), wxPoint(190, 97), wxSize(220, -1), wxTE_HT_BELOW);
	tfield_dbPassword	= new wxTextCtrl(this, ID_TFIELD_DBPASSWORD, wxT(""), wxPoint(190, 127), wxSize(220, -1), wxTE_HT_BELOW);
	
	button_save			= new wxButton(this, ID_BUTTON_SAVE, wxT("Speichern"), wxPoint(320, 160), wxSize(-1, -1));
	button_checkTableStructure = new wxButton(this, ID_BUTTON_CHECKTABLESTRUCTURE, wxT("Tabellenstruktur überprüfen"), wxPoint(520, 40), wxSize(-1, -1));
	this->FillDBConnectionData();
}

SettingsPanel::~SettingsPanel()
{
}

void SettingsPanel::FillDBConnectionData()
{
	tfield_dbAdress->SetValue(config->GetDBIPAdress());
	tfield_dbName->SetValue(config->GetDBName());
	tfield_dbUser->SetValue(config->GetDBUser());
	tfield_dbPassword->SetValue(config->GetDBPassword());	
}

void SettingsPanel::EventOnClickButtonSave(wxCommandEvent &event)
{
	wxMessageDialog *confirm = new wxMessageDialog(this, wxT("Sollen die Datenbankparameter überschrieben werden?"), wxT("Daten speichern"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	int result = confirm->ShowModal();
	if(result == wxID_YES)
	{
		config->SetDBIPAdress(tfield_dbAdress->GetValue());
		config->SetDBName(tfield_dbName->GetValue());
		config->SetDBUser(tfield_dbUser->GetValue());
		config->SetDBPassword(tfield_dbPassword->GetValue());
		
		config->SaveConfig();
		main->getDBManageObject()->CloseConnection();
		main->getDBManageObject()->SetDBData(config->GetDBIPAdress(), config->GetDBName(), config->GetDBUser(), config->GetDBPassword());
	}
}

void SettingsPanel::EventOnClickCheckTableStructure(wxCommandEvent &event)
{
	unsigned int result = this->db->checkTableStruktur();
	
	if(result)
	{
		wxMessageDialog *box = new wxMessageDialog(this, wxT("Die Datenbank entspricht den Anforderungen"), wxT("Datenbank check"), wxOK);
		box->ShowModal();
	}
	else
	{
		wxMessageDialog *confirm = new wxMessageDialog(this, wxT("Die Datenbankstruktur entspricht nicht den Anforderungen!\n\nSoll die Struktur jetzt angepasst werden?\nAchtung, dabei gehen eventuell bestehende Daten verloren!"), wxT("Datenbank check"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
		int result = confirm->ShowModal();
		if(result == wxID_YES)
		{
			wxString result = wxT("Ergebnis der Anpassung:\n\n");
			result << this->db->insertTableStruktur();
			
			wxMessageDialog *box = new wxMessageDialog(this, result, wxT("Datenbankstruktur anpassen"), wxOK);
			box->ShowModal();
		}
	}
}

