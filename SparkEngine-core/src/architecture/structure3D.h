#pragma once
#include <vector>
#include "component3D.h"


namespace sparky { namespace architecture {
	class Structure3D
	{
	private:
		std::vector<Structure3D*> children;
		std::vector<Component3D*> components;
		graphics::Transform transform;
	public:
		Structure3D();
		void addChild(Structure3D* child);
		Structure3D& addComponent(Component3D *component);

		void input(const float& delta, graphics::Window* window);
		void update(const float& delta);

		graphics::Transform* getTransform();
		void updateTransforms();

	};
} }