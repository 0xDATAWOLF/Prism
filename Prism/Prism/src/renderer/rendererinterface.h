#pragma once
#include "renderer/vertexarray.h"

#include <glm.hpp>

namespace Prism {

	enum class RendererType { OpenGL = 0, Vulkan = 1, DirectX12 = 2, Metal = 3 };

	// -------------------------------------------------------
	// --- RendererAPI ---------------------------------------
	// -------------------------------------------------------

	class BaseRendererInterface { // Interface class
	public:
		virtual ~BaseRendererInterface() {};
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4&) = 0;
		virtual void DrawIndexed(Ref<VertexArray>&, uint32_t count) = 0;
		virtual void Init() = 0;
		virtual RendererType GetAPIType() = 0;

	};

}