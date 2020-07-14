#pragma once
#include "renderer/renderer.h"

namespace Prism {

	// -------------------------------------------------------
	// --- OpenGL Renderer API -------------------------------
	// -------------------------------------------------------

	class OpenGLRendererInterface : public BaseRendererInterface {
	public:
		OpenGLRendererInterface();
		virtual ~OpenGLRendererInterface();

		virtual void Init();
		virtual void Clear();
		virtual void SetClearColor(const glm::vec4&);
		virtual void DrawIndexed(std::shared_ptr<VertexArray>&);
		virtual RendererType GetAPIType();
	};

};
