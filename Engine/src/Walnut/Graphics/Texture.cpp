#include "wnpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Walnut/Platform/OpenGL/GLTexture.h"

Walnut::Texture * Walnut::Texture::Create(const std::string& filePath)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: WN_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
	case RendererAPI::API::OpenGL: return new GLTexture(filePath);
	}

	WN_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}
