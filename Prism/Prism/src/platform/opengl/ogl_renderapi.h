#pragma once
#include <core/renderer/renderer.h>

namespace Prism {

	// -------------------------------------------------------
	// --- OpenGL Renderer API -------------------------------
	// -------------------------------------------------------

	class OpenGLRendererAPI : public BaseRendererInterface {
	public:
		OpenGLRendererAPI();
		virtual ~OpenGLRendererAPI();

		virtual void Clear();
		virtual void SetClearColor(const glm::vec4&);
		virtual void DrawIndexed(std::shared_ptr<VertexArray>&);
		virtual RendererType GetAPIType();
	};

};
