#include "camera.h"
#include "../../coreEngine.h"
namespace sparky { namespace components {
	camera::camera()
	{

	}

	camera::camera(float fov, float aspect, float zNear, float zFar)
	{
		this->projection = maths::mat4().perspective(fov, aspect, zNear, zFar);
	}

	void camera::addToEngine(CoreEngine engine)
	{
		engine.getRenderingEngine()->setMainCamera(this);
	}

	maths::mat4 camera::getViewProjection()
	{
		maths::mat4 cameraRotation = getTransform().getTransformedRot().conjugate().toRotationMatrix();
		maths::vec3 cameraPos = getTransform().getTransformedPos().multiply(-1.0);
		maths::mat4 cameraTranslation = maths::mat4().translation(cameraPos);
		return projection * (cameraRotation * cameraTranslation);
	}

	void camera::printState()
	{
		std::cout << "Current Position: " << getTransform().getTransformedPos() << std::endl;
		std::cout << "Current tilt: " << getTransform().getTransformedRot().getForward() << std::endl;
	}

} }