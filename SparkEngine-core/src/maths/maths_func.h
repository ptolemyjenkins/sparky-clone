#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

namespace sparky { namespace maths {

	inline float toRadians(float degrees)
	{
		return (float)(degrees * M_PI / 180);
	}
} }