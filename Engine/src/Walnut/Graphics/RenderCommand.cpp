#include "wnpch.h"
#include "RenderCommand.h"
#include "Walnut/Platform/OpenGL/GLRendererAPI.h"

Walnut::RendererAPI* Walnut::RenderCommand::sRendererApi = new GLRendererAPI();
