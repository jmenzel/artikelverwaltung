#include "lieferantedit.h"
#include "mainwindow.h"

BEGIN_EVENT_TABLE( LieferantEdit, wxFrame)
	EVT_TEXT(ID_TFIELD_NAME, LieferantEdit::EventTextChangedName)
    EVT_BUTTON(ID_BUTTON_SAVE, LieferantEdit::EventOnClickButtonSave)
END_EVENT_TABLE()

LieferantEdit::LieferantEdit(MainWindow *parent, unsigned int lieferantId)
    : wxFrame ( (wxFrame *) parent, -1, wxT("Lieferanten bearbeiten"), wxPoint(-1, -1), wxSize(420, 255))
{
	main = parent;
	this->lId = lieferantId;
	
	db = new DBCommand(main->getDBManageObject());
    panel = new wxPanel (this, ID_PANEL, wxPoint(0, 0), wxSize(420, 230));
    CreateStatusBar(1);
    
    
    tlabel_name = new wxStaticText(panel, ID_TLABEL_NAME, wxT("Name"), wxPoint(10, 15), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_strasse = new wxStaticText(panel, ID_TLABEL_STRASSE, wxT("Strasse"), wxPoint(10, 45), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_plz_ort = new wxStaticText(panel, ID_TLABEL_PLZORT, wxT("PLZ / Ort"), wxPoint(10, 75), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_telefon = new wxStaticText(panel, ID_TLABEL_TELEFON, wxT("Telefon"), wxPoint(10, 105), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_fax = new wxStaticText(panel, ID_TLABEL_FAX, wxT("Telfax"), wxPoint(10, 135), wxSize(-1, -1), wxALIGN_LEFT);
    tlabel_email = new wxStaticText(panel, ID_TLABEL_FAX, wxT("Email"), wxPoint(10, 165), wxSize(-1, -1), wxALIGN_LEFT);
    
    tfield_name = new wxTextCtrl( panel, ID_TFIELD_NAME, wxT(""), wxPoint(190, 13), wxSize(220, -1), wxTE_HT_BELOW );
    tfield_strasse = new wxTextCtrl( panel, ID_TFIELD_STRASSE, wxT(""), wxPoint(190, 43), wxSize(220, -1), wxTE_HT_BELOW );
    tfield_plz = new wxTextCtrl( panel, ID_TFIELD_PLZ, wxT(""), wxPoint(190, 73), wxSize(70, -1), wxTE_HT_BELOW );
    tfield_ort = new wxTextCtrl( panel, ID_TFIELD_ORT, wxT(""), wxPoint(265, 73), wxSize(145, -1), wxTE_HT_BELOW );
    tfield_telefon = new wxTextCtrl( panel, ID_TFIELD_TELEFON, wxT(""), wxPoint(190, 103), wxSize(220, -1), wxTE_HT_BELOW );
    tfield_fax = new wxTextCtrl( panel, ID_TFIELD_FAX, wxT(""), wxPoint(190, 133), wxSize(220, -1), wxTE_HT_BELOW );
    tfield_email = new wxTextCtrl( panel, ID_TFIELD_EMAIL, wxT(""), wxPoint(190, 163), wxSize(220, -1), wxTE_HT_BELOW );
    
    button_save = new wxButton(panel, ID_BUTTON_SAVE, wxT("Speichern"), wxPoint(300, 200), wxSize(-1, -1));
	button_save->Enable(false);
    
    arr_val_plz.Add(wxT('0'));
    arr_val_plz.Add(wxT('1'));
    arr_val_plz.Add(wxT('2'));
    arr_val_plz.Add(wxT('3'));
    arr_val_plz.Add(wxT('4'));
    arr_val_plz.Add(wxT('5'));
    arr_val_plz.Add(wxT('6'));
    arr_val_plz.Add(wxT('7'));
    arr_val_plz.Add(wxT('8'));
    arr_val_plz.Add(wxT('9'));
    
    arr_val_telFax.Add(wxT('0'));
    arr_val_telFax.Add(wxT('1'));
    arr_val_telFax.Add(wxT('2'));
    arr_val_telFax.Add(wxT('3'));
    arr_val_telFax.Add(wxT('4'));
    arr_val_telFax.Add(wxT('5'));
    arr_val_telFax.Add(wxT('6'));
    arr_val_telFax.Add(wxT('7'));
    arr_val_telFax.Add(wxT('8'));
    arr_val_telFax.Add(wxT('9'));
    arr_val_telFax.Add(wxT('-'));
    arr_val_telFax.Add(wxT('/'));
    arr_val_telFax.Add(wxT('('));
    arr_val_telFax.Add(wxT(')'));
    arr_val_telFax.Add(wxT(' '));
    arr_val_telFax.Add(wxT('+'));
    
    val_tfield_plz = new wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST);
    val_tfield_plz->SetIncludes(arr_val_plz);
    
    val_tfield_telFax = new wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST);
    val_tfield_telFax->SetIncludes(arr_val_telFax);
    
	tfield_plz->SetValidator(*val_tfield_plz);
    tfield_telefon->SetValidator(*val_tfield_telFax);
    tfield_fax->SetValidator(*val_tfield_telFax);

	db->getLieferantById(*new Callback<LieferantEdit>(this, &LieferantEdit::FillLieferantData), this->lId);

    this->Show();
}

LieferantEdit::~LieferantEdit()
{
}

void LieferantEdit::FillLieferantData(vector< vector< wxString > > data)
{
	if(data.size() > 0)
	{
		tfield_name->SetValue(data[0][1]);
		tfield_strasse->SetValue(data[0][2]);
		tfield_plz->SetValue(data[0][3]);
		tfield_ort->SetValue(data[0][4]);
		tfield_telefon->SetValue(data[0][5]);
		tfield_fax->SetValue(data[0][6]);
		tfield_email->SetValue(data[0][7]);
	}
}

void LieferantEdit::EventTextChangedName(wxCommandEvent &event)
{
    if(tfield_name->GetValue().Length() > 0)
    {
        button_save->Enable(true);
    }
    else
    {
        button_save->Enable(false);
    }
}

void LieferantEdit::EventOnClickButtonSave(wxCommandEvent &event)
{
    if(tfield_name->GetValue().Length() > 0)
    {
        if( tfield_strasse->GetValue().Length() == 0 || 
            tfield_plz->GetValue().Length() == 0 || 
            tfield_ort->GetValue().Length() == 0 || 
            tfield_telefon->GetValue().Length() == 0 || 
            tfield_fax->GetValue().Length() == 0 || 
            tfield_email->GetValue().Length() == 0 )
        {
            wxMessageDialog *confirm = new wxMessageDialog(this, wxT("Ihre Eingaben sind nicht vollständig,\nwollen Sie trotzdem fortfahren?"), wxT("Daten unvollständig"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
            int result = confirm->ShowModal();
            if(result == wxID_NO)
            {
                return;
            }

        }
        
        db->updateLieferantById(this->lId,
								tfield_name->GetValue(),
								tfield_strasse->GetValue(),
								tfield_plz->GetValue(),
								tfield_ort->GetValue(),
								tfield_telefon->GetValue(),
								tfield_fax->GetValue(),
								tfield_email->GetValue());
			
        main->getLieferantPanelObject()->SearchLieferant(wxT(""));
        
        
        this->Close();        
    }
        
}
