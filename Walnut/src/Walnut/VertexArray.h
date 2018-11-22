#pragma once
#include "Core.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Walnut {
	namespace Rendering {

		class WALNUT_API VertexArray
		{

		private:
			unsigned int mRenderID;
		public:
			VertexArray();
			~VertexArray();

			void Bind()const;
			void Unbind()const;

			void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)const;

		};
	}
}

