#include "Prism.h"
#include <iostream>

class SandboxApplication : public Prism::Application {
public:
	SandboxApplication() {
        // Print something out to the console.
        std::cout << "Hello world." << std::endl;
    };
	~SandboxApplication() {};
};

Prism::Application* Prism::CreateApplication() {
	return new SandboxApplication();
}
