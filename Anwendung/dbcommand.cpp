#include "dbcommand.h"
DBCommand::DBCommand(DBConnectionManager *dbHandle)
{
	this->db = dbHandle;
}

DBCommand::~DBCommand()
{
}


void DBCommand::run(wxString command, CallbackBase &cbHandle)
{
	this->db->DBRunCommand(command, cbHandle);
}

vector< vector < wxString > > DBCommand::run(wxString command)
{
	return this->db->DBRunCommand(command);
}

unsigned int DBCommand::run(wxString command, bool test)
{
	return this->db->DBRunCommandTest(command);
}

//Artikel
void DBCommand::getAllArtikelValues(CallbackBase &cbHandle)
{
	wxString command = wxT("SELECT \
                                art.id, \
                                art.nr, \
                                art.beschreibung, \
                                art.vk_preis, \
                                EXTRACT(EPOCH FROM  art.create_date::timestamp), \
                                hr.name \
                            FROM \
                                artikel AS art \
                            INNER JOIN \
                                hersteller AS hr \
                            ON \
                                art.hersteller_id = hr.id");
                                
    this->run(command, cbHandle);
}

void DBCommand::getArtikelBySearch(CallbackBase &cbHandle, wxString &seq)
{
    wxString command = wxT("SELECT \
                                art.id, \
                                art.nr, \
                                art.beschreibung, \
                                art.vk_preis, \
                                EXTRACT(EPOCH FROM  art.create_date::timestamp), \
                                hr.name \
                            FROM \
                                artikel AS art \
                            INNER JOIN \
                                hersteller AS hr \
                            ON \
                                art.hersteller_id = hr.id \
                            WHERE \
                                LOWER(beschreibung) LIKE LOWER('%");
                                command << seq;
                                command << wxT("%') \
                            OR \
                                LOWER(nr) LIKE LOWER('%");
                                command << seq;
                                command << wxT("%') ");
    
    this->run(command, cbHandle);
}

void DBCommand::getArtikelById(CallbackBase &cbHandle, unsigned int artId)
{
    wxString command = wxT("SELECT \
                                art.id, \
                                art.nr, \
                                art.beschreibung, \
                                art.vk_preis, \
                                EXTRACT(EPOCH FROM  art.create_date::timestamp), \
                                hr.name, \
                                art.hersteller_id \
                            FROM \
                                artikel AS art \
                            INNER JOIN \
                                hersteller AS hr \
                            ON \
                                art.hersteller_id = hr.id \
                            WHERE \
                                art.id = ");
                                command << artId;
    
    this->run(command, cbHandle);
}

void DBCommand::deleteArtikelById(unsigned int id)
{
    wxString command = wxT("DELETE FROM artikel WHERE id = ");
    command << id;
    
    this->run(command);
}

void DBCommand::deleteArtikelByHerstellerId(unsigned int id)
{
    wxString command = wxT("DELETE FROM artikel WHERE hersteller_id = ");
    command << id;
    
    this->run(command);
}

void DBCommand::getCountArtikelByNr(CallbackBase &cbHandle, wxString nr)
{
	wxString command = wxT("SELECT \
                                COUNT(id) \
                            FROM \
                                artikel \
                            WHERE \
                                nr = '");
                                command << nr;
                                command << wxT("'");
	
	this->run(command, cbHandle);
}

int DBCommand::addNewArtikel(wxString artikelNr, wxString preis, wxString beschreibung, int herstellerId)
{
    int next_id = (wxAtoi(this->run(wxT("SELECT MAX(id) FROM artikel"))[0][0]) + 1);
    
    wxString command = wxT("INSERT INTO \
                                artikel (\
                                id, \
                                nr, \
                                beschreibung, \
                                vk_preis, \
                                hersteller_id \
                                ) \
                            VALUES (");
                            command << next_id;
                            command << wxT(", '");
                            command << artikelNr;
                            command << wxT("', '");
                            command << beschreibung;
                            command << wxT("', ");
                            command << preis;
                            command << wxT(", ");
                            command << herstellerId;
                            command << wxT(")");
                            
    this->run(command);
    return next_id;
}

