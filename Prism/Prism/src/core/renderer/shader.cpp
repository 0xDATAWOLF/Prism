#include <core/renderer/shader.h>
#include <platform/opengl/ogl_shader.h>

namespace Prism {

	// -------------------------------------------------------
	// --- Shader --------------------------------------------
	// -------------------------------------------------------

	Shader* Shader::Create() {
		return new OpenGLShader();
	}

}