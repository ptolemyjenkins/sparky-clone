#pragma once
#include <GL\glew.h>
#include <vector>
#include <iostream>
#include "../ResourceManagment/ShaderResource.h"
#include "../util/fileutils.h"

#include "../graphics/constructs/transform.h"
#include "material.h"



namespace sparky { 
	namespace components {
		class pointLight;
		class baseLight;
		class directionalLight;
		class camera;
	}
	namespace graphics {

	class RenderingEngine;
	
	struct GLSLVar {
		std::string name;
		std::string  type;

		GLSLVar(std::string  name, std::string type) {
			this->name = name;
			this->type = type;
		}
	};

	class Shader
	{
	private:
		static std::unordered_map<std::string, resource::ShaderResource> loadedShaders;

		resource::ShaderResource m_resource;
		const char *m_VertPath, *m_FragPath;
		char *m_FileName;
	public:
		Shader() {};
		Shader( char * fileName, const char* vertexPath, const char* fragPath);
		~Shader();


		void setUniformMat4(const GLchar* name, const maths::mat4& matrix);
		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform2f(const GLchar* name, const maths::vec2& vector);
		void setUniform3f(const GLchar* name, const maths::vec3& vector);
		void setUniform4f(const GLchar* name, const maths::vec4& vector);

		void bind();
		void disable() const;

		void updateUniforms(Transform transform, Material material, RenderingEngine renderingEngine);
	private:
		GLint getUniformLocation(const GLchar* name);
		GLuint load();
		bool addVertexShader();
		bool addFragmentShader();
		void compileShader();

		void addAllUniforms(std::string shaderText, std::string fileName);
		std::unordered_map<std::string, std::vector<GLSLVar>> findUniformStructs(std::string shaderText);

		void addUniform(std::string uniformName, std::string uniformType, std::unordered_map<std::string, std::vector<GLSLVar>> structs);

		void setUniformBaseLight(std::string uniformName, components::baseLight baseLight);
		void setUniformDirectionalLight(std::string uniformName, components::directionalLight directionalLight);
		void setUniformPointLight(std::string uniformName, components::pointLight pointLight);
	};

} }