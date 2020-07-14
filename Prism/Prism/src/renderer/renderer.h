#pragma once
#include <memory>

#include "renderer/camera.h"
#include "renderer/vertexarray.h"
#include "renderer/shader.h"

#include <glm.hpp>

namespace Prism {

	enum class RendererType { OpenGL = 0, Vulkan = 1, DirectX12 = 2, Metal = 3 };

	// -------------------------------------------------------
	// --- RendererAPI ---------------------------------------
	// -------------------------------------------------------

	class BaseRendererInterface { // Interface class
	public:
		virtual ~BaseRendererInterface() {};
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4&) = 0;
		virtual void DrawIndexed(std::shared_ptr<VertexArray>&) = 0;
		virtual void Init() = 0;
		virtual RendererType GetAPIType() = 0;

	};

	// -------------------------------------------------------
	// --- RendererCommand -----------------------------------
	// -------------------------------------------------------

	class RendererCommand { // Container for RendererAPI
	public:
		static void Init() { _api->Init(); }; // fwd
		static void Clear() { _api->Clear(); }; // fwd
		static void SetClearColor(const glm::vec4& c) { _api->SetClearColor(c); }; // fwd
		static void DrawIndexed(std::shared_ptr<VertexArray>& v) { _api->DrawIndexed(v); }; // fwd
		static RendererType GetRendererType() { return _api->GetAPIType(); } // fwd
	private:
		static BaseRendererInterface* _api;
	};


	// -------------------------------------------------------
	// --- Renderer ------------------------------------------
	// -------------------------------------------------------

	class Renderer { // Renderer
	public:
		virtual ~Renderer() {};
		static void Init() { RendererCommand::Init(); };
		static void BeginScene(std::shared_ptr<Camera>&);
		static void EndScene() {}; // empty
		static void Submit(std::shared_ptr<Shader>&, std::shared_ptr<VertexArray>&, glm::mat4 transform);
		static RendererType GetRendererType() { return RendererCommand::GetRendererType(); };

	private:
		static glm::mat4 _viewProjectionMatrix;

	};

}