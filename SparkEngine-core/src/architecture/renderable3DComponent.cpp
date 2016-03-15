#include "renderable3DComponent.h"
#include "Renderable3D.h"
#include "application.h"
#include "../coreEngine.h"
namespace sparky { namespace architecture {

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
		return (*parent).getEngine();
	}
	void Renderable3DComponent::addToEngine(CoreEngine * engine)
	{

	}
} }