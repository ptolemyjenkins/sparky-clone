#pragma once
#include "../../Component.h"


namespace sparky { namespace components {
	class camera : public architecture::Component {
	private:
		maths::mat4 projection;
	public:
		camera();
		camera(float fov, float aspect, float zNear, float zFar);
		camera(float left, float right, float bottom, float top, float near, float far);

		maths::mat4 getViewProjection();

		void printState();
	};
} }