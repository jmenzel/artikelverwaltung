#include "herstellerdetail.h"
#include "mainwindow.h"

BEGIN_EVENT_TABLE( HerstellerDetail, wxFrame)
    EVT_BUTTON(ID_BUTTON_CLOSE, HerstellerDetail::EventOnClickButtonClose)
END_EVENT_TABLE()

HerstellerDetail::HerstellerDetail(MainWindow *parent, unsigned int herstellerId)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Hersteller anlegen"), wxPoint(-1, -1), wxSize(420, 285))
{
    main = parent;
	hId = herstellerId;
	
	db = new DBCommand(main->getDBManageObject());
    panel = new wxPanel (this, ID_PANEL, wxPoint(0, 0), wxSize(420, 260));
    CreateStatusBar(1);
    
    
    tlabel_name = new wxStaticText(panel, ID_TLABEL_NAME, wxT("Name"), wxPoint(10, 15), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_strasse = new wxStaticText(panel, ID_TLABEL_STRASSE, wxT("Strasse"), wxPoint(10, 45), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_plz_ort = new wxStaticText(panel, ID_TLABEL_PLZORT, wxT("PLZ / Ort"), wxPoint(10, 75), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_telefon = new wxStaticText(panel, ID_TLABEL_TELEFON, wxT("Telefon"), wxPoint(10, 105), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_fax = new wxStaticText(panel, ID_TLABEL_FAX, wxT("Telfax"), wxPoint(10, 135), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_email = new wxStaticText(panel, ID_TLABEL_FAX, wxT("Email"), wxPoint(10, 165), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_createDate = new wxStaticText(panel, ID_TLABEL_FAX, wxT("Erstellt am"), wxPoint(10, 195), wxSize(-1, -1), wxALIGN_LEFT);
	
    tfield_name = new wxTextCtrl( panel, ID_TFIELD_NAME, wxT(""), wxPoint(190, 13), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_strasse = new wxTextCtrl( panel, ID_TFIELD_STRASSE, wxT(""), wxPoint(190, 43), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_plz = new wxTextCtrl( panel, ID_TFIELD_PLZ, wxT(""), wxPoint(190, 73), wxSize(70, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_ort = new wxTextCtrl( panel, ID_TFIELD_ORT, wxT(""), wxPoint(265, 73), wxSize(145, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_telefon = new wxTextCtrl( panel, ID_TFIELD_TELEFON, wxT(""), wxPoint(190, 103), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_fax = new wxTextCtrl( panel, ID_TFIELD_FAX, wxT(""), wxPoint(190, 133), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_email = new wxTextCtrl( panel, ID_TFIELD_EMAIL, wxT(""), wxPoint(190, 163), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY);
    tfield_createDate = new wxTextCtrl( panel, ID_TFIELD_CREATEDATE, wxT(""), wxPoint(190, 193), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY);
	
    button_close = new wxButton(panel, ID_BUTTON_CLOSE, wxT("Schließen"), wxPoint(300, 230), wxSize(-1, -1));

	tfield_name->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_strasse->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_plz->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_ort->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_telefon->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_fax->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_email->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_createDate->SetBackgroundColour(wxColour(wxT("#FFE566")));


	db->getHerstellerById(*new Callback<HerstellerDetail>(this, &HerstellerDetail::FillHerstellerData), this->hId);
	
	this->Show();
}

HerstellerDetail::~HerstellerDetail()
{
}

void HerstellerDetail::FillHerstellerData(vector< vector< wxString > > data)
{
	if(data.size() > 0)
	{
		createDate = new wxDateTime((long)wxAtoi(data[0][8]));
		
		tfield_name->SetValue(data[0][1]);
		tfield_strasse->SetValue(data[0][2]);
		tfield_plz->SetValue(data[0][3]);
		tfield_ort->SetValue(data[0][4]);
		tfield_telefon->SetValue(data[0][5]);
		tfield_fax->SetValue(data[0][6]);
		tfield_email->SetValue(data[0][7]);
		tfield_createDate->SetValue(createDate->Format(wxT("%d.%m.%Y %H:%I:%S Uhr")));
	}
}


void HerstellerDetail::EventOnClickButtonClose(wxCommandEvent &event)
{
	this->Close();
}