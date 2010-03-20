#include "lieferantdetail.h"
#include "mainwindow.h"

BEGIN_EVENT_TABLE( LieferantDetail, wxFrame)
	EVT_TEXT(ID_TFIELDSEARCHLIEFERT, LieferantDetail::EventTextChangedLiefertSearch)
    EVT_LIST_ITEM_SELECTED(ID_LISTARTIKELLIEFERANT, LieferantDetail::EventListItemSelected)
    EVT_LIST_ITEM_DESELECTED(ID_LISTARTIKELLIEFERANT, LieferantDetail::EventListItemDeselected)
    EVT_BUTTON(ID_BUTTONADDLIEFERT, LieferantDetail::EventOnClickAddLiefertButton)
    EVT_BUTTON(ID_BUTTONDELETELIEFERT, LieferantDetail::EventOnClickDeleteLiefertButton)
END_EVENT_TABLE()

LieferantDetail::LieferantDetail(MainWindow *parent, unsigned int lieferantId)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Lieferantdetails"), wxPoint(-1, -1), wxSize(420, 465))
{
	this->main = parent;
	this->db = new DBCommand(this->main->getDBManageObject());
	
	this->lId = lieferantId;
	

	this->Initialize();
}

void LieferantDetail::Initialize()
{
	const wxSize &size = this->GetSize();
    
    listColumnCount = 4;
    unsigned short colWidth = (size.GetWidth() / listColumnCount);
	
	panel = new wxPanel (this, ID_PANEL, wxPoint(0, 0), wxSize(size.GetWidth(), (size.GetHeight() - 25)));
	CreateStatusBar(1);
	
	tlabel_name		= new wxStaticText(panel, ID_TLABELNAME, wxT("Name"), wxPoint(10, 10), wxSize(-1, -1), wxALIGN_LEFT);
	tlabel_strasse 	= new wxStaticText(panel, ID_TLABELSTRASSE, wxT("Strasse"), wxPoint(10, 40), wxSize(-1, -1), wxALIGN_LEFT);
	tlabel_plzOrt 	= new wxStaticText(panel, ID_TLABELPLZORT, wxT("PLZ / Ort"), wxPoint(10, 70), wxSize(-1, -1), wxALIGN_LEFT);
	tlabel_telefon 	= new wxStaticText(panel, ID_TLABELTELEFON, wxT("Telefon"), wxPoint(10, 100), wxSize(-1, -1), wxALIGN_LEFT);
	tlabel_telefax 	= new wxStaticText(panel, ID_TLABELTELEFAX, wxT("Telefax"), wxPoint(10, 130), wxSize(-1, -1), wxALIGN_LEFT);
	tlabel_email 	= new wxStaticText(panel, ID_TLABELEMAIL, wxT("EMail"), wxPoint(10, 160), wxSize(-1, -1), wxALIGN_LEFT);
	tlabel_createdate = new wxStaticText(panel, ID_TLABELCREATEDATE, wxT("Erstellt am"), wxPoint(10, 190), wxSize(-1, -1), wxALIGN_LEFT);
	
	
	tfield_name		= new wxTextCtrl( panel, ID_TFIELDNAME, wxT(""), wxPoint(190, 10), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
	tfield_strasse	= new wxTextCtrl( panel, ID_TFIELDSTRASSE, wxT(""), wxPoint(190, 40), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
	tfield_plz		= new wxTextCtrl( panel, ID_TFIELDPLZ, wxT(""), wxPoint(190, 70), wxSize(70, -1), wxTE_HT_BELOW | wxTE_READONLY );
	tfield_ort		= new wxTextCtrl( panel, ID_TFIELDORT, wxT(""), wxPoint(265, 70), wxSize(145, -1), wxTE_HT_BELOW | wxTE_READONLY );
	tfield_telefon	= new wxTextCtrl( panel, ID_TFIELDTELEFON, wxT(""), wxPoint(190, 100), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
	tfield_telefax	= new wxTextCtrl( panel, ID_TFIELDTELEFAX, wxT(""), wxPoint(190, 130), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
	tfield_email	= new wxTextCtrl( panel, ID_TFIELDEMAIL, wxT(""), wxPoint(190, 160), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
	tfield_createdate = new wxTextCtrl( panel, ID_TFIELDCREATEDATE, wxT(""), wxPoint(190, 190), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
	
	tfield_searchLiefert 	= new wxTextCtrl( panel, ID_TFIELDSEARCHLIEFERT, wxT(""), wxPoint(190, 240), wxSize(163, 26), wxTE_HT_BELOW);
    
    button_addLiefert 		= new wxButton( panel, ID_BUTTONADDLIEFERT, wxT("+"), wxPoint(357, 240), wxSize(26, 26));
    button_deleteLiefert 	= new wxButton( panel, ID_BUTTONDELETELIEFERT, wxT("-"), wxPoint(385, 240), wxSize(26, 26));
    
    listArtikelLieferant 	= new wxListCtrl(this, ID_LISTARTIKELLIEFERANT, wxPoint(0, 270), wxSize(size.GetWidth(), 160), wxLC_REPORT | wxLC_SINGLE_SEL);
    


    listArtikelLieferant->InsertColumn(0, wxT("Artikel Nr"),wxLIST_FORMAT_LEFT,colWidth);
	listArtikelLieferant->InsertColumn(1, wxT("Beschreibung"),wxLIST_FORMAT_LEFT,colWidth);
    listArtikelLieferant->InsertColumn(2, wxT("EK-Preis"),wxLIST_FORMAT_LEFT,colWidth);
    listArtikelLieferant->InsertColumn(3, wxT("VH-Date"),wxLIST_FORMAT_LEFT,colWidth);
	
	tfield_name->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_strasse->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_plz->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_ort->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_telefon->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_telefax->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_email->SetBackgroundColour(wxColour(wxT("#FFE566")));
	tfield_createdate->SetBackgroundColour(wxColour(wxT("#FFE566")));
	
	button_deleteLiefert->Enable(false);
	
	db->getLieferantById(*new Callback<LieferantDetail>(this, &LieferantDetail::FillLieferantData), this->lId);
	
	db->getLieferantArtikelByLieferantId(*new Callback<LieferantDetail>(this, &LieferantDetail::FillArtikelLieferantList), this->lId);
	
	this->Show();
}

LieferantDetail::~LieferantDetail()
{
}

void LieferantDetail::FillLieferantData(vector< vector < wxString > > data)
{
	if(data.size() > 0)
	{
		createDate = new wxDateTime((long)wxAtoi(data[0][8]));
		
		tfield_name->SetValue(data[0][1]);
		tfield_strasse->SetValue(data[0][2]);
		tfield_plz->SetValue(data[0][3]);
		tfield_ort->SetValue(data[0][4]);
		tfield_telefon->SetValue(data[0][5]);
		tfield_telefax->SetValue(data[0][6]);
		tfield_email->SetValue(data[0][7]);
		tfield_createdate->SetValue(createDate->Format(wxT("%d.%m.%Y %H:%I:%S Uhr")));
	}
}

void LieferantDetail::FillArtikelLieferantList(vector< vector< wxString > > data)
{
    listArtikelLieferant->DeleteAllItems();
    arr_db_list.Clear();
    if(data.size() > 0)
    {
        for(int i = 0; i < data.size(); ++i)
        {
            arr_db_list.Add(wxAtoi(data[i][0]));
			
			wxDateTime *dateTime = new wxDateTime((long)wxAtoi(data[i][4]));
			
            listArtikelLieferant->InsertItem(i, data[i][1]);
            listArtikelLieferant->SetItem(i, 1, data[i][2]);
            listArtikelLieferant->SetItem(i, 2, data[i][3]);  	
			listArtikelLieferant->SetItem(i, 3, dateTime->Format(wxT("%d.%m.%Y")));
        }   
    }
}

void LieferantDetail::Update()
{
	db->getLieferantById(*new Callback<LieferantDetail>(this, &LieferantDetail::FillLieferantData), this->lId);
	tfield_searchLiefert->SetValue(wxT(""));
}

void LieferantDetail::EventTextChangedLiefertSearch(wxCommandEvent &event)
{
    wxString seq = tfield_searchLiefert->GetValue();
    db->getLieferantArtikelByLieferantIdBySearch(*new Callback<LieferantDetail>(this, &LieferantDetail::FillArtikelLieferantList), this->lId, seq);
}

void LieferantDetail::EventListItemSelected(wxListEvent &event)
{  
    if(listArtikelLieferant->GetSelectedItemCount() > 1)
    {
        lastSelectedItem = -1;
        button_deleteLiefert->Enable(false);
    }
    else
    {
        lastSelectedItem = arr_db_list[event.GetIndex()];
        button_deleteLiefert->Enable(true);
    }
}

void LieferantDetail::EventListItemDeselected(wxListEvent &event)
{
    if(listArtikelLieferant->GetSelectedItemCount() == 0)
    {
        lastSelectedItem = -1;
        button_deleteLiefert->Enable(false);
    }
}


void LieferantDetail::EventOnClickAddLiefertButton(wxCommandEvent &event)
{
    new LieferantArtikelConnect(main, *new Callback<LieferantDetail>(this, &LieferantDetail::Update), this->GetPosition(), this->lId);
}

void LieferantDetail::EventOnClickDeleteLiefertButton(wxCommandEvent &event)
{
    if(lastSelectedItem != -1)
    {
        wxMessageDialog *confirm = new wxMessageDialog(this, wxT("Möchten Sie diesen Eintrag wirklich löschen?"), wxT("Eintrag löschen"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
        
        int result = confirm->ShowModal();
        if(result == wxID_YES)
        {
            db->deleteLiefertById(lastSelectedItem);
            this->Update();
        }
    }
}
