#include "application.h"
#include <GLFW/glfw3.h>

namespace Prism {

	Application::Application() {
        CORE_INFO("Prism Engine initializing startup.");
        
        GLFWwindow* window;

        if (!glfwInit()) {
            CORE_ERROR("Unable to initialize GLFW");
        }

        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window) {
            glfwTerminate();
            CORE_ERROR("Unable to initialize GLFW window.");
        }

        glfwMakeContextCurrent(window);

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        
    };

	Application::~Application() {
        
    };

	void Application::Run() {
		while (true);
	}

}
