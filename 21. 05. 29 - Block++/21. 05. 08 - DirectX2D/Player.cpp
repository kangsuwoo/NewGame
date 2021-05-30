#include "stdafx.h"
#include "Player.h"

#include "BlockManager.h"

Player::Player()
	: m_Renderer(nullptr), pBlocks(nullptr),
	m_Status(0)
{
}

Player::~Player()
{
	SAFE_DELETE(m_Renderer);
}

HRESULT Player::Start()
{
	auto tex = _Texture->LoadTexture("Character", L"../_Resources/jimmy.png", 11, 4);
	tex->Resize( 103.5, 90);

	m_Renderer = new Renderer("Character");
	m_Renderer->Position = { _Application->Width / 2.0f, _Application->Height / 2.0f };
	m_Renderer->Scale = { 1.0f , 1.0f };


	//	애니메이션 넣는 순서는
	//	내가 만든 상태 인덱스와 동일해야한다
	//	IDLE = 0, MOVE (1), JUMP (2)
	//	넣을 때 순서만 잘 지켜주자!

	D2D_POINT_2U idle[] = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0} };
	m_Renderer->AddAnimation(idle, 11, 5, true);

	D2D_POINT_2U move[] = { {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}};
	m_Renderer->AddAnimation(move, 6, 5);

	

	return S_OK;
}

void Player::Update()
{
	if (_KeyCode->GetKey(VK_LEFT) || _KeyCode->GetKey('A')) {
		m_Status = MOVE;

		m_Renderer->Position.x -= 4.0f;
		m_Renderer->isReverse = true;
	}
	else if (_KeyCode->GetKey(VK_RIGHT) || _KeyCode->GetKey('D')) {
		m_Status = MOVE;

		m_Renderer->Position.x += 4.0f;
		m_Renderer->isReverse = false;
	}
	else if (_KeyCode->GetKey(VK_UP) || _KeyCode->GetKey('W')) {
		m_Status = MOVE;

		m_Renderer->Position.y -= 4.0f;
		
	}
	else if (_KeyCode->GetKey(VK_DOWN) || _KeyCode->GetKey('S')) {
		 m_Status = MOVE;

		m_Renderer->Position.y += 4.0f;
	
	}
	else {
		 m_Status = IDLE;
	}

	m_Renderer->Update(m_Status);

	for (auto p : pBlocks->GetBlocks()) {
		if (m_Renderer->CheckLocation(p->GetRect()))
		{
			m_Status = IDLE;
			break;
		}
	}
}

void Player::Render()
{
	m_Renderer->Render();
}
