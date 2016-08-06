#include "layerStack.h"
#include "../graphics/renderingEngine.h"

namespace sparky { namespace architecture {
	sparky::architecture::LayerStack::LayerStack()
	{

	}
	void LayerStack::input(float delta, graphics::Window* window)
	{
		for (Layer* layer : layers) {
			layer->input(delta, window);
		}
	}
	void LayerStack::update(float delta)
	{
		for (Layer* layer : layers) {
			layer->update(delta);
		}
	}
	void LayerStack::render(graphics::RenderingEngine* renderingEngine)
	{
		for (Layer* layer : layers) {
			
			for (components::baseLight* light : layer->lightList) {
				graphics::Shader* shader = light->getShader();
				shader->bind();
				for (components::MeshRenderer* object : layer->meshList) {
					shader->updateUniforms(object->getTransform(), object->getMaterial(), renderingEngine, layer->activeCamera, light);
					object->getMesh()->draw();
				}
				shader->disable();
				renderingEngine->forwardBlendOn();
			}
			renderingEngine->forwardBlendOff();
		}
	}

	void LayerStack::updateTransforms()
	{
		for (Layer* layer : layers) {
			layer->updateTransforms();
		}
	}
	Layer * LayerStack::getLayer(int i)
	{
		return layers[i];
	}
} }