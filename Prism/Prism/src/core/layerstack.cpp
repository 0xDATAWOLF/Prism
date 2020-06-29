#include <core/layerstack.h>

namespace Prism {

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
		for (auto layer : _layers) delete layer; // dealloc on remaining layers
	}

	void LayerStack::PopLayer(Layer* layer) {
		for (int i = 0; i < _layers.size(); i++) {
			if (_layers[i] == layer) {
				_layers.erase(_layers.begin() + i);
				delete layer; // dealloc layer because it is a heap var.
				return;
			}
		}
	}

	void LayerStack::UpdateLayers() {
		for (auto it = _layers.rbegin(); it != _layers.rend(); it++) {
			(*it)->Update();
		}
	}

}