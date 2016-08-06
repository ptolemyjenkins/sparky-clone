#pragma once
#include "baseLight.h"
#include "../../../graphics/constructs/Attenuation.h"

namespace sparky { namespace components {
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