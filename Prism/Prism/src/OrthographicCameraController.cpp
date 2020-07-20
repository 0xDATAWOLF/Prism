#include <algorithm>

#include "OrthographicCameraController.h"
#include "application.h"


namespace Prism {

	OrthographicCameraController::OrthographicCameraController(float zoom, float speed)
		: zoom(zoom), position({0.0f, 0.0f, 0.0f}), speed(speed) {
		auto& app = Application::Get();
		aspectratio = (float)app.GetWindowWidth() / (float)app.GetWindowHeight();
		camera = std::make_shared<OrthographicCamera>(-aspectratio*zoom, aspectratio*zoom, -1*zoom, 1*zoom);
	}

	void OrthographicCameraController::OnUpdate(const Timestep& timestep) {
		if (Prism::Input::IsKeyPressed(Prism::Key::W))
			{ position = glm::vec3(position.x, position.y + (speed * timestep.GetDeltaInSeconds()), position.z); }
		if (Prism::Input::IsKeyPressed(Prism::Key::A))
			{ position = glm::vec3(position.x - (speed * timestep.GetDeltaInSeconds()), position.y, position.z); }
		if (Prism::Input::IsKeyPressed(Prism::Key::S))
			{ position = glm::vec3(position.x, position.y - (speed * timestep.GetDeltaInSeconds()), position.z); }
		if (Prism::Input::IsKeyPressed(Prism::Key::D))
			{ position = glm::vec3(position.x + (speed * timestep.GetDeltaInSeconds()), position.y, position.z); }
		camera->SetPosition(position);
	}

	void OrthographicCameraController::OnEvent(IEvent* e) {
		IDispatcher dispatcher(e);
		dispatcher.Forward<WindowResizeEvent>
			(std::bind(&OrthographicCameraController::OnWindowResize, this, std::placeholders::_1));
		dispatcher.Forward<MouseScrollEvent>
			(std::bind(&OrthographicCameraController::OnMouseScroll, this, std::placeholders::_1));
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent* e) {
		aspectratio = (float)e->GetWidth() / (float)e->GetHeight();
		camera->SetProjection(-aspectratio*zoom, aspectratio*zoom, -1*zoom, 1*zoom);
		return false;
	}

	bool OrthographicCameraController::OnMouseScroll(MouseScrollEvent* e) {
		zoom -= (e->GetYpos()*0.25f);
		zoom = std::max(zoom, 0.25f);
		camera->SetProjection(-aspectratio * zoom, aspectratio * zoom, -1 * zoom, 1 * zoom);
		return false;
	}

}