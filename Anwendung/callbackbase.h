#ifndef _CALLBACKBASE_H_
#define _CALLBACKBASE_H_

#include <wx/string.h>
#include <vector>

class CallbackBase 
{
  public:
    virtual void operator()(std::vector< std::vector< wxString > > wx_str){};
    virtual void operator()(std::vector< std::vector< wxString > > *wx_str){};
    virtual void operator()( wxString wx_str){};
    virtual void operator()(){};
};

#endif