#include "wnpch.h"
#include "GLBuffer.h"
#include "glad/glad.h"

//////////////////
//Vertex Buffer///
//////////////////
Walnut::GLVertexBuffer::GLVertexBuffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &mRenderID);
	glBindBuffer(GL_ARRAY_BUFFER, mRenderID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Walnut::GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &mRenderID);
}

void Walnut::GLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mRenderID);
}

void Walnut::GLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Walnut::GLVertexBuffer::SetLayout(const BufferLayout& layout)
{
	mLayout = layout;
}

/////////////////
//Index Buffer///
/////////////////
Walnut::GLIndexBuffer::GLIndexBuffer(uint32_t* indices, uint32_t count)
	: mCount(count)
{
	glCreateBuffers(1, &mRenderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRenderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

Walnut::GLIndexBuffer::~GLIndexBuffer()
{
	glDeleteBuffers(1, &mRenderID);
}

void Walnut::GLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRenderID);
}

void Walnut::GLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
