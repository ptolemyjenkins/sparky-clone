#pragma once
#include "baseLight.h"

namespace sparky { 
	namespace graphics {
	struct Attenuation {
		float m_constant;
		float m_linear;
		float m_exponent;
		Attenuation() {}
		Attenuation(float constant, float linear, float exponent) : m_constant(constant), m_linear(linear), m_exponent(exponent) {}

	};

	}
	namespace components {
		class pointLight : public baseLight {
		private:
			static const int COLOUR_DEPTH = 256;
			float range;
			graphics::Attenuation attenuation;

		public:
			pointLight();
			pointLight(maths::vec4 colour, float intensity, graphics::Attenuation attenuation);
			graphics::Attenuation getAttenuation() {
				return attenuation;
			}
			float getRange() {
				return range;
			}
			void setRange(float range) {
				this->range = range;
			}
		};
} }