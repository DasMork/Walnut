#include "wnpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Walnut::OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: Camera()
{
	mPosition = glm::vec3(0, 0, 0);
	mProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	mViewMatrix = glm::mat4(1.0f);
	mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
}

void Walnut::OrthographicCamera::CalculateMatrices()
{
	glm::mat4 transform = translate(glm::mat4(1.0f), mPosition)
		* rotate(glm::mat4(1.0f), mRotation, glm::vec3(0, 0, 1));

	mViewMatrix = glm::inverse(transform);
	mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
}

void Walnut::PerspectiveCamera::CalculateMatrices()
{
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(mPosition - cameraTarget);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);

	mViewMatrix = glm::lookAt(mPosition, mPosition + cameraFront, glm::vec3(0, 1, 0));

	mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
}

Walnut::PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float nearPlane, float farPlane)
	: Camera()
{
	mPosition = glm::vec3(0, 0, 0);
	mProjectionMatrix = glm::perspective(glm::radians(fov), width / height, nearPlane, farPlane);
	mViewMatrix = glm::lookAt(mPosition, mPosition + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0, 1, 0));
	mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
}
