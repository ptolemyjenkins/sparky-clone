#pragma once
#include "..\src\coreEngine.h"
#include "../src/util/meshLoading/basicMeshs.h"

namespace sparky {
	class DebugScene : public architecture::Application
	{
		void init(graphics::Window* window);
		void update(float delta);
		void input(float delta, graphics::Window* window);
		float counter=0;
	};
}