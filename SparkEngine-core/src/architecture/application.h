#pragma once
#include "Renderable3D.h"

namespace sparky { 
	class CoreEngine;
	namespace graphics {class RenderingEngine;}
	namespace architecture {
	class Application
	{
	private:
		Renderable3D *root;
	public:
		Application();
		virtual void init();
		void input(float delta);
		void update(float delta);
		Renderable3D* render();
		void addObject(Renderable3D object);
		void addComponent(Renderable3DComponent component);
		CoreEngine* engine = 0;
	private:
		Renderable3D * getRootRenderable3D();

	};
} }