#pragma once
#include <core/core.h>

class Layer {

public:
	inline Layer() {};
	inline virtual ~Layer() {};

	virtual void OnUpdate() = 0;
	virtual void OnAttach() = 0;
	virtual void OnDetach() = 0;

};

