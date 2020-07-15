#include "Layer2D.h"

Layer2D::Layer2D() : CameraController(5.0f), Color({0.8, 0.2, 0.3, 1.0}) {

	float verts[]{
		-1.0, -1.0, 0.0,
		1.0, -1.0, 0.0,
		1.0, 1.0, 0.0,
		-1.0, 1.0, 0.0,
	};

	uint32_t index[]{
		0, 1, 2, 0, 2, 3
	};

	ColoredSquare = Prism::VertexArray::Create();
	Prism::Ref<Prism::VertexBuffer> vb = Prism::VertexBuffer::Create(sizeof(verts), verts);
	Prism::Ref<Prism::IndexBuffer> ib = Prism::IndexBuffer::Create(sizeof(index), index);
	vb->SetLayout({ { "Vertices", Prism::BufferElementType::Float3 } });
	ColoredSquare->AddVertexBuffer(vb);
	ColoredSquare->SetIndexBuffer(ib);
	ShaderLibrary.Add("assets/shaders/basicshader.glsl");

}

Layer2D::~Layer2D() {}

void Layer2D::Update(const Prism::Timestep& timestep) {

	CameraController.OnUpdate(timestep);

	Prism::RendererCommand::SetClearColor({ 0.12f, 0.12f, 0.12f, 1.0f });
	Prism::RendererCommand::Clear();

	Prism::Renderer::BeginScene(CameraController.GetCamera());

	Prism::Ref<Prism::OpenGLShader> shader = std::dynamic_pointer_cast<Prism::OpenGLShader>(ShaderLibrary.Get("basicshader"));
	shader->DefineUniformFloat4("_uColor", Color);
	Prism::Renderer::Submit(ShaderLibrary.Get("basicshader"), ColoredSquare, glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0)));

	Prism::Renderer::EndScene();

}

void Layer2D::OnEvent(Prism::IEvent* e) {
	CameraController.OnEvent(e);
}

void Layer2D::ImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(Color));
	ImGui::End();
}
