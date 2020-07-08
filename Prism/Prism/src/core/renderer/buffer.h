#pragma once
#include <core/core.h>

namespace Prism {


	// ------------------------------------------------------------
	// --- BufferLayout -------------------------------------------
	// ------------------------------------------------------------

	enum class BufferLayoutType {
		Float1, Int1,
		Float2, Int2,
		Float3, Int3,
		Float4, Int4,
		Mat3, Mat4,
		Bool
	};

	namespace BufferLayoutUtils {
		uint32_t GetBufferLayoutSize(BufferLayoutType);
		uint32_t GetComponentCount(BufferLayoutType);
	}

	struct BufferLayoutElement {
		BufferLayoutElement() {};
		BufferLayoutElement(std::string name, BufferLayoutType, bool = false);

		std::string			name = "default";
		uint32_t			count = 1;
		BufferLayoutType	type = BufferLayoutType::Float1;
		bool				normalized = false;
		uint32_t			offset = 0;
	};

	class BufferLayout {
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferLayoutElement>&);
		virtual ~BufferLayout();

		void InsertElement(BufferLayoutElement);
		uint32_t GetStride() const { return _bufferElementStride; }

		std::vector<BufferLayoutElement>::iterator begin() { return _bufferElements.begin(); }
		std::vector<BufferLayoutElement>::iterator end() { return _bufferElements.end(); }
		std::vector<BufferLayoutElement>::const_iterator begin() const { return _bufferElements.begin(); }
		std::vector<BufferLayoutElement>::const_iterator end() const { return _bufferElements.end(); }

	protected:
		void RecalculateElements();

		std::vector<BufferLayoutElement> _bufferElements;
		uint32_t _bufferElementStride{ 0 };

	};



	// ------------------------------------------------------------
	// --- VertexBuffer -------------------------------------------
	// ------------------------------------------------------------

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float*, uint32_t);
	};



	// ------------------------------------------------------------
	// --- IndexBuffer --------------------------------------------
	// ------------------------------------------------------------

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;


		static IndexBuffer* Create(uint32_t*, uint32_t);
	};

}