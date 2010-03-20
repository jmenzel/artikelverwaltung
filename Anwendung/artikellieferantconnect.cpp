#include "artikellieferantconnect.h"
#include "mainwindow.h"
//#include "artikeldetail.h"

BEGIN_EVENT_TABLE( ArtikelLieferantConnect, wxFrame)
    EVT_CHECKLISTBOX(ID_CHKLISTLIEFERANTBOX, ArtikelLieferantConnect::EventOnClickChkListBox)
	EVT_TEXT(ID_TFIELDARTIKELEKPREIS, ArtikelLieferantConnect::EventTextChangedArtikelEKPreis)
	EVT_TEXT(ID_TFIELDLIEFERANTSEARCH , ArtikelLieferantConnect::EventTextChangedLieferantSearch)
    EVT_BUTTON(ID_BUTTONLIEFERANTADD, ArtikelLieferantConnect::EventOnClickLieferantAdd)
    EVT_BUTTON(ID_BUTTONSAVE, ArtikelLieferantConnect::EventOnClickSaveButton)
    EVT_BUTTON(ID_BUTTONABORT, ArtikelLieferantConnect::EventOnClickAbortButton)
END_EVENT_TABLE()

ArtikelLieferantConnect::ArtikelLieferantConnect( MainWindow* parent, wxPoint m_position, int artikelId)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Artikel mit Lieferant verknüpfen"), m_position, wxSize(420, 555))
{
    main = parent;
    db = new DBCommand(main->getDBManageObject());
    artId = artikelId;
    lastSelectedItem = -1;
    parent_check  = false;
    this->Initialize();
}

ArtikelLieferantConnect::ArtikelLieferantConnect( MainWindow *parent, CallbackBase &caller_update, wxPoint m_position, int artikelId)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Artikel mit Lieferant verknüpfen"), m_position, wxSize(420, 555))
{
    main = parent;
    update = &caller_update;
    db = new DBCommand(main->getDBManageObject());
    artId = artikelId;
    lastSelectedItem = -1;
    parent_check = true;
    this->Initialize();
}



