#include "MeshRenderer.h"
#include "../../graphics/renderingEngine.h"
namespace sparky {  namespace components {
	MeshRenderer::MeshRenderer(graphics::Mesh * mesh, graphics::Material * material)
	{
		this->mesh = mesh;
		this->material = material;
	}

	MeshRenderer::~MeshRenderer()
	{
		std::cout << "delete mesh rend" << std::endl;
		delete mesh;
		delete material;
	}

	void MeshRenderer::render(graphics::Shader &shader, graphics::RenderingEngine &renderingEngine)
	{

		shader.bind();
		shader.updateUniforms(getTransform(), *material, renderingEngine);
		mesh->draw();
	}

	void MeshRenderer::addToEngine(CoreEngine * engine)
	{

	}

	
} }