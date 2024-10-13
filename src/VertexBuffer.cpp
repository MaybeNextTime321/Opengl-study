#include "Render.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, unsigned int size)
{
    GL_DEBUG_CALL(glGenBuffers(1, &m_BufferID));
    GL_DEBUG_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
    GL_DEBUG_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GL_DEBUG_CALL(glDeleteBuffers(1, &m_BufferID));
}

unsigned int VertexBuffer::GetIndex() const
{
    return m_BufferID;
}

void VertexBuffer::Bind() const
{
    GL_DEBUG_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
}

void VertexBuffer::Unbind() const
{
    GL_DEBUG_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
