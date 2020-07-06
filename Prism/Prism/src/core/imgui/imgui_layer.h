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
		void ImGuiRender() override;

		void Begin();
		void End();
	protected:

	};

}