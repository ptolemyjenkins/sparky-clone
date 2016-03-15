#include "shader.h"
#include "renderingEngine.h"
#include "../architecture/components/camera.h"
#include "../architecture/components/pointLight.h"
#include "../architecture/components/directionalLight.h"
#include "../util/logging.h"

namespace sparky { namespace graphics {
	std::vector<std::string> Shader::loadedShaderMap;
	std::vector<resource::ShaderResource*> Shader::loadedShaders;


	Shader::Shader(char * fileName, const char * vertexPath, const char * fragPath)
		: m_VertPath(vertexPath), m_FragPath(fragPath), m_FileName(fileName)
	{
		int pos = std::find(loadedShaderMap.begin(), loadedShaderMap.end(), fileName) - loadedShaderMap.begin();
		if (pos < loadedShaderMap.size()) {
			m_resource = loadedShaders[pos];
			m_resource->addReference();
		}
		else {
			m_resource = new resource::ShaderResource();
			m_resource->init();
			loadedShaderMap.push_back(fileName);
			loadedShaders.push_back(m_resource);
			std::string pre = "./res/shaders/";
			std::string vertShaderString = util::FileUtils::read_file((pre + m_VertPath).c_str());
			std::string fragShaderString = util::FileUtils::read_file((pre + m_FragPath).c_str());
			if (addVertexShader(vertShaderString) && addFragmentShader(fragShaderString)) {
				compileShader();
			}
			else {
				util::Logging::Log("Error: failed shader build",1);
			}
			addAllUniforms(vertShaderString,fileName);
			addAllUniforms(fragShaderString,fileName);
		}
	}

	Shader::~Shader()
	{
		if (m_resource->removeReference()) {
			int pos = std::find(loadedShaderMap.begin(), loadedShaderMap.end(), m_FileName) - loadedShaderMap.begin();
			if (pos < loadedShaderMap.size()) {
				loadedShaderMap.erase(loadedShaderMap.begin() + pos);
				loadedShaders.erase(loadedShaders.begin() + pos);
			}
		}
	}

	void Shader::init(char * fileName, const char * vertexPath, const char * fragPath)
	{
		if (m_FileName != nullptr) {
			util::Logging::Log("Error: Reinitialisation of shader", 1);
		}
		m_VertPath = vertexPath;
		m_FragPath = fragPath;
		m_FileName = fileName;
		int pos = std::find(loadedShaderMap.begin(), loadedShaderMap.end(), fileName) - loadedShaderMap.begin();
		if (pos < loadedShaderMap.size()) {
			m_resource = loadedShaders[pos];
			m_resource->addReference();
		}
		else {
			m_resource = new resource::ShaderResource();
			m_resource->init();
			loadedShaderMap.push_back(fileName);
			loadedShaders.push_back(m_resource);
			std::string pre = "./res/shaders/";
			std::string vertShaderString = util::FileUtils::read_file((pre + m_VertPath).c_str());
			std::string fragShaderString = util::FileUtils::read_file((pre + m_FragPath).c_str());
			if (addVertexShader(vertShaderString) && addFragmentShader(fragShaderString)) {
				compileShader();
			}
			else {
				util::Logging::Log("Error: failed shader build", 1);
			}
			addAllUniforms(vertShaderString, fileName);
			addAllUniforms(fragShaderString, fileName);
		}
	}

	void Shader::bind()
	{
		glUseProgram(m_resource->getProgram());
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}

	GLint Shader::getUniformLocation(const GLchar * name)
	{
		return glGetUniformLocation(m_resource->getProgram(), name);
	}

