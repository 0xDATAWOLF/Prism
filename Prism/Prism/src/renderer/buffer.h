#pragma once
#include <vector>
#include <string>

#include "core/core.h"

namespace Prism {

	// -------------------------------------------------------
	// --- Buffer Layout -------------------------------------
	// -------------------------------------------------------

	enum class BufferElementType {
		Float1, Int1, UInt1,
		Float2, Int2, UInt2,
		Float3, Int3, UInt3,
		Float4, Int4, UInt4,
		Matrix3, Matrix4,
		Boolean
	};

	static uint32_t ElementTypeToCount(BufferElementType type) {
		switch (type) {
			case BufferElementType::Float1:		return 1;
			case BufferElementType::Float2:		return 2;
			case BufferElementType::Float3:		return 3;
			case BufferElementType::Float4:		return 4;
			case BufferElementType::Int1:		return 1;
			case BufferElementType::Int2:		return 2;
			case BufferElementType::Int3:		return 3;
			case BufferElementType::Int4:		return 4;
			case BufferElementType::UInt1:		return 1;
			case BufferElementType::UInt2:		return 2;
			case BufferElementType::UInt3:		return 3;
			case BufferElementType::UInt4:		return 4;
			case BufferElementType::Matrix3:	return 3*3;
			case BufferElementType::Matrix4:	return 4*4;
		}

		return 0;
	}

	class BufferElement {

	public:
		inline static uint32_t ElementTypeSize(BufferElementType t)
			{ return ElementTypeToCount(t) * 4; }

	public:
		BufferElement(std::string name, BufferElementType type, bool normalized = false)
			: name(name), type(type), normalized(normalized), count(ElementTypeToCount(type)) {};

		std::string name{ "Vertex Buffer Element" };
		uint32_t count{ 1 };
		BufferElementType type{ BufferElementType::Float1 };
		bool normalized{ false };
		uint32_t offset{ 0 };

	};

	class BufferLayout {
	public:
		BufferLayout() {};
		inline BufferLayout(const std::initializer_list<BufferElement>& e) : _elements(e)
			{ RecalculateLayout(); }
		inline virtual ~BufferLayout() {};

		uint32_t GetStride() const { return _elementStride; };

		std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
		std::vector<BufferElement>::iterator end() { return _elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }

	private:
		void RecalculateLayout();

	private:
		std::vector<BufferElement> _elements;
		uint32_t _elementStride{ 0 };
	};

	// -------------------------------------------------------
	// --- Vertex Buffer -------------------------------------
	// -------------------------------------------------------

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetData(uint32_t size, const void* data) = 0;

		virtual const BufferLayout GetLayout() const = 0;
		virtual void SetLayout(BufferLayout) = 0;

		static Ref<VertexBuffer> Create(uint32_t size, float* data);
		static Ref<VertexBuffer> Create(uint32_t size);
	};

	// -------------------------------------------------------
	// --- IndexBuffer ---------------------------------------
	// -------------------------------------------------------

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetIndexCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t size, uint32_t* data);

	};

}