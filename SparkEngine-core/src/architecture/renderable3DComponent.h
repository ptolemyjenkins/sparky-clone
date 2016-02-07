#pragma once
#include "../graphics/constructs/transform.h"
#include "../graphics/shader.h"
namespace sparky { 
	class CoreEngine;
	class RenderingEngine;
	namespace architecture {
	class Renderable3D;

	class Renderable3DComponent
	{
	protected:
		Renderable3D * parent;
	public:
		void input(float delta);
		void update(float delta);
		void render(graphics::Shader shader, RenderingEngine renderingEngine);
		graphics::Transform& getTransform();
		void setParent(Renderable3D * parent);
	private:
		CoreEngine* getEngine();
	};
} }