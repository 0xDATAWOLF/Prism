#pragma once
#include <core/renderer/graphicscontext.h>

struct GLFWwindow;

namespace Prism {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow*);
		virtual ~OpenGLContext();

		void Init() override;
		void SwapBuffers() override;

	protected:
		GLFWwindow* _window;
	};

}