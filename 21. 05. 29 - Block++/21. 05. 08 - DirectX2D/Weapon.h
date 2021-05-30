#pragma once
#include "Renderer.h"

class Weapon
{
public:
	Weapon();
	~Weapon();

	HRESULT Start();
	void Update();
	void Render();

	Player* pPlayer;
};

