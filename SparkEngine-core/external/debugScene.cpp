#include "debugScene.h"
#include "../libs/stb_image.h"

namespace sparky {
	void DebugScene::init(graphics::Window* window)
	{
		renderingEngine->setClearColour(maths::vec4(0.05, 0.1, 0.2, 0));

		graphics::Material* material = new graphics::Material(new graphics::Texture("Lbrick_COLOUR.png"), 2.0f, 0.1f, new graphics::Texture("Lbrick1_NRM.png"), new graphics::Texture("Lbrick1_DISP.png"),0.04f,-0.5f);
		graphics::Material* material1 = new graphics::Material();

		architecture::Layer3D* testLayer3D = new architecture::Layer3D;
		
		graphics::Mesh* mesh1 = new graphics::Mesh();
		util::BasicMesh::cubeMesh(mesh1);
		components::MeshRenderer* renderer1 = new components::MeshRenderer(mesh1, material1);
		components::MeshRenderer* renderer2 = new components::MeshRenderer(mesh1 /*new graphics::Mesh("skinner1.obj")*/, material);
		testLayer3D->addStructure("base");
		testLayer3D->addStructure("box1Struct", "base");
		testLayer3D->addStructure("skinnerStruct", "base");

		testLayer3D->addMesh("skinner", renderer2, "skinnerStruct");
		testLayer3D->addMesh("box", renderer1,"box1Struct");
		
		testLayer3D->getTransform("box1Struct")->pos.set(2, 0, 0);
		testLayer3D->getTransform("box1Struct")->scale.set(0.5, 0.5, 0.5);

		testLayer3D->getTransform("base")->rotateTrans(maths::quaternion(maths::vec3(0, 1, 0), 90));
		testLayer3D->getTransform("base")->pos.set(0, 0, 5);
		testLayer3D->getTransform("base")->scale.set(2, 2, 2);

		components::baseLight* amb = new components::baseLight(maths::vec4(1, 1, 1, 1), 0.005);
		testLayer3D->addLight("ambient", amb);

		components::directionalLight* dir = new components::directionalLight(maths::vec4(1, 1, 1, 1), 0.7);
		testLayer3D->addLight("directionalLight", dir, "directionalLightStruct");
		testLayer3D->getTransform("directionalLightStruct")->rotateTrans(maths::quaternion(maths::vec3(1, 0, 0), 45));


		components::freeLook* look = new components::freeLook(0.5f);
		components::freeMove* move = new components::freeMove(10);

		components::camera* cam = new components::camera(50, 19.0f / 12.0f, 0.1f, 1000);
		testLayer3D->addCamera("mainCamera", cam, "camStruct");
		testLayer3D->addMisc("look", look, "camStruct");
		testLayer3D->addMisc("move", move, "camStruct");
		testLayer3D->getTransform("camStruct")->pos.set(0, 0, -5);
		components::pointLight* poi = new components::pointLight(maths::vec4(0.8, 0.2, 0.9, 1), 2, graphics::Attenuation(1,1,0.1));
		testLayer3D->addLight("pointLight", poi, "camStruct");
		testLayer3D->visible = false;
		scene.addLayer3D(testLayer3D);

		float x = window->getWidth();
		float y = window->getHeight();

		architecture::Layer2D* testLayer2D = new architecture::Layer2D;
		components::camera* cam2D = new components::camera(-5, 5, -5 * y / x, 5 * y / x, -1, 1);
		testLayer2D->addCamera("mainCamera2D", cam2D, "camStruct2D");
		testLayer2D->addSprite("test", new components::Sprite(maths::vec4(1,1,1,1), maths::vec4(0,1,1,0),2), "spriteStruct");
		testLayer2D->addSprite("test2", new components::Sprite(maths::vec4(1, 1, 1, 1), maths::vec4(0, 1, 1, 0), 1), "spriteStruct2");
		testLayer2D->getStructure("spriteStruct2")->getTransform()->pos.set(0, -2, 0);
		testLayer2D->addTexture(1,new graphics::Texture("Debug.png"));
		testLayer2D->addTexture(2, new graphics::Texture("American_Typewriter.png"));

		testLayer2D->visible = true;
		scene.addLayer2D(testLayer2D);

	}

	void DebugScene::update(float delta)
	{
		architecture::Layer3D* layer3D = (scene.getLayer3D(0));
		architecture::Layer2D* layer2D =  (scene.getLayer2D(0));
		layer3D->getTransform("directionalLightStruct")->rotateTrans(maths::quaternion(maths::vec3(0, 1, 0), delta*8));
	}

	void DebugScene::input(float delta, graphics::Window * window)
	{
		Application::input(delta, window);
		if (window->isKeyDown(GLFW_KEY_ESCAPE) && window->isKeyDown(GLFW_KEY_LEFT_SHIFT))
			window->close();
		
		architecture::Layer3D* layer = static_cast<architecture::Layer3D*> (scene.getLayer3D(0));
		if (window->isKeyPressed(GLFW_KEY_L)) {
			layer->visible = !layer->visible;
		}
		if (window->isKeyPressed(GLFW_KEY_P)) {
			layer->getCamera("mainCamera")->printState();
		}
	}
	
}
