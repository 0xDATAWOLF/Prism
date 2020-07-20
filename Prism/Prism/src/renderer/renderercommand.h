#pragma once
#include "renderer/vertexarray.h"
#include "renderer/rendererinterface.h"

namespace Prism {

	// -------------------------------------------------------
	// --- RendererCommand -----------------------------------
	// -------------------------------------------------------

	class RendererCommand { // Container for RendererAPI
	public:
		static void Init(); // fwd
		static void Clear() { _api->Clear(); }; // fwd
		static void SetClearColor(const glm::vec4& c) { _api->SetClearColor(c); }; // fwd
		static void DrawIndexed(Ref<VertexArray>& v, uint32_t count = 0) { _api->DrawIndexed(v, count); }; // fwd
		static RendererType GetRendererType() { return _api->GetAPIType(); } // fwd
	private:
		static BaseRendererInterface* _api;
	};

}