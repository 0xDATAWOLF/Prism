
#include <core/logger.h>
#include <platform/opengl/ogl_shader.h>
#include <glad/glad.h>
#include <gtc/type_ptr.hpp>

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

	void OpenGLShader::DefineUniformMat3(const std::string& name, const glm::mat3& matrix) {
		int32_t location = glGetUniformLocation(_program, name.c_str());
		if (location == -1) {
			CORE_ERROR("Unable to get uniform location for {}", name);
			return;
		}

		glUniformMatrix3fv(location, 1, 0, glm::value_ptr(matrix));
	}

	void OpenGLShader::DefineUniformMat4(const std::string& name, const glm::mat4& matrix) {
		int32_t location = glGetUniformLocation(_program, name.c_str());
		if (location == -1) {
			CORE_ERROR("Unable to get uniform location for {}", name);
			return;
		}

		glUniformMatrix4fv(location, 1, 0, glm::value_ptr(matrix));
	}

	void OpenGLShader::DefineUniformFloat(const std::string& name, const float f) {
		int32_t location = glGetUniformLocation(_program, name.c_str());
		if (location == -1) {
			CORE_ERROR("Unable to get uniform location for {}", name);
			return;
		}

		glUniform1f(location, f);
	}

	void OpenGLShader::DefineUniformFloat2(const std::string& name, const glm::vec2& v) {
		int32_t location = glGetUniformLocation(_program, name.c_str());
		if (location == -1) {
			CORE_ERROR("Unable to get uniform location for {}", name);
			return;
		}

		glUniform2f(location, v.x, v.y);
	}

	void OpenGLShader::DefineUniformFloat3(const std::string& name, const glm::vec3& v) {
		int32_t location = glGetUniformLocation(_program, name.c_str());
		if (location == -1) {
			CORE_ERROR("Unable to get uniform location for {}", name);
			return;
		}

		glUniform3f(location, v.x, v.y, v.z);

	}

	void OpenGLShader::DefineUniformFloat4(const std::string& name, const glm::vec4& v) {
		int32_t location = glGetUniformLocation(_program, name.c_str());
		if (location == -1) {
			CORE_ERROR("Unable to get uniform location for {}", name);
			return;
		}

		glUniform4f(location, v.x, v.y, v.z, v.w);

	}

    void OpenGLShader::DefineUniformInt(const std::string& name, const int i) {
		int32_t location = glGetUniformLocation(_program, name.c_str());
		if (location == -1) {
			CORE_ERROR("Unable to get uniform location for {}", name);
			return;
		}

		glUniform1i(location, i);
	}

}