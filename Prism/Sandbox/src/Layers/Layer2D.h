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
	Prism::OrthographicCameraController CameraController;
	Prism::ShaderLibrary ShaderLibrary;
	Prism::Ref<Prism::VertexArray> ColoredSquare;
	glm::vec4 Color;

};