#include "component3D.h"
#include "Structure3D.h"
#include "application.h"
namespace sparky { namespace architecture {
	Component3D::Component3D()
	{

	}
	graphics::Transform* Component3D::getTransform()
	{
		return parent->getTransform();
	}
	void Component3D::setParent(Structure3D *  parent)
	{
		this->parent = parent;
	}
	
} }