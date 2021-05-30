#pragma once
#include "Bullet.h"

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

private:
	std::vector<Bullet*> m_Bullets;

public:
	void Update();
	void Render();

	void Shoot(float x, float y, float angle, float speed, bool isLeft);

};

