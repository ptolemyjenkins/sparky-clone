#include "debugScene.h"
#include "../libs/stb_image.h"

namespace sparky {
	void DebugScene::init()
	{
		renderingEngine->setClearColour(maths::vec4(0.05, 0.1, 0.2, 0));

		graphics::Material* material = new graphics::Material(new graphics::Texture("Lbrick_COLOUR.png"), 2.0f, 0.1f, new graphics::Texture("Lbrick1_NRM.png"), new graphics::Texture("Lbrick1_DISP.png"),0.04f,-0.5f);
		graphics::Material* material1 = new graphics::Material();

		architecture::Layer3D* testLayer3D = new architecture::Layer3D;
		
		testLayer3D->addStructure("box1Struct");
		graphics::Mesh* mesh1 = new graphics::Mesh();
		util::BasicMesh::cubeMesh(mesh1);
		components::MeshRenderer* renderer1 = new components::MeshRenderer(mesh1, material1);
		testLayer3D->addMesh("box", renderer1,"box1Struct");

		testLayer3D->addStructure("skinnerStruct");
		components::MeshRenderer* renderer2 = new components::MeshRenderer(new graphics::Mesh("skinner1.obj"), material);
		testLayer3D->addMesh("skinner", renderer2, "skinnerStruct");
		
		testLayer3D->getTransform("skinnerStruct")->rotateTrans(maths::quaternion(maths::vec3(0, 1, 0), 90));
		testLayer3D->getTransform("skinnerStruct")->pos.set(0, 0, 5);
		testLayer3D->getTransform("skinnerStruct")->scale.set(2, 2, 2);

		components::baseLight* amb = new components::baseLight(maths::vec4(1, 1, 1, 1), 0.005);
		testLayer3D->addLight("ambient", amb);

		testLayer3D->addStructure("directionalLightStruct");
		components::directionalLight* dir = new components::directionalLight(maths::vec4(1, 1, 1, 1), 0.7);
		testLayer3D->getTransform("directionalLightStruct")->rotateTrans(maths::quaternion(maths::vec3(1, 0, 0), 45));
		testLayer3D->addLight("directionalLight", dir, "directionalLightStruct");


		components::freeLook* look = new components::freeLook(0.5f);
		components::freeMove* move = new components::freeMove(10);

		testLayer3D->addStructure("camStruct");
		components::camera* cam = new components::camera(50, 19.0f / 12.0f, 0.1f, 1000);
		testLayer3D->addCamera("mainCamera", cam, "camStruct");
		testLayer3D->addMisc("look", look, "camStruct");
		testLayer3D->addMisc("move", move, "camStruct");
		testLayer3D->getTransform("camStruct")->pos.set(0, 0, -5);
		components::pointLight* poi = new components::pointLight(maths::vec4(0.8, 0.2, 0.9, 1), 2,graphics::Attenuation(1,1,0.1));
		testLayer3D->addLight("pointLight", poi, "camStruct");

		scene.layers.push_back(testLayer3D);
	}

	void DebugScene::update(float delta)
	{
		architecture::Layer3D* layer = static_cast<architecture::Layer3D*> (scene.getLayer(0));
		layer->getTransform("skinnerStruct")->rotateTrans(maths::quaternion(maths::vec3(0, 1, 0), 0.05));
	}
	
}
