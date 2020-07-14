#include <Prism.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class ExampleLayer : public Prism::Layer {

private:
	std::shared_ptr<Prism::Texture2D> _texture;
	std::shared_ptr<Prism::Texture2D> _alphaTexture;
	std::shared_ptr<Prism::VertexArray> _vertexArray;
	std::shared_ptr<Prism::Camera> _camera;
	Prism::ShaderLibrary Shaders;

public:
	inline ExampleLayer() {

		_vertexArray.reset(Prism::VertexArray::Create());

		float vb2[]{
			-1.0, -1.0, 0.0, 0.0, 0.0,
			1.0, -1.0, 0.0, 1.0, 0.0,
			1.0, 1.0, 0.0, 1.0, 1.0,
			-1.0, 1.0, 0.0, 0.0, 1.0
		};

		uint32_t ib2[]{ 0, 1, 2, 0, 2, 3 };


		std::shared_ptr<Prism::VertexBuffer> vertexBuffer2;
		vertexBuffer2.reset(Prism::VertexBuffer::Create(sizeof(vb2), vb2));
		vertexBuffer2->SetLayout({
			{ "VertexBuffer", Prism::BufferElementType::Float3 },
			{ "TexCoord", Prism::BufferElementType::Float2 }
			});

		std::shared_ptr<Prism::IndexBuffer> indexBuffer2;
		indexBuffer2.reset(Prism::IndexBuffer::Create(sizeof(ib2), ib2));

		_vertexArray->AddVertexBuffer(vertexBuffer2);
		_vertexArray->SetIndexBuffer(indexBuffer2);

		Shaders.Add("assets/shaders/basicshader.glsl");
		std::shared_ptr<Prism::Shader> _basicShader = Shaders.Get("basicshader");

		_texture.reset(Prism::Texture2D::Create("assets/sprites/16x16_Tilesprite.png"));
		_alphaTexture.reset(Prism::Texture2D::Create("assets/sprites/16x16_Alphasprite.png"));

		std::dynamic_pointer_cast<Prism::OpenGLShader>(_basicShader)->Bind();
		std::dynamic_pointer_cast<Prism::OpenGLShader>(_basicShader)->DefineUniformInt("_uTexture", 0);

		_camera.reset(new Prism::OrthographicCamera((-1.6f)*5, (1.6f)*5, (-0.9f)*5, (0.9f)*5));
		_camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		
	};

	inline virtual ~ExampleLayer() {};
	void ImGuiRender() override {}

	void Update(const Prism::Timestep& timestep) override {
		glm::vec3 cameraPos = _camera->GetPosition();
		float movement = 5.0;
		if (Prism::Input::IsKeyPressed(Prism::Key::W)) { cameraPos = glm::vec3(cameraPos.x, cameraPos.y + (movement*timestep.GetDeltaInSeconds()), cameraPos.z); }
		if (Prism::Input::IsKeyPressed(Prism::Key::A)) { cameraPos = glm::vec3(cameraPos.x - (movement * timestep.GetDeltaInSeconds()), cameraPos.y, cameraPos.z); }
		if (Prism::Input::IsKeyPressed(Prism::Key::S)) { cameraPos = glm::vec3(cameraPos.x, cameraPos.y - (movement * timestep.GetDeltaInSeconds()), cameraPos.z); }
		if (Prism::Input::IsKeyPressed(Prism::Key::D)) { cameraPos = glm::vec3(cameraPos.x + (movement * timestep.GetDeltaInSeconds()), cameraPos.y, cameraPos.z); }
		_camera->SetPosition(cameraPos);

		Prism::RendererCommand::SetClearColor({ 0.12f, 0.12f, 0.12f, 1.0f });
		Prism::RendererCommand::Clear();
		Prism::Renderer::BeginScene(_camera);

		_texture->Bind();
		Prism::Renderer::Submit(Shaders.Get("basicshader"), _vertexArray, glm::translate(glm::mat4(1.0), glm::vec3(0.0,0.0,0.0)));

		_alphaTexture->Bind();
		Prism::Renderer::Submit(Shaders.Get("basicshader"), _vertexArray, glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0)));

		Prism::Renderer::EndScene();

	}
};

class SandboxApplication : public Prism::Application {
public:

	SandboxApplication() : Application(1280, 720, "My Sandbox") {
		PushLayer<ExampleLayer>();
	};
	~SandboxApplication() {};

};

Prism::Application* Prism::CreateApplication() {
	return new SandboxApplication();
}
