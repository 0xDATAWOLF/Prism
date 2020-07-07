#include <core/logger.h>
#include <core/window.h>


#ifdef PRISM_PLATFORM_WINDOWS
	#include <platform/windows/windowswindow.h>
#endif

namespace Prism {

	std::unique_ptr<Window> Window::Create(uint32_t width, uint32_t height, std::string windowTitle) {

		#ifdef PRISM_PLATFORM_WINDOWS
		return std::make_unique<WindowsWindow>(width, height, windowTitle);
		#endif

	}

}