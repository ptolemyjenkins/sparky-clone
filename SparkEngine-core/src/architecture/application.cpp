#include "application.h"
namespace sparky { namespace architecture {
	Application::Application()
	{
	
	}

	void Application::init()
	{
		
	}

	void Application::input(float delta)
	{
		root.inputAll(delta);
	}

	void Application::update(float delta)
	{
		root.updateTransforms();
		root.updateAll(delta);
	}

	Renderable3D* Application::rootRender()
	{
		return &root;
	}

	void Application::addObject(Renderable3D* object)
	{
		root.addChild(object);
	}

	void Application::addComponent(Renderable3DComponent &component)
	{
		root.addComponent(&component);
	}

	void Application::setEngine(CoreEngine * engine)
	{
		this->engine = engine;
		root.setEngine(engine);
	}

	CoreEngine * Application::getEngine()
	{
		return engine;
	}

} }