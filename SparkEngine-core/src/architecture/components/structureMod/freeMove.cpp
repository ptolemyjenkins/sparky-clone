#include "freeMove.h"
#include "../../../coreEngine.h"
namespace sparky { namespace components{
	freeMove::freeMove(float speed, int forwardKey, int backKey, int leftKey, int rightKey, int upKey, int downKey, int boostKey, int slowKey)
	{
		this->speed = speed;
		this->forwardKey = forwardKey;
		this->backKey = backKey;
		this->leftKey = leftKey;
		this->rightKey = rightKey;
		this->upKey = upKey;
		this->downKey = downKey;
		this->boostKey = boostKey;
		this->slowKey = slowKey;
	}

	freeMove::freeMove(float speed): freeMove(speed, GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT, GLFW_KEY_R, GLFW_KEY_LEFT_CONTROL)
	{

	}

	void freeMove::input(float delta, graphics::Window* window)
	{
		movAmt = (float)(speed * delta);

		if (window->isKeyPressed(slowKey)) {
			slow = !slow;
		}

		if (slow) {
			movAmt *= 0.1;
		}

		if (window->isMouseButtonDown(1)) {
			movAmt *= 10;
		}

		if (window->isKeyDown(forwardKey)) move(getTransform()->rot.getForward(), movAmt);
		if (window->isKeyDown(backKey)) move(getTransform()->rot.getForward(), -movAmt);
		if (window->isKeyDown(leftKey)) move(getTransform()->rot.getRight(), movAmt);
		if (window->isKeyDown(rightKey)) move(getTransform()->rot.getRight(), -movAmt);
		if (window->isKeyDown(upKey)) move(getTransform()->rot.getUp(), movAmt);
		if (window->isKeyDown(downKey)) move(getTransform()->rot.getUp(), -movAmt);
	
	}

	void freeMove::move(maths::vec3 dir, float amt)
	{
		getTransform()->pos += (dir * amt);
	}
	

} }
