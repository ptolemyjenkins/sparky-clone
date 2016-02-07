#include "renderingEngine.h"

namespace sparky { namespace graphics {
	RenderingEngine::RenderingEngine()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//lights = new ArrayList<BaseLight>();
		//samplerMap = new HashMap<String, Integer>();

		//samplerMap.put("diffuse", 0);
		//samplerMap.put("normalMap", 1);
		//samplerMap.put("dispMap", 2);

		//addVector3f("ambient", new Vector3f(0.0f, 0.0f, 0.0f));

		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_CLAMP);
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}

	void RenderingEngine::render(architecture::Renderable3D* object) {
//		forwardAmbient = new Shader("forward-ambient");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		object.renderAll(forwardAmbient, this);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(false);
		glDepthFunc(GL_EQUAL);

		//for (BaseLight light : lights) {
		//	activeLight = light;
		//	object.renderAll(light.getShader(), this);
		//}

		glDepthFunc(GL_LESS);
		glDepthMask(true);
		glDisable(GL_BLEND);
	}

	void RenderingEngine::setClearColour(maths::vec3 colour)
	{
		glClearColor(colour.x, colour.y, colour.z, 1.0f);
	}
} }