#include <core/renderer/buffer.h>
#include <platform/opengl/oglbuffers.h>

namespace Prism {

	VertexBuffer* VertexBuffer::Create(uint32_t size, float* arr) {
		return new OpenGLVertexBuffer(size, arr);
	}

	IndexBuffer* IndexBuffer::Create(uint32_t size, uint32_t* arr) {
		return new OpenGLIndexBuffer(size, arr);
	}

}