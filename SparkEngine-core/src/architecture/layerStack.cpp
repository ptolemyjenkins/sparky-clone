#include "layerStack.h"
#include "../graphics/renderingEngine.h"

namespace sparky { namespace architecture {
	sparky::architecture::LayerStack::LayerStack()
	{

	}
	void LayerStack::input(float delta, graphics::Window* window)
	{
		for (Layer3D* layer : layers3D) {
			if (layer->visible) {
				layer->input(delta, window);
			}
		}
		for (Layer2D* layer : layers2D) {
			if (layer->visible) {
				layer->input(delta, window);
			}
		}
	}
	void LayerStack::update(float delta)
	{
		for (Layer3D* layer : layers3D) {
			if (layer->visible) {
				layer->update(delta);
			}
		}
		for (Layer2D* layer : layers2D) {
			if (layer->visible) {
				layer->update(delta);
			}
		}
	}
	void LayerStack::render(graphics::RenderingEngine* renderingEngine)
	{
		render2D(renderingEngine);
		render3D(renderingEngine);

	}
	void LayerStack::render3D(graphics::RenderingEngine* renderingEngine) {
		for (Layer3D* layer : layers3D) {
			if (layer->visible) {
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
	}

	void LayerStack::render2D(graphics::RenderingEngine* renderingEngine) {
		glDisable(GL_CULL_FACE);
		for (Layer2D* layer : layers2D) {
			if (layer->visible) {
				components::baseLight* light = layer->lightList[0];
				light->getShader()->bind();
				graphics::Mesh* mesh = layer->meshList[0]->getMesh();
				mesh->beginSprite();
				for (components::Sprite* sprite : layer->spriteList)
				{
					mesh->submitSprite(sprite->getTransform(), sprite->getColor(), maths::vec2(0, 0), maths::vec2(0, 0));
				}
				mesh->endSprite();
				light->getShader()->updateUniforms(layer->meshList[0]->getTransform(), layer->meshList[0]->getMaterial(), renderingEngine, layer->activeCamera, light);
				mesh->drawSprites();
				light->getShader()->disable();
			}
		}
		glEnable(GL_CULL_FACE);
	}

	void LayerStack::updateTransforms()
	{
		for (Layer3D* layer : layers3D) {
			layer->updateTransforms();
		}
		for (Layer2D* layer : layers2D) {
			layer->updateTransforms();
		}
	}
	Layer3D * LayerStack::getLayer3D(int i)
	{
		return layers3D[i];
	}
	Layer2D * LayerStack::getLayer2D(int i)
	{
		return layers2D[i];
	}
	void LayerStack::addLayer3D(Layer3D * layer3D)
	{
		layers3D.push_back(layer3D);
	}
	void LayerStack::addLayer3D(Layer3D * layer3D, int pos)
	{
		std::vector<Layer3D*>::iterator it = layers3D.begin();
		layers3D.insert(it + pos,layer3D);
	}
	void LayerStack::addLayer2D(Layer2D * layer2D)
	{
		layers2D.push_back(layer2D);

	}
	void LayerStack::addLayer2D(Layer2D * layer2D, int pos)
	{
		std::vector<Layer2D*>::iterator it = layers2D.begin();
		layers2D.insert(it + pos, layer2D);
	}
} }