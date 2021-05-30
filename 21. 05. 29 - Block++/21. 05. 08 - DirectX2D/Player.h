#pragma once
#include "Renderer.h"

class BlockManager;
class Player
{
	enum Status {
		IDLE = 0,
		MOVE,

		ATTACK,

	};

public:
	Player();
	~Player();

	HRESULT Start();
	void Update();
	void Render();

	D2D_VECTOR_2F GetPosition() { return m_Renderer->Position; }
	int GetReverse() { return m_Renderer->isReverse; }

private:
	Renderer* m_Renderer;
	int m_Status;

public:
	BlockManager* pBlocks;

};
