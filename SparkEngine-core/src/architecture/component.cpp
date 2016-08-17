#include "component.h"
#include "Structure.h"
#include "application.h"
namespace sparky { namespace architecture {
	Component::Component()
	{

	}
	graphics::Transform* Component::getTransform()
	{
		return parent->getTransform();
	}
	void Component::setParent(Structure *  parent)
	{
		this->parent = parent;
	}
	
} }