#include <core/renderer/buffer.h>
#include <platform/opengl/ogl_buffer.h>

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

	VertexBuffer* VertexBuffer::Create(uint32_t size, float* vertices) {
		return new OpenGLVertexBuffer(size, vertices);
	}

	// -------------------------------------------------------
	// --- IndexBuffer ---------------------------------------
	// -------------------------------------------------------

	IndexBuffer* IndexBuffer::Create(uint32_t size, uint32_t* indices) {
		return new OpenGLIndexBuffer(size, indices);
	}
}
