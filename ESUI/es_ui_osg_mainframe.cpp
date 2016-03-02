#include "es_ui_osg_mainframe.h"

enum
{
	ID_Hello = 1
};

ESUIOSGMainFrame::ESUIOSGMainFrame(wxFrame *frame, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(frame, wxID_ANY, title, pos, size, style)
{
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(ID_Hello, "&Hello...\tCtrl-F",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	CreateStatusBar();

	SetStatusText("Welcome to ESEngine!");
}

ESUIOSGMainFrame::~ESUIOSGMainFrame()
{
}

BEGIN_EVENT_TABLE(ESUIOSGMainFrame, wxFrame)
	EVT_IDLE(ESUIOSGMainFrame::OnIdle)
	EVT_MENU(wxID_EXIT, ESUIOSGMainFrame::OnExit)
	EVT_MENU(wxID_ABOUT, ESUIOSGMainFrame::OnAbout)
END_EVENT_TABLE()

void ESUIOSGMainFrame::OnIdle(wxIdleEvent& event)
{
	event.RequestMore();
}

void ESUIOSGMainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void ESUIOSGMainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("UI for ESEngine",
		"About ES UI", wxOK | wxICON_INFORMATION);
}
