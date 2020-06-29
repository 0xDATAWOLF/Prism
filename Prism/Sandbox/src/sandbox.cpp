#include <Prism.h>


class ExampleLayer : public Prism::Layer {

public:
	inline ExampleLayer() {
		PRISM_INFO("ExampleLayer constructor.");
	};

	inline virtual ~ExampleLayer() {
		PRISM_INFO("ExampleLayer destructor.");
	};

	void Update() override {
		_count++;
		if (_count <= 10) {
			PRISM_INFO("ExampleLayer updated.");
		}
	}

protected:
	uint16_t _count{ 0 };

};

class SandboxApplication : public Prism::Application {
public:

	SandboxApplication() : Application(1280, 720, "Prism Engine - Sandbox") {
		PushLayer<ExampleLayer>();
	};
	~SandboxApplication() {};

};

Prism::Application* Prism::CreateApplication() {
	return new SandboxApplication();
}
