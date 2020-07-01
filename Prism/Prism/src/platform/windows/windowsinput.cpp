#include "windowsinput.h"

namespace Prism {

	WindowsInputStrategy::WindowsInputStrategy() {}
	WindowsInputStrategy::~WindowsInputStrategy() {}

	bool WindowsInputStrategy::f_IsKeyPressed(Key k) {
		Application& app = Application::Get();
		auto [a, b] = _prismToGlfwKeyMap.find(k)->second;
		return (glfwGetKey((GLFWwindow*)app.GetNativeWindow(), b) == GLFW_PRESS) ? true : false;
	}

	bool WindowsInputStrategy::f_IsKeyHeld(Key) {
		return false; // TODO: Implement holding
	}

	bool WindowsInputStrategy::f_IsMouseButtonPressed(MouseBtn m) {
		Application& app = Application::Get();
		auto [a, b] = _ptrismToGlfwMouseBtnMap.find(m)->second;
		return (glfwGetMouseButton((GLFWwindow*)app.GetNativeWindow(), b) == GLFW_PRESS) ? true : false;
	}

	std::pair<float, float> WindowsInputStrategy::f_GetMouseCursorPosition() {
		Application& app = Application::Get();
		double x, y;
		glfwGetCursorPos((GLFWwindow*)app.GetNativeWindow(), &x, &y);
		return std::pair<float, float>(x,y);
	}

}