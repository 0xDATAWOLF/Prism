#include "Prism.h"

class SandboxApplication : public Prism::Application {
public:
	SandboxApplication() {};
	~SandboxApplication() {};
};

Prism::Application* Prism::CreateApplication() {
	return new SandboxApplication();
}
