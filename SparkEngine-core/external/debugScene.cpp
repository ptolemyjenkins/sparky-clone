#include "debugScene.h"
#include "../libs/stb_image.h"

namespace sparky {
	void DebugScene::init()
	{
		graphics::Material* material = new graphics::Material(new graphics::Texture("Lbrick_COLOUR.png"), 2.0f, 0.1f, new graphics::Texture("Lbrick1_NRM.png"), new graphics::Texture("Lbrick1_DISP.png"),0.04f,-0.5f);
		
		graphics::Mesh* mesh2 = new graphics::Mesh();
		util::BasicMesh::cubeMesh(mesh2);
		components::MeshRenderer* renderer2 = new components::MeshRenderer(mesh2, material);
		architecture::Renderable3D* box2 = new architecture::Renderable3D();
		architecture::Renderable3D* box3 = new architecture::Renderable3D();
		box2->addComponent(renderer2);
		box2->getTransform().pos.set(1, 0, 0);
		box2->getTransform().scale.set(0.1f, 0.1f, 0.1f);
		box3->addChild(box2);
		addObject(box3);

		graphics::Mesh* mesh = new graphics::Mesh("skinner1.obj");
		architecture::Renderable3D* box = new architecture::Renderable3D();
		components::MeshRenderer* renderer = new components::MeshRenderer(mesh, material);
		box->addComponent(renderer);
		box->getTransform().rotateTrans(maths::quaternion(maths::vec3(0, 1, 0), 90));
		addObject(box);

		
		architecture::Renderable3D* directionalLight = new architecture::Renderable3D();
		components::directionalLight* dir = new components::directionalLight(maths::vec4(1, 1, 1, 1), 0.7);
		
		directionalLight->addComponent(dir);
		directionalLight->getTransform().rotateTrans(maths::quaternion(maths::vec3(1, 0, 0), 45));
		
		addObject(directionalLight);

		architecture::Renderable3D* cam = new architecture::Renderable3D();
		cam->addComponent(new components::camera(50,19.0f/12.0f,0.1f,1000));
		cam->getTransform().pos.set(0, 0, -5);
		

		components::freeLook* look = new components::freeLook(0.5f);
		cam->addComponent(look);
		components::freeMove* move = new components::freeMove(10);
		cam->addComponent(move);
		
		addObject(cam);
		
	}

	void DebugScene::update(float delta)
	{
		root.getChild(1)->getTransform().rotateTrans(maths::quaternion(maths::vec3(0, 1, 0).normalised(), 0.5f));
		root.getChild(0)->getChild(0)->getTransform().rotateTrans(maths::quaternion(maths::vec3(0.2, 0, 2).normalised(), 2.0f));
		root.getChild(0)->getTransform().rotateTrans(maths::quaternion(maths::vec3(0, 1, 0).normalised(), 4.0f));
		root.getChild(2)->getTransform().rotateTrans(maths::quaternion(maths::vec3(0.2, 3, 2).normalised(), 0.73421f));
	}
}
