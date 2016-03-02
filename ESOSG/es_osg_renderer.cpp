#include "es_osg_renderer.h"

#include <tchar.h>

#include <osg/Group>
#include <osg/ShapeDrawable>
#include <osg/PolygonMode>
#include <osg/Projection>
#include <osg/MatrixTransform>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

class GraphicsWindowWX : public osgViewer::GraphicsWindow
{
public:
	GraphicsWindowWX(RenderingCanvas& canvas)
		: _canvas(canvas)
	{
		_traits = new GraphicsContext::Traits;
		_traits->x = 0;
		_traits->y = 0;
		_traits->width = canvas.getSizeX();
		_traits->height = canvas.getSizeY();

		Init();
	}
	~GraphicsWindowWX(){}

	void Init()
	{
		if (valid())
		{
			setState(new osg::State);
			getState()->setGraphicsContext(this);

			if (_traits.valid() && _traits->sharedContext.valid())
			{
				getState()->setContextID(_traits->sharedContext->getState()->getContextID());
				incrementContextIDUsageCount(getState()->getContextID());

			}
			else
			{
				getState()->setContextID(osg::GraphicsContext::createNewContextID());
			}
		}
	}

	void grabFocus()
	{
		_canvas.grabFocus();
	}
	
	void grabFocusIfPointerInWindow()
	{
		_canvas.grabFocusIfPointerInWindow();
	}

	bool makeCurrentImplementation()
	{
		return _canvas.makeCurrentImplementation();
	}

	void swapBuffersImplementation()
	{
		return _canvas.swapBuffersImplementation();
	}

	virtual bool valid() const { return true; }
	virtual bool realizeImplementation() { return true; }
	virtual bool isRealizedImplementation() const 
	{
		return _canvas.isRealizedImplementation();
	}
	virtual void closeImplementation() {}
	virtual bool releaseContextImplementation() { return true; }

private:
	RenderingCanvas& _canvas;
};

class ESOSGRenderer::RenderingThread : public OpenThreads::Thread
{
public:
	RenderingThread(ESOSGRenderer& renderer) : OpenThreads::Thread(), _renderer(renderer) {}
	virtual ~RenderingThread() {}

	virtual void run() {
		while (_renderer.Render()) {
			YieldCurrentThread();
#ifdef _DEBUG
			microSleep(10000);
#else
			microSleep(33000);
#endif
		}
	}

	ESOSGRenderer& _renderer;
};

ESOSGRenderer::ESOSGRenderer() : _viewer(0)
{

}

ESOSGRenderer::~ESOSGRenderer()
{
	if (_rendering_thread)
	{
		_viewer->setDone(true);
		_rendering_thread->cancel();
		_rendering_thread->join();
	}

	delete _rendering_thread;
}

void ESOSGRenderer::Init(RenderingCanvas& canvas)
{
	_viewer = new osgViewer::Viewer();
	
	GraphicsWindowWX* gw = new GraphicsWindowWX(canvas);
	canvas.SetGraphicsWindow(gw);

	osg::Camera* camera = _viewer->getCamera();

	camera->setGraphicsContext(gw);

	camera->setViewport(new osg::Viewport(0, 0, canvas.getSizeX(), canvas.getSizeY()));
	camera->setClearColor(osg::Vec4((40.0 / 255.0), (40.0 / 255.0), (40.0 / 255.0), 1.0));
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->setViewMatrixAsLookAt(osg::Vec3(0.0, 10.0, 0.0), osg::Vec3(0.0, 0.0, 0.0), osg::Vec3(0.0, 0.0, 1.0));

	osg::Box* unitCube = new osg::Box(osg::Vec3(0, 0, 0), 1.0f);

	osg::ShapeDrawable* unitCubeDrawable = new osg::ShapeDrawable(unitCube);
	unitCubeDrawable->setColor(osg::Vec4(255.0, 255.0, 255.0, 0.5));
	osg::Geode* basicShapesGeode = new osg::Geode();

	basicShapesGeode->addDrawable(unitCubeDrawable);

	_root = new osg::Group();
	_root->addChild(basicShapesGeode);

	osg::ref_ptr<osg::StateSet> stateset = _viewer->getCamera()->getOrCreateStateSet();
	osg::ref_ptr<osg::PolygonMode> pm = new osg::PolygonMode;
	pm->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	stateset->setAttribute(pm.get());

	//HUD
	AddHUD();
	////////
	
	_viewer->setSceneData(_root.get());
	_viewer->addEventHandler(new osgViewer::StatsHandler);
	_viewer->setCameraManipulator(new osgGA::TrackballManipulator);
}

