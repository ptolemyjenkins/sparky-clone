#pragma once
#include "../graphics/renderingEngine.h"

namespace sparky { namespace architecture {
	class Application
	{
	public:
		LayerStack scene;
		graphics::RenderingEngine * renderingEngine;
	public:
		Application();
		virtual void init();
		virtual void input(float delta, graphics::Window* window);
		virtual void update(float delta);
		
		void setRenderingEngine(graphics::RenderingEngine * renderingEngine);
	};
} }