#pragma once
#include <core/core.h>

namespace Prism {

	enum class ShaderType {
		Vertex = 0,
		Pixel = 1
	};

	std::string ShaderTypeToString(ShaderType);

	class Shader {
	public:
		virtual ~Shader() {};
		virtual void AddShaderSource(std::string, ShaderType) = 0;
		virtual void Compile() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Shader* Create();
	};


}