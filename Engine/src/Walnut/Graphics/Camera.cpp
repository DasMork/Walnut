#include "wnpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Walnut::OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: mPosition({ 0,0,0 }), mProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), mViewMatrix(1.0f)
{
	mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
}

void Walnut::OrthographicCamera::CalculateMatrices()
{
	glm::mat4 transform = translate(glm::mat4(1.0f), mPosition)
		* rotate(glm::mat4(1.0f), mRotation, glm::vec3(0, 0, 1));

	mViewMatrix = glm::inverse(transform);
	mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
}
