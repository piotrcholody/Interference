#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "InterferencjaApp.h"


IMPLEMENT_APP(InterferencjaApp);

bool InterferencjaApp::OnInit()
{
    wxInitAllImageHandlers();
    InterferencjaDlg* dlg = new InterferencjaDlg(NULL);
    dlg->Show();
    return true;
}

