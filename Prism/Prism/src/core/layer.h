#pragma once
#include <string>
#include <core/events.h>
#include <core/timestep.h>

namespace Prism {

	class Layer : public IObserver {

	public:
		inline Layer(std::string layerName = "Layer") : name(layerName) {};
		inline virtual ~Layer() {};

		virtual void Update(const Timestep&) {};
		virtual void ImGuiRender() {};

	protected:
		std::string name;

	};

};

