#include <core/renderer/texture.h>
#include <platform/opengl/ogl_texture.h>

namespace Prism {

	// -------------------------------------------------------
	// --- Texture2D -----------------------------------------
	// -------------------------------------------------------

	Texture2D* Texture2D::Create(std::string filepath) { return new OpenGLTexture2D(filepath); }

}