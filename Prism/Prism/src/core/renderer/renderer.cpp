#include <core/renderer/renderer.h>
#include <platform/opengl/ogl_renderapi.h>

namespace Prism {

	// -------------------------------------------------------
	// --- Renderer ------------------------------------------
	// -------------------------------------------------------

	void Renderer::Submit(std::shared_ptr<VertexArray>& v) {
		v->Bind();
		RendererCommand::DrawIndexed(v);
	};

	// -------------------------------------------------------
	// --- RendererCommand -----------------------------------
	// -------------------------------------------------------

	RendererAPI* RendererCommand::_api = new OpenGLRendererAPI();

}