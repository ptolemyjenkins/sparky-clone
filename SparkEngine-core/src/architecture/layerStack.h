#pragma once
#include "layer.h"

namespace sparky { namespace architecture {
	class LayerStack : Layer
	{
	public:
		std::vector<Layer*> layers;
	public:
		LayerStack();
		void input(float delta, graphics::Window* window);
		void update(float delta);
		void render(graphics::RenderingEngine* renderingEngine);
		void updateTransforms();

		Layer* getLayer(int i);
	};
} }