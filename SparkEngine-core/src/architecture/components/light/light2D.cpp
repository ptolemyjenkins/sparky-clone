#include "light2D.h"

namespace sparky {
	namespace components {
		Light2D::Light2D() {
			baseLight();
			setShader(new graphics::Shader("GUI", "GUI.vs", "GUI.fs"));
		}

		Light2D::Light2D(maths::vec4 colour, float intensity) {
			baseLight(colour, intensity);
			setShader(new graphics::Shader("GUI", "GUI.vs", "GUI.fs"));
		}
	}
}