#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(void* data, unsigned int count) : m_Count(count)
{
	GL_DEBUG_CALL(glGenBuffers(1, &m_BufferID));
	GL_DEBUG_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
	GL_DEBUG_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GL_DEBUG_CALL(glDeleteBuffers(1, &m_BufferID));
}

void IndexBuffer::Bind() const
{
	GL_DEBUG_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}

void IndexBuffer::Unbind() const
{
	GL_DEBUG_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::GetIndex() const
{
	return m_BufferID;
}

unsigned int IndexBuffer::GetCount() const
{
	return m_Count;
}
