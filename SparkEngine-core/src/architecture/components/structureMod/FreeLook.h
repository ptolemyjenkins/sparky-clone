#pragma once
#include "../../component3D.h"
#include "../../../graphics/window.h"
namespace sparky { namespace components {
	class freeLook : public architecture::Component3D {
	private:
		maths::vec3 const yAxis = maths::vec3(0, 1, 0);
		bool mouseLocked;
		float sensitivity;
		int unlockMouseKey;
		maths::vec2 centrePosition;
	public:
		freeLook(float sensitivity);
		freeLook(float sensitivity, int unlockMouseKey);
		void input(float delta, graphics::Window* window);
		

	};

} }