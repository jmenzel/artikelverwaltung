#include "lieferantpanel.h"
#include "mainwindow.h"

BEGIN_EVENT_TABLE( LieferantPanel, wxPanel)
    EVT_LIST_ITEM_SELECTED(ID_LISTLIEFERANT, LieferantPanel::EventListItemSelected)
    EVT_LIST_ITEM_DESELECTED(ID_LISTLIEFERANT, LieferantPanel::EventListItemDeselected)
	EVT_LIST_ITEM_ACTIVATED(ID_LISTLIEFERANT, LieferantPanel::EventListItemActivated)
    EVT_CONTEXT_MENU(LieferantPanel::EventHandleContextMenu)
    EVT_MENU(ID_CONTEXTLIEFERANTADD, LieferantPanel::EventHandleMenuLieferantAdd)
    EVT_MENU(ID_CONTEXTLIEFERANTDELETE, LieferantPanel::EventHandleMenuLieferantDelete)
	EVT_MENU(ID_CONTEXTLIEFERANTEDIT, LieferantPanel::EventHandleMenuLieferantEdit)
	EVT_MENU(ID_CONTEXTLIEFERANTDETAILS, LieferantPanel::EventHandleMenuLieferantDetails)
    EVT_MENU(ID_CONTEXTLIEFERANTARTIKELCONNECT, LieferantPanel::EventHandleMenuLieferantArtikelConnect)
END_EVENT_TABLE()

LieferantPanel::LieferantPanel(MainWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size , long style, const wxString& name)
    : wxPanel((wxWindow *)parent, id, pos, size, style, name)
{
    this->Show(false);
    
    main = parent;
    db = new DBCommand(parent->getDBManageObject());

    lastSelectedItem = -1;

    listLieferant = new wxListCtrl(this, ID_LISTLIEFERANT, wxPoint(0, 0), size, wxLC_REPORT);
    listColumnCount = 4;
    
    unsigned short colWidth = (size.GetWidth() / listColumnCount);
    
    listLieferant->InsertColumn(0, wxT("Name"),wxLIST_FORMAT_LEFT,colWidth);
    listLieferant->InsertColumn(1, wxT("Telefon"),wxLIST_FORMAT_LEFT,colWidth);
    listLieferant->InsertColumn(3, wxT("PLZ"),wxLIST_FORMAT_LEFT,colWidth);
    listLieferant->InsertColumn(4, wxT("Ort"),wxLIST_FORMAT_LEFT,colWidth);

    db->getAllLieferantValues(*new Callback<LieferantPanel>(this, &LieferantPanel::FillListLieferant));
}

void LieferantPanel::SearchLieferant(wxString seq)
{
    listLieferant->DeleteAllItems();
    db->getLieferantBySearch(*new Callback<LieferantPanel>(this, &LieferantPanel::FillListLieferant), seq);
}

void LieferantPanel::FillListLieferant(vector< vector< wxString > > sqlReturn)
{
    arr_db_list.Clear();
    
    for(int i = 0; i < sqlReturn.size(); ++i)
    {
        arr_db_list.Add(wxAtoi(sqlReturn[i][0]));
        
        listLieferant->InsertItem(i, sqlReturn[i][1]);
        listLieferant->SetItem(i, 1, sqlReturn[i][5]);
        listLieferant->SetItem(i, 2, sqlReturn[i][3]);
        listLieferant->SetItem(i, 3, sqlReturn[i][4]);
    }    
}

void LieferantPanel::EventListItemSelected(wxListEvent &event)
{    
    if(listLieferant->GetSelectedItemCount() > 1)
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

void LieferantPanel::EventListItemDeselected(wxListEvent &event)
{
    if(listLieferant->GetSelectedItemCount() == 0)
    {
        lastSelectedItem = -1;
        main->button_removeObject->Enable(false);
    }
}

void LieferantPanel::DeleteSelectedItem()
{
    if(lastSelectedItem != -1)
    {
        db->deleteLiefertByLieferantId(lastSelectedItem);
        db->deleteLieferantById(lastSelectedItem);
        this->SearchLieferant(wxT(""));
    }
}

void LieferantPanel::EventListItemActivated(wxListEvent &event)
{
    if(lastSelectedItem != -1)
    {
        new LieferantDetail(main, lastSelectedItem);
    }
}

void LieferantPanel::EventHandleContextMenu(wxContextMenuEvent &event)
{

        wxMenu menu(wxT(""));

        if(lastSelectedItem != -1)
        {
            menu.Append(ID_CONTEXTLIEFERANTDETAILS, wxT("Lieferantdetails"));
			menu.Append(ID_CONTEXTLIEFERANTEDIT, wxT("Lieferant bearbeiten"));
			menu.Append(ID_CONTEXTLIEFERANTARTIKELCONNECT, wxT("Artikel zuweisen"));
            menu.Append(ID_CONTEXTLIEFERANTDELETE, wxT("Lieferanten löschen"));
        }
        
        menu.Append(ID_CONTEXTLIEFERANTADD, wxT("Neuen Lieferanten anlegen"));
        
        PopupMenu(&menu, ScreenToClient(event.GetPosition()));
}

void LieferantPanel::EventHandleMenuLieferantAdd(wxCommandEvent &event)
{
    new LieferantAdd(main);
}

void LieferantPanel::EventHandleMenuLieferantDelete(wxCommandEvent &event)
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

void LieferantPanel::EventHandleMenuLieferantDetails(wxCommandEvent &event)
{
	if(lastSelectedItem != -1)
    {
		new LieferantDetail(main, lastSelectedItem);
	}
}

void LieferantPanel::EventHandleMenuLieferantEdit(wxCommandEvent &event)
{
	if(lastSelectedItem != -1)
    {
		new LieferantEdit(main, lastSelectedItem);
	}
}

void LieferantPanel::EventHandleMenuLieferantArtikelConnect(wxCommandEvent &event)
{
    if(lastSelectedItem != -1)
    {
        new LieferantArtikelConnect(main, this->GetPosition(), lastSelectedItem);
    }
}