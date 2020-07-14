#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

#include "core/core.h"
#include "core/logger.h"
#include "platform/opengl/ogl_shader.h"

#include <glad/glad.h>
#include <gtc/type_ptr.hpp>

namespace Prism {

	static GLenum ShaderTypeToOpenGLShaderEnum(ShaderType t) {
		switch (t) {
			case ShaderType::Null: return 0;
			case ShaderType::Vertex: return GL_VERTEX_SHADER;
			case ShaderType::Pixel: return GL_FRAGMENT_SHADER;
		}
		PRISM_ASSERT(false, "Default condition, undefined type.");
		return 0;
	}

	static std::string ShaderTypeToString(ShaderType t) {
		switch (t) {
			case ShaderType::Null: return "null";
			case ShaderType::Vertex: return "vertex";
			case ShaderType::Pixel: return "pixel";
		}

		return "";
		PRISM_ASSERT(false, "Default condition, undefined type.");
	}

	static ShaderType StringToShaderType(std::string s) {
		if (s == "vertex") return ShaderType::Vertex;
		if (s == "fragment" || s == "pixel") return ShaderType::Pixel;
		return ShaderType::Null;
	}



	// -------------------------------------------------------
	// --- OpenGL Shader -------------------------------------
	// -------------------------------------------------------

	OpenGLShader::OpenGLShader(std::string& filepath) {
		_program = glCreateProgram();
		_shadername = std::filesystem::path(filepath).stem().string();
		std::string src = ReadSourceFile(filepath);
		PrecompileShader(src);

	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(_program);
	}

	std::string OpenGLShader::ReadSourceFile(std::string& filepath) {

		if (!std::filesystem::exists(filepath)) {
			CORE_INFO("Filepath '{}' was not found.", filepath);
			PRISM_ASSERT(false, "Shader file was not found.");
		}

		auto filecontents = std::fstream(filepath, std::ios::binary | std::ios::in);
		if (!filecontents.is_open()) {
			CORE_INFO("Filepath '{}' was not able to be opened.", filepath);
			PRISM_ASSERT(false, "Shader file was not opened.");
		}

		filecontents.seekg(0, std::ios::end);
		size_t size = filecontents.tellg();
		std::string source(size, ' ');
		filecontents.seekg(0);
		filecontents.read(&source[0], size);
		return source;

	}

	void OpenGLShader::PrecompileShader(std::string& source) {

		const char* typeToken = "#shader";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			PRISM_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			ShaderType type = StringToShaderType(source.substr(begin, eol - begin));
			if (type == ShaderType::Null) PRISM_ASSERT(false, "Unknown type");
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			AddShaderSource(
				source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos)),
				type);
		}

		CompileShaders();

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