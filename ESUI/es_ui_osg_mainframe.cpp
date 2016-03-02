#include "es_ui_osg_mainframe.h"

ESUIOSGMainFrame::ESUIOSGMainFrame(wxFrame *frame, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(frame, wxID_ANY, title, pos, size, style)
{
}

ESUIOSGMainFrame::~ESUIOSGMainFrame()
{
}

BEGIN_EVENT_TABLE(ESUIOSGMainFrame, wxFrame)
	EVT_IDLE(ESUIOSGMainFrame::OnIdle)
END_EVENT_TABLE()

void ESUIOSGMainFrame::OnIdle(wxIdleEvent& event)
{
}