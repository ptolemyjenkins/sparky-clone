#include "material.h"
namespace sparky { namespace graphics {
	
	Material::Material()
	{
		addTexture("diffuse", new Texture("Debug.png"));
		addTexture("normalMap", new Texture("default_normal.jpg"));
		addTexture("dispMap",  new Texture("default_disp.png"));
		addFloat("specularIntensity", 1.0f);
		addFloat("specularPower", 0.01f);
		addFloat("dispMapScale", 0.0f);
		addFloat("dispMapBias", 0.0f);
		
	}

	Material::~Material()
	{
	}

	Material::Material(std::vector<Texture*>* textureList)
	{
		this->textureList = textureList;
		for (int i = 0; i < 32; i++)
		{
			texIDs.push_back(-1);
		}
	}

	Material::Material(Texture * diffuse, float specularIntensity, float specularPower) : Material()
	{
		if (diffuse != nullptr) addTexture("diffuse", diffuse);
		if (specularIntensity != 0) addFloat("specularIntensity", specularIntensity);
		if (specularPower != 0) addFloat("specularPower", specularPower);
	}

	Material::Material(Texture* diffuse, float specularIntensity, float specularPower, Texture* normalMap, Texture* dispMap, float dispMapScale, float dispMapOffset) : Material()
	{
		if (diffuse != nullptr) addTexture("diffuse", diffuse);
		if (normalMap != nullptr) addTexture("normalMap", normalMap);
		if (dispMap != nullptr) addTexture("dispMap", dispMap);
		if (specularIntensity != 0) addFloat("specularIntensity", specularIntensity);
		if (specularPower != 0) addFloat("specularPower", specularPower);
		if (dispMapScale != 0) addFloat("dispMapScale", dispMapScale);
		float baseBias = dispMapScale / 2.0f;
		if (dispMapOffset != 0) addFloat("dispMapBias", -baseBias + baseBias * dispMapOffset);
	}

	void Material::useDefaultNormal()
	{
		addTexture("normalMap", new Texture("default_normal.png"));
	}

	void Material::addTexture(const std::string & name, Texture * texture)
	{
		textureHashMap[name] = texture;
	}

	Texture* Material::getTexture(std::string name)
	{
		Texture* resource;
		auto result = textureHashMap.find(name);
		if (result != textureHashMap.end()) {
			resource = result->second;
			return resource;
		}
		else {
			util::Logging::log_exit("Error: [TEXTURE] unable to retrieve <" + name + "> from texture HashMap.\n",1);
		}
	}

	void Material::updateTextures()
	{
		for (unsigned int i = 0; i < textureList->size(); i++)
		{
			if ((*textureList)[i] == NULL) continue;
			addSpriteTexture(std::to_string(i), (*textureList)[i]);
		}
	}

	void Material::addSpriteTexture(const std::string & name, Texture * texture)
	{
		textureHashMap[name] = texture;
		texIDs[(atoi(name.c_str()))] = (atoi(name.c_str()));
	}

	std::vector<GLint> Material::getGLints()
	{
		std::vector<GLint> b;
		for (GLint a : texIDs) {
			if (a == -1) continue;
			b.push_back(a);
		}
		return b;
	}

} }