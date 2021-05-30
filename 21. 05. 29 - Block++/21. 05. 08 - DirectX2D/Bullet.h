#pragma once

class Bullet
{
public:
	Bullet(float x, float y, float angle, float speed, bool isLeft);
	~Bullet();

private:
	BaseTexture* m_Texture;

	UINT m_CurrentFrameX;
	D2D_VECTOR_2F m_Position;
	float m_Angle;
	float m_Speed;
	bool m_IsReverse;

	int m_CurrentFrame;

public:
	bool Update();
	void Render();

	D2D1_ELLIPSE GetCircle()
	{
		float radius = m_Texture->GetSize().width / 2.0f;
		return D2D1::Ellipse(
			D2D1::Point2F(m_Position.x + radius, m_Position.y + radius),
			radius, radius);
	}

};

