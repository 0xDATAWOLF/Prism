#pragma once
#include "core/core.h"
#include "core/input.h"
#include "core/events.h"
#include "renderer/camera.h"
#include "core/timestep.h"

#include <glm.hpp>

namespace Prism {

	class OrthographicCameraController : public IObserver {

	public:
		OrthographicCameraController(float zoom);
		virtual ~OrthographicCameraController() {};

		void OnUpdate(const Timestep&);
		void SetSpeed(float s) { speed = s; }

		Ref<Camera> GetCamera() { return camera; }

		void OnEvent(IEvent* e);

	private:
		bool OnWindowResize(WindowResizeEvent* e);
		bool OnMouseScroll(MouseScrollEvent* e);

	private:
		float aspectratio;
		float speed;
		float zoom;
		Ref<Camera> camera;
		glm::vec3 position;

	};

}