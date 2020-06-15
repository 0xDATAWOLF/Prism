#pragma once

#include "core.h"

namespace Prism {

	class PRISM_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// This is the user-defined entry point for the Prism Engine. The defined function must return a
	// a heap allocated Prism::Application user-defined derived class.
	Application* CreateApplication();

}