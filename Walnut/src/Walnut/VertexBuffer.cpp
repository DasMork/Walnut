#include "VertexBuffer.h"
#include "Rendering.h"


Walnut::Rendering::VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	:mRenderID(0)
{
	glGenBuffers(1, &mRenderID);
	glBindBuffer(GL_ARRAY_BUFFER, mRenderID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);
}


Walnut::Rendering::VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &mRenderID));
}

void Walnut::Rendering::VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mRenderID);
}

void Walnut::Rendering::VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
