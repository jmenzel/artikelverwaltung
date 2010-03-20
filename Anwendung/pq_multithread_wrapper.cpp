#include "pq_multithread_wrapper.h"

PQ_Multithread_Wrapper::PQ_Multithread_Wrapper(PostgreSQL_Connector *psMain, wxString &sql_command, CallbackBase &cb)
    : wxThread()
{
	ps = psMain;
    s = sql_command;
    m_pcb = &cb;
}

void PQ_Multithread_Wrapper::OnExit()
{

}

void *PQ_Multithread_Wrapper::Entry()
{	
    vector< vector<wxString> > sqlReturn;
    if(s.find(wxT("select")) != wxString::npos || s.find(wxT("SELECT")) != wxString::npos)
    {
        if(ps->runCommand(s, sqlReturn) == 0)
        {
            //GUI Thread reservieren
            wxMutexGuiEnter();
			
			//Rückgabe des SQL Results an den Memberzeiger;
            if(this->m_pcb)
            {
				(*this->m_pcb)(sqlReturn);
            }
			else
			{
				//Skipp
				cerr << "Methodenpointer nicht vorhanden - Nullpointer?" << endl;
			}
			
            wxMutexGuiLeave();
        }
		else
		{
			cerr << "SQL Statement nicht erfolgreich " << endl;
		}
    }
    else
    {
       ps->runCommand(s);
    }
   
    return NULL;
}