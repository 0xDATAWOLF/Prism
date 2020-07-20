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

		virtual void SetMat3(const std::string& s, const glm::mat3 v) { DefineUniformMat3(s,v); }
		virtual void SetMat4(const std::string& s, const glm::mat4 v) { DefineUniformMat4(s,v); };
		virtual void SetFloat(const std::string& s, const float v) { DefineUniformFloat(s,v); };
		virtual void SetFloat2(const std::string& s, const glm::vec2 v) { DefineUniformFloat2(s,v); };
		virtual void SetFloat3(const std::string& s, const glm::vec3 v) { DefineUniformFloat3(s,v); };
		virtual void SetFloat4(const std::string& s, const glm::vec4 v) { DefineUniformFloat4(s,v); };
		virtual void SetIntArray(const std::string& s, uint32_t count, void* data) { DefineUniformIntArray(s, count, data); }
		virtual void SetInt(const std::string& s, const int v) { DefineUniformInt(s,v); };

		void DefineUniformMat3(const std::string&, const glm::mat3&);
		void DefineUniformMat4(const std::string&, const glm::mat4&);
		void DefineUniformIntArray(const std::string& s, uint32_t count, void* data);
		void DefineUniformInt(const std::string&, const int);
		void DefineUniformFloat(const std::string&, const float);
		void DefineUniformFloat2(const std::string&, const glm::vec2&);
		void DefineUniformFloat3(const std::string&, const glm::vec3&);
		void DefineUniformFloat4(const std::string&, const glm::vec4&);

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