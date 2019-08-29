#pragma once
#include "Walnut/Component.h"
#include "Walnut/Graphics/Shader.h"
#include "Walnut/Graphics/VertexArray.h"
#include <glm/glm.hpp>
#include "Walnut/Graphics/Texture.h"

namespace Walnut
{
	namespace Components
	{
		class RendererComp : public Component
		{
		public:
			RendererComp(const GameObject& obj);
			void OnAdd() override;
			void Update() override;
			ComponentType GetEventType() const override { return GetStaticType(); }
			static ComponentType GetStaticType() { return ComponentType::Renderer; }

			const char* GetName()  const override { return "Renderer"; }
			void SetColor(const glm::vec3& color) { mColor = color; }
			void SetShader(const std::shared_ptr<Shader>& shader) { mShader = shader; }
			void SetShader(const std::string & shaderType);
			const glm::vec3& GetColor() const { return mColor; }
			const std::shared_ptr<Shader>& GetShader() const { return mShader; }
			const std::shared_ptr<Texture>& GetTexture() const { return mTexture; }
			const std::shared_ptr<VertexArray>& GetVA() const { return mVertexArray; }

		private:
			std::shared_ptr<Walnut::VertexArray> mVertexArray;
			std::shared_ptr<Walnut::Shader> mShader;
			std::shared_ptr<Walnut::Texture> mTexture;
			glm::vec3 mColor;
		};
	}
}
