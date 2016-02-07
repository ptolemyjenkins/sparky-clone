#pragma once
#include "../../maths/maths.h"
#include "../../coreEngine.h"
#include "../renderable3DComponent.h"


namespace sparky { namespace components {
	class baseLight : public architecture::Renderable3DComponent{
	private:
		maths::vec4 colour;
		float intensity;
		graphics::Shader * shader;
	public:
		baseLight();
		baseLight(maths::vec4 colour, float intensity);

		void addToEngine(const CoreEngine const engine);

		void setIntensity(float intensity);
		float getIntensity();

		void setColour(maths::vec4 colour);
		maths::vec4 getColour();

		void setShader(graphics::Shader shader);
		graphics::Shader* getShader();

	};

} }