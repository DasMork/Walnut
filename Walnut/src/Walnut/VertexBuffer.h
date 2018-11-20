#pragma once
#include "Core.h"

namespace Walnut {
	namespace Rendering {

		class WALNUT_API VertexBuffer
		{
		private:
			unsigned int mRenderID;

		public:
			VertexBuffer(const void* data, unsigned int size);
			~VertexBuffer();

			void Bind()const;
			void Unbind()const;
		};
	}
}