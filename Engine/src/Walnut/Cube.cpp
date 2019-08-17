#include "wnpch.h"
#include "Cube.h"

#include <glm/ext/matrix_transform.inl>

int Walnut::Cube::mID = 0;

Walnut::Cube::Cube(const glm::vec3 & color)
	: mPosition(glm::vec3(0, 0, 0)), mColor(color), mScale(glm::vec3(1, 1, 1))
{

	std::stringstream ss;
	ss << "Cube " << mID++;
	mName = ss.str();

	mVertexArray.reset(VertexArray::Create());

	float vertices[] = {
		// front
		-1.0, -1.0,  1.0, 0.0f, 0.0f,
		 1.0, -1.0,  1.0, 1.0f, 0.0f,
		 1.0,  1.0,  1.0, 1.0f, 1.0f,
		-1.0,  1.0,  1.0, 0.0f, 1.0f,
		// back
		-1.0, -1.0, -1.0, 0.0f, 0.0f,
		 1.0, -1.0, -1.0, 1.0f, 0.0f,
		 1.0,  1.0, -1.0, 1.0f, 1.0f,
		-1.0,  1.0, -1.0, 0.0f, 1.0f
	};

	std::shared_ptr<VertexBuffer> vertexbuffer;
	vertexbuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	Walnut::BufferLayout layout = {
		{Walnut::ShaderDataType::Float3, "aPosition"},
	};

	vertexbuffer->SetLayout(layout);

	mVertexArray->AddVertexBuffer(vertexbuffer);

	uint32_t indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	std::shared_ptr<Walnut::IndexBuffer> indexBuffer;
	indexBuffer.reset(Walnut::IndexBuffer::Create(indices, 36));
	mVertexArray->SetIndexBuffer(indexBuffer);

	mShader.reset(Walnut::Shader::CreateDefault());

	CalculateTransform();
}

void Walnut::Cube::SetPosition(const glm::vec3& pos)
{
	mPosition = pos;
	CalculateTransform();
}

void Walnut::Cube::SetScale(const glm::vec3& scale)
{
	mScale = scale;
	CalculateTransform();
}

const glm::mat4 & Walnut::Cube::GetTransform() const
{
	return mTransform;
}

void Walnut::Cube::CalculateTransform()
{
	mTransform = translate(glm::mat4(1.0f), mPosition) * scale(glm::mat4(1.0f), mScale);
}

