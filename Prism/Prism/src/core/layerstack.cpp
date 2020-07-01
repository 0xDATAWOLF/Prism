#include <core/layerstack.h>

namespace Prism {

	LayerStack::LayerStack() : _position(0) {}

	LayerStack::~LayerStack() {
		for (auto layer : _layers) delete layer; // dealloc on remaining layers
	}

	void LayerStack::Pop(Layer* layer) {
		for (int i = 0; i < _position; i++) { // (non-fixed only)
			if (_layers[i] == layer) {
				_layers.erase(_layers.begin() + i);
				delete layer; // dealloc layer
				_position--;
				return;
			}
		}
	}

	void LayerStack::PopOverlay(Layer* layer) {
		for (int i = _position; i < _layers.size(); i++) {
			if (_layers[i] == layer) {
				_layers.erase(_layers.begin() + i);
				delete layer; // dealloc layer
				return;
			}
		}
	}

}