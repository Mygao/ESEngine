#include "es_ui_osg_canvas.h"
#include <wx/dcclient.h>

ESUIOSGCanvas::ESUIOSGCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos,
	const wxSize& size,	long style,	const wxString& name, int* attributes) 
	: wxGLCanvas(parent, id, pos, size, style | wxFULL_REPAINT_ON_RESIZE, name, attributes)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	_oldCursor = *wxSTANDARD_CURSOR;
	_renderer = new ESOSGRenderer();
	_renderer->Init(*this);
	_renderer->Start();
}

ESUIOSGCanvas::~ESUIOSGCanvas()
{
	delete _renderer;
}

void ESUIOSGCanvas::SetGraphicsWindow(osgViewer::GraphicsWindow* gw)
{
	_graphics_window = gw;
}

BEGIN_EVENT_TABLE(ESUIOSGCanvas, wxGLCanvas)
	EVT_SIZE(ESUIOSGCanvas::OnSize)
	EVT_PAINT(ESUIOSGCanvas::OnPaint)
	EVT_ENTER_WINDOW(ESUIOSGCanvas::OnMouseEnter)
	EVT_LEFT_DOWN(ESUIOSGCanvas::OnMouseDown)
	EVT_MIDDLE_DOWN(ESUIOSGCanvas::OnMouseDown)
	EVT_RIGHT_DOWN(ESUIOSGCanvas::OnMouseDown)
	EVT_LEFT_UP(ESUIOSGCanvas::OnMouseUp)
	EVT_MIDDLE_UP(ESUIOSGCanvas::OnMouseUp)
	EVT_RIGHT_UP(ESUIOSGCanvas::OnMouseUp)
	EVT_MOTION(ESUIOSGCanvas::OnMouseMotion)
	EVT_MOUSEWHEEL(ESUIOSGCanvas::OnMouseWheel)
END_EVENT_TABLE()

void ESUIOSGCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
}


void ESUIOSGCanvas::OnSize(wxSizeEvent& event)
{
	// this is also necessary to update the context on some platforms
	wxGLCanvas::OnSize(event);
	// set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
	int width, height;
	GetClientSize(&width, &height);

	if (_graphics_window.valid())
	{
		// update the window dimensions, in case the window has been resized.
		_graphics_window->getEventQueue()->windowResize(0, 0, width, height);
		_graphics_window->resized(0, 0, width, height);
	}
}

void ESUIOSGCanvas::OnEraseBackground(wxEraseEvent& event)
{

}

void ESUIOSGCanvas::OnMouseEnter(wxMouseEvent& event)
{
	SetFocus();
}

void ESUIOSGCanvas::OnMouseDown(wxMouseEvent& event)
{
	if (_graphics_window.valid())
	{
		_graphics_window->getEventQueue()
			->mouseButtonPress(event.GetX(), event.GetY(), event.GetButton());
	}
}

void ESUIOSGCanvas::OnMouseUp(wxMouseEvent& event)
{
	if (_graphics_window.valid())
	{
		_graphics_window->getEventQueue()
			->mouseButtonRelease(event.GetX(), event.GetY(), event.GetButton());
	}
}

void ESUIOSGCanvas::OnMouseMotion(wxMouseEvent& event)
{
	if (_graphics_window.valid())
	{
		_graphics_window->getEventQueue()->mouseMotion(event.GetX(), event.GetY());
	}
}

void ESUIOSGCanvas::OnMouseWheel(wxMouseEvent& event)
{
	int delta = event.GetWheelRotation() / event.GetWheelDelta() * event.GetLinesPerAction();

	if (_graphics_window.valid())
	{
		_graphics_window->getEventQueue()->mouseScroll(
			delta > 0 ? osgGA::GUIEventAdapter::SCROLL_DOWN : osgGA::GUIEventAdapter::SCROLL_UP);
	}
}

//RenderingCanvas impl
void ESUIOSGCanvas::grabFocus()
{
	SetFocus();
}

void ESUIOSGCanvas::grabFocusIfPointerInWindow()
{
	wxPoint pos = wxGetMousePosition();
	if (wxFindWindowAtPoint(pos) == this) {
		SetFocus();
	}
}

void ESUIOSGCanvas::useCursor(bool bOn)
{
	if (bOn)
	{
		SetCursor(_oldCursor);
	}
	else
	{
		_oldCursor = GetCursor();

		// hide the cursor
		//    - can't find a way to do this neatly, so create a 1x1, transparent image
		wxImage image(1, 1);
		image.SetMask(true);
		image.SetMaskColour(0, 0, 0);
		wxCursor cursor(image);
		SetCursor(cursor);

		// On wxGTK, only works as of version 2.7.0
		// (http://trac.wxwidgets.org/ticket/2946)
		// SetCursor( wxStockCursor( wxCURSOR_BLANK ) );
	}
}

bool ESUIOSGCanvas::makeCurrentImplementation()
{
	SetCurrent();
	return true;
}

void ESUIOSGCanvas::swapBuffersImplementation()
{
	SwapBuffers();
}

bool ESUIOSGCanvas::isRealizedImplementation() const
{
	return IsShownOnScreen();
}

int ESUIOSGCanvas::getSizeX() const
{
	int width, height;
	GetClientSize(&width, &height);
	return width;
}

int ESUIOSGCanvas::getSizeY() const
{
	int width, height;
	GetClientSize(&width, &height);
	return height;
}
