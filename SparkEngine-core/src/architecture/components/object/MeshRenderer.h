#pragma once
#include "../../Component.h"
#include "../../../graphics/mesh.h"
#include "../../../graphics/material.h"

namespace sparky {
	namespace components {
		class MeshRenderer : public architecture::Component {
		private:
			graphics::Mesh* mesh;
			graphics::Material* material;
		public:
			MeshRenderer(graphics::Mesh * mesh, graphics::Material * material);
			MeshRenderer();
			~MeshRenderer();
			graphics::Mesh * getMesh();
			graphics::Material * getMaterial();

		};

	}
}