#pragma once
#include "../architecture/layerStack.h"
#include <memory>

namespace sparky { namespace graphics {
	class RenderingEngine : public resource::Mapping
	{
	private:
		std::unordered_map<std::string, int> samplerMap;

		architecture::LayerStack* scene;
	public:
		RenderingEngine();

		void render();
		void forwardBlendOn();
		void forwardBlendOff();

		void setScene(architecture::LayerStack* scene);
		void setClearColour(maths::vec4 colour);
		int getSamplerSlot(std::string samplerName);

	};
} }