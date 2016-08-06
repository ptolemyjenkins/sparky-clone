#include "baseLight.h"

namespace sparky { namespace components {
	baseLight::baseLight() {
		this->colour = maths::vec4(0,0,0,1);
		this->intensity = 0;
		this->shader = new graphics::Shader("forward-ambient", "forward-ambient.vs", "forward-ambient.fs");
	}

	baseLight::baseLight(maths::vec4 colour, float intensity) {
		this->colour = colour;
		this->intensity = intensity;
		this->shader = new graphics::Shader("forward-ambient", "forward-ambient.vs", "forward-ambient.fs");
	}

	void baseLight::setIntensity(float intensity)
	{
		this->intensity = intensity;
	}

	float baseLight::getIntensity()
	{
		return intensity;
	}

	void baseLight::setColour(maths::vec4 colour)
	{
		this->colour = colour;
	}

	maths::vec3 baseLight::getColour()
	{
		return maths::vec3(colour.x,colour.y,colour.z);
	}

	void baseLight::setShader(graphics::Shader* shader)
	{
		this->shader = shader;
	}

	graphics::Shader* baseLight::getShader()
	{
		return shader;
	}


} }