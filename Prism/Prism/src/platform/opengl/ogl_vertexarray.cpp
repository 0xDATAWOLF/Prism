#include "platform/opengl/ogl_vertexarray.h"

#include <glad/glad.h>

namespace Prism {

	static GLenum ElementTypeToOGLType(BufferElementType type) {
		switch (type) {
			case BufferElementType::Float1:		return GL_FLOAT;
			case BufferElementType::Float2:		return GL_FLOAT;
			case BufferElementType::Float3:		return GL_FLOAT;
			case BufferElementType::Float4:		return GL_FLOAT;
			case BufferElementType::Int1:		return GL_INT;
			case BufferElementType::Int2:		return GL_INT;
			case BufferElementType::Int3:		return GL_INT;
			case BufferElementType::Int4:		return GL_INT;
			case BufferElementType::UInt1:		return GL_UNSIGNED_INT;
			case BufferElementType::UInt2:		return GL_UNSIGNED_INT;
			case BufferElementType::UInt3:		return GL_UNSIGNED_INT;
			case BufferElementType::UInt4:		return GL_UNSIGNED_INT;
			case BufferElementType::Matrix3:	return GL_FLOAT;
			case BufferElementType::Matrix4:	return GL_FLOAT;
		}

		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &_vao);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &_vao); _vao = 0;
	}

	void OpenGLVertexArray::Bind() {
		glBindVertexArray(_vao);
	}

	void OpenGLVertexArray::Unbind() {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(Prism::Ref<VertexBuffer>& vb) {
		glBindVertexArray(_vao);
		vb->Bind();

		const BufferLayout& layout = vb->GetLayout();
		for (const auto& e : layout) {
			glEnableVertexAttribArray(_attribIndex);
			glVertexAttribPointer(_attribIndex,
				e.count,
				ElementTypeToOGLType(e.type),
				e.normalized,
				layout.GetStride(),
				(const void*)e.offset);
			_attribIndex++;
		}

		_vertexBuffers.push_back(vb);
	}

	void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer>& e) {
		glBindVertexArray(_vao);
		e->Bind();
		_indexBuffer = e;
	}

	const std::vector<Ref<VertexBuffer>> OpenGLVertexArray::GetVertexBuffers() const {
		return _vertexBuffers;
	}

	const Ref<IndexBuffer> OpenGLVertexArray::GetIndexBuffer() const {
		return _indexBuffer;
	}

}