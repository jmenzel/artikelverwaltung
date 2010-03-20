#include "herstellerpanel.h"
#include "mainwindow.h"

BEGIN_EVENT_TABLE( HerstellerPanel, wxPanel)
    EVT_LIST_ITEM_SELECTED(ID_LISTHERSTELLER, HerstellerPanel::EventListItemSelected)
    EVT_LIST_ITEM_DESELECTED(ID_LISTHERSTELLER, HerstellerPanel::EventListItemDeselected)
	EVT_LIST_ITEM_ACTIVATED(ID_LISTHERSTELLER, HerstellerPanel::EventListItemActivated)
	EVT_CONTEXT_MENU(HerstellerPanel::EventHandleContextMenu)
    EVT_MENU(ID_CONTEXTHERSTELLERDELETE, HerstellerPanel::EventHandleMenuHerstellerDelete)
    EVT_MENU(ID_CONTEXTHERSTELLERADD, HerstellerPanel::EventHandleMenuHerstellerAdd)
    EVT_MENU(ID_CONTEXTHERSTELLERDETAIL, HerstellerPanel::EventHandleMenuHerstellerDetail)
    EVT_MENU(ID_CONTEXTHERSTELLEREDIT, HerstellerPanel::EventHandleMenuHerstellerEdit)
END_EVENT_TABLE()

HerstellerPanel::HerstellerPanel(MainWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size , long style, const wxString& name)
    : wxPanel((wxWindow*)parent, id, pos, size, style, name)
{
    this->Show(false);

    main = parent;
    db = new DBCommand(parent->getDBManageObject());
	lastSelectedItem = -1;
    listHersteller = new wxListCtrl(this, ID_LISTHERSTELLER, wxPoint(0, 0), size, wxLC_REPORT);
    listColumnCount = 4;
    
    unsigned short colWidth = (size.GetWidth() / listColumnCount);
    
    listHersteller->InsertColumn(0, wxT("Name"),wxLIST_FORMAT_LEFT,colWidth);
    listHersteller->InsertColumn(1, wxT("Telefon"),wxLIST_FORMAT_LEFT,colWidth);
    listHersteller->InsertColumn(3, wxT("PLZ"),wxLIST_FORMAT_LEFT,colWidth);
    listHersteller->InsertColumn(3, wxT("Ort"),wxLIST_FORMAT_LEFT,colWidth);

    db->getAllHerstellerValues(*new Callback<HerstellerPanel>(this, &HerstellerPanel::FillListHersteller));
}

void HerstellerPanel::SearchHersteller(wxString seq)
{
    listHersteller->DeleteAllItems();
    db->getHerstellerBySearch(*new Callback<HerstellerPanel>(this, &HerstellerPanel::FillListHersteller), seq);
}

void HerstellerPanel::FillListHersteller(vector< vector< wxString > > sqlReturn)
{
    arr_db_list.Clear();
    
    for(int i = 0; i < sqlReturn.size(); ++i)
    {
        arr_db_list.Add(wxAtoi(sqlReturn[i][0]));
        listHersteller->InsertItem(i, sqlReturn[i][1]);
        listHersteller->SetItem(i, 1, sqlReturn[i][5]);
        listHersteller->SetItem(i, 2, sqlReturn[i][3]);
        listHersteller->SetItem(i, 3, sqlReturn[i][4]);
    }    
}

void HerstellerPanel::EventListItemSelected(wxListEvent &event)
{  
    if(listHersteller->GetSelectedItemCount() > 1)
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

void HerstellerPanel::EventListItemDeselected(wxListEvent &event)
{
    if(listHersteller->GetSelectedItemCount() == 0)
    {
        lastSelectedItem = -1;
        main->button_removeObject->Enable(false);
    }
}

void HerstellerPanel::EventListItemActivated(wxListEvent &event)
{
    if(lastSelectedItem != -1)
    {
        new HerstellerDetail(main, lastSelectedItem);
    }
}

void HerstellerPanel::DeleteSelectedItem()
{
    if(lastSelectedItem != -1)
    {
		db->deleteLiefertByHerstellerId(lastSelectedItem);
        db->deleteArtikelByHerstellerId(lastSelectedItem);
        db->deleteHerstellerById(lastSelectedItem);
        this->SearchHersteller(wxT(""));
    }
}

void HerstellerPanel::EventHandleContextMenu(wxContextMenuEvent &event)
{
        wxMenu menu(wxT(""));
        
        if(lastSelectedItem != -1)
        {
            menu.Append(ID_CONTEXTHERSTELLERDETAIL, wxT("Herstellerdetails"));
            menu.Append(ID_CONTEXTHERSTELLEREDIT, wxT("Hersteller bearbeiten"));
            menu.Append(ID_CONTEXTHERSTELLERDELETE, wxT("Hersteller löschen"));
        }
        
        menu.Append(ID_CONTEXTHERSTELLERADD, wxT("Neuen Hersteller anlegen"));
        
        PopupMenu(&menu, ScreenToClient(event.GetPosition()));
}

void HerstellerPanel::EventHandleMenuHerstellerDelete(wxCommandEvent &event)
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

void HerstellerPanel::EventHandleMenuHerstellerAdd(wxCommandEvent &event)
{
    new HerstellerAdd(main);
}

void HerstellerPanel::EventHandleMenuHerstellerDetail(wxCommandEvent &event)
{
    new HerstellerDetail(main, lastSelectedItem);
}

void HerstellerPanel::EventHandleMenuHerstellerEdit(wxCommandEvent &event)
{
    new HerstellerEdit(main, lastSelectedItem);
}
