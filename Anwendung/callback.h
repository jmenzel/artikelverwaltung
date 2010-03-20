#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include <wx/wx.h>
#include <vector>

#include "callbackbase.h"

using namespace std;

template <class C>
class Callback: public CallbackBase 
{
  public:
    Callback(C *obj, void (C::*method)(vector< vector< wxString > >)) 
        : m_obj(obj), m_method(method) {}
        
    Callback(C *obj, void (C::*method)(vector< vector< wxString > >*)) 
        : m_obj(obj), m_method_p(method) {}
        
    Callback(C *obj, void (C::*method)(wxString)) 
        : m_obj(obj), m_method_str(method) {}

    Callback(C *obj, void (C::*method)()) 
        : m_obj(obj), m_method_v(method) {}

    //Aufrufen der Memberfunktion
    virtual void operator()(vector< vector< wxString > > wx_str) 
    { 
        (m_obj->*m_method)(wx_str); 
    }
    
    virtual void operator()(vector< vector< wxString > > *wx_str) 
    { 
        (m_obj->*m_method_p)(wx_str); 
    }
    
    virtual void operator()( wxString wx_str) 
    { 
        (m_obj->*m_method_str)(wx_str); 
    }
    
    virtual void operator()() 
    { 
        (m_obj->*m_method_v)(); 
    }
    
  private:
    // Objekt, dessen Memberfunktion aufgerufen werden soll
    C *m_obj;  
    
    // Zeiger auf die Memberfunktion
    void (C::*m_method)(vector< vector< wxString > >);
    void (C::*m_method_p)(vector< vector< wxString > >*);
    void (C::*m_method_str)(wxString);
    void (C::*m_method_v)();
};

#endif