#pragma once
#include "core/logger.h"
#include "renderer/graphicscontext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

struct GLFWwindow;

namespace Prism {

	// -------------------------------------------------------
	// --- OpenGLContext -------------------------------------
	// -------------------------------------------------------

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow*);
		virtual ~OpenGLContext();

		void Init() override;
		void SwapBuffers() override;

	protected:
		GLFWwindow* _window;
	};

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