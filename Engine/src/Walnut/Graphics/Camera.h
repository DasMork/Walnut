#pragma once
#include <glm/glm.hpp>

namespace Walnut
{
	class Camera
	{
	public:
		virtual ~Camera() = default;

		const glm::vec3& GetPosition() const { return mPosition; }
		float GetRotation() const { return mRotation; }
		const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return mViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return mViewProjectionMatrix; }

		void SetPosition(const glm::vec3& position) { mPosition = position; CalculateMatrices(); }
		void SetRotation(float rot) { mRotation = rot; CalculateMatrices(); }

	protected:
		virtual void CalculateMatrices() = 0;
	protected:
		glm::mat4 mProjectionMatrix;
		glm::mat4 mViewMatrix;
		glm::mat4 mViewProjectionMatrix;

		glm::vec3 mPosition;
		float mRotation = 0;
	};

	class OrthographicCamera : public Camera
	{
	public:
		virtual ~OrthographicCamera() = default;
		OrthographicCamera(float left, float right, float bottom, float top);
	protected:
		void CalculateMatrices() override;
	};

	class PerspectiveCamera : public Camera
	{
	public:
		virtual ~PerspectiveCamera() = default;
		PerspectiveCamera(float fov, float width, float height, float nearPlane, float farPlane);
	protected:
		void CalculateMatrices() override;
	};
}
