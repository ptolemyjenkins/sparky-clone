#pragma once
#include "../../maths/maths.h"

namespace sparky { namespace graphics{
	class Attenuation : maths::vec3 {
	private:

	public:
		Attenuation();
		Attenuation(float constant, float linear, float exponent);
		float getConstant() {
			return x;
		}
		float getLinear() {
			return y;
		}
		float getExponent() {
			return z;
		}

	};
} }