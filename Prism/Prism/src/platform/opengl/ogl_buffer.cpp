#include "platform/opengl/ogl_buffer.h"

#include <glad/glad.h>

namespace Prism {

	// -------------------------------------------------------
	// --- OpenGL Vertex Buffer ------------------------------
	// -------------------------------------------------------

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
		glCreateBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size, float* vertices) {
		glCreateBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &_vbo);
	}

	void OpenGLVertexBuffer::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	}

	void OpenGLVertexBuffer::Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

    void OpenGLVertexBuffer::SetData(uint32_t size, const void* data) {
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}


	// -------------------------------------------------------
	// --- OpenGL Index Buffer -------------------------------
	// -------------------------------------------------------

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t size, uint32_t* indices) {
		glCreateBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
		_count = size / (sizeof(uint32_t));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &_ibo);
	}

	void OpenGLIndexBuffer::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	}

	void OpenGLIndexBuffer::Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
