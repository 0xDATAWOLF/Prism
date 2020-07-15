#pragma once
#include <cstdint>
#include "core/core.h"
#include "renderer/vertexarray.h"

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

		virtual void AddVertexBuffer(Ref<VertexBuffer>&) override;
		virtual void SetIndexBuffer(Ref<IndexBuffer>&) override;
		virtual const std::vector<Ref<VertexBuffer>> GetVertexBuffers() const override;
		virtual const Ref<IndexBuffer> GetIndexBuffer() const override;

	private:
		uint32_t _vao { 0 };
		uint32_t _attribIndex { 0 };

		std::vector<Ref<VertexBuffer>> _vertexBuffers;
		Ref<IndexBuffer> _indexBuffer;

	};

}