#pragma once
#include "Walnut/Component.h"
#include <glm/glm.hpp>

namespace Walnut
{
	namespace Components
	{
		class Transform : public Component
		{
		public:
			Transform();

			void OnAdd(const GameObject& obj) override;
			void Update() override;

			void SetPosition(const glm::vec3& pos);
			void SetScale(const glm::vec3& scale);

			const char* GetName()  const override { return "Transform"; }
			const glm::vec3& GetPosition() const { return mPosition; }
			const glm::vec3& GetScale() const { return mScale; }
			const glm::mat4& GetTransform() const;


			ComponentType GetEventType() const override { return GetStaticType(); }
			static ComponentType GetStaticType() { return ComponentType::Transform; }
		protected:
			void CalculateTransform();
		private:
			glm::vec3 mPosition;
			glm::vec3 mScale;
			glm::mat4 mTransform;
		};
	}
}
