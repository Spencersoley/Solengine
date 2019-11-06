#pragma once

#include <string>
#include <GL/glew.h>

namespace Solengine
{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		
		void LinkShaders();
		
		void AddAttribute(const std::string& attributeName);

		GLuint GetUniformLocation(const std::string& uniformName);

		void Use();
		void Unuse();

	private:
		void compileShader(const std::string& filePath, GLuint id);

		int numAttributes;
		GLuint programID;
		GLuint vertexShaderID;
		GLuint fragmentShaderID;
	};
}