#include "wnpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Walnut/Platform/OpenGL/GLShader.h"

Walnut::Shader* Walnut::Shader::CreateDefault()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
	case RendererAPI::API::OpenGL: return new GLShader();
	}

	WN_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

Walnut::Shader * Walnut::Shader::Create(const std::string & vertexSrc, const std::string & fragmentSrc)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
	case RendererAPI::API::OpenGL: return new GLShader(vertexSrc, fragmentSrc);
	}

	WN_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}