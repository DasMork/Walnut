#pragma once
#include "Core.h"

namespace Walnut {
	namespace Rendering {

		class WALNUT_API IndexBuffer
		{
		private:
			unsigned int mRenderID;
			unsigned int mCount;

		public:
			IndexBuffer(const void* data, unsigned int count);
			~IndexBuffer();

			void Bind()const;
			void Unbind()const;

			inline unsigned int GetRenderID() const { return mRenderID; }
			inline unsigned int GetCount() const { return mCount; }
		};
	}
}
