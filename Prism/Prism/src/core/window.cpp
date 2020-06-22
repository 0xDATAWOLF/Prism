#include <core/logger.h>
#include <core/window.h>


#ifdef PRISM_PLATFORM_WINDOWS
	#include <platform/windows/windowswindow.h>
#endif

namespace Prism {

	std::unique_ptr<Window> Window::Create(const WindowProperties& winprops) {

		#ifdef PRISM_PLATFORM_WINDOWS
		return std::make_unique<WindowsWindow>(winprops);
		#endif

	}

}