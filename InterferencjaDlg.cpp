#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "InterferencjaDlg.h"

InterferencjaDlg::InterferencjaDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
    : wxDialog(parent, id, title, pos, size, style)
{
    timer.Start(100); 
    
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* sizer_dc;
	sizer_dc = new wxFlexGridSizer( 2, 1, 0, 0 );
	sizer_dc->AddGrowableCol( 0 );
	sizer_dc->AddGrowableRow( 0 );
	sizer_dc->SetFlexibleDirection( wxHORIZONTAL );
	sizer_dc->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize );
	panel->SetBackgroundStyle(wxBG_STYLE_PAINT); 
	panel->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DDKSHADOW ) );
	panel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
	sizer_dc->Add( panel, 0, wxALIGN_TOP|wxEXPAND);
	
	wxFlexGridSizer* sizer_c;
	sizer_c = new wxFlexGridSizer( 3, 4, 0, 0 );
	sizer_c->SetFlexibleDirection( wxVERTICAL );
	sizer_c->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );	
	
	lenghtLABEL = new wxStaticText( this, wxID_ANY, wxT("lenght"), wxDefaultPosition, wxDefaultSize, 0 );
	lenghtLABEL->Wrap( -1 );
	sizer_c->Add( lenghtLABEL, 0, wxALIGN_CENTRE);
	
	lenght = new wxSlider( this, wxID_ANY, 50, 1, 100, wxDefaultPosition, wxSize( 100,30 ), wxSL_HORIZONTAL|wxRAISED_BORDER );
	sizer_c->Add( lenght, 0, wxALIGN_CENTRE);
	
	amplitudeLABEL = new wxStaticText( this, wxID_ANY, wxT("amplitude"), wxDefaultPosition, wxDefaultSize, 0 );
	amplitudeLABEL->Wrap( -1 );
	sizer_c->Add( amplitudeLABEL, 0, wxALIGN_CENTRE);
	
	amplitude = new wxSlider( this, wxID_ANY, 50, 1, 100, wxDefaultPosition, wxSize( 100,30 ), wxSL_HORIZONTAL|wxRAISED_BORDER );
	sizer_c->Add( amplitude, 0, wxALIGN_CENTRE);
	
	verticalLABEL = new wxStaticText( this, wxID_ANY, wxT("vertical"), wxDefaultPosition, wxDefaultSize, 0 );
	verticalLABEL->Wrap( -1 );
	sizer_c->Add( verticalLABEL, 0, wxALIGN_CENTRE);	
	
	vertical = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 100,30 ), wxSL_HORIZONTAL|wxRAISED_BORDER );
	sizer_c->Add( vertical, 0, wxALIGN_CENTRE);
	
	horizontalLABEL = new wxStaticText( this, wxID_ANY, wxT("horizontal"), wxDefaultPosition, wxDefaultSize, 0 );
	horizontalLABEL->Wrap( -1 );
	sizer_c->Add( horizontalLABEL, 0, wxALIGN_CENTRE);
	
	horizontal = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 100,30 ), wxSL_HORIZONTAL|wxRAISED_BORDER );
	sizer_c->Add( horizontal, 0, wxALIGN_CENTRE);
	
	frequencyLABEL = new wxStaticText( this, wxID_ANY, wxT("frequency"), wxDefaultPosition, wxDefaultSize, 0);
	frequencyLABEL->Wrap( -1 );
	sizer_c->Add( frequencyLABEL, 0, wxALIGN_CENTRE);
	
	frequency = new wxSlider( this, wxID_ANY, 50, 1, 100, wxDefaultPosition, wxSize( 100,30 ), wxSL_HORIZONTAL|wxRAISED_BORDER );
	sizer_c->Add( frequency, 0, wxALIGN_CENTRE);
	
	restart = new wxButton( this, wxID_ANY, wxT("restart"), wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxRAISED_BORDER );
	sizer_c->Add( restart, 0, wxALIGN_CENTRE);
	
	save = new wxButton( this, wxID_ANY, wxT("save"), wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxRAISED_BORDER );
	sizer_c->Add( save, 0, wxALIGN_CENTRE);
	
	sizer_dc->Add( sizer_c, 1, wxALIGN_CENTRE);
		
	this->SetSizer( sizer_dc );
	this->Layout();
	timer.SetOwner( this, wxID_ANY );
	
	panel->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( InterferencjaDlg::panelOnClick ), NULL, this );
	panel->Connect( wxEVT_PAINT, wxPaintEventHandler( InterferencjaDlg::panelOnPaint ), NULL, this );
	restart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InterferencjaDlg::restartOnButtonClick ), NULL, this );
	save->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( InterferencjaDlg::saveOnClick ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( InterferencjaDlg::OnTimerTimeout ) );
    Destroy(); 
}

void InterferencjaDlg::panelOnPaint( wxPaintEvent& event ) 
{ 
    wxAutoBufferedPaintDC dc(panel); 
    int x, y; 
    panel->GetSize(&x, &y); 
    Draw::draw(horizontal->GetValue(), &dc, x, y, vertical->GetValue(), wxGetLocalTimeMillis().ToDouble());
}

void InterferencjaDlg::panelOnClick( wxMouseEvent& event ) 
{ 
    Draw::source(event.GetPosition().x, event.GetPosition().y, wxGetLocalTimeMillis().ToDouble(), frequency->GetValue(), amplitude->GetValue(), lenght->GetValue());
}

void InterferencjaDlg::restartOnButtonClick(wxCommandEvent& event) 
{ 
    Draw::restart(); 
}

void InterferencjaDlg::saveOnClick( wxMouseEvent& event ) 
{
      timer.Stop();
      wxMemoryDC mdc;
      wxClientDC dc(panel);
      int w, h;
      panel->GetSize(&w,&h);
      wxBitmap bmp(w,h);
      wxFileDialog *save = new wxFileDialog(this,wxT("Save file"),wxT(""),wxT(""),wxT("*.png"),wxFD_SAVE);
      save->ShowModal();
      std::string dir = save->GetDirectory().ToStdString() + "/" + save->GetFilename().ToStdString();
      mdc.SelectObject(bmp);
      mdc.Blit(0,0,dc.GetSize().GetWidth(),dc.GetSize().GetHeight(),&dc,0,0,wxCOPY,false,-1,-1);
      wxImage image = bmp.ConvertToImage();
      image.SaveFile(dir,wxBITMAP_TYPE_TIFF);
}

void InterferencjaDlg::OnTimerTimeout( wxTimerEvent& event ) 
{ 
    panel->Refresh();
}

void InterferencjaDlg::OnClose(wxCloseEvent& event)
{
	Destroy();
}

InterferencjaDlg::~InterferencjaDlg()
{
	panel->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( InterferencjaDlg::panelOnClick ), NULL, this );
	panel->Disconnect( wxEVT_PAINT, wxPaintEventHandler( InterferencjaDlg::panelOnPaint ), NULL, this );
	restart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InterferencjaDlg::restartOnButtonClick ), NULL, this );
	save->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( InterferencjaDlg::saveOnClick ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( InterferencjaDlg::OnTimerTimeout ) );
}
