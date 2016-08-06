#include "MeshRenderer.h"
namespace sparky {  namespace components {
	MeshRenderer::MeshRenderer(graphics::Mesh * mesh, graphics::Material * material)
	{
		this->mesh = mesh;
		this->material = material;
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

} }