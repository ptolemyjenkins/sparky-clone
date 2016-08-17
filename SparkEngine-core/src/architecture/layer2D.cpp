#include "Layer2D.h"
namespace sparky {
	namespace architecture {
		sparky::architecture::Layer2D::Layer2D()
		{
			structures["root"] = &root;
			components::Light2D* light2D = new components::Light2D(maths::vec4(1, 1, 1, 0), 1);
			root.addComponent(light2D);
			lightList.push_back(light2D);

			components::MeshRenderer* mesh = new components::MeshRenderer();
			mesh->getMesh()->initSpriteSheet();
			root.addComponent(mesh);
			meshList.push_back(mesh);
		}

		Layer2D::~Layer2D()
		{
			for (auto kv : cameras) {
				delete kv.second;
			}
			for (auto kv : sprites) {
				delete kv.second;
			}
			for (auto kv : miscellaneous) {
				delete kv.second;
			}
			for (auto kv : structures) {
				delete kv.second;
			}
		}

		void Layer2D::addCamera(std::string name, components::camera * camera)
		{
			addCamera(name, camera, "root");
		}

		void Layer2D::addSprite(std::string name, components::Sprite * mesh)
		{
			addSprite(name, mesh, "root");
		}

		void Layer2D::addStructure(std::string name)
		{
			addStructure(name, "root");
		}

		void Layer2D::addCamera(std::string name, components::camera* camera, std::string parent)
		{
			std::unordered_map<std::string, components::camera*>::const_iterator got1 = cameras.find(name);
			if (got1 != cameras.end()) {
				util::Logging::log(("Error >> \"" + name + "\" already in camera pool\n"));
				return;
			}
			Structure* structure;
			std::unordered_map<std::string, Structure*>::const_iterator got = structures.find(parent);
			if (got == structures.end()) {
				addStructure(parent);
				structure = getStructure(parent);
			}
			else {
				structure = got->second;
			}
			cameras[name] = camera;
			activeCamera = camera;
			structure->addComponent(camera);
		}

		void Layer2D::addSprite(std::string name, components::Sprite* sprite, std::string parent)
		{

			std::unordered_map<std::string, components::Sprite*>::const_iterator got1 = sprites.find(name);
			if (got1 != sprites.end()) {
				util::Logging::log(("Error >> \"" + name + "\" already in object pool\n"));
				return;
			}
			Structure* structure;
			std::unordered_map<std::string, Structure*>::const_iterator got = structures.find(parent);
			if (got == structures.end()) {
				addStructure(parent);
				structure = getStructure(parent);
			}
			else {
				structure = got->second;
			}
			sprites[name] = sprite;
			spriteList.push_back(sprite);
			structure->addComponent(sprite);
		}


		void Layer2D::addMisc(std::string name, Component* misc, std::string parent)
		{

			std::unordered_map<std::string, Component*>::const_iterator got1 = miscellaneous.find(name);
			if (got1 != miscellaneous.end()) {
				util::Logging::log(("Error >> \"" + name + "\" already in misc pool\n"));
				return;
			}
			Structure* structure;
			std::unordered_map<std::string, Structure*>::const_iterator got = structures.find(parent);
			if (got == structures.end()) {
				addStructure(parent);
				structure = getStructure(parent);
			}
			else {
				structure = got->second;
			}
			miscellaneous[name] = misc;
			structure->addComponent(misc);
		}

		void Layer2D::addStructure(std::string name, std::string parent)
		{

			std::unordered_map<std::string, Structure*>::const_iterator got1 = structures.find(name);
			if (got1 != structures.end()) {
				util::Logging::log(("Error >> \"" + name + "\" already in structure tree\n"));
				return;
			}
			Structure* structure;
			std::unordered_map<std::string, Structure*>::const_iterator got = structures.find(parent);
			if (got == structures.end()) {
				addStructure(parent);
				structure = getStructure(parent);
			}
			else {
				structure = got->second;
			}
			Structure* newStructure = new Structure();
			structures[name] = newStructure;
			structure->addChild(newStructure);
		}

		Structure * Layer2D::getStructure(std::string structure)
		{
			std::unordered_map<std::string, Structure*>::const_iterator got = structures.find(structure);
			if (got == structures.end()) {
				util::Logging::log(("Error >> \"" + structure + "\" structure not found\n"));
				return nullptr;
			}
			return got->second;
		}

		graphics::Transform * Layer2D::getTransform(std::string structure)
		{
			std::unordered_map<std::string, Structure*>::const_iterator got = structures.find(structure);
			if (got == structures.end()) {
				util::Logging::log_exit(("Error >> \"" + structure + "\" structure not found"), 1);
				return nullptr;
			}
			return got->second->getTransform();
		}

		components::camera * Layer2D::getCamera(std::string camera)
		{
			std::unordered_map<std::string, components::camera*>::const_iterator got = cameras.find(camera);
			if (got == cameras.end()) {
				util::Logging::log_exit(("Error >> \"" + camera + "\" not found"), 1);
				return nullptr;
			}
			return got->second;
		}

		Component* Layer2D::getMisc(std::string misc)
		{
			std::unordered_map<std::string, Component*>::const_iterator got = miscellaneous.find(misc);
			if (got == miscellaneous.end()) {
				util::Logging::log_exit(("Error >> \"" + misc + "\" not found"), 1);
				return nullptr;
			}
			return got->second;
		}

		void Layer2D::input(float delta, graphics::Window* window)
		{
			root.input(delta, window);
		}
		void Layer2D::update(float delta)
		{
			root.update(delta);
		}
		void Layer2D::updateTransforms()
		{
			root.updateTransforms();
		}
	}
}