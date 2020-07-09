#pragma once
#include <cstdint>
#include <core/renderer/vertexarray.h>

namespace Prism {

	// -------------------------------------------------------
	// --- OpenGLVertexArray ---------------------------------
	// -------------------------------------------------------

	class OpenGLVertexArray : public VertexArray {

	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>&) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>&) override;
		virtual const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override;
		virtual const std::shared_ptr<IndexBuffer> GetIndexBuffer() const override;

	private:
		uint32_t _vao { 0 };
		uint32_t _attribIndex { 0 };

		std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
		std::shared_ptr<IndexBuffer> _indexBuffer;

	};

}