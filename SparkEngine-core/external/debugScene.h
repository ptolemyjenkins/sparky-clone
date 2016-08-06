#pragma once
#include "../src/architecture/application.h"
#include "../src/architecture/Layer3D.h"
#include "../src/util/meshLoading/basicMeshs.h"

namespace sparky {
	class DebugScene : public architecture::Application
	{
		void init();
		void update(float delta);
	};
}