#pragma once
#include "baseLight.h"

namespace sparky { namespace components {
	class directionalLight : public baseLight{
	private:
		
	public:
		directionalLight();
		directionalLight(maths::vec4 colour, float intensity);
		maths::vec3 getDirection();
	};
} }