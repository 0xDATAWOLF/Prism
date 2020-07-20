#include <Prism.h>
#include <src/core/entry.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Layers/Layer2D.h"

class SandboxApplication : public Prism::Application {
public:

	SandboxApplication() : Application(1280, 720, "My Sandbox") {
		PushLayer<Layer2D>();
	};
	~SandboxApplication() {};

};

Prism::Application* Prism::CreateApplication() {
	return new SandboxApplication();
}
