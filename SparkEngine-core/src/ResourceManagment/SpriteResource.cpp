#include "SpriteResource.h"
namespace sparky { namespace resource {
	SpriteResource::SpriteResource()
	{
		glGenBuffers(1, &Vbo);

		glGenBuffers(1, &ibo);
		glGenVertexArrays(1, &vao);
		this->size = 0;
	}
	SpriteResource::SpriteResource(int size)
	{
		glGenBuffers(1, &Vbo);

		glGenBuffers(1, &ibo);
		glGenVertexArrays(1, &vao);
		this->size = size;
	}
	SpriteResource::~SpriteResource()
	{
		glDeleteBuffers(1, &Vbo);

		glDeleteBuffers(1, &ibo);
		glDeleteVertexArrays(1, &vao);
	}
} }