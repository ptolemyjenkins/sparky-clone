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
		components::MeshRenderer* renderer2 = new components::MeshRenderer(new graphics::Mesh("skinner1.obj"), material);
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


		architecture::Layer2D* testLayer2D = new architecture::Layer2D;
		
		int x = window->getWidth();
		int y = window->getHeight();
		components::camera* cam2D = new components::camera(0,x,0,y,-1000,1000);
		srand(time(NULL));
		testLayer2D->addCamera("mainCamera2D", cam2D, "camStruct2D");
		for (int i=0; i < 100; i++) {
			for (int j=0; j < 100; j++) {
				testLayer2D->addSprite(std::to_string(i*100+j), new components::Sprite(maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f,1)), std::to_string(i * 100 + j));
				testLayer2D->getTransform(std::to_string(i * 100 + j))->scale.set(5, 5, 1);
				testLayer2D->getTransform(std::to_string(i * 100 + j))->pos.set(i * x/100.0f+10,j* y/100.0f+10,100);
			}
		}
		testLayer2D->visible = true;
		scene.addLayer2D(testLayer2D);

	}

	void DebugScene::update(float delta)
	{
		architecture::Layer3D* layer3D = (scene.getLayer3D(0));
		architecture::Layer2D* layer2D =  (scene.getLayer2D(0));
		layer3D->getTransform("directionalLightStruct")->rotateTrans(maths::quaternion(maths::vec3(0, 1, 0), delta*8));
		srand(time(NULL));
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				layer2D->getTransform(std::to_string(i * 100 + j))->rotateTrans(maths::quaternion(maths::vec3(i/100.0f, j/100, i+j/200), sin(i*j/20) *1000 *  delta));
				layer2D->getTransform(std::to_string(i * 100 + j))->rotateTrans(maths::quaternion(maths::vec3(0, 0, 1), 100 * delta));
				layer2D->getTransform(std::to_string(i * 100 + j))->pos.y += sin((i/16.0)+counter*2)*25;

			}
		}
		counter += delta;
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
