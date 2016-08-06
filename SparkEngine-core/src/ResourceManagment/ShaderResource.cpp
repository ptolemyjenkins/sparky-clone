#include "ShaderResource.h"
#include "../util/logging.h"
#include <iostream>
namespace sparky { namespace resource {
	ShaderResource::ShaderResource()
	{
		
	}

	void ShaderResource::init() {
		this->m_ShaderID = glCreateProgram();
		this->refCount = 1;

		if (m_ShaderID == 0) {
			util::Logging::log_exit("Shader creation failed: could not find valid memory location in constructor", 1);
		}
	}

	ShaderResource::~ShaderResource()
	{
		glDeleteProgram(m_ShaderID);
	}

	void ShaderResource::addReference()
	{
		refCount++;
	}

	bool ShaderResource::removeReference()
	{
		refCount--;
		return refCount == 0;
	}
	GLuint& ShaderResource::getProgram()
	{
		return m_ShaderID;
	}
	std::unordered_map<std::string, int>& ShaderResource::getUniforms()
	{
		return uniforms;
	}
	std::vector<std::string>& ShaderResource::getUniformNames()
	{
		return uniformNames;
	}
	std::vector<std::string>& ShaderResource::getUniformTypes()
	{
		return uniformTypes;
	}
} }