void DBCommand::updateArtikelById(unsigned int artId, wxString artikelNr, wxString preis, wxString beschreibung, int herstellerId)
{
    wxString command = wxT("UPDATE \
                                artikel \
                            SET \
                                nr='");
                                command << artikelNr;
                                command << wxT("', \
                                beschreibung='");
                                command << beschreibung;
                                command << wxT("', \
                                vk_preis=");
                                command << preis;
                                command << wxT(", \
                                hersteller_id=");
                                command << herstellerId;
                                command << wxT(" \
                            WHERE \
                                id=");
                                command << artId;
    this->run(command);
}



//Lieferant
void DBCommand::getAllLieferantValues(CallbackBase &cbHandle)
{
    wxString command = wxT("SELECT \
                                id, \
                                name, \
                                strasse, \
                                plz, \
                                ort, \
                                telefon, \
                                fax, \
                                email, \
                                EXTRACT(EPOCH FROM create_date::timestamp) \
                            FROM \
                                lieferant");
                                
    this->run(command, cbHandle);
}

void DBCommand::getLieferantBySearch(CallbackBase &cbHandle, wxString &seq)
{
    wxString command = wxT("SELECT \
                                id, \
                                name, \
                                strasse, \
                                plz, \
                                ort, \
                                telefon, \
                                fax, \
                                email, \
                                EXTRACT(EPOCH FROM create_date::timestamp) \
                            FROM \
                                lieferant \
                            WHERE \
                                LOWER(name) LIKE LOWER('%");
                                command << seq;
                                command << wxT("%')");
    
    this->run(command, cbHandle);
}

void DBCommand::getLieferantById(CallbackBase &cbHandle, int lieferantId)
{
    wxString command = wxT("SELECT \
                                id, \
                                name, \
                                strasse, \
                                plz, \
                                ort, \
                                telefon, \
                                fax, \
                                email, \
                                EXTRACT(EPOCH FROM create_date::timestamp) \
                            FROM \
                                lieferant \
                            WHERE \
                                id=");
                                command << lieferantId;
    
    this->run(command, cbHandle);
}

void DBCommand::deleteLieferantById(unsigned int id)
{
    wxString command = wxT("DELETE FROM lieferant WHERE id = ");
    command << id;
    
    this->run(command);
}

int DBCommand::addNewLieferant(wxString name, wxString strasse, wxString plz, wxString ort, wxString telefon, wxString fax, wxString email)
{
    int next_id = (wxAtoi(this->run(wxT("SELECT MAX(id) FROM lieferant"))[0][0]) + 1);
    
    wxString command = wxT("INSERT INTO \
                                lieferant (\
                                id, \
                                name, \
                                strasse, \
                                plz, \
                                ort, \
                                telefon, \
                                fax, \
                                email) \
                            VALUES (");
                                command << next_id;
                                command << wxT(", '");
                                command << name;
                                command << wxT("', '");
                                command << strasse;
                                command << wxT("', '");
                                command << plz;
                                command << wxT("', '");
                                command << ort;
                                command << wxT("', '");
                                command << telefon;
                                command << wxT("', '");
                                command << fax;
                                command << wxT("', '");
                                command << email;
                                command << wxT("')");
                                
    this->run(command);
    return next_id;
}

void DBCommand::updateLieferantById(unsigned int lieferantId, wxString name, wxString strasse, wxString plz, wxString ort, wxString telefon, wxString fax, wxString email)
{
    wxString command = wxT("UPDATE \
								lieferant \
							SET \
                                name='");
                                command << name;
                                command << wxT("', \
                                strasse='");
                                command << strasse;
                                command << wxT("', \
                                plz='");
                                command << plz;
                                command << wxT("', \
								ort='");
                                command << ort;
                                command << wxT("', \
								telefon='");
                                command << telefon;
                                command << wxT("', \
								fax='");
                                command << fax;
                                command << wxT("', \
								email='");
                                command << email;
                                command << wxT("' \
                            WHERE \
                                id=");
                                command << lieferantId;
	
	this->run(command);
}



