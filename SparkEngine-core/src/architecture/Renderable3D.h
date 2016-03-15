#pragma once
#include "renderable3DComponent.h"
#include "components\MeshRenderer.h"

namespace sparky { namespace architecture {
	class Renderable3D
	{
	private:
		CoreEngine *engine = 0;
		std::vector<Renderable3D> children;
		std::vector<Renderable3DComponent*> components;
		graphics::Transform transform;
	public:
		Renderable3D();
		void addChild(Renderable3D* child);
		Renderable3D& addComponent(Renderable3DComponent *component);

		void inputAll(const float& delta);
		void updateAll(const float& delta);
		void renderAll(graphics::Shader &shader, graphics::RenderingEngine &renderingEngine);

		graphics::Transform& getTransform();
		void updateTransforms();

		void setEngine(CoreEngine* engine);
		CoreEngine *  getEngine();

		Renderable3D* getChild(int i);
		Renderable3DComponent* getComponent(int i);
	private:
		void input(const float& delta);
		void update(const float& delta);
		void render(graphics::Shader &shader, graphics::RenderingEngine &renderingEngine);
	};
} }