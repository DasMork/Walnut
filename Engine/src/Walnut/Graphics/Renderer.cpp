#include "wnpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

void Walnut::Renderer::BeginScene()
{
}

void Walnut::Renderer::EndScene()
{

}

void Walnut::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
{
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