//Hersteller
void DBCommand::getAllHerstellerValues(CallbackBase &cbHandle)
{
    wxString command = wxT("SELECT \
                                id, \
                                name, \
                                strasse, \
                                plz, \
                                ort, \
                                telefon, \
                                fax, \
                                email, \
                                EXTRACT(EPOCH FROM  create_date::timestamp) \
                            FROM \
                                hersteller");
    this->run(command, cbHandle);
}

void DBCommand::getHerstellerById(CallbackBase &cbHandle, unsigned int herstellerId)
{
	wxString command = wxT("SELECT \
                                id, \
                                name, \
                                strasse, \
                                plz, \
                                ort, \
                                telefon, \
                                fax, \
                                email, \
                                EXTRACT(EPOCH FROM create_date::timestamp) \
                            FROM \
                                hersteller \
                            WHERE \
                                id=");
								command << herstellerId;
    
    this->run(command, cbHandle);
}

void DBCommand::getHerstellerBySearch(CallbackBase &cbHandle, wxString &seq)
{
    wxString command = wxT("SELECT \
                                id, \
                                name, \
                                strasse, \
                                plz, \
                                ort, \
                                telefon, \
                                fax, \
                                email, \
                                EXTRACT(EPOCH FROM  create_date::timestamp) \
                            FROM \
                                hersteller \
                            WHERE \
                                LOWER(name) LIKE LOWER('%");
                                command << seq;
                                command << wxT("%')");
    
    this->run(command, cbHandle);
}

void DBCommand::deleteHerstellerById(unsigned int id)
{
    wxString command = wxT("DELETE FROM hersteller WHERE id = ");
    command << id;
    
    this->run(command);
}

int DBCommand::addNewHersteller(wxString name, wxString strasse, wxString plz, wxString ort, wxString telefon, wxString fax, wxString email)
{
    int next_id = (wxAtoi(this->run(wxT("SELECT MAX(id) FROM hersteller"))[0][0]) + 1);
    
    wxString command = wxT("INSERT INTO \
                                hersteller (\
                                id, \
                                name, \
                                strasse, \
                                plz, \
                                ort, \
                                telefon, \
                                fax, \
                                email) \
                            VALUES (");
                                command << next_id;
                                command << wxT(", '");
                                command << name;
                                command << wxT("', '");
                                command << strasse;
                                command << wxT("', '");
                                command << plz;
                                command << wxT("', '");
                                command << ort;
                                command << wxT("', '");
                                command << telefon;
                                command << wxT("', '");
                                command << fax;
                                command << wxT("', '");
                                command << email;
                                command << wxT("')");
                                
    this->run(command);
    return next_id;
}

void DBCommand::updateHerstellerById(unsigned int herstellerId, wxString name, wxString strasse, wxString plz, wxString ort, wxString telefon, wxString fax, wxString email)
{
    wxString command = wxT("UPDATE \
								hersteller \
							SET \
                                name='");
                                command << name;
                                command << wxT("', \
                                strasse='");
                                command << strasse;
                                command << wxT("', \
                                plz='");
                                command << plz;
                                command << wxT("', \
								ort='");
                                command << ort;
                                command << wxT("', \
								telefon='");
                                command << telefon;
                                command << wxT("', \
								fax='");
                                command << fax;
                                command << wxT("', \
								email='");
                                command << email;
                                command << wxT("' \
                            WHERE \
                                id=");
                                command << herstellerId;
	
	this->run(command);
}

//Liefert

void DBCommand::addNewLiefert(unsigned int artikelId, unsigned int lieferantId, wxString ekPreis, wxString vhdate)
{
    int next_id = (wxAtoi(this->run(wxT("SELECT MAX(id) FROM liefert"))[0][0]) + 1);
    
    wxString command = wxT("INSERT INTO liefert (id, \
                                                artikel_id, \
                                                lieferant_id, \
                                                ek_preis, \
                                                vh_date \
                                                ) VALUES (");
                            command << next_id;
                            command << wxT(", ");
                            command << artikelId;
                            command << wxT(", ");
                            command << lieferantId;
                            command << wxT(", ");
                            command << ekPreis;
                            command << wxT(", '");
                            command << vhdate;
                            command << wxT("')");
                      
    this->run(command);
}

