#include "wnpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Walnut/Platform/OpenGL/GLBuffer.h"

Walnut::VertexBuffer* Walnut::VertexBuffer::Create(float* vertices, uint32_t size)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
	case RendererAPI::API::OpenGL: return new GLVertexBuffer(vertices, size);
	}

	WN_CORE_ASSERT(false, "Unknown RendererAPI");
}

Walnut::IndexBuffer * Walnut::IndexBuffer::Create(uint32_t * indices, uint32_t size)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
	case RendererAPI::API::OpenGL: return new GLIndexBuffer(indices, size);
	}

	WN_CORE_ASSERT(false, "Unknown RendererAPI");
}
