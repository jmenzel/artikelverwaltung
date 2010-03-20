#include "mainwindow.h"

//EVENT-Table
BEGIN_EVENT_TABLE( MainWindow, wxFrame)
    EVT_TOGGLEBUTTON(ID_TBUTTONARTIKEL, MainWindow::EventOnClickTButtonArtikel)
	EVT_TOGGLEBUTTON(ID_TBUTTONLIEFERANT, MainWindow::EventOnClickTButtonLieferant)
	EVT_TOGGLEBUTTON(ID_TBUTTONHERSTELLER, MainWindow::EventOnClickTButtonHersteller)
	EVT_TEXT(ID_TFIELDSEARCHBOX, MainWindow::EventTextChangedSearchBox)
    EVT_BUTTON(ID_BUTTONREMOVE, MainWindow::EventOnClickButtonRemoveObject)
    EVT_BUTTON(ID_BUTTONADD, MainWindow::EventOnClickButtonAddObject)
	EVT_CONTEXT_MENU(MainWindow::EventHandleContextMenu)
	EVT_MENU(ID_CONTEXTSETTINGS, MainWindow::EventHandleMenuSettings)
	EVT_MENU(ID_CONTEXTCLOSE, MainWindow::EventHandleMenuClose)
END_EVENT_TABLE()

