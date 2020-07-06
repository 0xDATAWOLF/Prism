#include <core/logger.h>
#include <platform/opengl/oglcontext.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Prism {

	OpenGLContext::OpenGLContext(GLFWwindow* win) : _window(win) {}
	OpenGLContext::~OpenGLContext() {}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(_window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // TODO: Check for init errors

		CORE_INFO("Using OpenGL:");
		CORE_INFO("    Vendor: {}", glGetString(GL_VENDOR));
		CORE_INFO("    Version: {}", glGetString(GL_VERSION)); 
		CORE_INFO("    Renderer: {}", glGetString(GL_RENDERER)); 
		CORE_INFO("    Shader Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));

	}
	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(_window);
	}

}