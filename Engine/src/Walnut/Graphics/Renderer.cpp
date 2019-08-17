#include "wnpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Walnut/Platform/OpenGL/GLShader.h"
#include "glad/glad.h"

Walnut::Renderer::SceneData* Walnut::Renderer::mSceneData = new Walnut::Renderer::SceneData();

void Walnut::Renderer::BeginScene(Camera& camera)
{
	mSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Walnut::Renderer::EndScene()
{

}

void Walnut::Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
{
	shader->Bind();
	std::dynamic_pointer_cast<Walnut::GLShader>(shader)->UploadUniformMat4("uViewProjection", mSceneData->ViewProjectionMatrix);
	std::dynamic_pointer_cast<Walnut::GLShader>(shader)->UploadUniformMat4("uTransform", transform);
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void Walnut::Renderer::Submit(const std::shared_ptr<Square>& square)
{
	glBindTexture(GL_TEXTURE_2D, square->GetTexture());
	square->GetShader()->Bind();
	std::dynamic_pointer_cast<Walnut::GLShader>(square->GetShader())->UploadUniformMat4("uViewProjection", mSceneData->ViewProjectionMatrix);
	std::dynamic_pointer_cast<Walnut::GLShader>(square->GetShader())->UploadUniformMat4("uTransform", square->GetTransform());
	std::dynamic_pointer_cast<Walnut::GLShader>(square->GetShader())->UploadUniformFloat3("uColor", square->GetColor());
	square->GetVA()->Bind();
	RenderCommand::DrawIndexed(square->GetVA());
}
