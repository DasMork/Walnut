#include "wnpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

Walnut::Renderer::SceneData* Walnut::Renderer::mSceneData = new Walnut::Renderer::SceneData();

void Walnut::Renderer::BeginScene(OrthographicCamera& camera)
{
	mSceneData->ViewPorjectionMatrix = camera.GetViewProjectionMatrix();
}

void Walnut::Renderer::EndScene()
{

}

void Walnut::Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
{
	shader->Bind();
	shader->UploadUniformMat4("uViewProjection", mSceneData->ViewPorjectionMatrix);
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
