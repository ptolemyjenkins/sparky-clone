#include "Attenuation.h"
namespace sparky { namespace graphics {
		Attenuation::Attenuation() : maths::vec3()
		{
		}

		Attenuation::Attenuation(float constant, float linear, float exponent) : maths::vec3(constant, linear, exponent)
		{

		}
} }