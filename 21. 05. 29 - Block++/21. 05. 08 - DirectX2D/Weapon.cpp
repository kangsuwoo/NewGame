#include "stdafx.h"
#include "Player.h"
#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

HRESULT Weapon::Start()
{
	_Texture->LoadTexture("Weapon", L"../_Resources/weapon rifle.png", 3, 1);

	return S_OK;
}

void Weapon::Update()
{
	if (MousePoint.x <= _Application->Width / 2.0f)
	{
		pPlayer->GetReverse(false);
	}
}

void Weapon::Render()
{
	_Texture->Find("Weapon")->Draw(pPlayer->GetPosition().x + 30, pPlayer->GetPosition().y + 50, 80, 40);
}
