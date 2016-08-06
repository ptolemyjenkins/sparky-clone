#include "camera.h"
namespace sparky { namespace components {
	camera::camera()
	{
		camera(50, 19.0f / 12.0f, 0.1f, 1000);
	}

	camera::camera(float fov, float aspect, float zNear, float zFar)
	{
		this->projection = maths::mat4().perspective(fov, aspect, zNear, zFar);
	}

	maths::mat4 camera::getViewProjection()
	{
		maths::mat4 cameraRotation = getTransform()->getTransformedRot().conjugate().toRotationMatrix();
		maths::vec3 cameraPos = getTransform()->getTransformedPos().multiply(-1.0);
		maths::mat4 cameraTranslation = maths::mat4().translation(cameraPos);
		return projection * (cameraRotation * cameraTranslation);
		
	}

	void camera::printState()
	{
		graphics::Transform* a = getTransform();
		std::cout << "Current Position: " << a->getTransformedPos() << std::endl;
		std::cout << "Current tilt: " << a->getTransformedRot().getForward() << std::endl;
	}

} }