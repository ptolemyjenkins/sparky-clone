#include "MeshResource.h"
namespace sparky { namespace resource {
	MeshResource::MeshResource() {
		glGenBuffers(1, &posVbo);
		glGenBuffers(1, &norVbo);
		glGenBuffers(1, &texVbo);
		glGenBuffers(1, &tanVbo);

		glGenBuffers(1, &ibo);
		glGenVertexArrays(1, &vao);
		this->size = 0;
		this->refCount = 1;
	}

	MeshResource::MeshResource(int size)
	{
		glGenBuffers(1, &posVbo);
		glGenBuffers(1, &norVbo);
		glGenBuffers(1, &texVbo);
		glGenBuffers(1, &tanVbo);

		glGenBuffers(1, &ibo);
		glGenVertexArrays(1, &vao);
		this->size = size;
		this->refCount = 1;
	}

	MeshResource::~MeshResource()
	{
		glDeleteBuffers(1, &posVbo);
		glDeleteBuffers(1, &norVbo);
		glDeleteBuffers(1, &texVbo);
		glDeleteBuffers(1, &tanVbo);

		glDeleteBuffers(1, &ibo);
		glDeleteVertexArrays(1, &vao);
	}

	void MeshResource::addReference() {
		refCount++;
	}
	bool MeshResource::removeReference()
	{
		refCount--;
		return refCount == 0;
	}
} }