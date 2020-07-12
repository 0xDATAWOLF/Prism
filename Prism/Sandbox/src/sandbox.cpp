#include <Prism.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class ExampleLayer : public Prism::Layer {

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

		_basicShader.reset(Prism::Shader::Create());
		std::string vertexShader = R"(
		#version 410 core
		layout(location = 0) in vec3 _aPosition;
		layout(location = 1) in vec2 _aTexCoord;

		uniform mat4 _uViewProjection;
		uniform mat4 _uTransform;

		out vec2 _texCoord;

		void main() {
			gl_Position = _uViewProjection * _uTransform * vec4(_aPosition, 1.0);
			_texCoord = _aTexCoord;
		}
		)";
		std::string fragmentShader = R"(
		#version 410 core
		in vec2 _texCoord;

		uniform sampler2D _uTexture;

		out vec4 color;

		void main() {
			color = texture(_uTexture, _texCoord);
		}
		)";

		_basicShader->AddShaderSource(vertexShader, Prism::ShaderType::Vertex);
		_basicShader->AddShaderSource(fragmentShader, Prism::ShaderType::Pixel);
		_basicShader->CompileShaders();

		_texture.reset(Prism::Texture2D::Create("assets/16x16_Tilesprite.png"));
		std::dynamic_pointer_cast<Prism::OpenGLShader>(_basicShader)->Bind();
		std::dynamic_pointer_cast<Prism::OpenGLShader>(_basicShader)->DefineUniformInt("_uTexture", 0);

		_camera.reset(new Prism::OrthographicCamera(-3.2f, 3.2f, -1.8f, 1.8f));
		_camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f)); // Camera position
		
	};

	inline virtual ~ExampleLayer() {};
	void ImGuiRender() override {}

	void Update(const Prism::Timestep& timestep) override {

		glm::vec3 cameraPos = _camera->GetPosition();
		float movement = 1.0;
		if (Prism::Input::IsKeyPressed(Prism::Key::W)) { cameraPos = glm::vec3(cameraPos.x, cameraPos.y + (movement*timestep.GetDeltaInSeconds()), cameraPos.z); }
		if (Prism::Input::IsKeyPressed(Prism::Key::A)) { cameraPos = glm::vec3(cameraPos.x - (movement * timestep.GetDeltaInSeconds()), cameraPos.y, cameraPos.z); }
		if (Prism::Input::IsKeyPressed(Prism::Key::S)) { cameraPos = glm::vec3(cameraPos.x, cameraPos.y - (movement * timestep.GetDeltaInSeconds()), cameraPos.z); }
		if (Prism::Input::IsKeyPressed(Prism::Key::D)) { cameraPos = glm::vec3(cameraPos.x + (movement * timestep.GetDeltaInSeconds()), cameraPos.y, cameraPos.z); }
		_camera->SetPosition(cameraPos);

		Prism::RendererCommand::SetClearColor({ 0.12f, 0.12f, 0.12f, 1.0f });
		Prism::RendererCommand::Clear();
		Prism::Renderer::BeginScene(_camera);

		_texture->Bind();
		Prism::Renderer::Submit(_basicShader, _vertexArray, glm::translate(glm::mat4(1.0), glm::vec3(0.0,0.0,0.0)));

		Prism::Renderer::EndScene();
	}

private:
	std::shared_ptr<Prism::Texture2D> _texture;
	std::shared_ptr<Prism::VertexArray> _vertexArray;
	std::shared_ptr<Prism::Shader> _basicShader;
	std::shared_ptr<Prism::Camera> _camera;
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
