#include "shader.h"
#include "renderingEngine.h"

namespace sparky { namespace graphics {
	std::vector<std::string> Shader::loadedShaderMap;
	std::vector<resource::ShaderResource*> Shader::loadedShaders;


	Shader::Shader(char * fileName, const char * vertexPath, const char * fragPath)
		: m_VertPath(vertexPath), m_FragPath(fragPath), m_FileName(fileName)
	{
		unsigned int pos = std::find(loadedShaderMap.begin(), loadedShaderMap.end(), fileName) - loadedShaderMap.begin();
		if (pos < loadedShaderMap.size()) {
			m_resource = loadedShaders[pos];
			m_resource->addReference();
		}
		else {
			m_resource = new resource::ShaderResource();
			m_resource->init();
			loadedShaderMap.push_back(fileName);
			loadedShaders.push_back(m_resource);
			std::string vertShaderString = importShader(m_VertPath);
			std::string fragShaderString = importShader(m_FragPath);
			if (addVertexShader(vertShaderString) && addFragmentShader(fragShaderString)) {
				compileShader();
			}
			else {
				util::Logging::log_exit("Error: failed shader build",1);
			}

			addAllUniforms(vertShaderString,fileName);
			addAllUniforms(fragShaderString,fileName);
		}
	}

	Shader::~Shader()
	{
		if (m_resource->removeReference()) {
			unsigned int pos = std::find(loadedShaderMap.begin(), loadedShaderMap.end(), m_FileName) - loadedShaderMap.begin();
			if (pos < loadedShaderMap.size()) {
				loadedShaderMap.erase(loadedShaderMap.begin() + pos);
				loadedShaders.erase(loadedShaders.begin() + pos);
			}
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

	std::string Shader::importShader(const char * path)
	{
		const std::string INCLUDE_DIRECTIVE = "#include";
		std::string pre = "./res/shaders/";
		std::string string = util::FileUtils::read_file((pre + path).c_str());
		int i = string.find(INCLUDE_DIRECTIVE);
		while (i != -1) {
			int end = util::FileUtils::find(string, '"', i+ INCLUDE_DIRECTIVE.size() + 2) - i;
			std::string title = util::FileUtils::trim(string.substr(i + INCLUDE_DIRECTIVE.size() + 2, end - INCLUDE_DIRECTIVE.size() - 2));
			string.erase(i, end + 1);
			std::string content = importShader(title.c_str());
			string.insert(i, content);
			i = util::FileUtils::find(string, INCLUDE_DIRECTIVE, i + content.size());
		}
		return string;
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
			std::string  a = (m_VertPath);
			util::Logging::log("ERROR: failed to compile " + a + ":\n" + &error[0] + "\n");
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
			std::string  a = (m_FragPath);
			util::Logging::log("ERROR: failed to compile " + a + ":\n" + &error[0]);
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

	void Shader::updateUniforms(Transform* transform, Material* material, RenderingEngine* renderingEngine, components::camera* camera, components::baseLight* light) {
		mat4 model = transform->getTransformation();
		mat4 MVP = camera->getViewProjection() *  model;
		for (unsigned int i = 0; i < m_resource->getUniformNames().size(); i++) {
			std::string uniformName = m_resource->getUniformNames()[i];
			std::string uniformType = m_resource->getUniformTypes()[i];

			if (uniformType == "sampler2D") {
				if (uniformName == "textures") {
					for (std::unordered_map<std::string, Texture*>::iterator iter = material->textureHashMap.begin(); iter != material->textureHashMap.end(); ++iter)
					{
						int i = atoi(iter->first.c_str());
						material->getTexture(std::to_string(i))->bind(i);
					}
					setUniform1iv("textures", &(material->getGLints())[0], (material->textureHashMap.size()));
				}
				else {
					int samplerSlot = renderingEngine->getSamplerSlot(uniformName);
					material->getTexture(uniformName)->bind(samplerSlot);
					setUniform1i(uniformName.c_str(), samplerSlot);
				}
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
					util::Logging::log_exit("Error: " + uniformName + " is not a valid component of Transform\n",1);
				}
			}
			else if (util::FileUtils::startsWith(uniformName,"R_")) {
				std::string uprefixedUniformName = uniformName.substr(2);
				if (uniformType == "vec3") {
					setUniform3f(uniformName.c_str(), light->getColour() * light->getIntensity());
					continue;
				}
				else if (uniformType == "float") {
					setUniform1f(uniformName.c_str(), renderingEngine->getFloat(uprefixedUniformName));
					continue;
				}
				else if (uniformType == "DirectionalLight") {
					components::directionalLight* a = static_cast<components::directionalLight*>(light);
					setUniformDirectionalLight(uniformName, *a);
					continue;
				}
				else if (uniformType == "PointLight") {
					setUniformPointLight(uniformName, *static_cast<components::pointLight*>(light));
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
					setUniform3f(uniformName.c_str(), camera->getTransform()->getTransformedPos());
					continue;
				}
				else {
					util::Logging::log_exit("Error: " + uniformName + " is not a valid component of Camera", 1);
				}
			}
			else {
				if (uniformType == "vec3") {
					setUniform3f(uniformName.c_str(), material->getVec3(uniformName));
					continue;
				}
				else if (uniformType == "float") {
					float a = material->getFloat(uniformName);
					setUniform1f(uniformName.c_str(), material->getFloat(uniformName));
					continue;
				}
				else {
					util::Logging::log_exit("Error: " + uniformName + " is not a supported type in Material", 1);
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
			int endPos = util::FileUtils::find(uniformLine, "[", 0);
			std::string uniformName;
			if (endPos != -1) {
				uniformName = util::FileUtils::trim(uniformLine.substr(whiteSpacePos + 1, endPos- whiteSpacePos - 1));
			}
			else {
				uniformName = util::FileUtils::trim(uniformLine.substr(whiteSpacePos + 1, uniformLine.length() - whiteSpacePos - 1));
			}
			std::string uniformType = util::FileUtils::trim(uniformLine.substr(0, whiteSpacePos));
			m_resource->getUniformNames().push_back(uniformName);
			m_resource->getUniformTypes().push_back(uniformType);
			addUniform(uniformName, uniformType, structs);
			uniformStartLocation = util::FileUtils::find(shaderText, UNIFORM_KEYWORD, uniformStartLocation + UNIFORM_KEYWORD.length());
		}
	}

	std::unordered_map<std::string, std::vector<GLSLVar>> Shader::findUniformStructs(std::string shaderText) {
		std::unordered_map<std::string, std::vector<GLSLVar>> result;
		std::string STRUCT_KEYWORD = "struct";
		int structStartLocation = shaderText.find(STRUCT_KEYWORD);
		while (structStartLocation != -1) {
			if (!(structStartLocation != 0 && (shaderText[structStartLocation - 1] == ' ' || shaderText[structStartLocation - 1] == ';' || shaderText[structStartLocation - 1] == '\n') && shaderText[structStartLocation + STRUCT_KEYWORD.length()] == ' ')) {
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
				while (shaderText[componentNameStart - 1] != ' ' && shaderText[componentNameStart - 1] != '\n' && shaderText[componentNameStart - 1] != '\t') {
					componentNameStart--;
				}
				int componentTypeEnd = componentNameStart - 1;
				int componentTypeStart = componentTypeEnd;
				while (shaderText[componentTypeStart - 1] != ' ' && shaderText[componentTypeStart - 1] != '\n' && shaderText[componentTypeStart - 1] != '\t') {
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
			util::Logging::log_exit("Error: Uniform " + uniformName + " could not be found", 1);
		}

		m_resource->getUniforms()[uniformName] =  uniformLocation;

	}

	void Shader::setUniformBaseLight(std::string uniformName, components::baseLight baseLight) {
		setUniform3f((uniformName + ".colour").c_str(), baseLight.getColour());
		setUniform1f((uniformName + ".intensity").c_str(), baseLight.getIntensity());
	}

	void Shader::setUniformDirectionalLight(std::string uniformName, components::directionalLight directionalLight) {
		setUniformBaseLight((uniformName + ".base").c_str(), directionalLight);	
		setUniform3f((uniformName + ".direction").c_str(), directionalLight.getDirection());

	}

	void Shader::setUniformPointLight(std::string uniformName, components::pointLight pointLight) {
		setUniformBaseLight(uniformName + ".base", pointLight);
		setUniform1f((uniformName + ".atten.constant").c_str(), pointLight.getAttenuation().m_constant);
		setUniform1f((uniformName + ".atten.linear").c_str(), pointLight.getAttenuation().m_linear);
		setUniform1f((uniformName + ".atten.exponent").c_str(), pointLight.getAttenuation().m_exponent);
		setUniform3f((uniformName + ".position").c_str(), pointLight.getTransform()->getTransformedPos());
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

	void Shader::setUniform1iv(const GLchar* name, int* value, int count)
	{
		glUniform1iv(getUniformLocation(name), count, value);
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