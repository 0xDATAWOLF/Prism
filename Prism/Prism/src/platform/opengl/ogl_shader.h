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

		virtual void DefineUniformMat4(const std::string&, const glm::mat4&) override;

	private:
		uint32_t _program { 0 };
		std::vector<uint32_t> _shaders;

	};

}