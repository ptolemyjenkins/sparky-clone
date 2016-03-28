#include "debugScene.h"
#include "../libs/stb_image.h"

namespace sparky {
	void DebugScene::init()
	{
		graphics::Material* material = new graphics::Material(new graphics::Texture("Dbrick_COLOUR.png"), 1.0f, 0.1f);
		graphics::Mesh* mesh = new graphics::Mesh("cube.obj");

		architecture::Renderable3D* box = new architecture::Renderable3D();
		components::MeshRenderer* renderer = new components::MeshRenderer(mesh, material);
		box->addComponent(renderer);
		box->getTransform().pos.set(0, 0, 0);
		box->getTransform().rotateTrans(maths::quaternion(maths::vec3(0, 1, 0), 0));
		addObject(box);

		architecture::Renderable3D* cam = new architecture::Renderable3D();
		cam->addComponent(new components::camera(50,19.0f/12.0f,0.1f,1000));
		cam->getTransform().pos.set(0, 0, -10);
		

		components::freeLook* look = new components::freeLook(0.7f);
		cam->addComponent(look);
		components::freeMove* move = new components::freeMove(10);
		cam->addComponent(move);
		addObject(cam);
		
	}

	void DebugScene::update(float delta)
	{
		architecture::Renderable3D* box = root.getChild(0);
		box->getTransform().rotateTrans(maths::quaternion(maths::vec3(0.2, 1, 0).normalised(), 0.5));
		box->getTransform().rotateTrans(maths::quaternion(maths::vec3(0.2, 0, 2).normalised(), 0.1));

	}
}
