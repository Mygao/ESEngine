#ifndef ES_UI_OSG_MAINFRAME_H_
#define ES_UI_OSG_MAINFRAME_H_

#include <wx/frame.h>

class ESUIOSGMainFrame : public wxFrame
{
public:
	ESUIOSGMainFrame(wxFrame *frame, const wxString& title, 
		const wxPoint& pos, const wxSize& size, 
		long style = wxDEFAULT_FRAME_STYLE);
	~ESUIOSGMainFrame();

	//void SetViewer(osgViewer::Viewer *viewer);
	void OnIdle(wxIdleEvent& event);

private:
	//osg::ref_prt<osgViewer::Viewer> _viewer;

	DECLARE_EVENT_TABLE()
};

#endif //ES_UI_OSG_MAINFRAME_H_