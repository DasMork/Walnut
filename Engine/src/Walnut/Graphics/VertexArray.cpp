#include "wnpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Walnut/Platform/OpenGL/GLVertexArray.h"

Walnut::VertexArray* Walnut::VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
	case RendererAPI::API::OpenGL: return new GLVertexArray();
	}

	WN_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}
