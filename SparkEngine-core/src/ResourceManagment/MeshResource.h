#pragma once
#include <GL\glew.h>
namespace sparky { namespace resource {
	class MeshResource {
	private:
		GLuint posVbo, norVbo, texVbo, tanVbo;
		GLuint ibo, vao;
		int size, refCount;
	public:
		MeshResource();
		MeshResource(int size);
		~MeshResource();
		void addReference();
		bool removeReference();

		GLuint& getPosVbo() {
			return posVbo;
		}

		GLuint& getNorVbo() {
			return norVbo;
		}

		GLuint& getTexVbo() {
			return texVbo;
		}

		GLuint& getTanVbo() {
			return tanVbo;
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
} }