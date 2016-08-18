#pragma once
#include "../ResourceManagment/Mapping.h"
#include "texture.h"

namespace sparky { namespace graphics {
	class Material : public resource::Mapping {
	public:
		std::unordered_map<std::string, Texture*> textureHashMap;
		std::vector<Texture*>* textureList;
		std::vector<GLint> texIDs;

	public:
		Material();
		~Material();

		Material(std::vector<Texture*>* textureList);
		Material(Texture* diffuse, float specularIntensity, float specularPower);
		Material(Texture* diffuse, float specularIntensity, float specularPower, Texture* normalMap, Texture* dispMap, float dispMapScale, float dispMapOffset);

		void useDefaultNormal();
		void addTexture(const std::string& name, Texture* texture);
		Texture* getTexture(std::string name);
		void updateTextures();
		void addSpriteTexture(const std::string& name, Texture* texture);
		std::vector<GLint> getGLints();
	};
} }