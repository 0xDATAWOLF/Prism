#pragma once
#include "core/core.h"
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
		virtual void DrawIndexed(Ref<VertexArray>&);
		virtual RendererType GetAPIType();
	};

};
