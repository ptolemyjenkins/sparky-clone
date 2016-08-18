#include "meshRenderer.h"
namespace sparky {
	namespace components {
		MeshRenderer::MeshRenderer(graphics::Mesh * mesh, graphics::Material * material)
		{
			this->mesh = mesh;
			this->material = material;
		}

		MeshRenderer::MeshRenderer(std::vector<graphics::Texture*>* textureList)
		{
			this->mesh = new graphics::Mesh();
			this->material = new graphics::Material(textureList);
		}

		MeshRenderer::~MeshRenderer()
		{

		}

		graphics::Mesh * MeshRenderer::getMesh() {
			return mesh;
		}

		graphics::Material * MeshRenderer::getMaterial()
		{
			return material;
		}

	}
}