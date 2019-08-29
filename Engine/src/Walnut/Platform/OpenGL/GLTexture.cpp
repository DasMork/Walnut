#include "wnpch.h"
#include "GLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../../Extern/stb_image.h"
#include "glad/glad.h"

Walnut::GLTexture::GLTexture(const std::string & filePath)
{
	glGenTextures(1, &mRendererID);
	glBindTexture(GL_TEXTURE_2D, mRendererID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	GLenum imageType;

	if (nrChannels == 3)
		imageType = GL_RGB;
	else if (nrChannels == 4)
		imageType = GL_RGBA;

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, imageType, width, height, 0, imageType, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void Walnut::GLTexture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, mRendererID);
}

void Walnut::GLTexture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
