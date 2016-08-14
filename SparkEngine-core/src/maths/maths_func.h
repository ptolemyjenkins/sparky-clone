#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "../util/fileutils.h"

namespace sparky { namespace maths {

	inline float toRadians(float degrees)
	{
		return (float)(degrees * M_PI / 180);
	}
} }