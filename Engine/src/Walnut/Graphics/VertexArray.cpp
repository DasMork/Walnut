#include "wnpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "GLVertexArray.h"

Walnut::VertexArray* Walnut::VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
	case RendererAPI::OpenGL: return new GLVertexArray();
	}

	WN_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}
