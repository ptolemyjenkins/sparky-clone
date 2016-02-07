#pragma once
#include <GL\glew.h>
namespace sparky { namespace resource {
	class MeshResource {
	private:
		GLuint vbo, ibo, vao;
		int size, refCount;
	public:
		MeshResource();
		MeshResource(int size);
		~MeshResource();
		void addReference();
		bool removeReference();

		int getVbo() {
			return vbo;
		}

		int getIbo() {
			return ibo;
		}

		int getVao() {
			return vao;
		}

		int getSize() {
			return size;
		}
	};
} }