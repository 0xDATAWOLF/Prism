#include <Prism.h>

class BarLayer : public Prism::Layer {

public:
	inline BarLayer() {};
	inline virtual ~BarLayer() {};

	inline void OnUpdate() override { PRISM_INFO("BarLayer updated."); }
	inline void OnAttach() override { PRISM_INFO("BarLayer attached."); }
	inline void OnDetach() override {}

};

class FooScene : public Prism::Scene {

public:
	inline FooScene() {
		_myBarLayer = std::make_shared<BarLayer>(BarLayer());
		Attach(_myBarLayer.get());
	}
	virtual ~FooScene() { }

	inline void Update() override {}

private:
	std::shared_ptr<BarLayer> _myBarLayer;

};

class SandboxApplication : public Prism::Application {
public:

	SandboxApplication() {
		SetScene<FooScene>();
	};


	~SandboxApplication() {};
};

Prism::Application* Prism::CreateApplication() {
	return new SandboxApplication();
}
