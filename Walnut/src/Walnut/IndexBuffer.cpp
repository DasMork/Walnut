#include "IndexBuffer.h"
#include "Rendering.h"


Walnut::Rendering::IndexBuffer::IndexBuffer(const void* data, unsigned int count)
	: mCount(count)
{
	glGenBuffers(1, &mRenderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRenderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}


Walnut::Rendering::IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &mRenderID));
}

void Walnut::Rendering::IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRenderID);
}

void Walnut::Rendering::IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}