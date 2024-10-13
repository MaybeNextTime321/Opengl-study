#pragma once

class VertexBuffer
{
private:
	unsigned int m_BufferID;

public:
	VertexBuffer(void* data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetIndex() const;


};