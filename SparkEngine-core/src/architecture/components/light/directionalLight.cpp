#include "directionalLight.h"

namespace sparky { namespace components {
	directionalLight::directionalLight() : baseLight()
	{

	}

	directionalLight::directionalLight(maths::vec4 colour, float intensity) : baseLight(colour, intensity)
	{
		setShader(new graphics::Shader("forward_directional", "forward-directional.vs", "forward-directional.fs"));
	}

	maths::vec3 directionalLight::getDirection()
	{
		return getTransform()->getTransformedRot().getForward();
	}


} }
