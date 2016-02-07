#pragma once
#include "../renderable3DComponent.h"
#include "../../graphics/mesh.h"
#include "../../graphics/material.h"

namespace sparky { namespace components {
	class MeshRenderer : public architecture::Renderable3DComponent {
	private:
		graphics::Mesh* mesh;
		graphics::Material* material;
	public:
		MeshRenderer(graphics::Mesh * mesh, graphics::Material * material);
		//void render(graphics::Shader shader, RenderingEngine renderingEngine);
	};

} }