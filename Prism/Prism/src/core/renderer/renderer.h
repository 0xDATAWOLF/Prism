#pragma once
#include <memory>
#include <core/renderer/vertexarray.h>
#include <glm.hpp>

namespace Prism {

	enum class RendererType { OpenGL = 0, Vulkan = 1, DirectX12 = 2, Metal = 3 };

	// -------------------------------------------------------
	// --- RendererAPI ---------------------------------------
	// -------------------------------------------------------

	class RendererAPI { // Interface class
	public:
		virtual ~RendererAPI() {};
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4&) = 0;
		virtual void DrawIndexed(std::shared_ptr<VertexArray>&) = 0;
		virtual RendererType GetAPIType() = 0;

	};

	// -------------------------------------------------------
	// --- RendererCommand -----------------------------------
	// -------------------------------------------------------

	class RendererCommand { // Container for RendererAPI
	public:
		static void Clear() { _api->Clear(); }; // fwd
		static void SetClearColor(const glm::vec4& c) { _api->SetClearColor(c); }; // fwd
		static void DrawIndexed(std::shared_ptr<VertexArray>& v) { _api->DrawIndexed(v); }; // fwd
		static RendererType GetRendererType() { return _api->GetAPIType(); } // fwd
	private:
		static RendererAPI* _api;
	};


	// -------------------------------------------------------
	// --- Renderer ------------------------------------------
	// -------------------------------------------------------

	class Renderer { // Renderer
	public:
		virtual ~Renderer() {};
		static void BeginScene() {}; // empty
		static void EndScene() {}; // empty
		static void Submit(std::shared_ptr<VertexArray>& v);
		static RendererType GetRendererType() { return RendererCommand::GetRendererType(); };

	};

}