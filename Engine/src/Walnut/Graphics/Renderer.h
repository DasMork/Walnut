#pragma once
#include "RendererAPI.h"
#include "Shader.h"
#include "Camera.h"


namespace Walnut
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr <VertexArray>& vertexArray);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewPorjectionMatrix;
		};

		static SceneData* mSceneData;
	};
}
