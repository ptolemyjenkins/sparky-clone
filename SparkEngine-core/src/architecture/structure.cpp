#include "structure.h"
namespace sparky { namespace architecture {
	Structure::Structure()
	{
		children.reserve(5);
		components.reserve(5);
	}

	void Structure::addChild(Structure *child)
	{
		children.push_back(child);
		child->getTransform()->setParent(&transform);
	}

	Structure & Structure::addComponent(Component* component)
	{
		components.push_back(component);
		component->setParent(this);
		return *this;
	}

	void Structure::input(const float & delta, graphics::Window* window)
	{
		int a = children.size();
		for (int i = 0; i < a; i++)
		{
			children[i]->input(delta, window);
		}
		
		for (int i = 0; i < (int)components.size(); i++)
		{
			components.at(i)->input(delta, window);
		}
	}

	void Structure::update(const float & delta)
	{
		for (int i = 0; i < (int) children.size(); i++)
		{
			children[i]->update(delta);
		}

		for (int i = 0; i < (int)components.size(); i++)
		{
			components.at(i)->update(delta);
		}
	}

	graphics::Transform* Structure::getTransform()
	{
		return &transform;
	}

	void Structure::updateTransforms()
	{
		for (int i = 0; i < (int)children.size(); i++)
		{
			children[i]->updateTransforms();
		}
		transform.update();
	}

} }