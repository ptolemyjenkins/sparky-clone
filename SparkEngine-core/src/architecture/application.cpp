#include "application.h"
namespace sparky { namespace architecture {
	Application::Application()
	{
		root = 0;
	}

	void Application::init()
	{
		
	}

	void Application::input(float delta)
	{
		(*getRootRenderable3D()).inputAll(delta);
	}

	void Application::update(float delta)
	{
		(*getRootRenderable3D()).updateAll(delta);
	}

	Renderable3D* Application::render()
	{
		root->updateTransforms();
		return root;
	}

	void Application::addObject(Renderable3D object)
	{
		(*getRootRenderable3D()).addChild(object);
	}

	void Application::addComponent(Renderable3DComponent component)
	{
		getRootRenderable3D()->addComponent(component);
	}

	Renderable3D * Application::getRootRenderable3D()
	{
		if (root == nullptr)
		{
			root = &Renderable3D();
		}
		return root;
	}
} }