#pragma once
#include <core/core.h>
#include <core/layer.h>

namespace Prism {

	class LayerStack {

	public:
		LayerStack();
		virtual ~LayerStack();

		template <class L> Layer* Push();
		template <class L> Layer* PushOverlay();

		void Pop(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return _layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return _layers.rend(); }

		std::vector<Layer*>::const_iterator cbegin() const noexcept { return _layers.cbegin(); }
		std::vector<Layer*>::const_iterator cend() const noexcept { return _layers.cend(); }
		std::vector<Layer*>::const_reverse_iterator crbegin() const noexcept { return _layers.crbegin(); }
		std::vector<Layer*>::const_reverse_iterator crend() const noexcept { return _layers.crend(); }

	protected:
		std::vector<Layer*> _layers;
		uint16_t _position;

	};

	template <class L>
	inline Layer* LayerStack::PushOverlay() {
		Layer* layer = new L();
		_layers.emplace_back(layer); // don't bump position, always front layer
		return layer;
	}

	template <class L>
	inline Layer* LayerStack::Push() {
		Layer* layer = new L();
		_layers.emplace(_layers.begin() + _position, layer);
		_position++;
		return layer;
	}

}
