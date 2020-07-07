#include <core/logger.h>
#include <platform/opengl/oglshader.h>
#include <glad/glad.h>

namespace Prism {

	OpenGLShader::OpenGLShader() {
		_program = glCreateProgram();
	}

	OpenGLShader::~OpenGLShader() {
		for (uint32_t shader : _shaders) glDeleteShader(shader);
	}

	void OpenGLShader::AddShaderSource(std::string src, ShaderType type) {

		uint32_t shader = GenerateShader(type);
		if (shader == 0) {
			CORE_INFO("{} Shader failed to generate.", ShaderTypeToString(type));
			return;
		}

		const char* source = (const GLchar*)src.c_str();
		glShaderSource(shader, 1, &source, 0);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
			CORE_INFO("{} Shader failed to compile:\n{}", ShaderTypeToString(type), infoLog.data());
			glDeleteShader(shader);
			return;
		}

		_shaders.push_back(shader);

	}

	void OpenGLShader::Compile() {
		for (uint32_t shader : _shaders) glAttachShader(_program, shader);
		glLinkProgram(_program);

		GLint isLinked = 0;
		glGetProgramiv(_program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {

			GLint maxLength = 0;
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_program, maxLength, &maxLength, &infoLog[0]);
			CORE_INFO("Shader program failed to link & compile:\n{}", infoLog.data());

			glDeleteProgram(_program);
			for (uint32_t shader : _shaders) glDeleteShader(shader);

			return;
		}

		for (uint32_t shader : _shaders) glDetachShader(_program, shader);

	}

	void OpenGLShader::Bind() {
		glUseProgram(_program);
	}

	void OpenGLShader::Unbind() {
		glUseProgram(0);
	}

	uint32_t OpenGLShader::GenerateShader(ShaderType type) {
		switch(type) {
			case ShaderType::Vertex:
				return glCreateShader(GL_VERTEX_SHADER);
			case ShaderType::Pixel:
				return glCreateShader(GL_FRAGMENT_SHADER);
			default:
				return 0; // non-zero val is invalid shader for opengl
		}
	}

}