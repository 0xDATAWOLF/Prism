#include "renderer/texture.h"
#include "renderer/renderer.h"
#include "platform/opengl/ogl_texture.h"

namespace Prism {

	// -------------------------------------------------------
	// --- Texture2D -----------------------------------------
	// -------------------------------------------------------

	Ref<Texture2D> Texture2D::Create(std::string filepath) { 
		switch (Renderer::GetRendererType()) {
			case RendererType::OpenGL: return std::make_shared<OpenGLTexture2D>(filepath);
		}

		PRISM_ASSERT(false, "Renderer does not support the given graphics library.");
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetRendererType()) {
			case RendererType::OpenGL: return std::make_shared<OpenGLTexture2D>(width, height);
		}

		PRISM_ASSERT(false, "Renderer does not support the given graphics library.");
	}


}