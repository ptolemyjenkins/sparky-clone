#pragma once
#include "layer.h"
#include "structure.h"
#include "components\components.h"
namespace sparky { namespace architecture {
	class Layer2D :public Layer
	{
	public:
		Structure root;
		std::unordered_map<std::string, Structure*> structures;
		std::unordered_map<std::string, components::camera*> cameras;
		std::unordered_map<std::string, components::Sprite*> sprites;
		std::unordered_map<std::string, Component*> miscellaneous;
		std::vector<components::Sprite*> spriteList;
		
		
		Layer2D();
		~Layer2D();
		void addCamera(std::string name, components::camera* camera);
		void addSprite(std::string name, components::Sprite* sprite);
		void addStructure(std::string name);

		void addCamera(std::string name, components::camera* camera, std::string parent);
		void addSprite(std::string name, components::Sprite* sprite, std::string parent);
		void addMisc(std::string name, Component* misc, std::string parent);
		void addStructure(std::string name, std::string parent);

		Structure* getStructure(std::string structure);
		graphics::Transform* getTransform(std::string structure);

		components::camera* getCamera(std::string camera);
		Component* getMisc(std::string misc);

		void input(float delta, graphics::Window* window);
		void update(float delta);
		void updateTransforms();


	};
}}