#include "es_ui_app.h"
#include "es_ui_osg_mainframe.h"
#include "es_ui_osg_canvas.h"

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