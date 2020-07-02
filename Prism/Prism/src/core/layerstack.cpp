#include <core/layerstack.h>

namespace Prism {

	LayerStack::LayerStack() : _position(0) {}

	LayerStack::~LayerStack() {
		for (auto layer : _layers) {
			bool f = false;
			for (auto u : _unmanagedLayers) if (u == layer) f = true;
			if (!f) delete layer; // dealloc layer
		}
	}

	void LayerStack::PushUnmanaged(Layer* layer) {
		for (auto l : _layers) if (layer == l) return; // no dupes
		_unmanagedLayers.push_back(layer);
		_layers.emplace(_layers.begin() + _position, layer);
		_position++;
	}

	void LayerStack::PushOverlayUnmanaged(Layer* layer) {
		for (auto l : _layers) if (layer == l) return; // no dupes
		_layers.emplace_back(layer);
		_unmanagedLayers.push_back(layer);
	}

	void LayerStack::Pop(Layer* layer) {
		for (int i = 0; i < _position; i++) { // only check up to position
			if (_layers[i] == layer) {
				_layers.erase(_layers.begin() + i);

				// check if unmanaged
				bool f = false;
				for (auto u : _unmanagedLayers) if (u == _layers[i]) f = true;
				if (!f) delete layer; // dealloc layer

				_position--;
				return;
			}
		}
	}

	void LayerStack::PopOverlay(Layer* layer) {
		for (int i = _position; i < _layers.size(); i++) {
			if (_layers[i] == layer) {
				_layers.erase(_layers.begin() + i);

				// check if unmanaged
				bool f = false;
				for (auto u : _unmanagedLayers) if (u == _layers[i]) f = true;
				if (!f) delete layer; // dealloc layer

				return;
			}
		}
	}

}