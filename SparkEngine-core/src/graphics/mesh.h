#pragma once
#include "../ResourceManagment/MeshResource.h"
#include "constructs\vertex.h"
#include "../util/meshLoading/meshLoading.h"
namespace sparky { namespace graphics {
	class Mesh {
	private:
		static std::unordered_map<std::string, resource::MeshResource> loadedModels;
		resource::MeshResource * resource;
		std::string fileName;
	public:
		Mesh();
		Mesh(const std::string& fileName);
		~Mesh();
	private:
		void uploadModel(util::IndexedModel* model);
		void loadMesh(std::string filename);
	public:
		void init(util::IndexedModel* model);
		void draw();
	};
} }