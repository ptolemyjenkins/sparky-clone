#pragma once
#include "../ResourceManagment/Mapping.h"
#include "texture.h"
#include <unordered_map>

namespace sparky { namespace graphics {
	class Material : public resource::Mapping {
	private:
		const std::string defaultDiffuse;
		const std::string defaultNormal;
		const std::string defaultDisp;
		std::unordered_map<std::string, Texture*> textureHashMap;
	public:
		Material();
		Material(Texture* diffuse, float specularIntensity, float specularPower, Texture* normalMap, Texture* dispMap, float dispMapScale, float dispMapOffset);

		void useDefaultNormal();
		void addTexture(const std::string& name, Texture* texture);
		Texture* getTexture(std::string name);
		Material* DebugMaterial();
	};
} }