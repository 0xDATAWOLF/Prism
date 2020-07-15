#include "core/logger.h"
#include "renderer/renderer.h"
#include "renderer/shader.h"
#include "platform/opengl/ogl_shader.h"

namespace Prism {

	// -------------------------------------------------------
	// --- Shader --------------------------------------------
	// -------------------------------------------------------

	Ref<Shader> Shader::Create(std::string filepath) {
		switch (Renderer::GetRendererType()) {
			case RendererType::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}

		PRISM_ASSERT(false, "Renderer does not support the given graphics library.");
	}
	
	// -------------------------------------------------------
	// --- Shader Library ------------------------------------
	// -------------------------------------------------------

    void ShaderLibrary::Add(std::string filepath) {
		Ref<Shader> shader = Shader::Create(filepath);
		_shaders[shader->GetName()] = shader;
	}

	bool ShaderLibrary::Exists(std::string name) {
		return _shaders.find(name) != _shaders.end();
	}

	Ref<Shader>& ShaderLibrary::Get(std::string name) {
		if (Exists(name)) return _shaders[name];
		else {
			CORE_INFO("Unable to location shader '{}'", name);
			PRISM_ASSERT(false, "Unable to locate shader.");
		}
	}

}