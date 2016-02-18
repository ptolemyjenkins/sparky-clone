#include "renderable3DComponent.h"
#include "Renderable3D.h"
#include "application.h"
#include "../coreEngine.h"
namespace sparky { namespace architecture {
	void Renderable3DComponent::input(float delta)
	{

	}

	void Renderable3DComponent::update(float delta)
	{

	}

	void Renderable3DComponent::render(graphics::Shader shader, graphics::RenderingEngine renderingEngine)
	{

	}

	graphics::Transform & Renderable3DComponent::getTransform()
	{
		return (*parent).getTransform();
	}

	void Renderable3DComponent::setParent(Renderable3D *  parent)
	{
		this->parent = parent;
	}

	CoreEngine * Renderable3DComponent::getEngine()
	{
		Application* app = (*parent).getApplication();
		if (app == 0)
			return nullptr;
		return app->engine;
	}
	
} }