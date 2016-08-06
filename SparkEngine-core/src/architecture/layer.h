#pragma once
#include "../graphics/shader.h"
#include "components\object\MeshRenderer.h"

namespace sparky { namespace architecture {
		class Layer
		{
		public:
			bool visible = 0;
			std::vector<components::baseLight*> lightList;
			std::vector<components::MeshRenderer*> meshList;
			components::camera* activeCamera;
		public:
			Layer() {};
			virtual void update(float delta) {};
			virtual void updateTransforms() {};
			virtual void input(float delta, graphics::Window* window) {};
			void setActiveCamera(components::camera* cam) {
				activeCamera = cam;
			}
		};
} }