#include "stdafx.h"
#include "BulletManager.h"

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::Update()
{
	for (int i = 0; i < m_Bullets.size(); ++i)
	{
		if (!m_Bullets[i]->Update())
		{
			SAFE_DELETE(m_Bullets[i]);
			m_Bullets.erase(m_Bullets.begin() + i--);
		}
	}
}

void BulletManager::Render()
{
	for (auto i : m_Bullets)
	{
		i->Render();
		_RenderTarget->DrawEllipse(i->GetCircle(), _Renderer->GetBrush());
	}
}

void BulletManager::Shoot(float x, float y, float angle, float speed, bool isLeft)
{
	Bullet* pBullet = new Bullet(x, y, angle, speed, isLeft);
	m_Bullets.push_back(pBullet);
}
