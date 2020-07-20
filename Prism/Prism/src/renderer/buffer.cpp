#include "renderer/renderer.h"
#include "platform/opengl/ogl_buffer.h"

namespace Prism {

	// -------------------------------------------------------
	// --- Buffer Layout -------------------------------------
	// -------------------------------------------------------

	void BufferLayout::RecalculateLayout() {
		uint32_t offset = 0;
		for (auto& element : _elements) {
			uint32_t size = BufferElement::ElementTypeSize(element.type);
			element.offset = offset;
			_elementStride += size;
			offset += size;
		}
	}

	// -------------------------------------------------------
	// --- Vertex Buffer -------------------------------------
	// -------------------------------------------------------

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
		switch (Renderer::GetRendererType()) {
			case RendererType::OpenGL: return std::make_shared<OpenGLVertexBuffer>(size);
		}

		PRISM_ASSERT(false, "Renderer does not support the given graphics library.");
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size, float* vertices) {
		switch (Renderer::GetRendererType()) {
			case RendererType::OpenGL: return std::make_shared<OpenGLVertexBuffer>(size, vertices);
		}

		PRISM_ASSERT(false, "Renderer does not support the given graphics library.");
	}



	// -------------------------------------------------------
	// --- IndexBuffer ---------------------------------------
	// -------------------------------------------------------

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t size, uint32_t* indices) {
		switch (Renderer::GetRendererType()) {
			case RendererType::OpenGL: return std::make_shared<OpenGLIndexBuffer>(size, indices);
		}

		PRISM_ASSERT(false, "Renderer does not support the given graphics library.");
	}
}
