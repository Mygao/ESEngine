#ifndef ES_UI_OSG_MAINFRAME_H_
#define ES_UI_OSG_MAINFRAME_H_

#include <wx/wx.h>

class ESUIOSGMainFrame : public wxFrame
{
public:
	ESUIOSGMainFrame(wxFrame *frame, const wxString& title, 
		const wxPoint& pos, const wxSize& size, 
		long style = wxDEFAULT_FRAME_STYLE);
	~ESUIOSGMainFrame();

	void OnIdle(wxIdleEvent& event);

private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

#endif //ES_UI_OSG_MAINFRAME_H_