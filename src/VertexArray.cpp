#include "VertexArray.h"
#include "Render.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GL_DEBUG_CALL(glGenVertexArrays(1, &m_RenderID));
}

VertexArray::~VertexArray()
{
	GL_DEBUG_CALL(glDeleteVertexArrays(1,&m_RenderID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const
{
	Bind();
	vb.Bind();
	const auto &layoutElements = layout.GetElement();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < layoutElements.size(); i++)
	{
		const auto& element = layoutElements[i];
		GL_DEBUG_CALL(glEnableVertexAttribArray(i));
		GL_DEBUG_CALL(glVertexAttribPointer(0, element.count, element.type, element.normalized, layout.GetStride(),(const void *)offset));

		offset += VertexBufferElement::GetSizeOfType(element.type) * element.count;
	}


}

void VertexArray::Bind() const
{
	GL_DEBUG_CALL(glBindVertexArray(m_RenderID));
}

void VertexArray::Unbind() const
{
	GL_DEBUG_CALL(glBindVertexArray(0));
}
