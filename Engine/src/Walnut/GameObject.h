#pragma once
#include <glm/glm.hpp>

namespace Walnut
{
	class Component;

	class GameObject
	{

	public:
		class Component;
		GameObject();
		GameObject(const std::string& name) { mName = name; }

		const std::string& GetName() const { return mName; }

		template<typename T>
		T* GetComponent();

		template<typename T>
		void AddComponent(T* comp);

		const std::vector<Walnut::Component*>& GetAllComponents() const { return mComponents; }
		const glm::mat4& GetTransformMatrix();

		std::vector<Walnut::Component*>::iterator begin() { return mComponents.begin(); }
		std::vector<Walnut::Component*>::iterator end() { return mComponents.end(); }

	private:
		std::string mName;
		std::vector<Walnut::Component*> mComponents;

		static int mID;
	};

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (auto& comp : mComponents)
		{
			if (comp->GetEventType() == T::GetStaticType())
				return (T*)comp;
		}
		return nullptr;
	}

	template <typename T>
	void GameObject::AddComponent(T* comp)
	{
		if (GetComponent<T>() != nullptr)
			return;

		mComponents.push_back(comp);
	}
}