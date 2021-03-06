#include "directionalLight.h"

namespace sparky { namespace components {
	directionalLight::directionalLight() : baseLight()
	{

	}

	directionalLight::directionalLight(maths::vec4 colour, float intensity) : baseLight(colour, intensity)
	{
		setShader(graphics::Shader("forward-directional.vert", "forward-directional.frag"));
	}

	maths::vec3 directionalLight::getDirection()
	{
		return getTransform().getTransformedRot().getForward();
	}


} }
