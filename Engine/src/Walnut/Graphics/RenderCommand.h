#pragma once
#include "RendererAPI.h"

namespace Walnut
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color) { sRendererApi->SetClearColor(color); }
		inline static void Clear() { sRendererApi->Clear(); }
		inline static void DrawIndexed(const std::shared_ptr <VertexArray>& vertexArray) { sRendererApi->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* sRendererApi;
	};
}
