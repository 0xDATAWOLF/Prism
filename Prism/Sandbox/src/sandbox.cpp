#include <Prism.h>
#include <src/core/entry.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Layers/Layer2D.h"

class ExampleLayer : public Prism::Layer {

private:
	Prism::Ref<Prism::Texture2D> _texture;
	Prism::Ref<Prism::Texture2D> _alphaTexture;
	Prism::Ref<Prism::VertexArray> _vertexArray;
	Prism::ShaderLibrary Shaders;
	Prism::Ref<Prism::OrthographicCameraController> CameraController;


public:
	inline ExampleLayer() {

		_vertexArray = Prism::VertexArray::Create();

		float vb2[]{
			-1.0, -1.0, 0.0, 0.0, 0.0,
			1.0, -1.0, 0.0, 1.0, 0.0,
			1.0, 1.0, 0.0, 1.0, 1.0,
			-1.0, 1.0, 0.0, 0.0, 1.0
		};

		uint32_t ib2[]{ 0, 1, 2, 0, 2, 3 };

		Prism::Ref<Prism::VertexBuffer> vertexBuffer2 = Prism::VertexBuffer::Create(sizeof(vb2), vb2);
		vertexBuffer2->SetLayout({
			{ "VertexBuffer", Prism::BufferElementType::Float3 },
			{ "TexCoord", Prism::BufferElementType::Float2 }
			});

		Prism::Ref<Prism::IndexBuffer> indexBuffer2;
		//indexBuffer2.reset(Prism::IndexBuffer::Create(sizeof(ib2), ib2));

		_vertexArray->AddVertexBuffer(vertexBuffer2);
		_vertexArray->SetIndexBuffer(indexBuffer2);

		Shaders.Add("assets/shaders/basicshader.glsl");
		Prism::Ref<Prism::Shader> _basicShader = Shaders.Get("basicshader");

		_texture = Prism::Texture2D::Create("assets/sprites/16x16_Tilesprite.png");
		_alphaTexture = Prism::Texture2D::Create("assets/sprites/16x16_Alphasprite.png");

		std::dynamic_pointer_cast<Prism::OpenGLShader>(_basicShader)->Bind();
		std::dynamic_pointer_cast<Prism::OpenGLShader>(_basicShader)->DefineUniformInt("_uTexture", 0);

		CameraController = std::make_shared<Prism::OrthographicCameraController>(5.0f);
		
	};

	inline virtual ~ExampleLayer() {};
	void ImGuiRender() override {}

	void Update(const Prism::Timestep& timestep) override {

		CameraController->OnUpdate(timestep);

		Prism::RendererCommand::SetClearColor({ 0.12f, 0.12f, 0.12f, 1.0f });
		Prism::RendererCommand::Clear();
		Prism::Renderer::BeginScene(CameraController->GetCamera());

		_texture->Bind();
		Prism::Renderer::Submit(Shaders.Get("basicshader"), _vertexArray, glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0)));

		_alphaTexture->Bind();
		Prism::Renderer::Submit(Shaders.Get("basicshader"), _vertexArray, glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0)));

		Prism::Renderer::EndScene();

	}

	void OnEvent(Prism::IEvent* e) {
		CameraController->OnEvent(e); // fwd
	}

};

class SandboxApplication : public Prism::Application {
public:

	SandboxApplication() : Application(1280, 720, "My Sandbox") {
		//PushLayer<ExampleLayer>();
		PushLayer<Layer2D>();
	};
	~SandboxApplication() {};

};

Prism::Application* Prism::CreateApplication() {
	return new SandboxApplication();
}
