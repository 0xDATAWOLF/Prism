#pragma once
#include <memory>

#include "core/core.h"
#include "renderer/buffer.h"

namespace Prism {

	// -------------------------------------------------------
	// --- VertexArray ---------------------------------------
	// -------------------------------------------------------

	class VertexArray {

	public:
		virtual ~VertexArray() {};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer>&) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer>&) = 0;
		virtual const std::vector<Ref<VertexBuffer>> GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer> GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();

	};

}
