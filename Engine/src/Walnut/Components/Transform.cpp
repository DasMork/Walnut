#include "wnpch.h"
#include "Transform.h"
#include <glm/ext/matrix_transform.inl>

Walnut::Components::Transform::Transform()
	: Component(), mPosition(glm::vec3(0, 0, 0)), mScale(glm::vec3(1, 1, 1))
{
}

Walnut::Components::Transform::Transform(const GameObject& obj)
	: Component(obj), mPosition(glm::vec3(0, 0, 0)), mScale(glm::vec3(1, 1, 1))
{
	mTransform = glm::mat4(1.0f);
}

void Walnut::Components::Transform::OnAdd()
{
}

void Walnut::Components::Transform::Update()
{
	CalculateTransform();
}

void Walnut::Components::Transform::SetPosition(const glm::vec3& pos)
{
	mPosition = pos;
	CalculateTransform();
}

void Walnut::Components::Transform::SetScale(const glm::vec3& scale)
{
	mScale = scale;
	CalculateTransform();
}

const glm::mat4 & Walnut::Components::Transform::GetTransform() const
{
	//return glm::mat4(1.0f);
	return mTransform;
}

void Walnut::Components::Transform::CalculateTransform()
{
	mTransform = translate(glm::mat4(1.0f), mPosition) * scale(glm::mat4(1.0f), mScale);
}
