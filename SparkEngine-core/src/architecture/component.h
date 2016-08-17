#pragma once
#include "../graphics/transform.h"
#include "../graphics/window.h"
namespace sparky { namespace architecture {
	class Structure;
	
	class Component
	{
	protected:
		Structure * parent;
	public:
		Component();
		virtual void input(float delta, graphics::Window* window) {}
		virtual void update(float delta) {}
		graphics::Transform* getTransform();
		void setParent(Structure * parent);
	};
} }