void DBCommand::deleteLiefertById(unsigned int liefertId)
{
    wxString command = wxT("DELETE FROM liefert WHERE id =");
    command << liefertId;
    
    this->run(command);
}

void DBCommand::deleteLiefertByArtikelId(unsigned int artId)
{
    wxString command = wxT("DELETE FROM liefert WHERE artikel_id=");
    command << artId;
    
    this->run(command);
}

void DBCommand::deleteLiefertByLieferantId(unsigned int lieferantId)
{
    wxString command = wxT("DELETE FROM liefert WHERE lieferant_id=");
    command << lieferantId;
    
    this->run(command);
}

void DBCommand::deleteLiefertByHerstellerId(unsigned int herstellerId)
{
	wxString command = wxT("DELETE FROM liefert WHERE artikel_id \
							IN \
							(SELECT id FROM artikel WHERE hersteller_id=");
							command << herstellerId;
							command << wxT(")");
							
	this->run(command);
}

void DBCommand::getArtikelLieferantByArtId(CallbackBase &cbHandle, unsigned int artId)
{
    wxString command = wxT("SELECT \
                                l.id, \
                                li.name, \
                                l.ek_preis, \
                                EXTRACT(EPOCH FROM  l.vh_date::timestamp) \
                            FROM \
                                liefert AS l \
                            INNER JOIN \
                                lieferant AS li \
                            ON \
                                li.id=l.lieferant_id \
                            WHERE \
                                l.artikel_id=");
                                command << artId;
    this->run(command, cbHandle);
}




void DBCommand::getArtikelLieferantByArtIdBySearch(CallbackBase &cbHandle, unsigned int artId, wxString &seq)
{
    wxString command = wxT("SELECT \
                                l.id, \
                                li.name, \
                                l.ek_preis, \
                                EXTRACT(EPOCH FROM  l.vh_date::timestamp) \
                            FROM \
                                liefert AS l \
                            INNER JOIN \
                                lieferant AS li \
                            ON \
                                li.id=l.lieferant_id \
                            WHERE \
                                l.artikel_id=");
                                command << artId;
                                command << wxT(" \
                            AND \
                                LOWER(li.name) LIKE LOWER('%");
                                command << seq;
                                command << wxT("%')");
    
    this->run(command, cbHandle);
}

void DBCommand::getLieferantArtikelByLieferantId(CallbackBase &cbHandle, unsigned int lieferantId)
{
    wxString command = wxT("SELECT \
                                l.id, \
                                art.nr, \
								art.beschreibung, \
                                l.ek_preis, \
                                EXTRACT(EPOCH FROM  l.vh_date::timestamp) \
                            FROM \
                                liefert AS l \
                            INNER JOIN \
                                artikel AS art \
                            ON \
                                art.id=l.artikel_id \
                            WHERE \
                                l.lieferant_id=");
                                command << lieferantId;
    this->run(command, cbHandle);
}

void DBCommand::getLieferantArtikelByLieferantIdBySearch(CallbackBase &cbHandle, unsigned int lieferantId, wxString &seq)
{
    wxString command = wxT("SELECT \
                                l.id, \
                                art.nr, \
								art.beschreibung, \
                                l.ek_preis, \
                                EXTRACT(EPOCH FROM  l.vh_date::timestamp) \
                            FROM \
                                liefert AS l \
                            INNER JOIN \
                                artikel AS art \
                            ON \
                                art.id=l.artikel_id \
                            WHERE \
                                l.lieferant_id=");
                                command << lieferantId;
                                command << wxT(" \
                            AND (\
                                LOWER(art.nr) LIKE LOWER('%");
                                command << seq;
                                command << wxT("%') \
							OR \
								LOWER(art.beschreibung) LIKE LOWER('%");
								command << seq;
								command << wxT("%'))");
    cerr << command << endl;
    this->run(command, cbHandle);
}

