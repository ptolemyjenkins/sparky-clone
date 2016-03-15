#pragma once
#include "Renderable3D.h"

namespace sparky { namespace architecture {
	class Application
	{
	public:
		Renderable3D root;
		CoreEngine* engine = 0;
	public:
		Application();
		virtual void init();
		virtual void input(float delta);
		virtual void update(float delta);
		Renderable3D* rootRender();
		void addObject(Renderable3D* object);
		void addComponent(Renderable3DComponent &component);
		void setEngine(CoreEngine* engine);
		CoreEngine* getEngine();
	};
} }