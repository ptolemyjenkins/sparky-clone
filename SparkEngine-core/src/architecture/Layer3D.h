#pragma once
#include "layer.h"
#include "structure3D.h"
#include "components\components.h"
namespace sparky { namespace architecture {
	class Layer3D :public Layer
	{
	public:
		Structure3D root;
		std::unordered_map<std::string,Structure3D*> structures;
		std::unordered_map<std::string, components::camera*> cameras;
		std::unordered_map<std::string, components::MeshRenderer*> objects;
		std::unordered_map<std::string, components::baseLight*> lights;
		std::unordered_map<std::string, Component3D*> miscellaneous;


	public:
		Layer3D();
		~Layer3D();
		void addCamera(std::string name, components::camera* camera);
		void addMesh(std::string name, components::MeshRenderer* mesh);
		void addLight(std::string name, components::baseLight* light);
		void addStructure(std::string name);

		void addCamera(std::string name, components::camera* camera, std::string parent);
		void addMesh(std::string name, components::MeshRenderer* mesh, std::string parent);
		void addLight(std::string name, components::baseLight* light, std::string parent);
		void addMisc(std::string name, Component3D* misc, std::string parent);
		void addStructure(std::string name, std::string parent);

		graphics::Transform* getTransform(std::string structure);

		void input(float delta, graphics::Window* window);
		void update(float delta);
		void updateTransforms();

	};
} }