#pragma once
#include <string>
#include <core/core.h>
#include <core/events.h>

namespace Prism {

	class Layer : public IObserver {

	public:
		inline Layer(std::string layerName = "Layer") : _name(layerName) {};
		inline virtual ~Layer() {};
		virtual void Update() = 0;

	protected:
		std::string _name;

	};

}

