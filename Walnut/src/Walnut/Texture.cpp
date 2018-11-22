#include "Texture.h"
#include "Rendering.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Walnut::Rendering::Texture::Texture(const std::string& filepath)
	: mFilePath(filepath), mWidth(0), mHeight(0), mBPP(0)
{
	stbi_set_flip_vertically_on_load(1);

	mLocalBuffer = stbi_load(filepath.c_str(), &mWidth, &mHeight, &mBPP, 4);

	if (mLocalBuffer == NULL)
		WN_CORE_ERROR("Could not load file at {}", filepath);

	GLCall(glGenTextures(1, &mRenderID));
	GLCall(glBindTexture(GL_TEXTURE_2D, mRenderID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (mLocalBuffer)
		stbi_image_free(mLocalBuffer);
}

Walnut::Rendering::Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &mRenderID));
}

void Walnut::Rendering::Texture::Bind(int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, mRenderID));
}

void Walnut::Rendering::Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
