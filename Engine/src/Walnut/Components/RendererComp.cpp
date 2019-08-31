#include "wnpch.h"
#include "RendererComp.h"
#include "Walnut/Graphics/Renderer.h"
#include "Transform.h"

Walnut::Components::RendererComp::RendererComp()
	: Component(), mColor(glm::vec3(1, 1, 1))
{
	mVertexArray.reset(VertexArray::Create());

	float verticesWithTexCoords[] = {
		// front 
		-1.0, -1.0,  1.0, 1.0f, 0.0f,
		 1.0, -1.0,  1.0, 0.0f, 0.0f,
		 1.0,  1.0,  1.0, 0.0f, 1.0f,
		-1.0,  1.0,  1.0, 1.0f, 1.0f,
		// back 
		-1.0, -1.0, -1.0, 1.0f, 0.0f,
		 1.0, -1.0, -1.0, 0.0f, 0.0f,
		 1.0,  1.0, -1.0, 0.0f, 1.0f,
		-1.0,  1.0, -1.0, 1.0f, 1.0f
	};

	mTexture.reset(Texture::Create("Logo.png"));

	std::shared_ptr<VertexBuffer> vertexbuffer;


	vertexbuffer.reset(VertexBuffer::Create(verticesWithTexCoords, sizeof(verticesWithTexCoords)));

	Walnut::BufferLayout layout = {
		{Walnut::ShaderDataType::Float3, "aPosition"},
		{Walnut::ShaderDataType::Float2, "aTexCoord"}
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
}


void Walnut::Components::RendererComp::OnAdd(const GameObject& obj)
{
	mGameObject = obj;
}

void Walnut::Components::RendererComp::Update()
{
	//Transform* t = mGameObject.GetTransformMatrix();
	const glm::mat4 transform = mGameObject.GetTransformMatrix();

	Walnut::Renderer::Submit(mShader, mVertexArray, mTexture, mColor, transform);
	//Walnut::Renderer::Submit(mShader, mVertexArray, mColor, glm::mat4(1.0f));
}

void Walnut::Components::RendererComp::SetShader(const std::string& shaderType)
{
	mShader.reset(Walnut::Shader::Create(shaderType));
}
