#pragma once
#include <string>
#include <glm.hpp>

namespace Prism {

	// -------------------------------------------------------
	// --- Shader --------------------------------------------
	// -------------------------------------------------------

	enum class ShaderType { Vertex, Pixel };

	class Shader {

	public:
		virtual ~Shader() {};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddShaderSource(std::string&, ShaderType) = 0;
		virtual void CompileShaders() = 0;

		static Shader* Create();

	};

}