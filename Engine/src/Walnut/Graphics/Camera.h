#pragma once
#include <glm/glm.hpp>

namespace Walnut
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return mPosition; }
		float GetRotation() const { return mRotation; }
		const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return mViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return mViewProjectionMatrix; }

		void SetPosition(const glm::vec3& position) { mPosition = position; CalculateMatrices(); }
		void SetRotation(float rot) { mRotation = rot; CalculateMatrices(); }

	private:
		void CalculateMatrices();
	private:
		glm::mat4 mProjectionMatrix;
		glm::mat4 mViewMatrix;
		glm::mat4 mViewProjectionMatrix;

		glm::vec3 mPosition;
		float mRotation = 0;
	};
}
