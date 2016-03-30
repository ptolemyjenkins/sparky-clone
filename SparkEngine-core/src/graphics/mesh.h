#pragma once
#include "../ResourceManagment/MeshResource.h"
#include "constructs\vertex.h"
#include "../maths/vec4.h"
#include "../util/meshLoading/meshLoading.h"
#include <unordered_map>
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