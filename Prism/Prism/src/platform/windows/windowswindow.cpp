#include <core/core.h>
#include <core/logger.h>
#include <core/events.h>
#include <platform/windows/windowswindow.h>

#include <glad/glad.h>

namespace Prism {

	/* A dirty flag indicating whether or not GLFW has already been initialized. */
	static bool dflag_GLFWInit{ false };

	WindowsWindow::WindowsWindow(const WindowProperties& winprops) {

		if (dflag_GLFWInit) { // Check if already init'd.
			CORE_WARN("An attempt to initialize GLFW has been made when GLFW has already been initialized. Is this intentional?");
			return; // Break from init.
		}

		dflag_GLFWInit = glfwInit();
		if (!dflag_GLFWInit) { // Check init succeeded.
			CORE_ERROR("GLFW was unable to initialize.");
			throw "GLFW was unable to initialize.";
		}

		_glfwWindow = glfwCreateWindow(winprops.width, winprops.height, winprops.title.c_str(), 0, 0);

		if (_glfwWindow == nullptr) { // Check if window was created.
			dflag_GLFWInit = false; // Flip the dflag.
			CORE_ERROR("GLFW window was unable to be created.");
			Shutdown(); // Shutdown before throwing.
			throw "GLFW window was unable to be created.";
		}

		// Set windata and attach it to the window for fetching later.
		_winData.width = winprops.width;
		_winData.height = winprops.height;
		_winData.title = winprops.title;
		_winData.callbackfn = std::bind(&WindowsWindow::Dispatch, this, std::placeholders::_1); // Bind ISubject::Dispatch as the callbackfn.
		glfwSetWindowUserPointer(_glfwWindow, &_winData);

		glfwMakeContextCurrent(_glfwWindow);
		SetVsync(true); // Enable vsync.

		// Load Glad.
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status) {
			dflag_GLFWInit = false;
			CORE_ERROR("Glad was unable to load the process address.");
			Shutdown();
			throw "Glad was unable to load the process address.";
		}

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
			InputCharEvent e(codepoint);
			windowData.callbackfn(&e);
		});

		// Sets the key callback.
		glfwSetKeyCallback(_glfwWindow, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
			InputKeyEvent e(key, scancode, action, mods);
			windowData.callbackfn(&e);
		});

		// Sets the cursor position callback.
		glfwSetCursorPosCallback(_glfwWindow, [](GLFWwindow* win, double xpos, double ypos) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
			InputMouseMoveEvent e(xpos, ypos);
			windowData.callbackfn(&e);
		});

		// Sets the mouse button callback.
		glfwSetMouseButtonCallback(_glfwWindow, [](GLFWwindow* win, int button, int action, int mods) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
			InputMouseButtonEvent e(button, action, mods);
			windowData.callbackfn(&e);
		});

		// Sets the mouse scroll callback.
		glfwSetScrollCallback(_glfwWindow, [](GLFWwindow* win, double xpos, double ypos) {
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(win);
			InputMouseScrollEvent e(xpos, ypos);
			windowData.callbackfn(&e);
		});

	}

	void WindowsWindow::SetVsync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);
		_winData.vsyncEnabled = enabled;
	}

	void WindowsWindow::Update() {
		glfwSwapBuffers(_glfwWindow);
		glfwPollEvents();
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(_glfwWindow);
		glfwTerminate();
	}

}
