#include "renderer/camera.h"

#include <gtc/matrix_transform.hpp>

namespace Prism {

	OrthographicCamera::OrthographicCamera(float l, float r, float b, float t) {
		_projectionMatrix = glm::ortho(l, r, b, t, -1.0f, 1.0f);
		_position = glm::vec3(0.0, 0.0, 0.0);
		RecalculateViewProjection();
	}

	OrthographicCamera::~OrthographicCamera() {}

	void OrthographicCamera::SetPosition(float x, float y, float z)
		{ SetPosition(glm::vec3(x, y, z)); } // fwd

	void OrthographicCamera::SetPosition(glm::vec3& pos) {
		_position = pos;
		RecalculateViewProjection();
	}

	const glm::mat4 OrthographicCamera::GetViewProjectionMatrix() const {
		return _viewProjectionMatrix;
	}

	const glm::mat4 OrthographicCamera::GetProjectionMatrix() const {
		return _projectionMatrix;
	}

	const glm::mat4 OrthographicCamera::GetViewMatrix() const {
		return _viewMatrix;
	}

	void OrthographicCamera::RecalculateViewProjection() {
		_viewMatrix = glm::translate(glm::mat4(1.0f), _position);
		_viewProjectionMatrix = _projectionMatrix * glm::inverse(_viewMatrix);
	}

}
