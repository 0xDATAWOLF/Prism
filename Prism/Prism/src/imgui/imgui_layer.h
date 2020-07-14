#pragma once
#include "core/layer.h"

namespace Prism {

	class ImGUILayer : public Layer {

	public:
		ImGUILayer();
		virtual ~ImGUILayer();

		void Update(const Timestep&) override;
		void ImGuiRender() override;

		void Begin();
		void End();
	protected:

	};

};