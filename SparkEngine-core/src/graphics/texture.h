#pragma once
#include <iostream>
#include "../ResourceManagment/TextureResource.h"
#include <unordered_map>
#include <exception>

namespace sparky { namespace graphics{
	class Texture {
	private:
		static std::unordered_map<std::string, resource::TextureResource> loadedTextures;
		resource::TextureResource* resource;
		std::string fileName;
	public:
		Texture();
		Texture(std::string fileName);
		~Texture();
		
		void bind();
		void bind(unsigned int samplerSlot);
		int getID();
	private:
		static resource::TextureResource* loadTexture(std::string fileName);
	};
} }