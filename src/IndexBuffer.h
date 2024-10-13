#pragma once
#include "Render.h"

class IndexBuffer
{
private:
	unsigned int m_BufferID;
	unsigned int m_Count;
public:
	IndexBuffer(void* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetIndex() const;
	unsigned int GetCount() const;


};