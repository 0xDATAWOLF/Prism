#pragma once
#include "core/core.h"

namespace Prism {

	// -------------------------------------------------------
	// --- Graphics Context ----------------------------------
	// -------------------------------------------------------

	class GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}