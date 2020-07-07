#include <core/core.h>

namespace Prism {

	enum class RendererType {
		OpenGL = 0,
		Vulkan = 1,
		DirectX12 = 2,
		Metal = 3
	};

	class Renderer {

	public:
		static RendererType GetRenderer();

	};

}