#pragma once
#include <GL\glew.h>
namespace sparky {
	namespace resource {
		class SpriteResource {
		private:
			GLuint Vbo;
			GLuint ibo, vao;
		public:
			int size;
			SpriteResource();
			SpriteResource(int size);
			~SpriteResource();

			GLuint& getVbo() {
				return Vbo;
			}

			GLuint& getIbo() {
				return ibo;
			}

			GLuint& getVao() {
				return vao;
			}

			int getSize() {
				return size;
			}
		};
	}
}