#include "artikeldetail.h"
#include "mainwindow.h"

BEGIN_EVENT_TABLE( ArtikelDetail, wxFrame)
	EVT_TEXT(ID_TFIELDSEARCHLIEFERT, ArtikelDetail::EventTextChangedLiefertSearch)
    EVT_LIST_ITEM_SELECTED(ID_LISTARTIKELLIEFERANT, ArtikelDetail::EventListItemSelected)
    EVT_LIST_ITEM_DESELECTED(ID_LISTARTIKELLIEFERANT, ArtikelDetail::EventListItemDeselected)
    EVT_BUTTON(ID_BUTTONADDLIEFERT, ArtikelDetail::EventOnClickAddLiefertButton)
    EVT_BUTTON(ID_BUTTONDELETELIEFERT, ArtikelDetail::EventOnClickDeleteLiefertButton)
END_EVENT_TABLE()

ArtikelDetail::ArtikelDetail(MainWindow *parent, unsigned int artikelId)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Artikeldetails"), wxPoint(-1, -1), wxSize(420, 465))
{
    main = parent;
    artId = artikelId;
    lastSelectedItem = -1;
    db = new DBCommand(main->getDBManageObject());
    
    panel = new wxPanel (this, ID_PANEL, wxPoint(0, 0), wxSize(420, 430));
    CreateStatusBar(1);
    
    tlabel_artNr 			= new wxStaticText(panel, ID_TLABELARTNR, wxT("Artikelnummer"), wxPoint(10, 10), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_artVKPreis 		= new wxStaticText(panel, ID_TLABELARTVKPREIS, wxT("Verkaufspreis"), wxPoint(10, 40), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_artHersteller 	= new wxStaticText(panel, ID_TLABELARTHERSTELLER, wxT("Hersteller"), wxPoint(10, 70), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_artCreateDate 	= new wxStaticText(panel, ID_TLABELARTCREATEDATE, wxT("Erstelldatum"), wxPoint(10, 100), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_artBeschreibung 	= new wxStaticText(panel, ID_TLABELARTBESCHREIBUNG, wxT("Beschreibung"), wxPoint(10, 130), wxSize(-1, -1), wxALIGN_LEFT);
        
    tfield_artNr 			= new wxTextCtrl( panel, ID_TFIELDARTNR, wxT(""), wxPoint(190, 10), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_artVKPreis 		= new wxTextCtrl( panel, ID_TFIELDARTVKPREIS, wxT(""), wxPoint(190, 40), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_artHersteller	= new wxTextCtrl( panel, ID_TFIELDARTHERSTELLER, wxT(""), wxPoint(190, 70), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_artCreateDate 	= new wxTextCtrl( panel, ID_TFIELDARTCREATEDATE, wxT(""), wxPoint(190, 100), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_artBeschreibung 	= new wxTextCtrl( panel, ID_TFIELDARTBESCHREIBUNG, wxT(""), wxPoint(190, 130), wxSize(220, 100), wxTE_HT_BELOW | wxTE_READONLY | wxTE_MULTILINE );
    
    tfield_searchLiefert 	= new wxTextCtrl( panel, ID_TFIELDSEARCHLIEFERT, wxT(""), wxPoint(190, 240), wxSize(163, 26), wxTE_HT_BELOW);
    
    button_addLiefert 		= new wxButton( panel, ID_BUTTONADDLIEFERT, wxT("+"), wxPoint(357, 240), wxSize(26, 26));
    button_deleteLiefert 	= new wxButton( panel, ID_BUTTONDELETELIEFERT, wxT("-"), wxPoint(385, 240), wxSize(26, 26));
    button_deleteLiefert->Enable(false);
    
    tfield_artNr->SetBackgroundColour(wxColour(wxT("#FFE566")));
    tfield_artVKPreis->SetBackgroundColour(wxColour(wxT("#FFE566")));
    tfield_artHersteller->SetBackgroundColour(wxColour(wxT("#FFE566")));
    tfield_artCreateDate->SetBackgroundColour(wxColour(wxT("#FFE566")));
    tfield_artBeschreibung->SetBackgroundColour(wxColour(wxT("#FFE566")));
    
    
    const wxSize &size 		= panel->GetSize();
    
    listArtikelLieferant 	= new wxListCtrl(this, ID_LISTARTIKELLIEFERANT, wxPoint(0, 270), wxSize(size.GetWidth(), 160), wxLC_REPORT | wxLC_SINGLE_SEL);
    listColumnCount = 3;
    
    unsigned short colWidth = (size.GetWidth() / listColumnCount);
    
    listArtikelLieferant->InsertColumn(0, wxT("Lieferant"),wxLIST_FORMAT_LEFT,colWidth);
    listArtikelLieferant->InsertColumn(1, wxT("EK-Preis"),wxLIST_FORMAT_LEFT,colWidth);
    listArtikelLieferant->InsertColumn(2, wxT("VH-Date"),wxLIST_FORMAT_LEFT,colWidth);
    
    db->getArtikelById(*new Callback<ArtikelDetail>(this, &ArtikelDetail::FillArtikelData), artId);
    db->getArtikelLieferantByArtId(*new Callback<ArtikelDetail>(this, &ArtikelDetail::FillArtikelLieferantList), artId);
    
    this->Show();
}

ArtikelDetail::~ArtikelDetail()
{
}

void ArtikelDetail::FillArtikelData(vector< vector< wxString > > data)
{
    if(data.size() > 0)
    {
		createDate = new wxDateTime((long)wxAtoi(data[0][4]));
		
        tfield_artNr->SetValue(data[0][1]);
        tfield_artVKPreis->SetValue(data[0][3]);
        tfield_artHersteller->SetValue(data[0][5]);
        tfield_artCreateDate->SetValue(createDate->Format(wxT("%d.%m.%Y %H:%I:%S Uhr")));
        tfield_artBeschreibung->SetValue(data[0][2]);
    }
	
	
}

void ArtikelDetail::FillArtikelLieferantList(vector< vector< wxString > > data)
{
    listArtikelLieferant->DeleteAllItems();
    arr_db_list.Clear();
    if(data.size() > 0)
    {
        for(int i = 0; i < data.size(); ++i)
        {
            arr_db_list.Add(wxAtoi(data[i][0]));

			wxDateTime *dateTime = new wxDateTime((long)wxAtoi(data[i][3]));
			
            listArtikelLieferant->InsertItem(i, data[i][1]);
            listArtikelLieferant->SetItem(i, 1, data[i][2]);
            listArtikelLieferant->SetItem(i, 2, dateTime->Format(wxT("%d.%m.%Y")));
			
			delete dateTime;
        }   
    }
}

void ArtikelDetail::EventTextChangedLiefertSearch(wxCommandEvent &event)
{
    wxString seq = tfield_searchLiefert->GetValue();
    db->getArtikelLieferantByArtIdBySearch(*new Callback<ArtikelDetail>(this, &ArtikelDetail::FillArtikelLieferantList), artId, seq);
}

void ArtikelDetail::EventListItemSelected(wxListEvent &event)
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

void ArtikelDetail::EventListItemDeselected(wxListEvent &event)
{
    if(listArtikelLieferant->GetSelectedItemCount() == 0)
    {
        lastSelectedItem = -1;
        button_deleteLiefert->Enable(false);
    }
}

void ArtikelDetail::EventOnClickAddLiefertButton(wxCommandEvent &event)
{
    new ArtikelLieferantConnect(main, *new Callback<ArtikelDetail>(this, &ArtikelDetail::Update), this->GetPosition(), artId);
}

void ArtikelDetail::EventOnClickDeleteLiefertButton(wxCommandEvent &event)
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

void ArtikelDetail::Update()
{
    lastSelectedItem = -1;
    button_deleteLiefert->Enable(false);
    
    tfield_searchLiefert->SetValue(wxT(""));
    db->getArtikelById(*new Callback<ArtikelDetail>(this, &ArtikelDetail::FillArtikelData), artId);
}



