#pragma once
#include <GL\glew.h>
#include <unordered_map>
#include <vector>
namespace sparky { namespace resource {
		class ShaderResource {
		private:
			GLuint m_ShaderID;
			int refCount;

			std::unordered_map<std::string, int> uniforms;
			std::vector<std::string> uniformNames;
			std::vector<std::string> uniformTypes;
		public:
			ShaderResource();
			void init();
			~ShaderResource();

			void addReference();
			bool removeReference();

			GLuint& getProgram();
			std::unordered_map<std::string, int>& getUniforms();
			std::vector<std::string>& getUniformNames();
			std::vector<std::string>& getUniformTypes();

		};
} }