void ArtikelLieferantConnect::Initialize()
{
    panel = new wxPanel (this, ID_PANEL, wxPoint(0, 0), wxSize(420, 530));
    CreateStatusBar(1);
    
    tlabel_nr = new wxStaticText(panel, ID_TLABELNR, wxT("Artikelnummer"), wxPoint(10, 17), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_preis = new wxStaticText(panel, ID_TLABELPREIS, wxT("Preis"), wxPoint(10, 47), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_hersteller = new wxStaticText(panel, ID_TLABELHERSTELLER, wxT("Hersteller"), wxPoint(10, 77), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_ek_preis = new wxStaticText(panel, ID_TLABELVHDATE, wxT("Einkaufspreis"), wxPoint(10, 115), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_vh_date = new wxStaticText(panel, ID_TLABELVHDATE, wxT("Datum der\nPreisfestlegung"), wxPoint(10, 150), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_lieferant = new wxStaticText(panel, ID_TLABELLIEFERANT, wxT("Lieferant"), wxPoint(10, 320), wxSize(-1, -1), wxALIGN_LEFT);
    
    
    tfield_artikelnummer = new wxTextCtrl( panel, ID_TFIELDARTIKELNUMMER, wxT(""), wxPoint(190, 15), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_artikel_vk_preis = new wxTextCtrl( panel, ID_TFIELDARTIKELVKPREIS, wxT(""), wxPoint(190, 45), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    tfield_artikel_hersteller = new wxTextCtrl( panel, ID_TFIELDARTIKELHERSTELLER, wxT(""), wxPoint(190, 75), wxSize(220, -1), wxTE_HT_BELOW | wxTE_READONLY );
    
    tfield_artikelnummer->SetBackgroundColour(wxColour(wxT("#FFE566")));
    tfield_artikel_vk_preis->SetBackgroundColour(wxColour(wxT("#FFE566")));
    tfield_artikel_hersteller->SetBackgroundColour(wxColour(wxT("#FFE566")));
    
    cal_vh_date = new wxCalendarCtrl(this, ID_CALVHDATE, wxDefaultDateTime, wxPoint(200, 150), wxSize(-1, -1), wxCAL_SEQUENTIAL_MONTH_SELECTION | wxCAL_MONDAY_FIRST | wxCAL_SHOW_SURROUNDING_WEEKS);
    
    tfield_artikel_ek_preis = new wxTextCtrl( panel, ID_TFIELDARTIKELEKPREIS, wxT(""), wxPoint(190, 113), wxSize(220, -1), wxTE_HT_BELOW );
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
	
	val_tfield_preis = new wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST);
	val_tfield_preis->SetIncludes(val_preis);
	tfield_artikel_ek_preis->SetValidator(*val_tfield_preis);
        
    
    this->db->getArtikelById(*new Callback<ArtikelLieferantConnect>(this, &ArtikelLieferantConnect::FillArtikelData), artId);
    
    
    button_lieferant_add = new wxButton(panel, ID_BUTTONLIEFERANTADD, wxT("+"), wxPoint(160, 320), wxSize(25, 25));
    
	tfield_lieferant_search = new wxTextCtrl( panel, ID_TFIELDLIEFERANTSEARCH, wxT(""), wxPoint(190, 320), wxSize(220, -1), wxTE_HT_BELOW );
	
    chklist_lieferantBox = new wxCheckListBox( panel, 
                                                ID_CHKLISTLIEFERANTBOX, 
                                                wxPoint(10, 350), 
                                                wxSize(400, 145), 
                                                arr_lieferant, 
                                                wxLB_SINGLE | wxLB_NEEDED_SB);
    this->db->getAllLieferantValues(*new Callback<ArtikelLieferantConnect>(this, &ArtikelLieferantConnect::FillChkListLieferant));

	button_save = new wxButton(panel, ID_BUTTONSAVE, wxT("Speichern"), wxPoint(160, 500), wxSize(-1, -1));
	button_save->Enable(false);
    
    button_abort = new wxButton(panel, ID_BUTTONABORT, wxT("Speichern und Beenden"), wxPoint(245, 500), wxSize(-1, -1));
        
    this->Show();
}

ArtikelLieferantConnect::~ArtikelLieferantConnect()
{
}

void ArtikelLieferantConnect::Update()
{
    tfield_lieferant_search->SetValue(wxT(""));
}


void ArtikelLieferantConnect::FillArtikelData(vector< vector< wxString > > data)
{
    if(data.size() > 0)
    {
        tfield_artikelnummer->SetValue(data[0][1]);
        tfield_artikel_vk_preis->SetValue(data[0][3]);
        tfield_artikel_hersteller->SetValue(data[0][5]);
    }
}


void ArtikelLieferantConnect::FillChkListLieferant(vector< vector< wxString > > data)
{
	if(chklist_lieferantBox)
	{
        arr_db_list.Clear();
		chklist_lieferantBox->Clear();
        
		for(int i = 0; i < data.size(); ++i)
		{
            arr_db_list.Add(wxAtoi(data[i][0]));

            
			chklist_lieferantBox->Append(data[i][1]);
		}
	}
}

void ArtikelLieferantConnect::EventOnClickChkListBox(wxCommandEvent &event)
{
    for(int i = 0; i < arr_db_list.size(); ++i)
    {
        if(chklist_lieferantBox->IsChecked(i))
        {
            if(i != event.GetSelection())
            {
                chklist_lieferantBox->Deselect(i);
                chklist_lieferantBox->Check(i, false);
            }
        }
    }
    
    if(chklist_lieferantBox->IsChecked(event.GetSelection()))
    {
        lastSelectedItem = event.GetSelection();
        EnableButtonSave();
    }
    else
    {
        lastSelectedItem = -1;
        button_save->Enable(false);
        
    }
}

void ArtikelLieferantConnect::EventTextChangedLieferantSearch(wxCommandEvent &event)
{
	wxString seq = tfield_lieferant_search->GetValue();
	db->getLieferantBySearch(*new Callback<ArtikelLieferantConnect>(this, &ArtikelLieferantConnect::FillChkListLieferant), seq);
}

void ArtikelLieferantConnect::EventTextChangedArtikelEKPreis(wxCommandEvent &event)
{
    if(tfield_artikel_ek_preis->GetValue().Length() == 0)
    {
        button_save->Enable(false);
    }
    else
    {
        EnableButtonSave();
    }
}

void ArtikelLieferantConnect::EnableButtonSave()
{ 
    if(lastSelectedItem != -1 && tfield_artikel_ek_preis->GetValue().Length() > 0)
    {
        button_save->Enable(true);
    }
}

void ArtikelLieferantConnect::EventOnClickLieferantAdd(wxCommandEvent &event)
{
    new LieferantAdd(main, *new Callback<ArtikelLieferantConnect>(this, &ArtikelLieferantConnect::Update));
}

void ArtikelLieferantConnect::EventOnClickSaveButton(wxCommandEvent &event)
{ 
    this->db->addNewLiefert(artId, arr_db_list[lastSelectedItem], tfield_artikel_ek_preis->GetValue(), cal_vh_date->GetDate().Format(wxT("%Y-%m-%d %H:%M:%S")));
      
    if(parent_check)
    {
        if(this->update)
        {
            (*this->update)();
        }
        new ArtikelLieferantConnect(main, *update, this->GetPosition(), artId);
    }
    else
    {
        new ArtikelLieferantConnect(main, this->GetPosition(), artId);
    }
    this->Close();
}

void ArtikelLieferantConnect::EventOnClickAbortButton(wxCommandEvent &event)
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
        this->db->addNewLiefert(artId, arr_db_list[lastSelectedItem], tfield_artikel_ek_preis->GetValue(), cal_vh_date->GetDate().Format(wxT("%Y-%m-%d %H:%M:%S")));
        
        
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