//Überprüfung der DBStruktur
bool DBCommand::checkTableStruktur()
{
	wxString check_artikel 		= wxT("SELECT id, nr, beschreibung, hersteller_id, vk_preis, create_date FROM artikel LIMIT 1");
	wxString check_lieferant 	= wxT("SELECT id, name, strasse, plz, ort, telefon, fax, email, create_date FROM lieferant LIMIT 1");
	wxString check_hersteller	= wxT("SELECT id, name, strasse, plz, ort, telefon, fax, email, create_date FROM hersteller LIMIT 1");
	wxString check_liefert		= wxT("SELECT id, artikel_id, lieferant_id, ek_preis, vh_date, create_date FROM liefert LIMIT 1");

	if(this->run(check_artikel, true) == 0)
	{
		if(this->run(check_lieferant, true) == 0)
		{
			if(this->run(check_hersteller, true) == 0)
			{
				if(this->run(check_liefert, true) ==0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

wxString DBCommand::insertTableStruktur()
{
	wxString table_artikel = wxT("\
		CREATE TABLE artikel (\
			id integer NOT NULL,\
			nr character varying(60) NOT NULL,\
			beschreibung text,\
			hersteller_id integer NOT NULL,\
			vk_preis numeric(8,2),\
			create_date timestamp without time zone DEFAULT now(),\
			CONSTRAINT artikel_pk PRIMARY KEY (id), \
			CONSTRAINT artikel_nr_key UNIQUE (nr), \
			CONSTRAINT artikel_fk_hersteller FOREIGN KEY (hersteller_id) REFERENCES hersteller(id) \
		);");
			
	wxString table_lieferant = wxT("\
		CREATE TABLE lieferant (\
			id integer NOT NULL,\
			name character varying(120) NOT NULL,\
			strasse character varying(120),\
			plz character varying(10),\
			ort character varying(120),\
			telefon character varying(40),\
			fax character varying(40),\
			email character varying(120),\
			create_date timestamp without time zone DEFAULT now(), \
			CONSTRAINT lieferant_pk PRIMARY KEY (id) \
		);\n");
		
	wxString table_hersteller = wxT("\
		CREATE TABLE hersteller (\
			id integer NOT NULL,\
			name character varying(80) NOT NULL,\
			strasse character varying(120),\
			plz character varying(10),\
			ort character varying(120),\
			telefon character varying(40),\
			fax character varying(40),\
			create_date timestamp without time zone DEFAULT now(),\
			email character varying(120), \
			CONSTRAINT hersteller_pk PRIMARY KEY (id) \
		);\n");
		
	wxString table_liefert = wxT("\
		CREATE TABLE liefert (\
			id integer NOT NULL,\
			artikel_id integer NOT NULL,\
			lieferant_id integer NOT NULL,\
			ek_preis numeric(8,2),\
			vh_date timestamp without time zone,\
			create_date timestamp without time zone DEFAULT now(), \
			CONSTRAINT liefert_pk PRIMARY KEY (id), \
			CONSTRAINT liefert_fk_artikel FOREIGN KEY (artikel_id) REFERENCES artikel(id), \
			CONSTRAINT liefert_fk_lieferant FOREIGN KEY (lieferant_id) REFERENCES lieferant(id) \
		);\n");
	
	this->run(wxT("DROP TABLE liefert, lieferant, hersteller, artikel"), true);

	unsigned short check_hersteller = this->run(table_hersteller, true);
	unsigned short check_lieferant 	= this->run(table_lieferant, true);
	
	unsigned short check_artikel	= this->run(table_artikel, true);
	unsigned short check_liefert	= this->run(table_liefert, true);
	
	wxString result = wxT("");
	result << ((check_lieferant) ? wxT("Tabelle Lieferant Okay\n") : wxT("Tabelle Lieferant failed\n"));
	result << ((check_hersteller) ? wxT("Tabelle Hersteller Okay\n") : wxT("Tabelle Hersteller failed\n"));
	result << ((check_artikel) ? wxT("Tabelle Artikel Okay\n") : wxT("Tabelle Artikel failed\n"));
	result << ((check_liefert) ? wxT("Tabelle liefert Okay\n") : wxT("Tabelle liefert failed\n"));
	
	return result;
}