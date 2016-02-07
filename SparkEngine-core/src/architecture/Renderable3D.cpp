#include "Renderable3D.h"
#include "application.h"
namespace sparky { namespace architecture {
	Renderable3D::Renderable3D()
	{
		children.reserve(5);
		components.reserve(5);

	}

	void Renderable3D::addChild(Renderable3D child)
	{
		children.push_back(child);
		child.getTransform().setParent(&transform);
		child.setApplication(application);
	}

	Renderable3D & Renderable3D::addComponent(Renderable3DComponent component)
	{
		components.push_back(component);
		component.setParent(this);
		return *this;
	}

	void Renderable3D::inputAll(const float & delta)
	{
		for (int i = 0; i < (int) children.size(); i++)
		{
			children.at(i).inputAll(delta);
		}
		input(delta);
	}

	void Renderable3D::updateAll(const float & delta)
	{
		for (int i = 0; i < (int) children.size(); i++)
		{
			children.at(i).updateAll(delta);
		}
		update(delta);
	}

	graphics::Transform & Renderable3D::getTransform()
	{
		return transform;
	}

	void Renderable3D::updateTransforms()
	{
		for (int i = 0; i < (int)children.size(); i++)
		{
			children.at(i).updateTransforms();
		}
		transform.update();
	}

	void Renderable3D::setApplication(Application* app)
	{
		application = app;
		for (int i = 0; i < (int)children.size(); i++)
		{
			children.at(i).setApplication(app);
		}
	}

	Application * Renderable3D::getApplication()
	{
		return application;
	}

	void Renderable3D::input(const float & delta)
	{
		for (int i = 0; i < (int)components.size(); i++)
		{
			components.at(i).input(delta);
		}

	}

	void Renderable3D::update(const float & delta)
	{
		for (int i = 0; i < (int)components.size(); i++)
		{
			components.at(i).update(delta);
		}
	}

	

} }