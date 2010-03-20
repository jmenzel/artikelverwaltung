#include "mainwindow.h"

#include <stdlib.h>
#include <wx/wx.h>


IMPLEMENT_APP(Artikelverwaltung)

bool Artikelverwaltung::OnInit()
{
    MainWindow *frame = new MainWindow( wxT("Artikelverwaltung"), 50, 50, 850, 500);

    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
}
