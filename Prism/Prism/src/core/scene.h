#pragma once
#include <core/core.h>
#include <core/layer.h>

namespace Prism {

	class Scene {
		friend class Application;

	public:
		inline Scene() {};
		inline virtual ~Scene() {};
		
		virtual void Update() {};

		/* Attaches a layer to the scene. */
		inline void Attach(Layer* layer) {
			for (Layer* l : _layers) if (l == layer) return;
			_layers.push_back(layer);
			layer->OnAttach();
		};

		/* Detaches a layer from the scene. */
		inline void Detach(Layer* layer) {
			for (int i = 0; i < _layers.size(); i++) {
				if (_layers[i] == layer) {
					_layers.erase(_layers.begin()+i);
					layer->OnDetach();
					return;
				}
			}
		};

	private:

		inline void _pFrameUpdateLayers() {
			Update();
			for (auto it = _layers.rbegin(); it != _layers.rend(); it++) {
				(*it)->OnUpdate();
			}
		}

		std::vector<Layer*> _layers;

	};

}
