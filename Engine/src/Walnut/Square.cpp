#include "wnpch.h"
#include "Square.h"
#include <glm/ext/matrix_transform.inl>


int Walnut::Square::mID = 0;

Walnut::Square::Square(const glm::vec3 & color)
	: mPosition(glm::vec3(0, 0, 0)), mColor(color), mScale(glm::vec3(1, 1, 1))
{

	std::stringstream ss;
	ss << "Square " << mID++;
	mName = ss.str();

	mVertexArray.reset(VertexArray::Create());

	float vertices[4 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 -0.5f,  0.5f, 0.0f
	};

	std::shared_ptr<VertexBuffer> vertexbuffer;
	vertexbuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	Walnut::BufferLayout layout = {
		{Walnut::ShaderDataType::Float3, "aPosition"},
	};

	vertexbuffer->SetLayout(layout);

	mVertexArray->AddVertexBuffer(vertexbuffer);

	uint32_t indices[6] = { 0,1,2,2,3,0 };

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

