#pragma once
#include <core/renderer/buffer.h>

namespace Prism {

	class OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(float*, uint32_t);
		virtual ~OpenGLVertexBuffer();

		void Bind() const;
		void Unbind() const;

	protected:
		uint32_t _vbo;

	};

	class OpenGLIndexBuffer : public IndexBuffer {

	public:
		OpenGLIndexBuffer(uint32_t*, uint32_t);
		virtual ~OpenGLIndexBuffer();

		void Bind() const;
		void Unbind() const;

	protected:
		uint32_t _ibo;

	};

}