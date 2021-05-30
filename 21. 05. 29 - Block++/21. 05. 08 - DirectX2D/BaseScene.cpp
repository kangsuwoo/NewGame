#include "stdafx.h"
#include "BaseScene.h"

BaseScene::BaseScene()
{
}

BaseScene::~BaseScene()
{
	//	delete m_Player;
	SAFE_DELETE(m_BlockManager);
	SAFE_DELETE(m_Player);

}

HRESULT BaseScene::Start()
{
	m_Cursor = new Cursor();
	if (FAILED(m_Cursor->Start())) return E_FAIL;

	m_Weapon = new Weapon();
	if (FAILED(m_Weapon->Start())) return E_FAIL;

	m_BlockManager = new BlockManager();
	if (FAILED(m_BlockManager->Start())) return E_FAIL;

	m_Player = new Player();
	m_Player->pBlocks = m_BlockManager;
	m_Player->Start();

	m_Weapon->pPlayer = m_Player;


	return S_OK;
}

void BaseScene::Update()
{
	m_Player->Update();

	m_Cursor->Update();

	m_Weapon->Update();
	
	if (_KeyCode->GetKeyDown(VK_ESCAPE)) PostQuitMessage(0);

	
}

void BaseScene::Render()
{
	m_BlockManager->Render();
	m_Player->Render();

	m_Weapon->Render();

	m_Cursor->Render();
}
