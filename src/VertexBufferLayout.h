#pragma once

#include <vector>
#include "Render.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case(GL_FLOAT):			return 4;
			case(GL_UNSIGNED_INT):	return 4;
			case(GL_UNSIGNED_BYTE):	return 1;
		}
		ASSERT(false);
		return 0;

	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Element;
	unsigned int m_Stride;

public:
	VertexBufferLayout() : m_Stride(0) {};

	template<typename T>

	void PushBack(unsigned int count)
	{
		ASSERT(false);
	}

	template<>
	void PushBack<float>(unsigned int count)
	{
		m_Element.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void PushBack<unsigned int>(unsigned int count)
	{
		m_Element.push_back({ GL_UNSIGNED_INT,count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void PushBack<unsigned char>(unsigned int count)
	{
		m_Element.push_back({ GL_UNSIGNED_BYTE,count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline unsigned int GetStride()const { return m_Stride; }
	inline std::vector<VertexBufferElement> GetElement() const { return m_Element; }
};