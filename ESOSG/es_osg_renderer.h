#ifndef ES_OSG_RENDERER_H_
#define ES_OSG_RENDERER_H_

#include <osgViewer/Viewer>

class RenderingCanvas
{
public:
	virtual void SetGraphicsWindow(osgViewer::GraphicsWindow* gw) = 0;

	virtual void grabFocus() = 0;
	virtual void grabFocusIfPointerInWindow() = 0;
	virtual void useCursor(bool bOn) = 0;

	virtual bool makeCurrentImplementation() = 0;
	virtual void swapBuffersImplementation() = 0;

	virtual bool isRealizedImplementation() const = 0;

	virtual int getSizeX() const = 0;
	virtual int getSizeY() const = 0;
};

class ESOSGRenderer
{
public:
	ESOSGRenderer();
	~ESOSGRenderer();

	void Init(RenderingCanvas& canvas);
	void Start();

	bool Render();

private:
	osg::ref_ptr<osgViewer::Viewer> _viewer;
	class RenderingThread;
	RenderingThread* _rendering_thread;
};

#endif //ES_OSG_RENDERER_H_