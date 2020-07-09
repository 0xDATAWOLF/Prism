#pragma once

namespace Prism {

	// -------------------------------------------------------
	// --- Renderer ------------------------------------------
	// -------------------------------------------------------

	enum class RendererAPI { OpenGL = 0, Vulkan = 1, DirectX12 = 2, Metal = 3 };

	class Renderer {

	public:
		Renderer() {};
		virtual ~Renderer() {};

		static RendererAPI GetRendererAPI() { return RendererAPI::OpenGL; };

	};

}