
#include <core/logger.h>
#include <platform/opengl/ogl_shader.h>
#include <glad/glad.h>

namespace Prism {

	static GLenum ShaderTypeToOpenGLShaderEnum(ShaderType t) {
		switch (t) {
			case ShaderType::Vertex: return GL_VERTEX_SHADER;
			case ShaderType::Pixel: return GL_FRAGMENT_SHADER;
		}
	}

	static std::string ShaderTypeToString(ShaderType t) {
		switch (t) {
			case ShaderType::Vertex: return "Vertex";
			case ShaderType::Pixel: return "Pixel";
		}
	}

	OpenGLShader::OpenGLShader() {
		_program = glCreateProgram();
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(_program);
	}

	void OpenGLShader::AddShaderSource(std::string& source, ShaderType type) {

		uint32_t shader = glCreateShader(ShaderTypeToOpenGLShaderEnum(type));

		const GLchar* s = (const GLchar*)source.c_str();
		glShaderSource(shader, 1, &s, 0);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(shader);
			CORE_ERROR("{} Shader failed to compile:\n{}", ShaderTypeToString(type), infoLog.data());
			return;
		}

		_shaders.push_back(shader);

	}

	void OpenGLShader::CompileShaders() {

		if (_shaders.size() == 0) {
			PRISM_ERROR("Unable to link because there are no compiled shaders attached to the program.");
			return;
		}

		for (auto& a : _shaders) {
			glAttachShader(_program, a);
		}

		glLinkProgram(_program);

		GLint isLinked = 0;
		glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);
			if (maxLength > 0) {
				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(_program, maxLength, &maxLength, &infoLog[0]);
				PRISM_ERROR("Program failed to link:\n{}", infoLog.data());
			}
			else {
				PRISM_ERROR("InfoLog length is 0!");
			}
			glDeleteProgram(_program);

			return;
		}

	}

	void OpenGLShader::Bind() {
		glUseProgram(_program);
	}

	void OpenGLShader::Unbind() {
		glUseProgram(_program);
	}

}