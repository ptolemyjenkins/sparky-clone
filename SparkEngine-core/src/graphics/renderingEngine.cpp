#include "renderingEngine.h"
#include "../coreEngine.h"

namespace sparky { namespace graphics {
	RenderingEngine::RenderingEngine()
	{
		samplerMap["diffuse"] =  0;
		samplerMap["normalMap"] = 1;
		samplerMap["dispMap"] =  2;

		addVec3("ambient", maths::vec3(0.1f, 0.1f, 0.1f));
	}

	void RenderingEngine::initShaders()
	{
		forwardAmbient.init("forward-ambient", "forward-ambient.vs", "forward-ambient.fs");
		//forwardAmbient.init("basic", "basic.vert", "basic.frag");
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_CLAMP);
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}

	void RenderingEngine::render(architecture::Renderable3D* object) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		object->renderAll(forwardAmbient, *this);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(false);
		glDepthFunc(GL_EQUAL);

		for (components::baseLight* light : lights) {
			activeLight = light;
			object->renderAll(*light->getShader(), *this);
		}

		glDepthFunc(GL_LESS);
		glDepthMask(true);
		glDisable(GL_BLEND);
	}

	void RenderingEngine::setClearColour(maths::vec4 colour)
	{
		glClearColor(colour.x, colour.y, colour.z, colour.w);
	}

	void RenderingEngine::setMainCamera(components::camera* cam)
	{
		mainCamera = cam;
	}

	components::camera* RenderingEngine::getMainCamera()
	{
		return mainCamera;
	}

	int RenderingEngine::getSamplerSlot(std::string samplerName)
	{
		return samplerMap[samplerName];
	}

	void RenderingEngine::addLight(components::baseLight* light)
	{
		lights.push_back(light);
	}

	components::baseLight* RenderingEngine::getActiveLight()
	{
		return activeLight;
	}
} }