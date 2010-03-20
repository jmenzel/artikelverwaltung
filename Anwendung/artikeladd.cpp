#include "artikeladd.h"
#include "mainwindow.h"

BEGIN_EVENT_TABLE( ArtikelAdd, wxFrame)
    EVT_CHECKLISTBOX(ID_CHKLISTHERSTELLERBOX, ArtikelAdd::EventOnClickChkListBox)
	EVT_TEXT(ID_TFIELDNR, ArtikelAdd::EventTextChangedArtikelnummer)
	EVT_TEXT(ID_TFIELDPREIS, ArtikelAdd::EventTextChangedArtikelPreis)
	EVT_TEXT(ID_TFIELDHERSTELLERSEARCH , ArtikelAdd::EventTextChangedHerstellerSearch)
    EVT_BUTTON(ID_BUTTONHERSTELLERADD, ArtikelAdd::EventOnClickHerstellerAddButton)
    EVT_BUTTON(ID_BUTTONSAVE, ArtikelAdd::EventOnClickSaveButton)
END_EVENT_TABLE()

ArtikelAdd::ArtikelAdd( MainWindow* parent)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Artikel anlegen"), wxPoint(-1, -1), wxSize(420, 425))
{
    main = parent;
    db = new DBCommand(main->getDBManageObject());
    
    panel = new wxPanel (this, ID_PANEL, wxPoint(0, 0), wxSize(420, 400));
    CreateStatusBar(1);
    
    artikelNrValidated = false;
    lastSelectedItem = -1;
	parent_check  = false;
	
	this->Initialize();
}

ArtikelAdd::ArtikelAdd( MainWindow* parent, CallbackBase &caller_update)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Artikel anlegen"), wxPoint(-1, -1), wxSize(420, 425))
{
    main = parent;
    db = new DBCommand(main->getDBManageObject());
    
    panel = new wxPanel (this, ID_PANEL, wxPoint(0, 0), wxSize(420, 400));
    CreateStatusBar(1);
    
    artikelNrValidated = false;
    lastSelectedItem = -1;
	parent_check  = true;
	this->update = &caller_update;
	
	this->Initialize();
}

