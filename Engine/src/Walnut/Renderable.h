#pragma once
#include <glm/vec3.hpp>
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include <glm/glm.hpp>

namespace Walnut
{
	class Renderable
	{
	public:
		void SetColor(const glm::vec3& color) { mColor = color; }
		void SetPosition(const glm::vec3& pos);
		void SetScale(const glm::vec3& scale);
		const glm::vec3& GetColor() const { return mColor; }
		const glm::vec3& GetPosition() const { return mPosition; }
		const glm::vec3& GetScale() const { return mScale; }
		const std::string& GetName() const { return mName; }
		uint32_t GetTexture() const { return mTexture; }
		const glm::mat4& GetTransform() const;
		const std::shared_ptr<Walnut::Shader>& GetShader() const { return mShader; }
		const std::shared_ptr<Walnut::VertexArray>& GetVA() const { return mVertexArray; }

		virtual bool HasTexture() const { return mHasTexture; };

	protected:
		void CalculateTransform();
	protected:
		static int mID;
		std::shared_ptr<Walnut::VertexArray> mVertexArray;
		std::shared_ptr<Walnut::Shader> mShader;
		std::string mName;

		glm::vec3 mPosition;
		glm::vec3 mColor;
		glm::vec3 mScale;
		glm::mat4 mTransform;

		bool mHasTexture = false;
		uint32_t mTexture;
	};
}