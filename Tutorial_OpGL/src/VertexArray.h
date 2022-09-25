#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout;
class VertexArray
{
public:
	unsigned int m_RendererID;
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer const& vb, VertexBufferLayout const& layout);

	void Bind() const;
	void Unbind() const;
};

