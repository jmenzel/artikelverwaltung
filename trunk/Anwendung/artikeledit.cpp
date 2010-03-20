#include "artikeledit.h"
#include "mainwindow.h"

BEGIN_EVENT_TABLE( ArtikelEdit, wxFrame)
    EVT_CHECKLISTBOX(ID_CHKLISTHERSTELLERBOX, ArtikelEdit::EventOnClickChkListBox)
    EVT_TEXT(ID_TFIELDNR, ArtikelEdit::EventTextChangedArtikelnummer)
	EVT_TEXT(ID_TFIELDPREIS, ArtikelEdit::EventTextChangedArtikelPreis)
	EVT_TEXT(ID_TFIELDHERSTELLERSEARCH , ArtikelEdit::EventTextChangedHerstellerSearch)
	EVT_BUTTON(ID_BUTTONHERSTELLERADD, ArtikelEdit::EventOnClickHerstellerAddButton)
    EVT_BUTTON(ID_BUTTONSAVE, ArtikelEdit::EventOnClickSaveButton)
END_EVENT_TABLE()

ArtikelEdit::ArtikelEdit(MainWindow *parent, unsigned int artikelId)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Artikel bearbeiten"), wxPoint(-1, -1), wxSize(420, 425))
{
    main = parent;
    db = new DBCommand(main->getDBManageObject());
    artId = artikelId;
    artikelNrValidated = false;
    herstellerSelectionChanged = false;
    
    panel = new wxPanel (this, ID_PANEL, wxPoint(0, 0), wxSize(420, 400));
    CreateStatusBar(1);
    
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

    db->getArtikelById(*new Callback<ArtikelEdit>(this, &ArtikelEdit::FillArtikelEditForm), artId);
    
    this->Show();
}

void ArtikelEdit::FillChkListHersteller(vector< vector< wxString > > data)
{
    if(data.size() > 0)
    {
        if(chklist_herstellerBox)
        {
            arr_db_list.Clear();
            chklist_herstellerBox->Clear();
            
            for(int i = 0; i < data.size(); ++i)
            {
                arr_db_list.Add(wxAtoi(data[i][0]));               
                chklist_herstellerBox->Append(data[i][1]);
                
                if(!herstellerSelectionChanged && wxAtoi(data[i][0]) == oldHerstellerId)
                {
                    chklist_herstellerBox->Select(i);
                    chklist_herstellerBox->Check(i, true);
                    lastSelectedItem = i;
                    herstellerIdArrPos = i;
                }
            }
        }
    }
    
    
}

void ArtikelEdit::FillArtikelEditForm(vector< vector< wxString > > data)
{
    if(data.size() > 0)
    {
        oldArtikelNummer = data[0][1];
        oldVKPreis = data[0][3];
        oldBeschreibung = data[0][2];
        oldHerstellerId = wxAtoi(data[0][6]);
        
        tfield_nr->SetValue(data[0][1]);
        tfield_preis->SetValue(data[0][3]);
        tfield_beschreibung->SetValue(data[0][2]);
        
        db->getAllHerstellerValues(*new Callback<ArtikelEdit>(this, &ArtikelEdit::FillChkListHersteller));
    }
}

void ArtikelEdit::EventOnClickChkListBox(wxCommandEvent &event)
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
        chklist_herstellerBox->Select(herstellerIdArrPos);
        chklist_herstellerBox->Check(herstellerIdArrPos, true);
    }
    herstellerSelectionChanged = true;
}

void ArtikelEdit::EventTextChangedHerstellerSearch(wxCommandEvent &event)
{
	wxString seq = tfield_hersteller_search->GetValue();
	db->getHerstellerBySearch(*new Callback<ArtikelEdit>(this, &ArtikelEdit::FillChkListHersteller), seq);
}

void ArtikelEdit::EnableButtonSave()
{ 
    if(artikelNrValidated == true && tfield_preis->GetValue().Length() != 0 && lastSelectedItem != -1)
    {
        button_save->Enable(true);
    }
}

void ArtikelEdit::EventTextChangedArtikelnummer(wxCommandEvent &event)
{
	if(tfield_nr->GetValue().Length() == 0)
	{
		tfield_nr->SetBackgroundColour(wxColour(wxT("white")));
        artikelNrValidated = false;
        button_save->Enable(false);
	}
	else
	{
		db->getCountArtikelByNr(*new Callback<ArtikelEdit>(this, &ArtikelEdit::ValidateUniqueArtikelNr), tfield_nr->GetValue());
	}
}

void ArtikelEdit::ValidateUniqueArtikelNr(vector< vector < wxString > > data)
{
	if(wxAtoi(data[0][0]) == 0)
	{
        if(tfield_nr->GetValue() != oldArtikelNummer)
        {
            tfield_nr->SetBackgroundColour(wxColour(wxT("green")));
        }
        else
        {
            tfield_nr->SetBackgroundColour(wxColour(wxT("white")));
        }
            
        artikelNrValidated = true;
        EnableButtonSave();
    }
	else
	{
        if(tfield_nr->GetValue() != oldArtikelNummer)
        {
            tfield_nr->SetBackgroundColour(wxColour(wxT("red")));
            artikelNrValidated = false;
            button_save->Enable(false);
        }
        else
        {
            tfield_nr->SetBackgroundColour(wxColour(wxT("white")));
            artikelNrValidated = true;
            EnableButtonSave();
        }
	}
}

void ArtikelEdit::EventTextChangedArtikelPreis(wxCommandEvent &event)
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

void ArtikelEdit::EventOnClickHerstellerAddButton(wxCommandEvent &event)
{
    new HerstellerAdd(main, *new Callback<ArtikelEdit>(this, &ArtikelEdit::Update));
}

void ArtikelEdit::Update()
{
    tfield_hersteller_search->SetValue(wxT(""));
}

void ArtikelEdit::EventOnClickSaveButton(wxCommandEvent &event)
{
    if(tfield_nr->GetValue() != oldArtikelNummer || tfield_preis->GetValue() != oldVKPreis || tfield_beschreibung->GetValue() != oldBeschreibung || arr_db_list[lastSelectedItem] != oldHerstellerId )
    {
        SetStatusText(wxT("Mache eine DB Abfrage"));
        db->updateArtikelById(artId, tfield_nr->GetValue(), tfield_preis->GetValue(), tfield_beschreibung->GetValue(), arr_db_list[lastSelectedItem]);
        main->getArtikelPanelObject()->SearchArtikel(wxT(""));
    }
    
    wxString msg = wxT("Der Artikel ");
    msg << tfield_nr->GetValue();
    msg << wxT(" wurde gespeichert!");
    
    main->SetStatusText(msg);
    
    this->Close();
}