void ESOSGRenderer::Start()
{
	if (!_viewer)
	{
		return;
	}

	//_viewer->run();

	_rendering_thread = new RenderingThread(*this);
	_rendering_thread->startThread();
}

bool ESOSGRenderer::Render()
{
	if (!_viewer.valid() || _viewer->done())
	{
		return false;
	}
	
	_viewer->frame();

	return true;
}

void ESOSGRenderer::AddHUD()
{
	osg::Projection* HUDProjectionMatrix = new osg::Projection;
	HUDProjectionMatrix->setMatrix(osg::Matrix::ortho2D(0, 800, 0, 600));

	osg::MatrixTransform* HUDModelViewMatrix = new osg::MatrixTransform;
	HUDModelViewMatrix->setMatrix(osg::Matrix::identity());

	HUDModelViewMatrix->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	_root->addChild(HUDProjectionMatrix);
	HUDProjectionMatrix->addChild(HUDModelViewMatrix);

	osg::Geode* HUDGeode = new osg::Geode();
	osgText::Text* text = new osgText::Text();

	HUDModelViewMatrix->addChild(HUDGeode);

	osg::Geometry* HUDBackgroundGeometry = new osg::Geometry();

	osg::Vec3Array* HUDBackgroundVertices = new osg::Vec3Array;
	HUDBackgroundVertices->push_back(osg::Vec3(0, 0, -1));
	HUDBackgroundVertices->push_back(osg::Vec3(800, 0, -1));
	HUDBackgroundVertices->push_back(osg::Vec3(800, 200, -1));
	HUDBackgroundVertices->push_back(osg::Vec3(0, 200, -1));

	osg::DrawElementsUInt* HUDBackgroundIndices = new osg::DrawElementsUInt(osg::PrimitiveSet::POLYGON, 0);
	HUDBackgroundIndices->push_back(0);
	HUDBackgroundIndices->push_back(1);
	HUDBackgroundIndices->push_back(2);
	HUDBackgroundIndices->push_back(3);

	osg::Vec4Array* HUDcolors = new osg::Vec4Array;
	HUDcolors->push_back(osg::Vec4(0.8f, 0.0f, 0.8f, 0.8f));

	osg::Vec2Array* texcoords = new osg::Vec2Array(4);
	(*texcoords)[0].set(0.0f, 0.0f);
	(*texcoords)[1].set(1.0f, 0.0f);
	(*texcoords)[2].set(1.0f, 1.0f);
	(*texcoords)[3].set(0.0f, 1.0f);

	HUDBackgroundGeometry->setTexCoordArray(0, texcoords);
	osg::Vec3Array* HUDnormals = new osg::Vec3Array;
	HUDnormals->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	HUDBackgroundGeometry->setNormalArray(HUDnormals);
	HUDBackgroundGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
	HUDBackgroundGeometry->addPrimitiveSet(HUDBackgroundIndices);
	HUDBackgroundGeometry->setVertexArray(HUDBackgroundVertices);
	HUDBackgroundGeometry->setColorArray(HUDcolors);
	HUDBackgroundGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	HUDGeode->addDrawable(HUDBackgroundGeometry);

	osg::StateSet* HUDStateSet = new osg::StateSet();
	HUDGeode->setStateSet(HUDStateSet);

	HUDStateSet
		->setMode(GL_BLEND, osg::StateAttribute::ON);

	HUDStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	HUDStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	HUDStateSet->setRenderBinDetails(11, "RenderBin");

	HUDGeode->addDrawable(text);
	text->setCharacterSize(25);
	text->setFont("C:/WINDOWS/Fonts/impact.ttf");
	text->setText(_T("ABC"));
	text->setAxisAlignment(osgText::Text::SCREEN);
	text->setPosition(osg::Vec3(360, 165, -1.5));
	text->setColor(osg::Vec4(199, 77, 15, 1));
}