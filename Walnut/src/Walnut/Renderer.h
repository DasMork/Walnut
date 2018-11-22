#pragma once
#include "Core.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace Walnut {
	namespace Rendering {

		class WALNUT_API Renderer
		{
		public:
			Renderer();
			~Renderer();

			void Clear();
			void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

		};
	}
}

