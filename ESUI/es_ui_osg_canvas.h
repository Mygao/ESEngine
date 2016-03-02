#ifndef ES_UI_OSG_CANVAS_H_
#define ES_UI_OSG_CANVAS_H_

#include "wx/glcanvas.h"
#include "es_osg_renderer.h"

class ESUIOSGCanvas : public wxGLCanvas, public RenderingCanvas
{
public:
	ESUIOSGCanvas(wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxT("ESUIOSGCanvas"),
		int* attributes = 0);
	
	virtual ~ESUIOSGCanvas();
	
	DECLARE_EVENT_TABLE()

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& event);

	//RenderingCanvas impl
	virtual void grabFocus();
	virtual void grabFocusIfPointerInWindow();
	virtual void useCursor(bool bOn);

	virtual bool makeCurrentImplementation();
	virtual void swapBuffersImplementation();

	virtual bool isRealizedImplementation() const;

	virtual int getSizeX() const;
	virtual int getSizeY() const;

private:
	wxCursor _oldCursor;
	ESOSGRenderer* _renderer;
	osg::ref_ptr<osgViewer::GraphicsWindow> _graphics_window;

};

#endif //ES_UI_OSG_CANVAS_H_