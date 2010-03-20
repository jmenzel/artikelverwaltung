#include "artikelpanel.h"
#include "mainwindow.h"

BEGIN_EVENT_TABLE( ArtikelPanel, wxPanel)
    EVT_LIST_ITEM_SELECTED(ID_LISTARTIKEL, ArtikelPanel::EventListItemSelected)
    EVT_LIST_ITEM_DESELECTED(ID_LISTARTIKEL, ArtikelPanel::EventListItemDeselected)
    EVT_LIST_ITEM_ACTIVATED(ID_LISTARTIKEL, ArtikelPanel::EventListItemActivated)
    EVT_CONTEXT_MENU(ArtikelPanel::EventHandleContextMenu)
    EVT_MENU(ID_CONTEXTARTIKELLIEFERANTCONNECT, ArtikelPanel::EventHandleMenuArtikelLieferantConnect)
    EVT_MENU(ID_CONTEXTARTIKELDELETE, ArtikelPanel::EventHandleMenuArtikelDelete)
    EVT_MENU(ID_CONTEXTARTIKELADD, ArtikelPanel::EventHandleMenuArtikelAdd)
    EVT_MENU(ID_CONTEXTARTIKELDETAIL, ArtikelPanel::EventHandleMenuArtikelDetail)
    EVT_MENU(ID_CONTEXTARTIKELEDIT, ArtikelPanel::EventHandleMenuArtikelEdit)
END_EVENT_TABLE()

ArtikelPanel::ArtikelPanel(MainWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size , long style, const wxString &name)
    : wxPanel((wxWindow*)parent, id, pos, size, style, name)
{
    this->Show(false);
    lastSelectedItem = -1;
    main = parent;
    db = new DBCommand(parent->getDBManageObject());

    listArtikel = new wxListCtrl(this, ID_LISTARTIKEL, wxPoint(0, 0), size, wxLC_REPORT | wxLC_SINGLE_SEL);
    listColumnCount = 4;
    
    unsigned short colWidth = (size.GetWidth() / listColumnCount);
    
    listArtikel->InsertColumn(0, wxT("Nummer"),wxLIST_FORMAT_LEFT,colWidth);
    listArtikel->InsertColumn(1, wxT("Beschreibung"),wxLIST_FORMAT_LEFT,colWidth);
    listArtikel->InsertColumn(2, wxT("Hersteller"),wxLIST_FORMAT_LEFT,colWidth);
    listArtikel->InsertColumn(3, wxT("Preis"),wxLIST_FORMAT_LEFT,colWidth);
    //listArtikel->InsertColumn(4, wxT("Erstelldatum"),wxLIST_FORMAT_LEFT,colWidth);
    
    db->getAllArtikelValues(*new Callback<ArtikelPanel>(this, &ArtikelPanel::FillListArtikel));
}

void ArtikelPanel::SearchArtikel(wxString seq)
{
    db->getArtikelBySearch(*new Callback<ArtikelPanel>(this, &ArtikelPanel::FillListArtikel), seq);
}

void ArtikelPanel::FillListArtikel(vector< vector< wxString > > sqlReturn)
{
    listArtikel->DeleteAllItems();
    arr_db_list.Clear();
    for(int i = 0; i < sqlReturn.size(); ++i)
    {
        arr_db_list.Add(wxAtoi(sqlReturn[i][0]));
        listArtikel->InsertItem(i, sqlReturn[i][1]);
        listArtikel->SetItem(i, 1, sqlReturn[i][2]);
        listArtikel->SetItem(i, 2, sqlReturn[i][5]);
        listArtikel->SetItem(i, 3, sqlReturn[i][3]);
        //listArtikel->SetItem(i, 4, sqlReturn[i][4]);        
    }    
}

void ArtikelPanel::EventListItemSelected(wxListEvent &event)
{  
    if(listArtikel->GetSelectedItemCount() > 1)
    {
        lastSelectedItem = -1;
        main->button_removeObject->Enable(false);
    }
    else
    {
        lastSelectedItem = arr_db_list[event.GetIndex()];
        main->button_removeObject->Enable(TRUE);
    }
}

void ArtikelPanel::EventListItemDeselected(wxListEvent &event)
{
    if(listArtikel->GetSelectedItemCount() == 0)
    {
        lastSelectedItem = -1;
        main->button_removeObject->Enable(false);
    }
}

void ArtikelPanel::EventListItemActivated(wxListEvent &event)
{
    if(lastSelectedItem != -1)
    {
        new ArtikelDetail(main, lastSelectedItem);
    }
}

void ArtikelPanel::DeleteSelectedItem()
{
    if(lastSelectedItem != -1)
    {
        db->deleteLiefertByArtikelId(lastSelectedItem);
        db->deleteArtikelById(lastSelectedItem);
        
        main->button_removeObject->Enable(false);
        this->SearchArtikel(wxT(""));
    }
}

void ArtikelPanel::EventHandleContextMenu(wxContextMenuEvent &event)
{

        wxMenu menu(wxT(""));
        
        
        
        if(lastSelectedItem != -1)
        {
            menu.Append(ID_CONTEXTARTIKELDETAIL, wxT("Artikeldetails"));
            menu.Append(ID_CONTEXTARTIKELEDIT, wxT("Artikel bearbeiten"));
            menu.Append(ID_CONTEXTARTIKELLIEFERANTCONNECT, wxT("Lieferanten zuweisen"));
            menu.Append(ID_CONTEXTARTIKELDELETE, wxT("Artikel löschen"));
        }
        
        menu.Append(ID_CONTEXTARTIKELADD, wxT("Neuen Artikel anlegen"));
        
        PopupMenu(&menu, ScreenToClient(event.GetPosition()));
}

void ArtikelPanel::EventHandleMenuArtikelLieferantConnect(wxCommandEvent &event)
{
    if(lastSelectedItem != -1)
    {
        new ArtikelLieferantConnect(main, this->GetPosition(), lastSelectedItem);
    }
}

void ArtikelPanel::EventHandleMenuArtikelDelete(wxCommandEvent &event)
{
    if(lastSelectedItem != -1)
    {
        wxMessageDialog *confirm = new wxMessageDialog(this, wxT("Möchten Sie diesen Eintrag wirklich löschen?"), wxT("Eintrag löschen"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
        
        int result = confirm->ShowModal();
        if(result == wxID_YES)
        {
            this->DeleteSelectedItem();
            lastSelectedItem = -1;
        }
    }
}

void ArtikelPanel::EventHandleMenuArtikelAdd(wxCommandEvent &event)
{
    new ArtikelAdd(main);
}

void ArtikelPanel::EventHandleMenuArtikelDetail(wxCommandEvent &event)
{
    new ArtikelDetail(main, lastSelectedItem);
}

void ArtikelPanel::EventHandleMenuArtikelEdit(wxCommandEvent &event)
{
    new ArtikelEdit(main, lastSelectedItem);
}