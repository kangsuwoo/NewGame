#include "stdafx.h"
#include "Block.h"

Block::Block(std::string name, D2D_RECT_F rect)
	: m_Rect(rect)
{
	m_Texture = _Texture->Find(name);
}

Block::~Block()
{
}

void Block::Update()
{
}

void Block::Render()
{
	if (m_Texture != nullptr)
		m_Texture->Draw(
			m_Rect.left,
			m_Rect.top,
			m_Rect.right - m_Rect.left,
			m_Rect.bottom - m_Rect.top);
}
