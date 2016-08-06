#include "structure3D.h"
namespace sparky { namespace architecture {
	Structure3D::Structure3D()
	{
		children.reserve(5);
		components.reserve(5);
	}

	void Structure3D::addChild(Structure3D *child)
	{
		children.push_back(child);
		child->getTransform()->setParent(&transform);
	}

	Structure3D & Structure3D::addComponent(Component3D* component)
	{
		components.push_back(component);
		component->setParent(this);
		return *this;
	}

	void Structure3D::input(const float & delta, graphics::Window* window)
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

	void Structure3D::update(const float & delta)
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

	graphics::Transform* Structure3D::getTransform()
	{
		return &transform;
	}

	void Structure3D::updateTransforms()
	{
		for (int i = 0; i < (int)children.size(); i++)
		{
			children[i]->updateTransforms();
		}
		transform.update();
	}

} }