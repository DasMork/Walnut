#pragma once
#include "GameObject.h"

namespace Walnut
{
	class Component
	{
	public:
		Component() {}
		Component(const GameObject& obj)
			: mGameObject(obj)
		{
		}
		virtual ~Component() = default;

		enum class ComponentType
		{
			None = 0,
			Transform,
			Renderer
		};
	public:
		virtual void OnAdd() = 0;
		virtual void Update() = 0;
		virtual const char* GetName() const = 0;
		void SetGameObject(const GameObject& obj) { mGameObject = obj; }
		const GameObject& GetGameObject() const { return mGameObject; }
		virtual ComponentType GetEventType() const = 0;


	protected:
		GameObject mGameObject;
	};
}
