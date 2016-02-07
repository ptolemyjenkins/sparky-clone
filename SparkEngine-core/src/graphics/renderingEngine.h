#pragma once
#include "../architecture/application.h"

namespace sparky { namespace graphics {
	class RenderingEngine
	{
	public:
		RenderingEngine();
		void render(architecture::Renderable3D* object);
		void setClearColour(maths::vec3 colour);
	};
} }