#include <Prism.h>

class ExampleLayer : public Prism::Layer {

public:
	inline ExampleLayer() {
		PRISM_INFO("ExampleLayer constructed.");
	};
	inline virtual ~ExampleLayer() {
		PRISM_INFO("ExampleLayer removed.");
	};

	void Update() override {
		PRISM_INFO("ExampleLayer updated.");
	}

	
};

class ExampleScene : public Prism::Scene {

public:
	inline ExampleScene() {};
	inline virtual ~ExampleScene() {};

	inline void Update() override {
		updateCount++;
		if (updateCount >= 5) {
			RemoveLayer(exLayer);
		}
	};

	uint16_t updateCount = 0;
	Prism::Layer* exLayer;

};

class SandboxApplication : public Prism::Application {
public:

	SandboxApplication() : Application(1280, 720, "Prism Engine - Sandbox") {
		SetScene<ExampleScene>();
		auto currentScene = GetScene<ExampleScene>();
		Prism::Layer* pLayer = currentScene->PushLayer<ExampleLayer>();
		currentScene->exLayer = pLayer;
	};
	~SandboxApplication() {};

};

Prism::Application* Prism::CreateApplication() {
	return new SandboxApplication();
}
