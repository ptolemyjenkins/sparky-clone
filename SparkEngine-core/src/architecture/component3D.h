#pragma once
#include "../graphics/constructs/transform.h"
#include "../graphics/window.h"
namespace sparky { namespace architecture {
	class Structure3D;
	
	class Component3D
	{
	protected:
		Structure3D * parent;
	public:
		Component3D();
		virtual void input(float delta, graphics::Window* window) {}
		virtual void update(float delta) {}
		graphics::Transform* getTransform();
		void setParent(Structure3D * parent);
	};
} }