#pragma once

#include "Core.h"
#include <string>


namespace Walnut {
	namespace Rendering {

		class WALNUT_API Texture
		{
		private:
			unsigned int mRenderID;
			std::string mFilePath;
			unsigned char* mLocalBuffer;
			int mWidth, mHeight, mBPP;
		public:
			Texture(const std::string& filepath);
			~Texture();

			void Bind(int slot = 0);
			void Unbind();
		};
	}
}
