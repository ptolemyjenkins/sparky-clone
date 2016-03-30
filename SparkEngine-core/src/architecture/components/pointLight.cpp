#include "pointLight.h"
namespace sparky { namespace components {
	pointLight::pointLight() : baseLight()
	{
		
	}

	pointLight::pointLight(maths::vec4 colour, float intensity, graphics::Attenuation attenuation) : baseLight(colour, intensity) 
	{
		this->attenuation = attenuation;
		float a = attenuation.getExponent();
		float b = attenuation.getLinear();
		float c = attenuation.getConstant() - COLOUR_DEPTH * getIntensity() * getColour().max();
		this->range = (float)(-b + sqrt(b*b - 4 * a*c)) / (2 * a);
		setShader(new graphics::Shader("forward-point","forward-point.vs", "forward-point.fs"));

	}
} }