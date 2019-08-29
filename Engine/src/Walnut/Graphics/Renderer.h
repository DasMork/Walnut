#pragma once
#include "RendererAPI.h"
#include "Shader.h"
#include "Camera.h"
#include "Walnut/Square.h"
#include "Texture.h"


namespace Walnut
{
	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr <VertexArray>& vertexArray, const std::shared_ptr<Texture>& texture,
			const glm::vec3& color = glm::vec3(1, 1, 1), const glm::mat4& transform = glm::mat4(1.0f));
		static void Submit(const std::shared_ptr<Renderable>& square, const glm::mat4& transform = glm::mat4(1.0f));

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* mSceneData;
	};
}
