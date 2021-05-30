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

//	�Ķ���� : in state
//	�Ķ���� ���� �޾� �ִϸ��̼��� �����Ѵ�
void Renderer::Update(int state)
{
	//	������ �������� �ִϸ��̼� �ε����� �����Ǿ� ������
	//	�������� �ִϸ��̼� �ε����� �������ش�
	if (m_AnimDownIndex != -1 && isDown)
		state = m_AnimDownIndex;

	//	������� �ִϸ��̼� �ε����� ���� ���� �ε����� �ٸ���
	//	���� ���� �ִϸ��̼����� �������ش�
	if (m_CurrentStatus != state)
	{
		m_CurrentFrameTime = 0;
		m_CurrentStatus = state;

		m_CurrentFrame = AnimFrame[state];
		m_CurrentFrameIndex = 0;
	}
	else {	//	���� �ִϸ��̼ǰ� �����ϸ� ���� �ִϸ��̼����� ����
		if (m_CurrentFrameTime == m_CurrentFrame.tick)
		{
			m_CurrentFrameTime = 0;
			m_CurrentFrameIndex++;

			//	�ε����� �ִϸ��̼� �� �� ���� �Դٸ� (����Ŭ �� ������ ��)
			if (m_CurrentFrameIndex == m_CurrentFrame.frames.size())
			{
				//	�� �ִϸ��̼��� ������ ���ư� �ε����� �ִٸ�
				if (m_CurrentFrame.invokeIndex != -1)
				{
					if (m_AnimIndexPointer != nullptr)
						*m_AnimIndexPointer = m_CurrentFrame.invokeIndex;

					//	��� �Լ� : �Լ� �ȿ��� ������ �Լ��� �ٽ� ��
					Update(m_CurrentFrame.invokeIndex);
					return;	//	�Լ��� ���⼭ �����Ѵ� (�� �̻� ������ �������� �ʴ´�)
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
	//	������ �� �� �������� �ִϸ��̼��� x, y �̹��� �������� ������ �´�
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
