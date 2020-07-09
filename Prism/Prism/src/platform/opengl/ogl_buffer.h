#pragma once
#include <core/renderer/buffer.h>
#include <glad/glad.h>

namespace Prism {

	// -------------------------------------------------------
	// --- OpenGL Vertex Buffer ------------------------------
	// -------------------------------------------------------

	class OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(uint32_t, float*);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		inline virtual const BufferLayout GetLayout() const override { return _bufferLayout; }
		inline virtual void SetLayout(BufferLayout b) override { _bufferLayout = b; }

	private:
		uint32_t _vbo;
		BufferLayout _bufferLayout;

	};

	// -------------------------------------------------------
	// --- OpenGL Index Buffer -------------------------------
	// -------------------------------------------------------

	class OpenGLIndexBuffer : public IndexBuffer {

	public:
		OpenGLIndexBuffer(uint32_t, uint32_t*);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind();
		virtual void Unbind();
		virtual uint32_t GetIndexCount() const { return _count; };

	private:
		uint32_t _ibo { 0 };
		uint32_t _count { 0 };

	};

}