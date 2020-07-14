#include "core/core.h"
#include "core/logger.h"
#include "renderer/shader.h"
#include "platform/opengl/ogl_shader.h"

namespace Prism {

	// -------------------------------------------------------
	// --- Shader --------------------------------------------
	// -------------------------------------------------------

	Shader* Shader::Create(std::string filepath) {
		return new OpenGLShader(filepath);
	}
	
	// -------------------------------------------------------
	// --- Shader Library ------------------------------------
	// -------------------------------------------------------

    void ShaderLibrary::Add(std::string filepath) {
		std::shared_ptr<Shader> shader;
		shader.reset(Shader::Create(filepath));
		_shaders[shader->GetName()] = shader;
	}

	bool ShaderLibrary::Exists(std::string name) {
		return _shaders.find(name) != _shaders.end();
	}

	std::shared_ptr<Shader>& ShaderLibrary::Get(std::string name) {
		if (Exists(name)) return _shaders[name];
		else {
			CORE_INFO("Unable to location shader '{}'", name);
			PRISM_ASSERT(false, "Unable to locate shader.");
		}
	}

}