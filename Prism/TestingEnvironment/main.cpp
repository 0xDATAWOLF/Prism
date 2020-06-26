#include <Prism.h>
#include <iostream>

class TestEnvironment : public Prism::Application {
public:
	TestEnvironment() {

	};
	~TestEnvironment() {};
};

Prism::Application* Prism::CreateApplication() {
	return new TestEnvironment();
}
