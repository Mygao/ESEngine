#include "es_ui_app.h"
#include "es_ui_osg_mainframe.h"
#include "es_ui_osg_canvas.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()

IMPLEMENT_APP(ESUIApp)

bool ESUIApp::OnInit()
{
	//MainFrame *frame = new MainFrame("ES UI", wxPoint(50, 50), wxSize(450, 340));
	ESUIOSGMainFrame *frame = new ESUIOSGMainFrame(NULL, "ES UI", wxPoint(50, 50), wxSize(800, 600));

	int attributes[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER,
		WX_GL_SAMPLE_BUFFERS, GL_TRUE,	// Required only for multi-sampling(AA)
		WX_GL_SAMPLES, 4,				// Required only for supersampleing
		WX_GL_DEPTH_SIZE, 16,
		WX_GL_STENCIL_SIZE, 8,
		0, 0 };

	wxPanel* panel = new wxPanel(frame, wxID_ANY, wxDefaultPosition, wxSize(800, 600), wxNO_BORDER);
	ESUIOSGCanvas* canvas = new ESUIOSGCanvas(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600), wxNO_BORDER, wxT("OSGCanvas"), attributes);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(canvas, 1, wxEXPAND);

	panel->SetSizer(sizer);
	panel->SetAutoLayout(true);

	frame->Show(true);

	return true;
}

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
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

void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("UI for ESEngine",
		"About ES UI", wxOK | wxICON_INFORMATION);
}
