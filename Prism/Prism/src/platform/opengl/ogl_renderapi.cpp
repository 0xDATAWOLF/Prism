#include <platform/opengl/ogl_renderapi.h>
#include <glad/glad.h>

namespace Prism {

	OpenGLRendererAPI::OpenGLRendererAPI() {}
	OpenGLRendererAPI::~OpenGLRendererAPI() {}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& c) {
		glClearColor(c.r, c.g, c.b, c.a);
	}

	void OpenGLRendererAPI::DrawIndexed(std::shared_ptr<VertexArray>& va) {
		glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}

	RendererType OpenGLRendererAPI::GetAPIType() {
		return RendererType::OpenGL;
	}

}