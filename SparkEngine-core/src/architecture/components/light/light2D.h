#pragma once
#include "baseLight.h"

namespace sparky {
	namespace components {
		class Light2D : public baseLight {
		private:

		public:
			Light2D();
			Light2D(maths::vec4 colour, float intensity);
		};
	}
}