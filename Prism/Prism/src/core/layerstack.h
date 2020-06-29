#pragma once
#include <core/core.h>
#include <core/layer.h>

namespace Prism {

	class LayerStack {

	public:
		LayerStack();
		virtual ~LayerStack();

		template <class L> inline void PushLayer();
		void PopLayer(Layer* layer);
		void UpdateLayers();



	protected:
		std::vector<Layer*> _layers;

	};

	template <class L>
	inline void LayerStack::PushLayer() {
		_layers.emplace_back(new L());
	}

}
