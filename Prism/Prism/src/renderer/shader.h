#pragma once
#include <unordered_map>
#include <memory>
#include <string>

#include "core/core.h"

#include "glm.hpp"

namespace Prism {

	// -------------------------------------------------------
	// --- Shader --------------------------------------------
	// -------------------------------------------------------

	enum class ShaderType { Null = 0, Vertex, Pixel };

	class Shader {

	public:
		virtual ~Shader() {};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual std::string GetName() const = 0;

		virtual void SetMat3(const std::string&, const glm::mat3) = 0;
		virtual void SetMat4(const std::string&, const glm::mat4) = 0;
		virtual void SetInt(const std::string&, const int) = 0;
		virtual void SetIntArray(const std::string&, uint32_t, void*) = 0;
		virtual void SetFloat(const std::string&, const float) = 0;
		virtual void SetFloat2(const std::string&, const glm::vec2) = 0;
		virtual void SetFloat3(const std::string&, const glm::vec3) = 0;
		virtual void SetFloat4(const std::string&, const glm::vec4) = 0;

		static Ref<Shader> Create(std::string filepath);

	};

	// -------------------------------------------------------
	// --- Shader Library ------------------------------------
	// -------------------------------------------------------

	class ShaderLibrary {

	public:
		virtual ~ShaderLibrary() {};

		void Add(std::string filepath);
		bool Exists(std::string name);
		Ref<Shader>& Get(std::string name);
	
	private:
		std::unordered_map<std::string, Ref<Shader>> _shaders;

	};

}