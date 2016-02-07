#pragma once
#include "renderable3DComponent.h"

namespace sparky { namespace architecture {
	class Application;
	class RendingEngine;
	class Renderable3D
	{
	private:
		Application *application = 0;
		std::vector<Renderable3D> children;
		std::vector<Renderable3DComponent> components;
		graphics::Transform transform;
	public:
		Renderable3D();
		void addChild(Renderable3D child);
		Renderable3D& addComponent(Renderable3DComponent component);
		void inputAll(const float& delta);
		void updateAll(const float& delta);
		void renderAll(graphics::Shader shader, RenderingEngine renderingEngine);
		graphics::Transform& getTransform();
		void updateTransforms();
		void setApplication(Application* app);
		Application *  getApplication();
	private:
		void input(const float& delta);
		void update(const float& delta);
		void render(graphics::Shader shader, RenderingEngine renderingEngine);
	};
} }