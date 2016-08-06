#pragma once
#include "../../Component3D.h"
#include "../../../graphics/mesh.h"
#include "../../../graphics/material.h"

namespace sparky { namespace components {
	class MeshRenderer : public architecture::Component3D {
	private:
		graphics::Mesh* mesh;
		graphics::Material* material;
	public:
		MeshRenderer(graphics::Mesh * mesh, graphics::Material * material);
		~MeshRenderer();
		graphics::Mesh * getMesh();
		graphics::Material * getMaterial();

	};

} }