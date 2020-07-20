#pragma once
#include <Prism.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Layer2D : public Prism::Layer {

public:
	Layer2D();
	virtual ~Layer2D();

	virtual void Update(const Prism::Timestep&);
	virtual void OnEvent(Prism::IEvent* e);
	virtual void ImGuiRender();

private:
	Prism::Ref<Prism::Texture2D> CheckerboardTexture;
	Prism::OrthographicCameraController CameraController;
	glm::vec4 Color;
	glm::vec4 SecondColor;

	float deltaAverage = 16.0f;
	float deltaAverageCounter = 0.0f;
	uint32_t index = 0;
	int32_t draws = 0;

};