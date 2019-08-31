#include "wnpch.h"
#include "Cube.h"

Walnut::Cube::Cube(const glm::vec3 & color)
	:Renderable()
{

	mPosition = glm::vec3(0, 0, 0);
	mColor = color;
	mScale = glm::vec3(1, 1, 1);

	mHasTexture = false;

	std::stringstream ss;
	ss << "Cube " << mID++;
	mName = ss.str();

	mVertexArray.reset(VertexArray::Create());

	float vertices[] = {
		// front
		-1.0, -1.0,  1.0,
		 1.0, -1.0,  1.0,
		 1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		// back
		-1.0, -1.0, -1.0,
		 1.0, -1.0, -1.0,
		 1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0
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

	mShader.reset(Walnut::Shader::Create("Flat Color"));

	CalculateTransform();
}
