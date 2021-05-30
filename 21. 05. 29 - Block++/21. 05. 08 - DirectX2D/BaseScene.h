#pragma once
#include "Player.h"
#include "Cursor.h"
#include "Weapon.h"
#include "BlockManager.h"

//	IScene �̶�� �༮�� ������ָ�
//	�� �༮�� �� �̾�! ��� �˷��ְԵȴ� (Start, Update, Render)
class BaseScene : public IScene
{
public:
	BaseScene();
	~BaseScene();

private:
	Player* m_Player;
	Cursor* m_Cursor;
	Weapon* m_Weapon;
	BlockManager* m_BlockManager;

public:
	// IScene��(��) ���� ��ӵ�
	virtual HRESULT Start() override;
	virtual void Update() override;
	virtual void Render() override;
};

