#include "TextureResource.h"

namespace sparky { namespace resource {
	TextureResource::TextureResource()
	{
		glGenTextures(1, &id);
		this->refCount = 1;
	}

	TextureResource::~TextureResource()
	{
		glDeleteBuffers(1,&id);
	}

	void TextureResource::addReference()
	{
		refCount++;
	}

	bool TextureResource::removeReference()
	{
		refCount--;
		return refCount == 0;
	}

	int TextureResource::getID()
	{
		return id;
	}
} }