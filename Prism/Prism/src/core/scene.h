#pragma once
#include <core/core.h>
#include <core/layer.h>

namespace Prism {

	class Scene {
		friend class Application;

	public:
		inline Scene() {};
		inline virtual ~Scene() {
			
		};
		
		virtual void Update() {}

		/* Pushes a layer onto the scene using the provided template class. */
		template <class L> inline Layer* PushLayer() {
			std::shared_ptr<Layer> layer = std::make_shared<L>(L());
			_layers.push_back(layer);
			return layer.get();
		}

		/* Detaches a layer from the scene. */
		inline void RemoveLayer(Layer* layer) {
			for (int i = 0; i < _layers.size(); i++) {
				if (_layers[i].get() == layer) {
					// Layer deconstructs & deallocs from memory
					_layers.erase(_layers.begin()+i); 
					return; 
				}
			}
		};

	private:

		inline void _pFrameUpdateLayers() {
			Update();
			for (auto it = _layers.rbegin(); it != _layers.rend(); it++) {
				(*it)->Update();
			}
		}

		std::vector<std::shared_ptr<Layer>> _layers;

	};

}
