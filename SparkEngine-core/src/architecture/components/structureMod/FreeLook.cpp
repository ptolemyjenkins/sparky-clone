#include "FreeLook.h"
#include "../../../coreEngine.h"
namespace sparky { namespace components {
	
	freeLook::freeLook(float sensitivity) : freeLook(sensitivity, GLFW_KEY_ESCAPE)
	{
	}

	freeLook::freeLook(float sensitivity, int unlockMouseKey)
	{
		this->mouseLocked = false;
		this->sensitivity = sensitivity;
		this->unlockMouseKey = unlockMouseKey;
	}

	void freeLook::input(float delta, graphics::Window* window)
	{
		centrePosition = maths::vec2((float) (window->getWidth() / 2.0),(float) (window->getHeight() / 2.0));
		if (window->isKeyPressed(unlockMouseKey)) {
			mouseLocked = false;
		}



		float keyRot = 150 * sensitivity * delta;
		if (window->isKeyDown(GLFW_KEY_RIGHT)) getTransform()->rotateTrans(maths::quaternion(yAxis, keyRot));
		if (window->isKeyDown(GLFW_KEY_LEFT)) getTransform()->rotateTrans(maths::quaternion(yAxis, -keyRot));
		if (window->isKeyDown(GLFW_KEY_UP)) getTransform()->rotateTrans(maths::quaternion(getTransform()->rot.getRight(), keyRot));
		if (window->isKeyDown(GLFW_KEY_DOWN)) getTransform()->rotateTrans(maths::quaternion(getTransform()->rot.getRight(), -keyRot));


		if (mouseLocked) {
			maths::vec2 deltaPos = window->getMousePosition() - centrePosition;

			bool rotY = deltaPos.x != 0;
			bool rotX = deltaPos.y != 0;

			if (rotY) getTransform()->rotateTrans(maths::quaternion(yAxis, deltaPos.x * sensitivity));
			if (rotX) getTransform()->rotateTrans(maths::quaternion(getTransform()->rot.getRight(), -deltaPos.y * sensitivity));

			if (rotY || rotX) {
				window->setMousePosition(centrePosition.x,centrePosition.y);
			}
		}
		
		if (window->isMouseButtonPressed(0)) {
			window->setMousePosition(centrePosition.x, centrePosition.y);
			mouseLocked = true;
		}
	}

} }