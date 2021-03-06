#pragma once
#include <GL\glew.h>

namespace sparky { namespace resource{
	class TextureResource {
	private:
		GLuint id;
		int refCount;

	public:
		TextureResource();
		~TextureResource();

		void addReference();
		bool removeReference();
		
		int getID();
	};
} }