#pragma once
#include <memory>

#include "core/core.h"
#include "renderer/rendererinterface.h"
#include "renderer/renderercommand.h"
#include "renderer/camera.h"
#include "renderer/vertexarray.h"
#include "renderer/shader.h"
#include "renderer/texture.h"

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

namespace Prism {

	// -------------------------------------------------------
	// --- Renderer ------------------------------------------
	// -------------------------------------------------------

	class Renderer { // Renderer
	public:
		virtual ~Renderer() {};
		static void Init() { RendererCommand::Init(); };
		static void BeginScene(Ref<Camera>&);
		static void EndScene() {}; // empty
		static void Submit(Ref<Shader>&, Ref<VertexArray>&, glm::mat4 transform);
		static RendererType GetRendererType() { return RendererCommand::GetRendererType(); };

	private:
		static glm::mat4 _viewProjectionMatrix;

	};

	// -------------------------------------------------------
	// --- Renderer2D ----------------------------------------
	// -------------------------------------------------------

	struct DrawStatistics {
		uint32_t drawcalls = 0;
		uint32_t quads = 0;
		uint32_t vertices = 0;
		uint32_t indices = 0;
	};

	class Renderer2D {

	public:
		virtual ~Renderer2D() {}
		static void Init();
		static void Shutdown();

		static void BeginScene(Ref<Camera>&);
		static void EndScene();
		static void Flush();
		static void Reset();

		static void ResetStats() { drawstats = DrawStatistics{}; }
		static const DrawStatistics& GetStats() { return drawstats; }

		static void DrawQuad(const glm::vec3 position, const glm::vec2 size, const glm::vec4 color);
		static void DrawQuad(const glm::vec3 position, const glm::vec2 size, const glm::vec4 color, const Ref<Texture2D> texture);

	private:
		static DrawStatistics drawstats;

	};


}