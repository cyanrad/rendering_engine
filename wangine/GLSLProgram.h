#pragma once
#include <string>
#include <GL/glew.h>

namespace wangine {

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		//this will contain the shaders and compileShader fucntoin
		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);

		//this is where we combine thme into one program
		void linkShaders();

		void addAttribute(const std::string& attributeName);

		void use();
		void unuse();

		GLint getUniformLocation(const std::string& uniformName);
	private:
		//this does the actual compilation
		void compileShader(const std::string& filePath, GLuint id);

		int _numAttributes;

		GLuint _programID;

		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};
}