MainWindow::MainWindow( const wxChar *title, int xpos, int ypos, int width, int height)
    : wxFrame ( (wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
{
	//Gui erstellen
	top_panel = new wxPanel (this, ID_PANELTOP, wxPoint(0, 0), wxSize(850, 40));
	top_panel->Show(true);
	
	CreateStatusBar(1);
	
    //Anwendungobjekte instanziiern
    db = new DBConnectionManager();
    
    //Datenhaltungobjekte instanziieren
    config = new ConfigurationManager(wxT("Artikelverwaltung"));
    
    bool connected;

	db->SetDBData(config->GetDBIPAdress(), config->GetDBName(), config->GetDBUser(), config->GetDBPassword());
	connected = db->Connect();

    
	//UpdateDaemon starten
	updater = new UpdateDaemon(this);
	
    if(connected)
    {
		locked = false;
		
		this->CreateContentPanels();
	}
        tbutton_artikel = new wxToggleButton(top_panel, ID_TBUTTONARTIKEL, wxT("Artikel"), wxPoint(10, 5), wxSize(80, -1));
        tbutton_lieferant = new wxToggleButton(top_panel, ID_TBUTTONLIEFERANT, wxT("Lieferanten"), wxPoint(100, 5), wxSize(90, -1));
        tbutton_hersteller = new wxToggleButton(top_panel, ID_TBUTTONHERSTELLER, wxT("Hersteller"), wxPoint(200, 5), wxSize(80, -1));

        tfield_searchBox = new wxTextCtrl( top_panel, ID_TFIELDSEARCHBOX, wxT(""), wxPoint(300, 7), wxSize(200, -1), wxTE_HT_BELOW );
		
        button_removeObject = new wxButton( top_panel, ID_BUTTONREMOVE, wxT("-"), wxPoint(820, 5) , wxSize(30, -1));
        button_removeObject->Enable(false);

        button_addObject = new wxButton (top_panel, ID_BUTTONADD, wxT("+"), wxPoint(785, 5), wxSize(30, -1));
        button_addObject->Enable(false);
	
    settings_panel = new SettingsPanel(this, ID_PANELMAIN, wxPoint(0, 45), wxSize(850, 430));
    
	SetStatusText((connected) ? wxT("Geklappt") : wxT("scheisse"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateContentPanels()
{
	if(artikel_panel == NULL)
	{
		artikel_panel = new ArtikelPanel(this, ID_PANELMAIN, wxPoint(0, 45), wxSize(850, 430));
	}
	
	if(lieferant_panel == NULL)
	{
		lieferant_panel = new LieferantPanel(this, ID_PANELMAIN, wxPoint(0, 45), wxSize(850, 430));
	}
	
	if(hersteller_panel == NULL)
	{
		hersteller_panel = new HerstellerPanel(this, ID_PANELMAIN, wxPoint(0, 45), wxSize(850, 430));
	}
}

DBConnectionManager *MainWindow::getDBManageObject()
{
    return db;
}

ConfigurationManager *MainWindow::getConfigManageObject()
{
	return config;
}

void MainWindow::EventOnClickTButtonArtikel(wxCommandEvent &event)
{
    if(tbutton_lieferant->GetValue())
    {
        tbutton_lieferant->SetValue(false);
        lieferant_panel->Show(false);
    }
    
    if(tbutton_hersteller->GetValue())
    {
        tbutton_hersteller->SetValue(false);
        hersteller_panel->Show(false);
    }

    tbutton_artikel->SetValue(true);
	this->button_removeObject->Enable(false);
    this->button_addObject->Enable(true);
    artikel_panel->Show(true);
}

void MainWindow::EventOnClickTButtonLieferant(wxCommandEvent &event)
{
    if(tbutton_artikel->GetValue())
    {
        tbutton_artikel->SetValue(false);
        artikel_panel->Show(false);
    }
    
    if(tbutton_hersteller->GetValue())
    {
        tbutton_hersteller->SetValue(false);
        hersteller_panel->Show(false);
    }
    

    tbutton_lieferant->SetValue(true);
	this->button_removeObject->Enable(false);
    this->button_addObject->Enable(true);
    lieferant_panel->Show(true);
    
}

void MainWindow::EventOnClickTButtonHersteller(wxCommandEvent &event)
{   
    if(tbutton_artikel->GetValue())
    {
        tbutton_artikel->SetValue(false);
        artikel_panel->Show(false);
    }
    
    if(tbutton_lieferant->GetValue())
    {
        tbutton_lieferant->SetValue(false);
        lieferant_panel->Show(false);
    }
    
    tbutton_hersteller->SetValue(true);
	this->button_removeObject->Enable(false);
    this->button_addObject->Enable(true);
    hersteller_panel->Show(true);
}

void MainWindow::EventTextChangedSearchBox(wxCommandEvent &event)
{
    wxString msg = wxT("Suche: ");
    msg << tfield_searchBox->GetValue();
    SetStatusText(msg);
    
    this->button_removeObject->Enable(false);
    
    if(tbutton_artikel->GetValue())
    {
        artikel_panel->SearchArtikel(tfield_searchBox->GetValue());
    }
    
    if(tbutton_lieferant->GetValue())
    {
        lieferant_panel->SearchLieferant(tfield_searchBox->GetValue());
    }
    
    if(tbutton_hersteller->GetValue())
    {
        hersteller_panel->SearchHersteller(tfield_searchBox->GetValue());
    }    
}

void MainWindow::EventOnClickButtonRemoveObject(wxCommandEvent &event)
{
    if(tbutton_artikel->GetValue())
    {
        wxMessageDialog *confirm = new wxMessageDialog(this, wxT("Möchten Sie diesen Artikel wirklich löschen?"), wxT("Artikel löschen"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
        int result = confirm->ShowModal();
        if(result == wxID_YES)
        {
            artikel_panel->DeleteSelectedItem();
        }
    }
    
    if(tbutton_lieferant->GetValue())
    {
        wxMessageDialog *confirm = new wxMessageDialog(this, wxT("Möchten Sie diesen Lieferanten wirklich löschen?"), wxT("Lieferanten löschen"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
        int result = confirm->ShowModal();
        if(result == wxID_YES)
        {
            lieferant_panel->DeleteSelectedItem();
        }
    }
    
    if(tbutton_hersteller->GetValue())
    {
        wxMessageDialog *confirm = new wxMessageDialog(this, wxT("Möchten Sie diesen Hersteller und\nalle Artikel dieses Herstellers wirklich löschen?"), wxT("Hersteller und Artikel löschen"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
        int result = confirm->ShowModal();
        if(result == wxID_YES)
        {
            hersteller_panel->DeleteSelectedItem();
        }
    }
}

void MainWindow::EventOnClickButtonAddObject(wxCommandEvent &event)
{
    if(tbutton_artikel->GetValue())
    {
        new ArtikelAdd(this);
        this->SetStatusText(wxT("Neuen Artikel"));
    }
    
    if(tbutton_lieferant->GetValue())
    {
        new LieferantAdd(this);
        this->SetStatusText(wxT("Neuen Lieferanten"));
    }
    
    if(tbutton_hersteller->GetValue())
    {
        new HerstellerAdd(this);
        this->SetStatusText(wxT("Neuen Hersteller"));
    }
}

ArtikelPanel* MainWindow::getArtikelPanelObject()
{
    return artikel_panel;
}

LieferantPanel *MainWindow::getLieferantPanelObject()
{
    return lieferant_panel;
}

HerstellerPanel *MainWindow::getHerstellerPanelObject()
{
    return hersteller_panel;
}

SettingsPanel *MainWindow::getSettingsPanelObject()
{
    return settings_panel;
}

void MainWindow::Lock()
{
	this->locked = true;
	if(this->top_panel != NULL)
	{
		this->top_panel->Enable(false);
	}
	
	if(this->artikel_panel != NULL)
	{
		this->artikel_panel->Enable(false);
	}
	
	if(this->lieferant_panel != NULL)
	{
		this->lieferant_panel->Enable(false);
	}
	
	if(this->hersteller_panel != NULL)
	{
		this->hersteller_panel->Enable(false);
	}
}

void MainWindow::Unlock()
{
	this->locked = false;
	CreateContentPanels();
	
	if(this->settings_panel != NULL)
	{
		this->settings_panel->Show(false);
	}
	
	if(this->top_panel != NULL)
	{
		this->top_panel->Show(true);
		this->top_panel->Enable(true);
	}
	
	if(this->artikel_panel != NULL)
	{
		this->artikel_panel->Enable(true);
		this->artikel_panel->SearchArtikel(wxT(""));
	}
	
	if(this->lieferant_panel != NULL)
	{
		this->lieferant_panel->Enable(true);
		this->lieferant_panel->SearchLieferant(wxT(""));
	}
	
	if(this->hersteller_panel != NULL)
	{
		this->hersteller_panel->Enable(true);
		this->hersteller_panel->SearchHersteller(wxT(""));
	}
}

bool MainWindow::IsLocked()
{
	return this->locked;
}

void MainWindow::EventHandleContextMenu(wxContextMenuEvent &event)
{
	wxMenu menu(wxT(""));
	
	menu.Append(ID_CONTEXTSETTINGS, wxT("Einstellungen"));
	menu.Append(ID_CONTEXTCLOSE, wxT("Beenden"));
	
	PopupMenu(&menu, ScreenToClient(event.GetPosition()));
}

void MainWindow::EventHandleMenuSettings(wxCommandEvent &event)
{
	if(this->tbutton_artikel != NULL)
	{
		tbutton_artikel->SetValue(false);
	}
	
	if(this->tbutton_lieferant != NULL)
	{
		tbutton_lieferant->SetValue(false);
	}
	
	if(this->tbutton_hersteller)
	{
		tbutton_hersteller->SetValue(false);
	}
	
	if(this->artikel_panel != NULL)
	{
		this->artikel_panel->Show(false);
	}
	
	if(this->lieferant_panel != NULL)
	{
		this->lieferant_panel->Show(false);
	}
	
	if(this->hersteller_panel != NULL)
	{
		this->hersteller_panel->Show(false);
	}


	this->settings_panel->Show(true);
}

void MainWindow::EventHandleMenuClose(wxCommandEvent &event)
{
	wxMessageDialog *confirm = new wxMessageDialog(this, wxT("Möchten Sie das Programm wirklich beenden?"), wxT("Programm beenden"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	
	int result = confirm->ShowModal();
	if(result == wxID_YES)
	{
		this->Close();
	}
}
