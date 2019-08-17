#include "wnpch.h"
#include "Renderable.h"
#include <glm/ext/matrix_transform.inl>

int Walnut::Renderable::mID = 0;

void Walnut::Renderable::SetPosition(const glm::vec3& pos)
{
	mPosition = pos;
	CalculateTransform();
}

void Walnut::Renderable::SetScale(const glm::vec3& scale)
{
	mScale = scale;
	CalculateTransform();
}

const glm::mat4 & Walnut::Renderable::GetTransform() const
{
	return mTransform;
}

void Walnut::Renderable::CalculateTransform()
{
	mTransform = translate(glm::mat4(1.0f), mPosition) * scale(glm::mat4(1.0f), mScale);
}

