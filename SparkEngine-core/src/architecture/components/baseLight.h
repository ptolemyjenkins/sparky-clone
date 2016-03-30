#pragma once
#include "../renderable3DComponent.h"


namespace sparky { 
	class coreEngine;
	namespace components {
	class baseLight : public architecture::Renderable3DComponent{
	private:
		maths::vec4 colour;
		float intensity;
		graphics::Shader * shader;
	public:
		baseLight();
		baseLight(maths::vec4 colour, float intensity);

		void addToEngine(CoreEngine* engine);

		void setIntensity(float intensity);
		float getIntensity();

		void setColour(maths::vec4 colour);
		maths::vec3 getColour();

		void setShader(graphics::Shader* shader);
		graphics::Shader* getShader();

	};

} }