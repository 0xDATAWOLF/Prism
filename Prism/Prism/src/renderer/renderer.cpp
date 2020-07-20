#include "core/logger.h"
#include "renderer/renderer.h"

#include <array>

namespace Prism {

	// -------------------------------------------------------
	// --- Renderer ------------------------------------------
	// -------------------------------------------------------

	glm::mat4 Renderer::_viewProjectionMatrix = glm::mat4(1.0);

	void Renderer::BeginScene(Ref<Camera>& camera) {
		_viewProjectionMatrix = camera->GetViewProjectionMatrix();
	}

	void Renderer::Submit(Ref<Shader>& shader, Ref<VertexArray>& vertexArray, glm::mat4 transform) {
		shader->Bind();
		shader->SetMat4("_uViewProjection", _viewProjectionMatrix);
		shader->SetMat4("_uTransform", transform);
		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	};

	// -------------------------------------------------------
	// --- Renderer2D ----------------------------------------
	// -------------------------------------------------------

	struct QuadVertex2D {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexID;
	};

	struct Renderer2DData {

		static const uint32_t MaxTextureSlots = 32;
		const uint32_t MaxQuads = 100000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		QuadVertex2D* VertexBufferBase;
		QuadVertex2D* VertexBufferBasePtrPos;
		uint32_t QuadIndexCount;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> DefaultTexture;

		std::array<glm::vec4, 4> BaseVertices;
		std::array<glm::vec2, 4> BaseTexCoords;

		std::array<Ref<Texture>, MaxTextureSlots> TextureSlots;
		uint32_t TextureIndex = 0;
	};

	static Renderer2DData Data;
	DrawStatistics Renderer2D::drawstats;

	void Renderer2D::Init() {

		// Initialize base verts and texcoords.
		Data.BaseVertices[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		Data.BaseVertices[1] = glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
		Data.BaseVertices[2] = glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
		Data.BaseVertices[3] = glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f);

		Data.BaseTexCoords[0] = glm::vec2(0.0, 0.0);
		Data.BaseTexCoords[1] = glm::vec2(1.0, 0.0); 
		Data.BaseTexCoords[2] = glm::vec2(1.0, 1.0);
		Data.BaseTexCoords[3] = glm::vec2(0.0, 1.0);

		// Vertex Array
		Data.QuadVertexArray = Prism::VertexArray::Create();

		// Vertex Buffer
		Data.QuadVertexBuffer = Prism::VertexBuffer::Create(sizeof(QuadVertex2D) * Data.MaxVertices);
		Data.VertexBufferBase = new QuadVertex2D[Data.MaxVertices];
		Data.VertexBufferBasePtrPos = Data.VertexBufferBase;
		Data.QuadVertexBuffer->SetLayout({
			{ "Vertices", Prism::BufferElementType::Float3 },
			{ "Color", Prism::BufferElementType::Float4 },
			{ "TextureCoords", Prism::BufferElementType::Float2 },
			{ "TextureId", Prism::BufferElementType::Float1 }
		});

		// set indices
		uint32_t* quadIndices = new uint32_t[Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < Data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Prism::Ref<Prism::IndexBuffer> ib = Prism::IndexBuffer::Create(sizeof(uint32_t)*Data.MaxIndices, quadIndices);

		Data.QuadVertexArray->AddVertexBuffer(Data.QuadVertexBuffer);
		Data.QuadVertexArray->SetIndexBuffer(ib);

		// Create Shader & Texture
		int32_t samplers[Data.MaxTextureSlots];
		for (uint32_t i = 0; i < Data.MaxTextureSlots; i++)
			samplers[i] = i;

		Data.TextureShader = Shader::Create("assets/shaders/texturedshader.glsl");
		Data.TextureShader->Bind();
		Data.TextureShader->SetIntArray("_uTextures", Data.MaxTextureSlots, samplers);

		Data.DefaultTexture = Texture2D::Create(1, 1);
		uint32_t texdata = 0xFFFFFFFF;
		Data.DefaultTexture->SetData(&texdata, sizeof(texdata));

		delete[] quadIndices; // Delete index

	}

	void Renderer2D::Shutdown() {
		Data.VertexBufferBasePtrPos = nullptr;
		delete[] Data.VertexBufferBase;
	}

	void Renderer2D::BeginScene(Ref<Camera>& camera) {

		Data.TextureShader->Bind();
		Data.TextureShader->SetMat4("_uViewProjection", camera->GetViewProjectionMatrix());

		Data.VertexBufferBasePtrPos = Data.VertexBufferBase;
		Data.QuadIndexCount = 0;
		Data.TextureIndex = 0;

	}

	void Renderer2D::EndScene() {
	
		uint32_t size = (uint8_t*)Data.VertexBufferBasePtrPos - (uint8_t*)Data.VertexBufferBase;
		Data.QuadVertexBuffer->SetData(size, Data.VertexBufferBase);

		Flush();

	}

	void Renderer2D::Flush() {

		for (uint32_t i = 0; i < Data.TextureIndex; i++)
			Data.TextureSlots[i]->Bind(i);

		RendererCommand::DrawIndexed(Data.QuadVertexArray, Data.QuadIndexCount);
		drawstats.drawcalls++;
		drawstats.indices += Data.QuadIndexCount;
		drawstats.vertices += (Data.QuadIndexCount/6) * 4;

	}

	void Renderer2D::Reset() {
		EndScene();

		Data.VertexBufferBasePtrPos = Data.VertexBufferBase;
		Data.QuadIndexCount = 0;
		Data.TextureIndex = 0;
	}

	void Renderer2D::DrawQuad(const glm::vec3 position, const glm::vec2 size, const glm::vec4 color) {

		DrawQuad(position, size, color, Data.DefaultTexture); // fwd

	}

	void Renderer2D::DrawQuad(const glm::vec3 position, const glm::vec2 size, const glm::vec4 color, const Ref<Texture2D> texture) {

		if (Data.TextureIndex >= Data.MaxTextureSlots) Reset();
		if (Data.QuadIndexCount >= Data.MaxIndices) Reset();

		float index = 0.0f;
		bool found = false;
		for (uint32_t i = 0; i < Data.TextureIndex; i++) {
			if (*Data.TextureSlots[i].get() == *texture.get()) {
				found = true; index = (float)i;
				break;
			}
		}

		if (!found) { // Add to texture slots
			Data.TextureSlots[Data.TextureIndex] = texture;
			index = (float)Data.TextureIndex;
			Data.TextureIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 0.0f));

		for (auto i = 0; i < 4; i++) {
			Data.VertexBufferBasePtrPos->Position = transform * Data.BaseVertices[i];
			Data.VertexBufferBasePtrPos->Color = color;
			Data.VertexBufferBasePtrPos->TexCoord = Data.BaseTexCoords[i];
			Data.VertexBufferBasePtrPos->TexID = index;
			Data.VertexBufferBasePtrPos++;
		}
		
		Data.QuadIndexCount += 6;
		drawstats.quads++;

	}

}