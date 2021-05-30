#include "stdafx.h"
#include "BlockManager.h"

BlockManager::BlockManager()
{
}

BlockManager::~BlockManager()
{
	for (auto p : m_Blocks)
		SAFE_DELETE(p);
}

HRESULT BlockManager::Start()
{
	_Texture->LoadTexture("Block", L"../_Resources/block.png");

	//	Floor
	m_Blocks.push_back(new Block(
		"Block",
		D2D1::RectF(0,0,(float)_Application->Width + 50.0f, (float)_Application->Height)));

	//	Left block
	m_Blocks.push_back(new Block(
		"Block",
		D2D1::RectF(-10.0f, 500.0f - 50.0f, 200.0f, 500.0f)
	));

	return S_OK;
}

void BlockManager::Update()
{
}

void BlockManager::Render()
{
	for (auto p : m_Blocks)
		p->Render();
}
