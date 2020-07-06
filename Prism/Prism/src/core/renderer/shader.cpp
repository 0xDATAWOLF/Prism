#include <core/renderer/shader.h>
#include <glad/glad.h>
#include <core/logger.h>

namespace Prism {

	Shader::Shader(std::string vertexSource, std::string fragmentSource) {

		uint32_t _vShader;
		uint32_t _fShader;

		// Create an empty vertex shader handle
		_vShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSource.c_str();
		glShaderSource(_vShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(_vShader);

		GLint isCompiled = 0;
		glGetShaderiv(_vShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(_vShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(_vShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(_vShader);

			// Use the infoLog as you see fit.
			CORE_INFO("Vertex shader compilation failed:\n {}", infoLog.data());

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		_fShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(_fShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(_fShader);

		glGetShaderiv(_fShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(_fShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(_fShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(_fShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(_vShader);

			// Use the infoLog as you see fit.
			CORE_INFO("Fragment shader compilation failed:\n {}", infoLog.data());

			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		_prog = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(_prog, _vShader);
		glAttachShader(_prog, _fShader);

		// Link our program
		glLinkProgram(_prog);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_prog, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(_prog, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_prog, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_prog);
			// Don't leak shaders either.
			glDeleteShader(_vShader);
			glDeleteShader(_fShader);

			// Use the infoLog as you see fit.
			CORE_INFO("Shader program linking failed:\n {}", infoLog.data());

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(_prog, _vShader);
		glDetachShader(_prog, _fShader);
	}

	Shader::~Shader() {
		glDeleteProgram(_prog);
	}

	void Shader::Bind() {
		glUseProgram(_prog);
	}

	void Shader::Unbind() {
		glUseProgram(0);
	}

}