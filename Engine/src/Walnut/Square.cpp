#include "wnpch.h"
#include "Square.h"
#include <glm/ext/matrix_transform.inl>


#define STB_IMAGE_IMPLEMENTATION
#include "../Extern/stb_image.h"
#include "glad/glad.h"

int Walnut::Square::mID = 0;

Walnut::Square::Square(const glm::vec3 & color)
	: mPosition(glm::vec3(0, 0, 0)), mColor(color), mScale(glm::vec3(1, 1, 1))
{

	std::stringstream ss;
	ss << "Square " << mID++;
	mName = ss.str();

	mVertexArray.reset(VertexArray::Create());

	float vertices[] = {
		-1.0, -1.0,  1.0, 0.0f, 0.0f,
		 1.0, -1.0,  1.0, 1.0f, 0.0f,
		 1.0,  1.0,  1.0, 1.0f, 1.0f,
		-1.0,  1.0,  1.0, 0.0f, 1.0f,
	};


	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("Circle.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	std::shared_ptr<VertexBuffer> vertexbuffer;
	vertexbuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	Walnut::BufferLayout layout = {
		{Walnut::ShaderDataType::Float3, "aPosition"},
		{Walnut::ShaderDataType::Float2, "aTexCoord"},
	};

	vertexbuffer->SetLayout(layout);

	mVertexArray->AddVertexBuffer(vertexbuffer);

	uint32_t indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
	};

	std::shared_ptr<Walnut::IndexBuffer> indexBuffer;
	indexBuffer.reset(Walnut::IndexBuffer::Create(indices, 6));
	mVertexArray->SetIndexBuffer(indexBuffer);

	mShader.reset(Walnut::Shader::CreateDefault());

	CalculateTransform();
}

void Walnut::Square::SetPosition(const glm::vec3& pos)
{
	mPosition = pos;
	CalculateTransform();
}

void Walnut::Square::SetScale(const glm::vec3& scale)
{
	mScale = scale;
	CalculateTransform();
}

const glm::mat4 & Walnut::Square::GetTransform() const
{
	return mTransform;
}

void Walnut::Square::CalculateTransform()
{
	mTransform = translate(glm::mat4(1.0f), mPosition) * scale(glm::mat4(1.0f), mScale);
}

