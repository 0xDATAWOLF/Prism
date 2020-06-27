#include <Prism.h>
#include <core/scene.h>

class MemoryManager {

public:
	inline MemoryManager() {

	}

	inline virtual ~MemoryManager() {

	}

};

class TestEnvironment : public Prism::Application {
public:
	TestEnvironment() {



	};
	~TestEnvironment() {};
};

Prism::Application* Prism::CreateApplication() {
	return new TestEnvironment();
}
