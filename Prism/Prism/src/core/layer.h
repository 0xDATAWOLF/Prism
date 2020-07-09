#pragma once
#include <string>
#include <core/core.h>
#include <core/events.h>

namespace Prism {

	class Layer : public IObserver {

	public:
		inline Layer(std::string layerName = "Layer") : name(layerName) {};
		inline virtual ~Layer() {};
		virtual void Update() {};
		virtual void ImGuiRender() {};

	protected:
		std::string name;

	};

}

