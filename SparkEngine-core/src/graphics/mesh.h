#pragma once
#include "../ResourceManagment/MeshResource.h"
#include "constructs\vertex.h"
#include "../maths/vec4.h"
#include <fstream>
#include <sstream>
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
		Mesh(Vertex vertices[], int vertSize, int indices[], int intSize);
		Mesh(Vertex vertices[], int vertSize, int indices[], int intSize, bool calcNormal);
		~Mesh();
	private:
		float* toBuffer(Vertex vertices[], int vertSize);
		void addVertices(Vertex vertices[], int vertSize, int indices[], int intSize, bool calcNormal);
		void calcNormals(Vertex vertices[], int vertSize, int indices[], int intSize);
		void loadMesh(std::string filename);
	public:
		void draw();
		void calcTangents(Vertex vertices[], int vertSize, int indices[], int intSize);
		
	};
} }