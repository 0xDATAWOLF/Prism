#include <core/logger.h>
#include <core/input.h>
#include <platform/windows/windowsinput.h>

namespace Prism {

	Input* Input::_singletonInstance = nullptr;

	Input::Input() {
		#ifdef PRISM_PLATFORM_WINDOWS
			_inputStrategy = new WindowsInputStrategy(); // GLFW -> Prism bindings
		#endif
	}

	Input::~Input() {
		delete _inputStrategy;
	}

}