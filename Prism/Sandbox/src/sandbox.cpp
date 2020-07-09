#include <Prism.h>

class ExampleLayer : public Prism::Layer {

public:
	inline ExampleLayer() {

	};

	inline virtual ~ExampleLayer() {

	};

	void ImGuiRender() override {
		if (open) {
			ImGui::Begin("Test Window", &open);
			ImGui::Text("Test text in window.");
			ImGui::End();
		}

		if (Prism::Input::IsKeyPressed(Prism::Key::F3)) open = true;
	}

	void Update() override {
	
	}

protected:
	uint16_t _count{ 0 };
	bool open{ false };

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
