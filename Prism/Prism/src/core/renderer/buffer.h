#pragma once
#include <core/core.h>

namespace Prism {

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		static VertexBuffer* Create(uint32_t, float*);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		static IndexBuffer* Create(uint32_t, uint32_t*);
	};

}