#pragma once
#include "..\src\coreEngine.h"
#include "../src/architecture/layer3D.h"
#include "../src/util/meshLoading/basicMeshs.h"

namespace sparky {
	class DebugScene : public architecture::Application
	{
		void init();
		void update(float delta);
		void input(float delta, graphics::Window* window);
	};
}