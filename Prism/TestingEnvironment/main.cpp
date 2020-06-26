#include <Prism.h>
#include <iostream>
#include "tsrc/memorymanager.h"

class TestEnvironment : public Prism::Application {
public:
	TestEnvironment() {

		Prism::MemoryManager _memManager;

	};
	~TestEnvironment() {};
};

Prism::Application* Prism::CreateApplication() {
	return new TestEnvironment();
}
