#include "Renderable3D.h"
#include "application.h"
#include "../graphics/renderingEngine.h"
namespace sparky { namespace architecture {
	Renderable3D::Renderable3D()
	{
		children.reserve(5);
		components.reserve(5);
	}

	void Renderable3D::addChild(Renderable3D *child)
	{
		children.push_back(child);
		child->getTransform().setParent(&transform);
		child->setEngine(engine);
	}

	Renderable3D & Renderable3D::addComponent(Renderable3DComponent* component)
	{
		components.push_back(component);
		component->setParent(this);
		return *this;
	}

	void Renderable3D::inputAll(const float & delta)
	{
		int a = children.size();
		for (int i = 0; i < a; i++)
		{
			children[i]->inputAll(delta);
		}
		input(delta);
	}

	void Renderable3D::updateAll(const float & delta)
	{
		for (int i = 0; i < (int) children.size(); i++)
		{
			children[i]->updateAll(delta);
		}
		update(delta);
	}

	void Renderable3D::renderAll(graphics::Shader &shader, graphics::RenderingEngine &renderingEngine)
	{
		for (int i = 0; i < (int)children.size(); i++)
		{
			children[i]->renderAll(shader, renderingEngine);
		}
		render(shader, renderingEngine);
	}

	graphics::Transform & Renderable3D::getTransform()
	{
		return transform;
	}

	void Renderable3D::updateTransforms()
	{
		for (int i = 0; i < (int)children.size(); i++)
		{
			children[i]->updateTransforms();
		}
		transform.update();
	}

	void Renderable3D::setEngine(CoreEngine* engine)
	{
		this->engine = engine;
		for (int i = 0; i < (int)children.size(); i++)
		{
			children[i]->setEngine(engine);
		}
		for (int i = 0; i < (int)components.size(); i++)
		{
			components.at(i)->addToEngine(engine);
		}
	}

	CoreEngine * Renderable3D::getEngine()
	{
		return engine;
	}

	Renderable3D * Renderable3D::getChild(int i)
	{
		return children[i];
	}

	Renderable3DComponent * Renderable3D::getComponent(int i)
	{
		return components[i];
	}

	void Renderable3D::input(const float & delta)
	{
		for (int i = 0; i < (int)components.size(); i++)
		{
			components.at(i)->input(delta);
		}

	}

	void Renderable3D::update(const float & delta)
	{
		for (int i = 0; i < (int)components.size(); i++)
		{
			components.at(i)->update(delta);
		}
	}

	void Renderable3D::render(graphics::Shader &shader, graphics::RenderingEngine &renderingEngine)
	{
		for (int i = 0; i < (int)components.size(); i++)
		{
			
			components[i]->render(shader,renderingEngine);
		}
	}

	

} }