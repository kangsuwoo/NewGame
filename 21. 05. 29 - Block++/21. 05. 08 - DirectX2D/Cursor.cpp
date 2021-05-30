#include "stdafx.h"
#include "Cursor.h"

Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

HRESULT Cursor::Start()
{
	ShowCursor(false);
	_Texture->LoadTexture("Cursor", L"../_Resources/spr_crosshair_0.png");

	return S_OK;
}

void Cursor::Update()
{
}

void Cursor::Render()
{
	_Texture->Find("Cursor")->Draw(MousePoint.x, MousePoint.y, 45, 45);
}
