#pragma once
#include "layer3D.h"
#include "layer2D.h"

namespace sparky { namespace architecture {
	class LayerStack : Layer
	{
	public:
		std::vector<Layer3D*> layers3D;
		std::vector<Layer2D*> layers2D;
	public:
		LayerStack();
		void input(float delta, graphics::Window* window);
		void update(float delta);
		void render(graphics::RenderingEngine* renderingEngine);
		void render3D(graphics::RenderingEngine * renderingEngine);
		void render2D(graphics::RenderingEngine* renderingEngine);
		void updateTransforms();

		Layer3D* getLayer3D(int i);
		Layer2D* getLayer2D(int i);

		void addLayer3D(Layer3D * layer3D);
		void addLayer3D(Layer3D * layer3D, int pos);

		void addLayer2D(Layer2D * layer2D);
		void addLayer2D(Layer2D * layer2D, int pos);
	};
} }