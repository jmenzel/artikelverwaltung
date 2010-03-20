#include "lieferantartikelconnect.h"
#include "mainwindow.h"
BEGIN_EVENT_TABLE( LieferantArtikelConnect, wxFrame)
	EVT_TEXT(ID_TFIELDARTIKELSEARCH , LieferantArtikelConnect::EventTextChangedArtikelSearch)
	EVT_LIST_ITEM_SELECTED(ID_LISTARTIKEL, LieferantArtikelConnect::EventListItemSelected)
    EVT_LIST_ITEM_DESELECTED(ID_LISTARTIKEL, LieferantArtikelConnect::EventListItemDeselected)
	EVT_TEXT(ID_TFIELDEKPREIS, LieferantArtikelConnect::EventTextChangedArtikelEKPreis)
    //EVT_LIST_ITEM_ACTIVATED(ID_LISTARTIKEL, LieferantArtikelConnect::EventListItemActivated)
	EVT_BUTTON(ID_BUTTONARTIKELADD, LieferantArtikelConnect::EventOnClickArtikelAdd)
	EVT_BUTTON(ID_BUTTONSAVE, LieferantArtikelConnect::EventOnClickSaveButton)
    EVT_BUTTON(ID_BUTTONABORT, LieferantArtikelConnect::EventOnClickAbortButton)
END_EVENT_TABLE()

LieferantArtikelConnect::LieferantArtikelConnect(MainWindow *parent, wxPoint m_position, int lieferantId)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Lieferant mit Artikel verknüpfen"), m_position, wxSize(420, 575))
{
    this->main = parent;
    this->db = new DBCommand(main->getDBManageObject());
    this->lId = lieferantId;
    this->lastSelectedItem = -1;
    this->parent_check = false;
    this->Initialize();
}

LieferantArtikelConnect::LieferantArtikelConnect(MainWindow *parent, CallbackBase &caller_update, wxPoint m_position, int lieferantId)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Lieferant mit Artikel verknüpfen"), m_position, wxSize(420, 575))
{
    this->main = parent;
    this->db = new DBCommand(main->getDBManageObject());
    this->lId = lieferantId;
    
    this->parent_check = true;
    this->update = &caller_update;
    this->Initialize();
}

LieferantArtikelConnect::~LieferantArtikelConnect()
{
}

