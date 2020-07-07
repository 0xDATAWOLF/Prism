#include <platform/opengl/oglbuffers.h>
#include <glad/glad.h>

namespace Prism {

	// -------------------------------------------------------------------------
	// --- OpenGlVertexBuffer --------------------------------------------------
	// -------------------------------------------------------------------------

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* arr, uint32_t size) {
		glCreateBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, size, arr, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &_vbo);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	}

	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}



	// -------------------------------------------------------------------------
	// --- OpenGLIndexBuffer ---------------------------------------------------
	// -------------------------------------------------------------------------

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* arr, uint32_t size) {
		glCreateBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, arr, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &_ibo);
	}

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	}

	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}