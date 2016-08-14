#include "renderingEngine.h"
#include "../coreEngine.h"

namespace sparky { namespace graphics {
	RenderingEngine::RenderingEngine()
	{
		samplerMap["diffuse"] =  0;
		samplerMap["normalMap"] = 1;
		samplerMap["dispMap"] =  2;

		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_CLAMP);
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}

	void RenderingEngine::render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene->render(this);
	}

	void RenderingEngine::forwardBlendOn()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(false);
		glDepthFunc(GL_EQUAL);
	}

	void RenderingEngine::forwardBlendOff()
	{
		glDepthFunc(GL_LESS);
		glDepthMask(true);
		glDisable(GL_BLEND);
	}



	void RenderingEngine::setScene(architecture::LayerStack * scene)
	{
		this->scene = scene;
	}

	void RenderingEngine::setClearColour(maths::vec4 colour)
	{
		glClearColor(colour.x, colour.y, colour.z, colour.w);
	}


	int RenderingEngine::getSamplerSlot(std::string samplerName)
	{
		return samplerMap[samplerName];
	}

} }