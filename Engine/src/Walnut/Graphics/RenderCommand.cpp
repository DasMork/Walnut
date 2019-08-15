#include "wnpch.h"
#include "RenderCommand.h"
#include "GLRendererAPI.h"

Walnut::RendererAPI* Walnut::RenderCommand::sRendererApi = new GLRendererAPI();
