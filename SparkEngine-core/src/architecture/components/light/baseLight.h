#pragma once
#include "../../Component.h"
#include "../../../graphics/shader.h"

namespace sparky { namespace components {
	class baseLight : public architecture::Component {
	private:
		maths::vec4 colour;
		float intensity;
		graphics::Shader * shader;

	public:
		baseLight();
		baseLight(maths::vec4 colour, float intensity);

		void setIntensity(float intensity);
		float getIntensity();

		void setColour(maths::vec4 colour);
		maths::vec3 getColour();

		void setShader(graphics::Shader* shader);
		graphics::Shader* getShader();
	};
} }