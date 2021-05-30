#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer(std::string name)
	: m_Texture(nullptr),
	Opacity(1.0f), isReverse(false),
	m_CurrentFrame(Frame()), m_CurrentStatus(0), m_CurrentFrameTime(0),
	m_CurrentFrameIndex(0), m_AnimDownIndex(-1), m_AnimIndexPointer(nullptr)
{
	m_Texture = _Texture->Find(name);
	m_Size = m_Texture->GetSize();

	SetImageSize(m_Size);
}

Renderer::Renderer(std::string name, std::wstring fileName, UINT fx, UINT fy)
	: m_Texture(nullptr),
	Opacity(1.0f), isReverse(false),
	m_CurrentFrame(Frame()), m_CurrentStatus(0), m_CurrentFrameTime(0),
	m_CurrentFrameIndex(0), m_AnimDownIndex(-1), m_AnimIndexPointer(nullptr)
{
	m_Texture = _Texture->LoadTexture(name, fileName, fx, fy);
	m_Size = m_Texture->GetSize();

	SetImageSize(m_Size);
}

Renderer::~Renderer()
{
}

//	파라메터 : in state
//	파라메터 값을 받아 애니메이션을 실행한다
void Renderer::Update(int state)
{
	//	밑으로 떨어지는 애니메이션 인덱스가 설정되어 있으면
	//	떨어지는 애니메이션 인덱스로 변경해준다
	if (m_AnimDownIndex != -1 && isDown)
		state = m_AnimDownIndex;

	//	사용중인 애니메이션 인덱스와 새로 들어온 인덱스가 다르면
	//	새로 들어온 애니메이션으로 설정해준다
	if (m_CurrentStatus != state)
	{
		m_CurrentFrameTime = 0;
		m_CurrentStatus = state;

		m_CurrentFrame = AnimFrame[state];
		m_CurrentFrameIndex = 0;
	}
	else {	//	기존 애니메이션과 동일하면 기존 애니메이션으로 진행
		if (m_CurrentFrameTime == m_CurrentFrame.tick)
		{
			m_CurrentFrameTime = 0;
			m_CurrentFrameIndex++;

			//	인덱스가 애니메이션 맨 끝 까지 왔다면 (사이클 다 돌았을 때)
			if (m_CurrentFrameIndex == m_CurrentFrame.frames.size())
			{
				//	이 애니메이션은 끝나고 돌아갈 인덱스가 있다면
				if (m_CurrentFrame.invokeIndex != -1)
				{
					if (m_AnimIndexPointer != nullptr)
						*m_AnimIndexPointer = m_CurrentFrame.invokeIndex;

					//	재귀 함수 : 함수 안에서 동일한 함수로 다시 들어감
					Update(m_CurrentFrame.invokeIndex);
					return;	//	함수를 여기서 종료한다 (더 이상 밑으로 내려가지 않는다)
				}

				m_CurrentFrameIndex = 0;
			}
		}
		else
			m_CurrentFrameTime++;
	}

	//Transform::UpdateJump();
	UpdateJump();
}

void Renderer::Render()
{
	//	렌더링 할 때 진행중인 애니메이션의 x, y 이미지 프레임을 가지고 온다
	UINT fx = m_CurrentFrame.frames[m_CurrentFrameIndex].x;
	UINT fy = m_CurrentFrame.frames[m_CurrentFrameIndex].y;

	m_Texture->DrawFrame(
		Position.x, Position.y,
		fx, fy,
		m_Size.width * Scale.x, m_Size.height * Scale.y,
		isReverse,
		Rotation,
		Opacity);
}

void Renderer::AddAnimation(D2D_POINT_2U frames[], int length, int tick, bool isSetAnimation, int invokeIndex)
{
	std::vector<D2D_POINT_2U> vec;

	for (int i = 0; i < length; ++i)
		vec.push_back(frames[i]);

	AnimFrame.push_back({ vec, tick, invokeIndex });
	if (isSetAnimation)
		SetAnimation((int)AnimFrame.size() - 1);
}

void Renderer::SetAnimation(int state)
{
	m_CurrentStatus = state;

	m_CurrentFrame = AnimFrame[state];
	m_CurrentFrameTime = 0;
	m_CurrentFrameIndex = 0;
}

//void Renderer::SetDownAnimation(int index)
//{
//	m_AnimDownIndex = index;
//}

void Renderer::SetIndexPointer(int * pStatus)
{
	m_AnimIndexPointer = pStatus;
}
