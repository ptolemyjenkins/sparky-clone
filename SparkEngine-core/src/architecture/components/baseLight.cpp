#include "baseLight.h"
#include "../../coreEngine.h"

namespace sparky { namespace components {
	baseLight::baseLight() {
		this->colour = maths::vec4(0,0,0,1);
		this->intensity = 0;
		this->shader = NULL;
	}

	baseLight::baseLight(maths::vec4 colour, float intensity) {
		this->colour = colour;
		this->intensity = intensity;
		this->shader = NULL;
	}

	void baseLight::addToEngine(CoreEngine* engine)
	{
		//Engine.getRenderingEngine().addLight(this);

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

	maths::vec4 baseLight::getColour()
	{
		return maths::vec4();
	}

	void baseLight::setShader(graphics::Shader &shader)
	{
		this->shader = &shader;
	}

	graphics::Shader* baseLight::getShader()
	{
		return shader;
	}


} }