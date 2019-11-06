#include "GLSLProgram.h"

#include <iostream>
#include <vector>
#include <fstream>

#include "ErrorManager.h"

namespace Solengine
{
	GLSLProgram::GLSLProgram() : 
		numAttributes(0), 
		programID(0), 
		vertexShaderID(0), 
		fragmentShaderID(0) 
	{}

	GLSLProgram::~GLSLProgram() {}

	void GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		//Creates shader IDs 
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (vertexShaderID == 0) ErrorManager::FatalError("Vertex shader failed to be created!");
	
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (fragmentShaderID == 0) ErrorManager::FatalError("Fragment shader failed to be created!");

		//Compiles individual shaders
		compileShader(vertexShaderFilePath, vertexShaderID);
		compileShader(fragmentShaderFilePath, fragmentShaderID);
	}

	void GLSLProgram::compileShader(const std::string& filePath, GLuint id)
	{
		//Creates program ID
		programID = glCreateProgram();

		//Reads contents of filePath into fileContents
		std::ifstream shaderFile(filePath);
		if (shaderFile.fail())
		{
			perror(filePath.c_str());
			ErrorManager::FatalError("Failed to open " + filePath);
		}
		//Extracts from shareFile, to line, formatted into fileContents
		std::string fileContents = "";
		std::string tempLine;
		while (std::getline(shaderFile, tempLine))
			fileContents += tempLine + "\n";
		
		shaderFile.close();

		//Creates pointer to fileContents
		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);
		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(id);

			std::printf("%s\n", (&errorLog[0]));
			ErrorManager::FatalError("Shader " + filePath + "failed to compile");
		}
	}

	void GLSLProgram::LinkShaders()
	{
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);

		glLinkProgram(programID);

		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);


			glDeleteProgram(programID);

			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			std::printf("%s\n", &(errorLog[0]));
			ErrorManager::FatalError("Shaders failed to link");
		}

		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	void GLSLProgram::AddAttribute(const std::string& attributeName)
	{
		glBindAttribLocation(programID, numAttributes++, attributeName.c_str());
	}

	GLuint GLSLProgram::GetUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
			ErrorManager::FatalError("Uniform " + uniformName + " not found in shader!");
		
		return location;
	}

	void GLSLProgram::Use()
	{
		glUseProgram(programID);
		for (int i = 0; i < numAttributes; i++)
			glEnableVertexAttribArray(i);
	}

	void GLSLProgram::Unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < numAttributes; i++)
			glDisableVertexAttribArray(i);
	}
}

