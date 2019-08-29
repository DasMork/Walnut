#pragma once
#include "Walnut/Graphics/Texture.h"

namespace Walnut
{
	class GLTexture : public Texture
	{
	public:
		GLTexture(const std::string& filePath);
		void Bind() const override;
		void Unbind() const override;

		uint32_t GetID() const override { return mRendererID; }
	private:
		uint32_t mRendererID;
	};
}
