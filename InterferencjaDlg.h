#ifndef __INTERFERECJADLG_h__
#define __INTERFERECJADLG_h__

#include <wx/filedlg.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/timer.h>
#include "draw.h"

class InterferencjaDlg : public wxDialog 
{
	private:
		wxPanel* panel;
		wxStaticText* lenghtLABEL;
		wxSlider* lenght;
		wxStaticText* amplitudeLABEL;
		wxSlider* amplitude;
		wxStaticText* verticalLABEL;
		wxSlider* vertical;
		wxStaticText* horizontalLABEL;
		wxSlider* horizontal;
		wxStaticText* frequencyLABEL;
		wxSlider* frequency;
		wxButton* restart;
		wxButton* save;
		wxTimer timer;
		
		void panelOnClick( wxMouseEvent& event );
		void panelOnPaint( wxPaintEvent& event );
		void restartOnButtonClick( wxCommandEvent& event );
		void saveOnClick( wxMouseEvent& event );
		void OnTimerTimeout( wxTimerEvent& event );
		void OnClose( wxCloseEvent& event );
		
	public:
		InterferencjaDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Inteferencja fal"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(425, 425), long style = wxDEFAULT_DIALOG_STYLE ); 
		~InterferencjaDlg();
};

#endif
