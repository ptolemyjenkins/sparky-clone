#include "texture.h"
#include <unordered_map>
#include "../../libs/stb_image.h"

namespace sparky { namespace graphics {
	std::unordered_map<std::string, resource::TextureResource> Texture::loadedTextures;
	
	Texture::Texture()
	{
		this->fileName = "";
		resource = &resource::TextureResource();
	}

	Texture::Texture(std::string fileName)
	{

		this->fileName = fileName;
		std::unordered_map<std::string, resource::TextureResource>::const_iterator result = Texture::loadedTextures.find(fileName);
		if (result != Texture::loadedTextures.end()) {
			resource = &Texture::loadedTextures[fileName];
			resource->addReference();
		}
		else {
			resource = Texture::loadTexture(fileName);
			Texture::loadedTextures[fileName] = *resource;
		}
	}

	Texture::~Texture()
	{
		if (resource->removeReference() && fileName != "") {
			delete resource;
			if (loadedTextures.find(fileName) != loadedTextures.end()) {
				loadedTextures.erase(fileName);
			}
		}
	}
	void Texture::bind()
	{
		bind(0);
	}
	void Texture::bind(unsigned int samplerSlot)
	{
		if (samplerSlot >= 0 && samplerSlot <= 31) {
			glActiveTexture(GL_TEXTURE0 + samplerSlot);
			glBindTexture(GL_TEXTURE_2D, resource->getID());
		}
		else {
			std::cerr << "Error: Invalid texture sampler slot:" << samplerSlot << std::endl;
		}
	}

	int Texture::getID()
	{
		return resource->getID();
	}

	resource::TextureResource* Texture::loadTexture(std::string fileName)
	{
		resource::TextureResource* resource1 = new resource::TextureResource();
		try {
			int width, height, numComponents;
			std::string pre = "./res/textures/";
			unsigned char* imageData = stbi_load((pre + fileName).c_str(), &width, &height, &numComponents, 4);
			glBindTexture(GL_TEXTURE_2D, resource1->getID());

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;
			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(imageData);
		}catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			exit(1);
		}
		return resource1;
	}
} }