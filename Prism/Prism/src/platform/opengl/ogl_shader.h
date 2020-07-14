#pragma once
#include <vector>

#include "renderer/shader.h"

#include <glm.hpp>


namespace Prism {

	// -------------------------------------------------------
	// --- OpenGL Shader -------------------------------------
	// -------------------------------------------------------

	class OpenGLShader : public Shader {

	public:
		OpenGLShader(std::string& filepath);
		virtual ~OpenGLShader();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual std::string GetName() const override { return _shadername; };

		virtual void DefineUniformMat3(const std::string&, const glm::mat3&);
		virtual void DefineUniformMat4(const std::string&, const glm::mat4&);
		virtual void DefineUniformFloat(const std::string&, const float);
		virtual void DefineUniformFloat2(const std::string&, const glm::vec2&);
		virtual void DefineUniformFloat3(const std::string&, const glm::vec3&);
		virtual void DefineUniformFloat4(const std::string&, const glm::vec4&);
		virtual void DefineUniformInt(const std::string&, const int);

	private:
		std::string ReadSourceFile(std::string&);
		void PrecompileShader(std::string&);
		void AddShaderSource(std::string&, ShaderType);
		void CompileShaders();

	private:
		uint32_t _program { 0 };
		std::vector<uint32_t> _shaders;
		std::string _shadername{ "null" };

	};

}