#pragma once
#include <core/core.h>
#include <core/events.h>
#include <core/layer.h>

namespace Prism {

	class ImGUILayer : public Layer {

	public:
		ImGUILayer();
		virtual ~ImGUILayer();

		void Update() override;

		void OnEvent(IEvent* ev) override;

		bool OnMouseButtonDown(MouseButtonDownEvent*);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent*);
		bool OnMouseMove(MouseMoveEvent*);
		bool OnMouseScroll(MouseScrollEvent*);
		bool OnKeyDown(KeyDownEvent*);
		bool OnKeyReleased(KeyReleasedEvent*);
		bool OnKeyTyped(KeyTypedEvent*);
		bool OnWindowResize(WindowResizeEvent*);

	protected:
		float _LTime;

	};

}