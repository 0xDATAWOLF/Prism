#include <core/renderer/buffer.h>
#include <platform/opengl/oglbuffers.h>

namespace Prism {

	VertexBuffer* VertexBuffer::Create(float* arr, uint32_t size) {
		return new OpenGLVertexBuffer(arr, size);
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* arr, uint32_t size) {
		return new OpenGLIndexBuffer(arr, size);
	}

}