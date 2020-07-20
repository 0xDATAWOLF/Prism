#include "platform/opengl/ogl_renderapi.h"
#include <glad/glad.h>

namespace Prism {

	// -------------------------------------------------------
	// --- OpenGL Renderer API -------------------------------
	// -------------------------------------------------------

	OpenGLRendererInterface::OpenGLRendererInterface() {}
	OpenGLRendererInterface::~OpenGLRendererInterface() {}

	void OpenGLRendererInterface::Init() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererInterface::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererInterface::SetClearColor(const glm::vec4& c) {
		glClearColor(c.r, c.g, c.b, c.a);
	}

	void OpenGLRendererInterface::DrawIndexed(Ref<VertexArray>& va, uint32_t count) {
		auto c = (count) ? count : va->GetIndexBuffer()->GetIndexCount();
		glDrawElements(GL_TRIANGLES, c, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0); // unbind texture
	}

	RendererType OpenGLRendererInterface::GetAPIType() {
		return RendererType::OpenGL;
	}

}