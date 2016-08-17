#include "application.h"
namespace sparky { namespace architecture {
	Application::Application()
	{
	
	}

	void Application::init(graphics::Window* window)
	{
		
	}

	void Application::input(float delta, graphics::Window* window)
	{
		scene.input(delta, window);
	}

	void Application::update(float delta)
	{
		scene.updateTransforms();
		scene.update(delta);
	}

	void Application::setRenderingEngine(graphics::RenderingEngine * renderingEngine)
	{
		this->renderingEngine = renderingEngine;
		renderingEngine->setScene(&scene);
	}

} }