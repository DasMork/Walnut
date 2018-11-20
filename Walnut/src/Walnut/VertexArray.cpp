#include "VertexArray.h"
#include "Rendering.h"


Walnut::Rendering::VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &mRenderID));
}


Walnut::Rendering::VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &mRenderID));
}

void Walnut::Rendering::VertexArray::Bind() const
{
	GLCall(glBindVertexArray(mRenderID));
}

void Walnut::Rendering::VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));

}

void Walnut::Rendering::VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout) const
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i) {
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(0, element.count, element.type, element.normalized, layout.GetStride(), (void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);

	}
}
