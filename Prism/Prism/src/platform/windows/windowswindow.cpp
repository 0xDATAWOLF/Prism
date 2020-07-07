#include <core/core.h>
#include <core/logger.h>
#include <core/events.h>
#include <platform/windows/windowswindow.h>
#include <platform/opengl/oglcontext.h>

#include <glad/glad.h>

namespace Prism {

	WindowsWindow::WindowsWindow(uint32_t width, uint32_t height, std::string windowTitle) {

		if (!glfwInit()) {
			CORE_ERROR("GLFW was unable to initialize.");
			throw "GLFW was unable to initialize.";
		}

		_glfwWindow = glfwCreateWindow(width, height, windowTitle.c_str(), 0, 0);
		_context = new OpenGLContext(_glfwWindow);
		_context->Init();

		_winData.width = width;
		_winData.height = height;
		_winData.title = windowTitle;
		_winData.callbackfn = std::bind(&WindowsWindow::Send, this, std::placeholders::_1);
		glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &_winData.wScale, &_winData.hScale);
		glfwSetWindowUserPointer(_glfwWindow, &_winData);
		SetVsync(true);

		// Sets the window close callback.
		glfwSetWindowCloseCallback(_glfwWindow, [](GLFWwindow* win) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
			WindowCloseEvent e{};
			windowData.callbackfn(&e);
		});

		// Sets the window resize callback.
		glfwSetWindowSizeCallback(_glfwWindow, [](GLFWwindow* win, int width, int height) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
			WindowResizeEvent e(width, height);
			windowData.callbackfn(&e);
		});

		// Sets the text input callback.
		glfwSetCharCallback(_glfwWindow, [](GLFWwindow* win, uint32_t codepoint) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
			KeyTypedEvent e(codepoint);
			windowData.callbackfn(&e);
		});

		// Sets the key callback.
		glfwSetKeyCallback(_glfwWindow, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
			
			if (key == GLFW_KEY_UNKNOWN) return; // do nothing on unknown key

			if (action == GLFW_PRESS) {
				KeyDownEvent e(key);
				windowData.callbackfn(&e);
				return;
			}

			if (action == GLFW_REPEAT) {
				KeyHeldEvent e(key);
				windowData.callbackfn(&e);
				return;
			}

			if (action == GLFW_RELEASE) {
				KeyReleasedEvent e(key);
				windowData.callbackfn(&e);
				return;
			}

		});

		// Sets the cursor position callback.
		glfwSetCursorPosCallback(_glfwWindow, [](GLFWwindow* win, double xpos, double ypos) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
			MouseMoveEvent e(xpos, ypos);
			windowData.callbackfn(&e);
		});

		// Sets the mouse button callback.
		glfwSetMouseButtonCallback(_glfwWindow, [](GLFWwindow* win, int button, int action, int mods) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);

			if (action == GLFW_PRESS) {
				MouseButtonDownEvent e(button);
				windowData.callbackfn(&e);
				return;
			}

			if (action == GLFW_RELEASE) {
				MouseButtonReleasedEvent e(button);
				windowData.callbackfn(&e);
				return;
			}

		});

		// Sets the mouse scroll callback.
		glfwSetScrollCallback(_glfwWindow, [](GLFWwindow* win, double xpos, double ypos) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
			MouseScrollEvent e(xpos, ypos);
			windowData.callbackfn(&e);
		});

	}

	void WindowsWindow::SetVsync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);
		_winData.vsyncEnabled = enabled;
	}

	void WindowsWindow::Update() {
		glViewport(0, 0, GetWidth(), GetHeight());
		_context->SwapBuffers();
		glfwPollEvents();
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(_glfwWindow);
		glfwTerminate();
	}

}
