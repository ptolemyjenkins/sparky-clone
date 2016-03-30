#pragma once
#include "../../graphics/mesh.h"
namespace sparky {	namespace util {
	class BasicMesh {
	public:
		static void planeMesh(graphics::Mesh* mesh);
		static void plane2Mesh(graphics::Mesh* mesh);
		static void cubeMesh(graphics::Mesh* mesh);
		static void cube2Mesh(graphics::Mesh* mesh);
		static void cubeApproxMesh(graphics::Mesh* mesh);

	};
} }