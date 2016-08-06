#pragma once
#include "../../Component3D.h"


namespace sparky { namespace components {
	class camera : public architecture::Component3D {
	private:
		maths::mat4 projection;
	public:
		camera();
		camera(float fov, float aspect, float zNear, float zFar);

		maths::mat4 getViewProjection();

		void printState();
	};
} }