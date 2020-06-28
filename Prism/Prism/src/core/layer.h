#pragma once
#include <core/core.h>

namespace Prism {

	class Layer {

	public:
		inline Layer() {};
		inline virtual ~Layer() {};

		virtual void Update() = 0;

	};

}

