#include <core/renderer/buffer.h>
#include <platform/opengl/oglbuffers.h>

namespace Prism {

	// ---------------------------------------------------------------
	// --- BufferLayoutUtils -----------------------------------------
	// ---------------------------------------------------------------

	namespace BufferLayoutUtils {

		uint32_t GetBufferLayoutSize(BufferLayoutType type) {
			switch (type) {
				case BufferLayoutType::Float1:		return 4;
				case BufferLayoutType::Float2:		return 4 * 2;
				case BufferLayoutType::Float3:		return 4 * 3;
				case BufferLayoutType::Float4:		return 4 * 4;
				case BufferLayoutType::Int1:		return 4;
				case BufferLayoutType::Int2:		return 4 * 2;
				case BufferLayoutType::Int3:		return 4 * 3;
				case BufferLayoutType::Int4:		return 4 * 4;
				case BufferLayoutType::Mat3:		return 4 * 3 * 3;
				case BufferLayoutType::Mat4:		return 4 * 4 * 4;
				case BufferLayoutType::Bool:		return 1;
			}

			PRISM_ASSERT(false, "BufferLayoutSize() defaulted.");
			return 0;

		}

		uint32_t GetComponentCount(BufferLayoutType type) {
			switch (type) {
				case BufferLayoutType::Float1:		return 1;
				case BufferLayoutType::Float2:		return 2;
				case BufferLayoutType::Float3:		return 3;
				case BufferLayoutType::Float4:		return 4;
				case BufferLayoutType::Int1:		return 1;
				case BufferLayoutType::Int2:		return 2;
				case BufferLayoutType::Int3:		return 3;
				case BufferLayoutType::Int4:		return 4;
				case BufferLayoutType::Mat3:		return 3 * 3;
				case BufferLayoutType::Mat4:		return 4 * 4;
				case BufferLayoutType::Bool:		return 1;
			}

			PRISM_ASSERT(false, "GetComponentSize() defaulted.");
			return 0;

		}

	}


	// ---------------------------------------------------------------
	// --- BufferLayoutElement ---------------------------------------
	// ---------------------------------------------------------------

	BufferLayoutElement::BufferLayoutElement(std::string name, BufferLayoutType type, bool norm)
		: name(name),
		  count(BufferLayoutUtils::GetComponentCount(type)),
		  type(type), normalized(norm), offset(0) {}



	// ---------------------------------------------------------------
	// --- BufferLayout ----------------------------------------------
	// ---------------------------------------------------------------

	BufferLayout::BufferLayout(const std::initializer_list<BufferLayoutElement>& elements)
	: _bufferElements(elements) {
		RecalculateElements();
	}

	BufferLayout::~BufferLayout() {}

	void BufferLayout::RecalculateElements() {

		uint32_t offset = 0;
		_bufferElementStride = 0;
		for (auto& element : _bufferElements) {
			uint32_t sz = BufferLayoutUtils::GetBufferLayoutSize(element.type);
			element.offset = offset;
			offset += sz;
			_bufferElementStride += sz;
		}

	}

	void BufferLayout::InsertElement(BufferLayoutElement e) {
		_bufferElements.push_back(e);
		RecalculateElements();
	}

	// ---------------------------------------------------------------
	// --- VertexBuffer ----------------------------------------------
	// ---------------------------------------------------------------

	VertexBuffer* VertexBuffer::Create(float* arr, uint32_t size) {
		return new OpenGLVertexBuffer(arr, size);
	}



	// ---------------------------------------------------------------
	// --- IndexBuffer -----------------------------------------------
	// ---------------------------------------------------------------

	IndexBuffer* IndexBuffer::Create(uint32_t* arr, uint32_t size) {
		return new OpenGLIndexBuffer(arr, size);
	}



}