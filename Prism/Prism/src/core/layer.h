#pragma once
#include <core/core.h>

namespace Prism {

	class Layer {

	public:
		inline Layer() {};
		inline virtual ~Layer() {};

		virtual void OnUpdate() = 0;
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;

	};

}

