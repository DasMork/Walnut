#include "wnpch.h"
#include "GLVertexArray.h"
#include "glad/glad.h"

static GLenum ShaderDataTypeToOpenGLBasetype(Walnut::ShaderDataType type)
{
	switch (type)
	{
	case Walnut::ShaderDataType::Float:  return GL_FLOAT;
	case Walnut::ShaderDataType::Float2: return GL_FLOAT;
	case Walnut::ShaderDataType::Float3: return GL_FLOAT;
	case Walnut::ShaderDataType::Float4: return GL_FLOAT;
	case Walnut::ShaderDataType::Mat3:   return GL_FLOAT;
	case Walnut::ShaderDataType::Mat4:   return GL_FLOAT;
	case Walnut::ShaderDataType::Int:    return GL_INT;
	case Walnut::ShaderDataType::Int2:   return GL_INT;
	case Walnut::ShaderDataType::Int3:   return GL_INT;
	case Walnut::ShaderDataType::Int4:   return GL_INT;
	case Walnut::ShaderDataType::Bool:   return GL_BOOL;
	}
	WN_CORE_ASSERT(false, "Unknown ShaderDataType!");
}

Walnut::GLVertexArray::GLVertexArray()
{
	glCreateVertexArrays(1, &mRenderID);
}

Walnut::GLVertexArray::~GLVertexArray()
{
	glDeleteVertexArrays(1, &mRenderID);
}

void Walnut::GLVertexArray::Bind() const
{
	glBindVertexArray(mRenderID);
}

void Walnut::GLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void Walnut::GLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(mRenderID);
	vertexBuffer->Bind();

	uint32_t index = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBasetype(element.Type),
			element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);

		index++;
	}

	mVertexBuffers.push_back(vertexBuffer);
}

void Walnut::GLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(mRenderID);
	indexBuffer->Bind();
	mIndexBuffer = indexBuffer;
}
