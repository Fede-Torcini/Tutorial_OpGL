#pragma once
#include "Renderer.h"

class Texture3D
{
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture3D(const std::string& path);
	~Texture3D();

	void Bind(unsigned int slot=0) const;
	void Unbind();

	inline int GetWidth() const { return m_Width; }
	inline int Getheight() const { return m_Height; }
};

