#include "core/core.h"
#include "core/logger.h"
#include "platform/windows/windowswindow.h"
#include "platform/windows/windowsinput.h"
#include "platform/opengl/ogl_context.h"

#include <glad/glad.h>

namespace Prism {

	// -------------------------------------------------------
	// --- Callback Definitions ------------------------------
	// -------------------------------------------------------

	void WindowSizeCallback(GLFWwindow* win, int width, int height) {
		WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
		WindowResizeEvent e(width, height);
		windowData.callbackfn(&e);
	}

	void WindowCloseCallback(GLFWwindow* win) {
		WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
		WindowCloseEvent e{};
		windowData.callbackfn(&e);
	}
	
	void WindowCharCallback(GLFWwindow* win, uint32_t codepoint) {
		WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
		KeyTypedEvent e(codepoint);
		windowData.callbackfn(&e);
	}

	void WindowKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods) {
		WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
		if (key == GLFW_KEY_UNKNOWN) return; // do nothing on unknown key
		auto a = std::find_if(WindowsInputInterface::PrismToGLFWKeyBindings.begin(),
			WindowsInputInterface::PrismToGLFWKeyBindings.end(),
			[key](const std::pair<Key, uint32_t>& pair) { return pair.second == key; });

		PRISM_ASSERT(a != WindowsInputInterface::PrismToGLFWKeyBindings.end(), "Unknown key found!");
		Key k = a->first;

		if (action == GLFW_PRESS) {
			KeyDownEvent e(k);
			Input::SetKeyPressed(k);
			windowData.callbackfn(&e);
			return;
		}

		if (action == GLFW_REPEAT) {
			KeyHeldEvent e(k);
			windowData.callbackfn(&e);
			return;
		}

		if (action == GLFW_RELEASE) {
			KeyReleasedEvent e(k);
			windowData.callbackfn(&e);
			return;
		}

	}

	void WindowCursorPosCallback(GLFWwindow* win, double xpos, double ypos) {
		WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
		MouseMoveEvent e(xpos, ypos);
		windowData.callbackfn(&e);
	}

	void WindowMouseButtonCallback(GLFWwindow* win, int button, int action, int mods) {
		WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);

		// Convert the key.
		auto a = std::find_if(WindowsInputInterface::PrismToGLFWMouseBtnBindings.begin(),
			WindowsInputInterface::PrismToGLFWMouseBtnBindings.end(),
			[button](const std::pair<MouseBtn, uint32_t>& pair) { return pair.second == button; });

		PRISM_ASSERT(a != WindowsInputInterface::PrismToGLFWMouseBtnBindings.end(), "Unknown mouse button found!");
		MouseBtn mb = a->first;

		if (action == GLFW_PRESS) {
			MouseButtonDownEvent e(mb);
			Input::SetMouseBtnPressed(mb);
			windowData.callbackfn(&e);
			return;
		}

		if (action == GLFW_RELEASE) {
			MouseButtonReleasedEvent e(mb);
			windowData.callbackfn(&e);
			return;
		}

	}

	void WindowScrollCallback(GLFWwindow* win, double xpos, double ypos) {
		WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
		MouseScrollEvent e(xpos, ypos);
		windowData.callbackfn(&e);
	}

	// -------------------------------------------------------
	// --- Windows Window ------------------------------------
	// -------------------------------------------------------

	WindowsWindow::WindowsWindow(uint32_t width, uint32_t height, std::string windowTitle) {

		if (!glfwInit()) {
			CORE_ERROR("GLFW was unable to initialize.");
			throw "GLFW was unable to initialize.";
		}

		RawWindowPointer = glfwCreateWindow(width, height, windowTitle.c_str(), 0, 0);
		_context = std::make_shared<OpenGLContext>(RawWindowPointer);
		_context->Init();

		WindowDataInstance.width = width;
		WindowDataInstance.height = height;
		WindowDataInstance.title = windowTitle;
		WindowDataInstance.callbackfn = std::bind(&WindowsWindow::Send, this, std::placeholders::_1);
		glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &WindowDataInstance.wScale, &WindowDataInstance.hScale);
		glfwSetWindowUserPointer(RawWindowPointer, &WindowDataInstance);
		SetVsync(true);

		glfwSetWindowCloseCallback(RawWindowPointer, &WindowCloseCallback);
		glfwSetWindowSizeCallback(RawWindowPointer, &WindowSizeCallback);
		glfwSetCharCallback(RawWindowPointer, &WindowCharCallback);
		glfwSetKeyCallback(RawWindowPointer, &WindowKeyCallback);
		glfwSetCursorPosCallback(RawWindowPointer, &WindowCursorPosCallback);
		glfwSetMouseButtonCallback(RawWindowPointer, &WindowMouseButtonCallback);
		glfwSetScrollCallback(RawWindowPointer, &WindowScrollCallback);

	}

	void WindowsWindow::SetVsync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);
		WindowDataInstance.vsyncEnabled = enabled;
	}

	void WindowsWindow::Update() {

		int32_t width, height;
		glfwGetFramebufferSize(RawWindowPointer, &width, &height);
		glViewport(0, 0, width, height);

		_context->SwapBuffers();
		glfwPollEvents();

	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(RawWindowPointer);
		glfwTerminate();
	}

}