void ArtikelAdd::Initialize()
{
    tlabel_nr = new wxStaticText(panel, ID_TLABELNR, wxT("Artikelnummer"), wxPoint(10, 17), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_preis = new wxStaticText(panel, ID_TLABELPREIS, wxT("Preis"), wxPoint(10, 47), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_beschreibung = new wxStaticText(panel, ID_TLABELBESCHREIBUNG, wxT("Beschreibung"), wxPoint(10, 77), wxSize(-1, -1), wxALIGN_LEFT);
    
    tlabel_hersteller = new wxStaticText(panel, ID_TLABELHERSTELLER, wxT("Hersteller"), wxPoint(10, 173), wxSize(-1, -1), wxALIGN_LEFT);
    
    tfield_nr = new wxTextCtrl( panel, ID_TFIELDNR, wxT(""), wxPoint(190, 15), wxSize(220, -1), wxTE_HT_BELOW );
    tfield_nr->SetValidator( wxTextValidator(wxFILTER_ALPHANUMERIC) );
    
    tfield_preis = new wxTextCtrl( panel, ID_TFIELDPREIS, wxT(""), wxPoint(190, 45), wxSize(220, -1), wxTE_HT_BELOW );
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
	tfield_preis->SetValidator(*val_tfield_preis);
    
    tfield_beschreibung = new wxTextCtrl( panel, ID_TFIELDBESCHREIBUNG, wxT(""), wxPoint(190, 75), wxSize(220, 80), wxTE_HT_BELOW | wxTE_MULTILINE );
	
    button_hersteller_add = new wxButton(panel, ID_BUTTONHERSTELLERADD, wxT("+"), wxPoint(160, 170), wxSize(25, 25));
    
	tfield_hersteller_search = new wxTextCtrl( panel, ID_TFIELDHERSTELLERSEARCH, wxT(""), wxPoint(190, 170), wxSize(220, -1), wxTE_HT_BELOW );
	
    chklist_herstellerBox = new wxCheckListBox( panel, 
                                                ID_CHKLISTHERSTELLERBOX, 
                                                wxPoint(10, 200), 
                                                wxSize(400, 145), 
                                                arr_hersteller, 
                                                wxLB_SINGLE | wxLB_NEEDED_SB);

	button_save = new wxButton(panel, ID_BUTTONSAVE, wxT("Speichern"), wxPoint(300, 360), wxSize(-1, -1));
	button_save->Enable(false);

                                                
	db->getAllHerstellerValues(*new Callback<ArtikelAdd>(this, &ArtikelAdd::FillChkListHersteller));
	    
	this->Show(TRUE);
}

ArtikelAdd::~ArtikelAdd()
{
}

void ArtikelAdd::FillChkListHersteller(vector< vector< wxString > > data)
{
    
	if(chklist_herstellerBox)
	{
        arr_db_list.Clear();
		chklist_herstellerBox->Clear();
        
		for(int i = 0; i < data.size(); ++i)
		{
            arr_db_list.Add(wxAtoi(data[i][0]));

            
			chklist_herstellerBox->Append(data[i][1]);
		}
	}
}

void ArtikelAdd::EventOnClickChkListBox(wxCommandEvent &event)
{
    for(int i = 0; i < arr_db_list.size(); ++i)
    {
        if(chklist_herstellerBox->IsChecked(i))
        {
            if(i != event.GetSelection())
            {
                chklist_herstellerBox->Deselect(i);
                chklist_herstellerBox->Check(i, false);
            }
        }
    }
    
    if(chklist_herstellerBox->IsChecked(event.GetSelection()))
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

void ArtikelAdd::EventTextChangedArtikelnummer(wxCommandEvent &event)
{
	if(tfield_nr->GetValue().Length() == 0)
	{
		tfield_nr->SetBackgroundColour(wxColour(wxT("white")));
        artikelNrValidated = false;
        button_save->Enable(false);
	}
	else
	{
		db->getCountArtikelByNr(*new Callback<ArtikelAdd>(this, &ArtikelAdd::ValidateUniqueArtikelNr), tfield_nr->GetValue());
	}
}

void ArtikelAdd::ValidateUniqueArtikelNr(vector< vector < wxString > > data)
{
	SetStatusText(data[0][0]);
	
	if(wxAtoi(data[0][0]) == 0)
	{
		tfield_nr->SetBackgroundColour(wxColour(wxT("green")));
        artikelNrValidated = true;
        EnableButtonSave();
    }
	else
	{
		tfield_nr->SetBackgroundColour(wxColour(wxT("red")));
        artikelNrValidated = false;
        button_save->Enable(false);
	}
}

void ArtikelAdd::EventTextChangedHerstellerSearch(wxCommandEvent &event)
{
	wxString seq = tfield_hersteller_search->GetValue();
	db->getHerstellerBySearch(*new Callback<ArtikelAdd>(this, &ArtikelAdd::FillChkListHersteller), seq);
}

void ArtikelAdd::EventTextChangedArtikelPreis(wxCommandEvent &event)
{
    if(tfield_preis->GetValue().Length() == 0)
    {
        button_save->Enable(false);
    }
    else
    {
        EnableButtonSave();
    }
    
}

void ArtikelAdd::EnableButtonSave()
{ 
    if(artikelNrValidated == true && tfield_preis->GetValue().Length() != 0 && lastSelectedItem != -1)
    {
        button_save->Enable(true);
    }
}

void ArtikelAdd::Update()
{
    tfield_hersteller_search->SetValue(wxT(""));
}

void ArtikelAdd::EventOnClickHerstellerAddButton(wxCommandEvent &event)
{
    new HerstellerAdd(main, *new Callback<ArtikelAdd>(this, &ArtikelAdd::Update));
}

void ArtikelAdd::EventOnClickSaveButton(wxCommandEvent &event)
{
    int artId = this->db->addNewArtikel(tfield_nr->GetValue(), tfield_preis->GetValue(), tfield_beschreibung->GetValue(), arr_db_list[lastSelectedItem]);
    
	if(parent_check)
	{
		if(this->update)
		{
			(*this->update)();
		}
	}
	else
	{
		new ArtikelLieferantConnect(main, this->GetPosition(), artId);
	}
	
	main->getArtikelPanelObject()->SearchArtikel(wxT(""));	
    this->Close();
}