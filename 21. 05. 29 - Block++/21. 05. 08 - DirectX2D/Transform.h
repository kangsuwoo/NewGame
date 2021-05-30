#pragma once

//	Transform ?
//	��ġ (Position), ũ��(Scale), ȸ��(Rotation)
//	�� ����ϴ� ��ü
//	��� �������� ����ϴ� Ŭ����
class Transform
{
public:
	Transform();
	virtual ~Transform();	//	���� �Ҹ���

	
	bool CheckLocation(D2D_RECT_F rect);

private:
	float m_Gravity;				//	�߷� ��
	float m_GravityDirection;		//	�߷� ����
	float m_PrevPositionY;			//	���� Position Y ��
	D2D_RECT_F m_CurrentFloorRect;	//	���� ����ִ� ��
	D2D_SIZE_F m_ImageSize;			//	������� �̹��� ũ��

protected:
	void UpdateJump();
	void SetImageSize(D2D_SIZE_F size) { m_ImageSize = size; }

public:
	D2D_VECTOR_2F Position;		//	��ġ
	float Rotation;				//	ȸ�� ��
	D2D_VECTOR_2F Scale;		//	ũ�� ��� ��
	float GravityAcceleration;	//	�߷� ���ӵ�
	float LocationOffsetY;		//	??

	bool isJumping;				//	���� ���̴�?
	bool isDown;				//	�߷��� �� ������� �ִ�?

public:
	D2D_RECT_F GetRect() {
		return D2D1::RectF(
			Position.x,
			Position.y,
			Position.x + m_ImageSize.width * Scale.x,
			Position.y + m_ImageSize.height * Scale.y
		);
	}
	D2D_VECTOR_2F GetBottomPoint() {
		return {
			Position.x + (m_ImageSize.width * Scale.x) / 2.0f,
			Position.y + m_ImageSize.height * Scale.y + LocationOffsetY };
	}
};

