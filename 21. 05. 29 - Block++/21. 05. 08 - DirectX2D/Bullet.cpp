#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(float x, float y, float angle, float speed, bool isLeft)
	: m_Position({x, y}), m_Speed(speed),
	  m_CurrentFrameX(9), m_CurrentFrame(0),
	  m_Angle(angle), m_IsReverse(isLeft)
{
	m_Texture = _Texture->LoadTexture("Ä³¸¯ÅÍ", L"../_Resources/Bullet.png", 16, 11);
}

Bullet::~Bullet()
{
}

bool Bullet::Update()
{
	float x = cosf(m_Angle) * m_Speed;
	float y = sinf(m_Angle) * m_Speed;

	m_Position.x += x;
	m_Position.y += y;

	m_CurrentFrame++;
	if (m_CurrentFrame % 8 == 0)
	{
		m_CurrentFrameX++;
		if (m_CurrentFrameX == 14 + 1)
			m_CurrentFrameX = 9;

		m_CurrentFrame = 0;
	}

	if (m_Position.x <= -m_Texture->GetSize().width || m_Position.x > _Application->Width + m_Texture->GetSize().width)
		return false;

	return true;
}

void Bullet::Render()
{
	m_Texture->DrawFrame(m_Position.x, m_Position.y, m_CurrentFrameX, 0, 0, 0, m_IsReverse);
}
