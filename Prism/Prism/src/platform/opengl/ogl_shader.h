#pragma once
#include <vector>
#include <core/renderer/shader.h>

namespace Prism {

	// -------------------------------------------------------
	// --- OpenGL Shader -------------------------------------
	// -------------------------------------------------------

	class OpenGLShader : public Shader {

	public:
		OpenGLShader();
		virtual ~OpenGLShader();

		virtual void AddShaderSource(std::string&, ShaderType) override;
		virtual void CompileShaders() override;
		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void DefineUniformMat3(const std::string&, const glm::mat3&);
		virtual void DefineUniformMat4(const std::string&, const glm::mat4&);
		virtual void DefineUniformFloat(const std::string&, const float);
		virtual void DefineUniformFloat2(const std::string&, const glm::vec2&);
		virtual void DefineUniformFloat3(const std::string&, const glm::vec3&);
		virtual void DefineUniformFloat4(const std::string&, const glm::vec4&);
		virtual void DefineUniformInt(const std::string&, const int);

	private:
		uint32_t _program { 0 };
		std::vector<uint32_t> _shaders;

	};

}