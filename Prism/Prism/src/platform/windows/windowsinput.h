#pragma once
#include <map>
#include <core/input.h>
#include <GLFW/glfw3.h>


namespace Prism {

	class WindowsInputInterface : public InputInterface {

	public:
		virtual void ValidateHoldStates() override;

		static const std::map<Key, uint32_t> PrismToGLFWKeyBindings;
		static const std::map<MouseBtn, uint32_t> PrismToGLFWMouseBtnBindings;

	};

}