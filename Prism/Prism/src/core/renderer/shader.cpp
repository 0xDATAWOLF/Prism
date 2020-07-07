#include <core/renderer/renderer.h>
#include <core/renderer/shader.h>

#include <platform/opengl/oglshader.h>

namespace Prism {

	Shader* Shader::Create() {
		return new OpenGLShader();
	}

	std::string ShaderTypeToString(ShaderType type) {
		switch (type) {
			case ShaderType::Vertex:
				return "VERTEX";
			case ShaderType::Pixel:
				return "PIXEL";
			default:
				return "UNKNOWN";
		}
	}

}