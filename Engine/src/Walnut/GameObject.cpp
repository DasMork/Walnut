#include "wnpch.h"
#include "GameObject.h"
#include "Components/Transform.h"

int Walnut::GameObject::mID = 0;

Walnut::GameObject::GameObject()
{
	std::stringstream ss;
	ss << "new GameObject (" << mID++ << ")";
	mName = ss.str();
}

const glm::mat4& Walnut::GameObject::GetTransformMatrix()
{
	return GetComponent<Components::Transform>()->GetTransform();
}
