#include "renderer/vertexarray.h"
#include "renderer/renderer.h"
#include "platform/opengl/ogl_vertexarray.h"

namespace Prism {

	Ref<VertexArray> VertexArray::Create() {

		switch (Renderer::GetRendererType()) {
			case RendererType::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}

		PRISM_ASSERT(false, "Renderer does not support the given graphics library.");

	}

}