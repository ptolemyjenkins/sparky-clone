#include "Layer3D.h"
namespace sparky {
	namespace architecture {
		sparky::architecture::Layer3D::Layer3D()
		{
			structures["root"] = &root;
		}

		Layer3D::~Layer3D()
		{
			for (auto kv : cameras) {
				delete kv.second;
			}
			for (auto kv : objects) {
				delete kv.second;
			}
			for (auto kv : lights) {
				delete kv.second;
			}
			for (auto kv : miscellaneous) {
				delete kv.second;
			}
			for (auto kv : structures) {
				delete kv.second;
			}
		}

		void Layer3D::addCamera(std::string name, components::camera * camera)
		{
			addCamera(name, camera, "root");
		}

		void Layer3D::addMesh(std::string name, components::MeshRenderer * mesh)
		{
			addMesh(name, mesh, "root");
		}

		void Layer3D::addLight(std::string name, components::baseLight * light)
		{
			addLight(name, light, "root");
		}

		void Layer3D::addStructure(std::string name)
		{
			addStructure(name, "root");
		}

		void Layer3D::addCamera(std::string name, components::camera* camera, std::string parent)
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

		void Layer3D::addMesh(std::string name, components::MeshRenderer* mesh, std::string parent)
		{

			std::unordered_map<std::string, components::MeshRenderer*>::const_iterator got1 = objects.find(name);
			if (got1 != objects.end()) {
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
			objects[name] = mesh;
			meshList.push_back(mesh);
			structure->addComponent(mesh);
		}
		void Layer3D::addLight(std::string name, components::baseLight* light, std::string parent)
		{
			std::unordered_map<std::string, components::baseLight*>::const_iterator got1 = lights.find(name);
			if (got1 != lights.end()) {
				util::Logging::log(("Error >> \"" + name + "\" already in light pool\n"));
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
			lights[name] = light;
			lightList.push_back(light);
			structure->addComponent(light);
		}

		void Layer3D::addMisc(std::string name, Component* misc, std::string parent)
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

		void Layer3D::addStructure(std::string name, std::string parent)
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

		Structure * Layer3D::getStructure(std::string structure)
		{
			std::unordered_map<std::string, Structure*>::const_iterator got = structures.find(structure);
			if (got == structures.end()) {
				util::Logging::log(("Error >> \"" + structure + "\" structure not found\n"));
				return nullptr;
			}
			return got->second;
		}

		graphics::Transform * Layer3D::getTransform(std::string structure)
		{
			std::unordered_map<std::string, Structure*>::const_iterator got = structures.find(structure);
			if (got == structures.end()) {
				util::Logging::log_exit(("Error >> \"" + structure + "\" structure not found"), 1);
				return nullptr;
			}
			return got->second->getTransform();
		}

		components::camera * Layer3D::getCamera(std::string camera)
		{
			std::unordered_map<std::string, components::camera*>::const_iterator got = cameras.find(camera);
			if (got == cameras.end()) {
				util::Logging::log_exit(("Error >> \"" + camera + "\" not found"), 1);
				return nullptr;
			}
			return got->second;
		}

		components::baseLight * Layer3D::getLight(std::string light)
		{
			std::unordered_map<std::string, components::baseLight*>::const_iterator got = lights.find(light);
			if (got == lights.end()) {
				util::Logging::log_exit(("Error >> \"" + light + "\" not found"), 1);
				return nullptr;
			}
			return got->second;
		}

		Component* Layer3D::getMisc(std::string misc)
		{
			std::unordered_map<std::string, Component*>::const_iterator got = miscellaneous.find(misc);
			if (got == miscellaneous.end()) {
				util::Logging::log_exit(("Error >> \"" + misc + "\" not found"), 1);
				return nullptr;
			}
			return got->second;
		}

		void Layer3D::input(float delta, graphics::Window* window)
		{
			root.input(delta, window);
		}
		void Layer3D::update(float delta)
		{
			root.update(delta);
		}
		void Layer3D::updateTransforms()
		{
			root.updateTransforms();
		}
	}
}