	bool Shader::addVertexShader(std::string shaderString)
	{
		
		const char * text = shaderString.c_str();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &text, NULL);
		glCompileShader(vertex);
		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "ERROR: failed to compile " << m_VertPath << ":\n" << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}
		glAttachShader(m_resource->getProgram(), vertex);
		glDeleteShader(vertex);
		return 1;
	}

	bool Shader::addFragmentShader(std::string shaderString)
	{
		const char * text = shaderString.c_str();
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &text, NULL);
		glCompileShader(fragment);
		GLint result;
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "ERROR: failed to compile " << m_FragPath << ":\n" << &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}
		glAttachShader(m_resource->getProgram(), fragment);
		glDeleteShader(fragment);
		return 1;
	}

	void Shader::compileShader()
	{
		glLinkProgram(m_resource->getProgram());
		glValidateProgram(m_resource->getProgram());
	}

	// -------------------------------------------------------------------------------------------------------------------
	// uniform handling
	// -------------------------------------------------------------------------------------------------------------------

	void Shader::updateUniforms(Transform transform, Material material, RenderingEngine renderingEngine) {
		mat4 model = transform.getTransformation();
		mat4 MVP = renderingEngine.getMainCamera()->getViewProjection() *  model;
		for (int i = 0; i < m_resource->getUniformNames().size(); i++) {
			std::string uniformName = m_resource->getUniformNames()[i];
			std::string uniformType = m_resource->getUniformTypes()[i];

			if (uniformType == "sampler2D") {
				int samplerSlot = renderingEngine.getSamplerSlot(uniformName);
				material.getTexture(uniformName)->bind(1);
				setUniform1i(uniformName.c_str(), samplerSlot);
				continue;
			}
			else if (util::FileUtils::startsWith(uniformName,"T_")) {
				if (uniformName == ("T_MVP")) {
					setUniformMat4(uniformName.c_str(), MVP);
					continue;
				}
				else if (uniformName == ("T_model")) {
					setUniformMat4(uniformName.c_str(), model);
					continue;
				}
				else {
					 std::cout << "Error: " << uniformName << " is not a valid component of Transform" << std::endl;
				}
			}
			else if (util::FileUtils::startsWith(uniformName,"R_")) {
				std::string uprefixedUniformName = uniformName.substr(2);
				if (uniformType == "vec3") {
					setUniform3f(uniformName.c_str(), renderingEngine.getVec3(uprefixedUniformName));
					continue;
				}
				else if (uniformType == "float") {
					setUniform1f(uniformName.c_str(), renderingEngine.getFloat(uprefixedUniformName));
					continue;
				}
				else if (uniformType == "DirectionalLight") {
					setUniformDirectionalLight(uniformName, *static_cast<components::directionalLight*>(renderingEngine.getActiveLight()));
					continue;
				}
				else if (uniformType == "PointLight") {
					setUniformPointLight(uniformName, *static_cast<components::pointLight*>(renderingEngine.getActiveLight()));
					continue;
				}
				//else if (uniformType == "SpotLight") {
				//	setUniformSpotLight(uniformName, *static_cast<components::spotLight*>(renderingEngine.getActiveLight()));
				//	continue;
				//}
				else {
					//renderingEngine.updateUniformStruct(transform, material, this, uniformName, uniformType);
					continue;
				}
			}
			else if (util::FileUtils::startsWith(uniformName,"C_")) {
				if (uniformName == "C_eyePos") {
					setUniform3f(uniformName.c_str(), renderingEngine.getMainCamera()->getTransform().getTransformedPos());
					continue;
				}
				else {
					util::Logging::Log("Error: " + uniformName + " is not a valid component of Camera", 1);
				}
			}
			else {
				if (uniformType == "vec3") {
					setUniform3f(uniformName.c_str(), material.getVec3(uniformName));
					continue;
				}
				else if (uniformType == "float") {
					setUniform1f(uniformName.c_str(), material.getFloat(uniformName));
					continue;
				}
				else {
					util::Logging::Log("Error: " + uniformName + " is not a supported type in Material", 1);
				}
			}
		}
	}

	void Shader::addAllUniforms(std::string  shaderText, std::string  fileName) {
		std::unordered_map<std::string, std::vector<GLSLVar>> structs = findUniformStructs(shaderText);
		std::string UNIFORM_KEYWORD = "uniform";
		int uniformStartLocation = shaderText.find(UNIFORM_KEYWORD);
		while (uniformStartLocation != -1) {
			if (!(uniformStartLocation != 0 && (shaderText[uniformStartLocation - 1] == ' ' || shaderText[uniformStartLocation - 1] == ';' || shaderText[uniformStartLocation - 1] == '\n') && shaderText[uniformStartLocation + UNIFORM_KEYWORD.length()] == ' ')) {
				uniformStartLocation = util::FileUtils::find(shaderText, UNIFORM_KEYWORD, uniformStartLocation + UNIFORM_KEYWORD.length());
				continue;
			}
			int start = uniformStartLocation + UNIFORM_KEYWORD.length() + 1;
			int end = util::FileUtils::find(shaderText, ";", start);
			std::string uniformLine = util::FileUtils::trim(shaderText.substr(start, end - start));
			int whiteSpacePos = util::FileUtils::find(uniformLine, " ", 0);
			std::string uniformName = util::FileUtils::trim(uniformLine.substr(whiteSpacePos + 1, uniformLine.length()- whiteSpacePos - 1));
			std::string uniformType = util::FileUtils::trim(uniformLine.substr(0, whiteSpacePos));
			if (fileName != "GUI") {
				m_resource->getUniformNames().push_back(uniformName);
				m_resource->getUniformTypes().push_back(uniformType);
			}
			addUniform(uniformName, uniformType, structs);
			uniformStartLocation = util::FileUtils::find(shaderText, UNIFORM_KEYWORD, uniformStartLocation + UNIFORM_KEYWORD.length());
		}
	}

	std::unordered_map<std::string, std::vector<GLSLVar>> Shader::findUniformStructs(std::string shaderText) {
		std::unordered_map<std::string, std::vector<GLSLVar>> result;
		std::string STRUCT_KEYWORD = "struct";
		int structStartLocation = shaderText.find(STRUCT_KEYWORD);
		while (structStartLocation != -1) {
			if (!(structStartLocation != 0 && (shaderText[structStartLocation - 1] == ' ' || shaderText[structStartLocation - 1] == ';') && shaderText[structStartLocation + STRUCT_KEYWORD.length()] == ' ')) {
				structStartLocation = util::FileUtils::find(shaderText , STRUCT_KEYWORD, structStartLocation + STRUCT_KEYWORD.length());
				continue;
			}

			int nameStart = structStartLocation + STRUCT_KEYWORD.length() + 1;
			int braceStart = util::FileUtils::find(shaderText, "{", nameStart);
			int braceEnd = util::FileUtils::find(shaderText, "}", braceStart);
			std::string structName = util::FileUtils::trim(shaderText.substr(nameStart, braceStart- nameStart));
			std::vector<GLSLVar> glslStructs;
			int componentSemicolonPos = util::FileUtils::find(shaderText, ";", braceStart);
			while (componentSemicolonPos != -1 && componentSemicolonPos < braceEnd) {
				int componentNameStart = componentSemicolonPos;
				while (shaderText[componentNameStart - 1] != ' ') {
					componentNameStart--;
				}
				int componentTypeEnd = componentNameStart - 1;
				int componentTypeStart = componentTypeEnd;
				while (shaderText[componentTypeStart - 1] != ' ') {
					componentTypeStart--;
				}
				std::string componentName = shaderText.substr(componentNameStart, componentSemicolonPos- componentNameStart);
				std::string componentType = shaderText.substr(componentTypeStart, componentTypeEnd- componentTypeStart);
				GLSLVar structComponents = GLSLVar(componentName, componentType);
				glslStructs.push_back(structComponents);
				componentSemicolonPos = util::FileUtils::find(shaderText,";", componentSemicolonPos + 1);
			}
			result[structName] = glslStructs;
			structStartLocation = util::FileUtils::find(shaderText, STRUCT_KEYWORD, structStartLocation + STRUCT_KEYWORD.length());
		}
		return result;
	}

	void Shader::addUniform(std::string uniformName, std::string uniformType, std::unordered_map<std::string, std::vector<GLSLVar>> structs) {
		bool primitive = true;
		std::vector<GLSLVar> structComponents;
		auto result = structs.find(uniformType);
		if (result != structs.end()) {
			structComponents = result->second;
			primitive = false;
			for (GLSLVar variables : structComponents) {
				addUniform(uniformName + "." + variables.name, variables.type, structs);
			}
		}

		if (!primitive) {
			return;
		}

		int uniformLocation = glGetUniformLocation(m_resource->getProgram(), uniformName.c_str());

		if (uniformLocation == 0xFFFFFFFF) {
			util::Logging::Log("Error: Uniform " + uniformName + " could not be found", 1);
		}

		m_resource->getUniforms()[uniformName] =  uniformLocation;

	}

	void Shader::setUniformBaseLight(std::string uniformName, components::baseLight baseLight) {
		setUniform4f((uniformName + ".colour").c_str(), baseLight.getColour());
		setUniform1f((uniformName + ".intensity").c_str(), baseLight.getIntensity());
	}

	void Shader::setUniformDirectionalLight(std::string uniformName, components::directionalLight directionalLight) {
		setUniformBaseLight((uniformName + ".base").c_str(), directionalLight);
		setUniform3f((uniformName + ".direction").c_str(), directionalLight.getDirection());

	}

	void Shader::setUniformPointLight(std::string uniformName, components::pointLight pointLight) {
		setUniformBaseLight(uniformName + ".base", pointLight);
		setUniform1f((uniformName + ".atten.constant").c_str(), pointLight.getAttenuation().getConstant());
		setUniform1f((uniformName + ".atten.linear").c_str(), pointLight.getAttenuation().getLinear());
		setUniform1f((uniformName + ".atten.exponent").c_str(), pointLight.getAttenuation().getExponent());
		setUniform3f((uniformName + ".position").c_str(), pointLight.getTransform().getTransformedPos());
		setUniform1f((uniformName + ".range").c_str(), pointLight.getRange());
	}

	//void Shader::setUniformSpotLight(std::string uniformName, components::spotLight spotLight) {
	//	setUniformPointLight(uniformName + ".pointLight", spotLight);
	//	setUniform3f(uniformName + ".direction", spotLight.getDirection());
	//	setUniform1f(uniformName + ".cutoff", spotLight.getCutoff());
	//}

	void Shader::setUniformMat4(const GLchar * name, const maths::mat4 & matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	void Shader::setUniform1f(const GLchar * name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1i(const GLchar * name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar * name, const maths::vec2 & vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const GLchar * name, const maths::vec3 & vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar * name, const maths::vec4 & vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}
} }