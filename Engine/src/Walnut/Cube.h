#pragma once
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include <glm/glm.hpp>

namespace Walnut
{
	class Cube
	{
	public:
		Cube(const glm::vec3& color = { 1,1,1 });


		void SetColor(const glm::vec3& color) { mColor = color; }
		void SetPosition(const glm::vec3& pos);
		void SetScale(const glm::vec3& scale);
		const glm::vec3& GetColor() const { return mColor; }
		const glm::vec3& GetPosition() const { return mPosition; }
		const glm::vec3& GetScale() const { return mScale; }
		const std::string& GetName() const { return mName; }
		const glm::mat4& GetTransform() const;
		const std::shared_ptr<Walnut::Shader>& GetShader() const { return mShader; }
		const std::shared_ptr<Walnut::VertexArray>& GetVA() const { return mVertexArray; }
		glm::vec3 mColor;

	private:
		void CalculateTransform();
	private:
		static int mID;
		std::shared_ptr<Walnut::VertexArray> mVertexArray;
		std::shared_ptr<Walnut::Shader> mShader;
		std::string mName;

		glm::vec3 mPosition;
		glm::vec3 mScale;
		glm::mat4 mTransform;

	};
}