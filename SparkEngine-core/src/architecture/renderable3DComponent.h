#pragma once
#include "../graphics/shader.h"
namespace sparky { 
	class CoreEngine;
	namespace graphics {
		class RenderingEngine;
	}
	
	namespace architecture {
	class Renderable3D;
	class Application;

	class Renderable3DComponent
	{
	protected:
		Renderable3D * parent;
	public:
		virtual void input(float delta) {}
		virtual void update(float delta) {}
		virtual void render(graphics::Shader &shader, graphics::RenderingEngine &renderingEngine) {}
		graphics::Transform& getTransform();
		void setParent(Renderable3D * parent);
		CoreEngine* getEngine();
		virtual void addToEngine(CoreEngine* engine);
	};
} }