#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
	: Position({0, }), Rotation(0), Scale({1.0f, 1.0f}),
	isJumping(false), m_Gravity(0), m_GravityDirection(0), m_PrevPositionY(0),
	m_ImageSize({0, }), m_CurrentFloorRect({0, }), isDown(false),
	GravityAcceleration(1.0f),
	LocationOffsetY(0)
{
}
Transform::~Transform()
{
}


bool Transform::CheckLocation(D2D_RECT_F rect)
{
	if (m_GravityDirection < PI) return false;

	D2D_RECT_F rc = GetRect();
	D2D_VECTOR_2F point = GetBottomPoint();
	if (Collision::IsInRectPoint(rect, point))
	{
		if (m_PrevPositionY <= rect.top)
		{
			Position.y = rect.top - m_ImageSize.height * Scale.y + LocationOffsetY;

			isJumping = false;
			isDown = false;
			m_GravityDirection = 0.0f;

			m_CurrentFloorRect = rect;
			m_PrevPositionY = 0.0f;
			return true;
		}
	}

	return false;
}

void Transform::UpdateJump()
{
	////	점프 중 이면
	//if (isJumping)
	//{
	//	//	중력 값 구하고
	//	float gravity = sinf(m_GravityDirection) * m_Gravity;

	//	//	sin 곡선을 이용해 Position.y 에다가 넣을 값을 구해준다
	//	//	단, PI * 2.0f 이상부터는 곡선이 다시 상승하기 때문에 그 전 까지만 넣어준다
	//	if (m_GravityDirection <= PI * 2.0f)
	//		m_GravityDirection += (PI / 128.0f) * GravityAcceleration;

	//	//	GravityDirection 이 PI 가 되면 바닥에 있는 렉트와 비교하기 위해
	//	//	PrevPositionY 에다가 내 바닥 좌표 값을 계속 넣어준다
	//	if (m_GravityDirection >= PI)
	//		m_PrevPositionY = GetBottomPoint().y;

	//	Position.y -= gravity;
	//}
	////	점프하지 않았는데 떨어지는 경우
	//else if (m_CurrentFloorRect.bottom != 0)
	//{
	//	float x = GetBottomPoint().x;
	//	if (x < m_CurrentFloorRect.left || x > m_CurrentFloorRect.right)
	//	{
	//		Jump(24.0f, PI);
	//		isDown = true;
	//	}
	//}

}
