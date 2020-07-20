#include "renderer/renderercommand.h"
#include "platform/opengl/ogl_renderapi.h"

namespace Prism {

	// -------------------------------------------------------
	// --- RendererCommand -----------------------------------
	// -------------------------------------------------------

	BaseRendererInterface* RendererCommand::_api = new OpenGLRendererInterface();

	void RendererCommand::Init() {

		_api->Init();

	}

}