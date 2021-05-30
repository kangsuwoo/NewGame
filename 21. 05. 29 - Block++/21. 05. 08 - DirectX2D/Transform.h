#pragma once

//	Transform ?
//	위치 (Position), 크기(Scale), 회전(Rotation)
//	를 담당하는 객체
//	모든 움직임을 담당하는 클래스
class Transform
{
public:
	Transform();
	virtual ~Transform();	//	가상 소멸자

	
	bool CheckLocation(D2D_RECT_F rect);

private:
	float m_Gravity;				//	중력 값
	float m_GravityDirection;		//	중력 방향
	float m_PrevPositionY;			//	이전 Position Y 값
	D2D_RECT_F m_CurrentFloorRect;	//	지금 밟고있는 블럭
	D2D_SIZE_F m_ImageSize;			//	사용중인 이미지 크기

protected:
	void UpdateJump();
	void SetImageSize(D2D_SIZE_F size) { m_ImageSize = size; }

public:
	D2D_VECTOR_2F Position;		//	위치
	float Rotation;				//	회전 값
	D2D_VECTOR_2F Scale;		//	크기 배수 값
	float GravityAcceleration;	//	중력 가속도
	float LocationOffsetY;		//	??

	bool isJumping;				//	점프 중이니?
	bool isDown;				//	중력이 널 끌어당기고 있니?

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

