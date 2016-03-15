#pragma once
#include "../architecture/application.h"
#include "../architecture/components/camera.h"
#include "../architecture/components/pointLight.h"
#include "../architecture/components/directionalLight.h"

#include "../ResourceManagment/Mapping.h"
#include <unordered_map>
#include <memory>
#include <vector>

namespace sparky { namespace graphics {
	class RenderingEngine : public resource::Mapping
	{
	private:
		graphics::Shader &forwardAmbient = graphics::Shader();

		components::baseLight* activeLight;
		std::unordered_map<std::string, int> samplerMap;
		std::vector<components::baseLight*> lights;

		components::camera* mainCamera;
	public:
		RenderingEngine();
		void initShaders();

		void render(architecture::Renderable3D* object);
		void setClearColour(maths::vec4 colour);

		void setMainCamera(components::camera* cam);
		components::camera* getMainCamera();

		int getSamplerSlot(std::string samplerName);
		void addLight(components::baseLight* light);
		components::baseLight* getActiveLight();
	};
} }