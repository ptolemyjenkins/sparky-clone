#pragma once
#include "../../Component3D.h"
#include "../../../graphics/window.h"
namespace sparky { namespace components {
	class freeMove : public architecture::Component3D {
	private:
		float speed;
		float movAmt;
		bool slow = false;

		int forwardKey;
		int backKey;
		int leftKey;
		int rightKey;
		int upKey;
		int downKey;

		int boostKey;
		int slowKey;
	public:
		freeMove(float speed, int forwardKey, int backKey, int leftKey, int rightKey, int upKey, int downKey, int boostKey, int slowKey);
		freeMove(float speed);
		void input(float delta, graphics::Window* window);
		void move(maths::vec3 dir, float amt);

	};

} }