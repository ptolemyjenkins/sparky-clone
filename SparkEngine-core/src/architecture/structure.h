#pragma once
#include <vector>
#include "component.h"


namespace sparky { namespace architecture {
	class Structure
	{
	private:
		std::vector<Structure*> children;
		std::vector<Component*> components;
		graphics::Transform transform;
	public:
		Structure();
		void addChild(Structure* child);
		Structure& addComponent(Component *component);

		void input(const float& delta, graphics::Window* window);
		void update(const float& delta);

		graphics::Transform* getTransform();
		void updateTransforms();

	};
} }