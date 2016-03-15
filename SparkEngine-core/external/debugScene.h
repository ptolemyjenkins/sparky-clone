#pragma once
#include "../src/architecture/application.h"
#include "../src/architecture/components/components.h"
#include "../src/graphics/material.h"
#include "../src/graphics/mesh.h"

namespace sparky {
	class DebugScene : public architecture::Application
	{
		void init();
		void update(float delta);
	};
}