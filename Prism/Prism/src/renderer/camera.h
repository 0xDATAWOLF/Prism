#pragma once
#include <glm.hpp>

namespace Prism {

	// -------------------------------------------------------
	// --- Camera --------------------------------------------
	// -------------------------------------------------------

	class Camera {
	public:
		virtual ~Camera() {};

		virtual const glm::vec3 GetPosition() const = 0;
		virtual void SetPosition(glm::vec3&) = 0;
		virtual void SetProjection(float, float, float, float) = 0;
		virtual const glm::mat4 GetViewProjectionMatrix() const = 0;
		virtual const glm::mat4 GetProjectionMatrix() const = 0;
		virtual const glm::mat4 GetViewMatrix() const = 0;

	};

	class OrthographicCamera : public Camera {

	public:
		OrthographicCamera(float, float, float, float);
		virtual ~OrthographicCamera();

		const glm::vec3 GetPosition() const { return _position; };
		void SetPosition(glm::vec3&);
		void SetProjection(float, float, float, float);
		const glm::mat4 GetViewProjectionMatrix() const;
		const glm::mat4 GetProjectionMatrix() const;
		const glm::mat4 GetViewMatrix() const;

	private:
		void RecalculateViewProjection();

	private:
		glm::mat4 _viewProjectionMatrix;
		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;
		glm::vec3 _position;

	};

}