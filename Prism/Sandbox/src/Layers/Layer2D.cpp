#include "Layer2D.h"

Layer2D::Layer2D() : CameraController(5.0f, 10.0f), Color({ 0.2, 0.8, 0.3, 1.0 }), SecondColor({ 1.0,1.0,1.0,1.0 }) {
	CheckerboardTexture = Prism::Texture2D::Create("assets/sprites/16x16_Tilesprite.png");
}

Layer2D::~Layer2D() {}

void Layer2D::Update(const Prism::Timestep& timestep) {

	deltaAverageCounter += timestep.GetDeltaInMilliseconds();
	index++;
	if (index >= 5) {
		deltaAverage = deltaAverageCounter / 5; index = 0;
		deltaAverageCounter = 0.0f;
	}

	CameraController.OnUpdate(timestep);
	Prism::Renderer2D::ResetStats();

	Prism::RendererCommand::SetClearColor({ 0.12f, 0.12f, 0.12f, 1.0f });
	Prism::RendererCommand::Clear();
	Prism::Renderer2D::BeginScene(CameraController.GetCamera());
	Prism::Renderer2D::DrawQuad({ -2.0f, -1.0f, 1.0f }, { 1.0f, 1.0f }, Color);
	Prism::Renderer2D::DrawQuad({ -4.0f, -4.0f, 1.0f }, { 6.0f, 6.0f }, SecondColor, CheckerboardTexture);
	for (float x = 0; x < draws; x += 0.5f) {
		for (float y = 0; y < draws; y += 0.5f)
		Prism::Renderer2D::DrawQuad({ x, y, 1.0f }, { 0.4f, 0.4f }, SecondColor, CheckerboardTexture);
	}
	Prism::Renderer2D::EndScene();

}

void Layer2D::OnEvent(Prism::IEvent* e) {
	CameraController.OnEvent(e);
}

void Layer2D::ImGuiRender() {
	auto stats = Prism::Renderer2D::GetStats();

	ImGui::Begin("Settings");
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Framedelta: %fms", deltaAverage);
	ImGui::Text("Draw Calls: %d", stats.drawcalls);
	ImGui::Text("Quads: %d", stats.quads);
	ImGui::Text("Vertices: %d", stats.vertices);
	ImGui::Text("Indices: %d", stats.indices);
	ImGui::Separator();
	ImGui::InputInt("Stress Draws (x,y), total^2", &draws, 1, 100);
	ImGui::ColorPicker4("Square #1 Color", glm::value_ptr(Color));
	ImGui::ColorPicker4("Square #2 Color", glm::value_ptr(SecondColor));
	ImGui::End();

}