void LieferantArtikelConnect::Initialize()
{
    panel = new wxPanel (this, ID_PANEL, wxPoint(0, 0), wxSize(420, 550));
    CreateStatusBar(1);
	
    const wxSize &size = panel->GetSize();
	listColumnCount = 4;
	unsigned short colWidth = (size.GetWidth() / listColumnCount);
	
    tlabel_name 	= new wxStaticText(panel, ID_TLABELLIEFERANTNAME, wxT("Name"), wxPoint(10, 17), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_plzOrt 	= new wxStaticText(panel, ID_TLABELLIEFERANTPLZORT, wxT("PLZ / Ort"), wxPoint(10, 47), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_email 	= new wxStaticText(panel, ID_TLABELLIEFERANTEMAIL, wxT("Email"), wxPoint(10, 77), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_ek_preis = new wxStaticText(panel, ID_TLABELLIEFERANTEKPREIS, wxT("Einkaufspreis"), wxPoint(10, 115), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_vh_date 	= new wxStaticText(panel, ID_TLABELLIEFERANTVHDATE, wxT("Datum der\nPreisfestlegung"), wxPoint(10, 150), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_artikel 	= new wxStaticText(panel, ID_TLABELLIEFERANTARTIKEL, wxT("Artikel"), wxPoint(10, 320), wxSize(-1, -1), wxALIGN_LEFT);
        
    tfield_name 	= new wxTextCtrl( panel, ID_TFIELDLIEFERANTNAME, wxT(""), wxPoint(190, 15), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_plz 		= new wxTextCtrl( panel, ID_TFIELDLIEFERANTPLZ, wxT(""), wxPoint(190, 45), wxSize(70, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_ort 		= new wxTextCtrl( panel, ID_TFIELDLIEFERANTORT, wxT(""), wxPoint(265, 45), wxSize(145, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_email 	= new wxTextCtrl( panel, ID_TFIELDLIEFERANTEMAIL, wxT(""), wxPoint(190, 75), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_ek_preis = new wxTextCtrl( panel, ID_TFIELDEKPREIS, wxT(""), wxPoint(190, 113), wxSize(220, -1), wxTE_HT_BELOW );
	
	val_tfield_preis = new wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST);
	
    cal_vh_date = new wxCalendarCtrl(this, ID_CALVHDATE, wxDefaultDateTime, wxPoint(200, 150), wxSize(-1, -1), wxCAL_SEQUENTIAL_MONTH_SELECTION | wxCAL_MONDAY_FIRST | wxCAL_SHOW_SURROUNDING_WEEKS);

	button_artikel_add = new wxButton(panel, ID_BUTTONARTIKELADD, wxT("+"), wxPoint(160, 320), wxSize(25, 25));
	tfield_artikel_search = new wxTextCtrl( panel, ID_TFIELDARTIKELSEARCH, wxT(""), wxPoint(190, 320), wxSize(220, -1), wxTE_HT_BELOW );
	
    listArtikel = new wxListCtrl(this, ID_LISTARTIKEL, wxPoint(0, 350), wxSize(size.GetWidth(), 160), wxLC_REPORT | wxLC_SINGLE_SEL);
	
	button_save = new wxButton(panel, ID_BUTTONSAVE, wxT("Speichern"), wxPoint(160, 520), wxSize(-1, -1));   
    button_abort = new wxButton(panel, ID_BUTTONABORT, wxT("Speichern und Beenden"), wxPoint(245, 520), wxSize(-1, -1));
  
	val_preis.Add(wxT('0'));
	val_preis.Add(wxT('1'));
	val_preis.Add(wxT('2'));
	val_preis.Add(wxT('3'));
	val_preis.Add(wxT('4'));
	val_preis.Add(wxT('5'));
	val_preis.Add(wxT('6'));
	val_preis.Add(wxT('7'));
	val_preis.Add(wxT('8'));
	val_preis.Add(wxT('9'));
	val_preis.Add(wxT('.'));
	
	
	val_tfield_preis->SetIncludes(val_preis);
	tfield_ek_preis->SetValidator(*val_tfield_preis);
		
    tfield_name->SetBackgroundColour(wxColour(wxT("#FFE566")));
    tfield_plz->SetBackgroundColour(wxColour(wxT("#FFE566")));
    tfield_ort->SetBackgroundColour(wxColour(wxT("#FFE566")));
    tfield_email->SetBackgroundColour(wxColour(wxT("#FFE566")));
	
    
    listArtikel->InsertColumn(0, wxT("Nummer"),wxLIST_FORMAT_LEFT,colWidth);
    listArtikel->InsertColumn(1, wxT("Beschreibung"),wxLIST_FORMAT_LEFT,colWidth);
    listArtikel->InsertColumn(2, wxT("Hersteller"),wxLIST_FORMAT_LEFT,colWidth);
    listArtikel->InsertColumn(3, wxT("Preis"),wxLIST_FORMAT_LEFT,colWidth);
	
	button_save->Enable(false);
    
	this->db->getLieferantById(*new Callback<LieferantArtikelConnect>(this, &LieferantArtikelConnect::FillLieferantData), this->lId);
	this->db->getAllArtikelValues(*new Callback<LieferantArtikelConnect>(this, &LieferantArtikelConnect::FillListArtikel));
	
    this->Show();
}

void LieferantArtikelConnect::Update()
{
    this->db->getLieferantById(*new Callback<LieferantArtikelConnect>(this, &LieferantArtikelConnect::FillLieferantData), this->lId);
	this->tfield_artikel_search->SetValue(wxT(""));
}

void LieferantArtikelConnect::FillLieferantData(vector< vector< wxString > > data)
{
	if(data.size() > 0)
	{
		this->tfield_name->SetValue(data[0][1]);
		this->tfield_plz->SetValue(data[0][3]);
		this->tfield_ort->SetValue(data[0][4]);
		this->tfield_email->SetValue(data[0][7]);
	}
}

void LieferantArtikelConnect::FillListArtikel(vector< vector< wxString > > data)
{
    listArtikel->DeleteAllItems();
    arr_db_list.Clear();
	
    for(int i = 0; i < data.size(); ++i)
    {
        arr_db_list.Add(wxAtoi(data[i][0]));
        listArtikel->InsertItem(i, data[i][1]);
        listArtikel->SetItem(i, 1, data[i][2]);
        listArtikel->SetItem(i, 2, data[i][5]);
        listArtikel->SetItem(i, 3, data[i][3]);
    }    
}

void LieferantArtikelConnect::EventTextChangedArtikelSearch(wxCommandEvent &event)
{
	wxString seq = tfield_artikel_search->GetValue();
	this->db->getArtikelBySearch(*new Callback<LieferantArtikelConnect>(this, &LieferantArtikelConnect::FillListArtikel), seq);
}

void LieferantArtikelConnect::EventListItemSelected(wxListEvent &event)
{  
    if(listArtikel->GetSelectedItemCount() > 1)
    {
        lastSelectedItem = -1;
		this->button_save->Enable(false);
    }
    else
    {
        lastSelectedItem = arr_db_list[event.GetIndex()];
		this->EnableButtonSave();
    }
}

void LieferantArtikelConnect::EventListItemDeselected(wxListEvent &event)
{
    if(listArtikel->GetSelectedItemCount() == 0)
    {
        lastSelectedItem = -1;
		this->button_save->Enable(false);
    }
}

/*
void LieferantArtikelConnect::EventListItemActivated(wxListEvent &event)
{
    if(lastSelectedItem != -1)
    {
        new ArtikelDetail(main, lastSelectedItem);
    }
}
*/

void LieferantArtikelConnect::EventTextChangedArtikelEKPreis(wxCommandEvent &event)
{
    if(tfield_ek_preis->GetValue().Length() == 0)
    {
        button_save->Enable(false);
    }
    else
    {
        EnableButtonSave();
    }
}

void LieferantArtikelConnect::EnableButtonSave()
{ 
    if(lastSelectedItem != -1 && tfield_ek_preis->GetValue().Length() > 0)
    {
        button_save->Enable(true);
    }
}

void LieferantArtikelConnect::EventOnClickArtikelAdd(wxCommandEvent &event)
{
	new ArtikelAdd(main, *new Callback<LieferantArtikelConnect>(this, &LieferantArtikelConnect::Update));
}

void LieferantArtikelConnect::EventOnClickSaveButton(wxCommandEvent &event)
{ 
    this->db->addNewLiefert(this->lastSelectedItem, this->lId, this->tfield_ek_preis->GetValue(), this->cal_vh_date->GetDate().Format(wxT("%Y-%m-%d %H:%M:%S")));
      
    if(parent_check)
    {
        if(this->update)
        {
            (*this->update)();
        }
        new LieferantArtikelConnect(main, *update, this->GetPosition(), this->lId);
    }
    else
    {
        new LieferantArtikelConnect(main, this->GetPosition(), this->lId);
    }
    this->Close();
}

void LieferantArtikelConnect::EventOnClickAbortButton(wxCommandEvent &event)
{
	wxMessageDialog *confirm;
    
    if(!button_save->IsEnabled())
    {
        confirm = new wxMessageDialog(this, wxT("Die Werte sind nicht vollständig!\nDie Eingaben werden verworfen und die Bearbeitung wird beendet"), wxT("Daten verwerfen und Bearbeitung beenden"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
    
        int result = confirm->ShowModal();
        if(result == wxID_YES)
        {      
            if(parent_check)
            {
                if(this->update)
                {
                    (*this->update)();
                }
            }
            else
            {
                main->SetStatusText(wxT("Die Bearbeitung wurde abgebrochen!"));
            }
            this->Close();
        }
    }
    else
    {
        this->db->addNewLiefert(this->lastSelectedItem, this->lId, this->tfield_ek_preis->GetValue(), this->cal_vh_date->GetDate().Format(wxT("%Y-%m-%d %H:%M:%S")));
                
        if(parent_check)
        {
            if(this->update)
            {
				(*this->update)();
            }
        }
        else
        {
            main->SetStatusText(wxT("Die Zuordnung zu dem Lieferanten wurde erstellt!"));
        }
        
        this->Close();
    }
} 