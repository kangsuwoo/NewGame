#pragma once
#include "Transform.h"

class Renderer : public Transform
{
	//	Frame ?
	//	�ִϸ��̼� �������� ������ �ִ� ����ü
	struct Frame {
		//	�ִϸ��̼� �ε����� �ִ´�
		//	Ex) frames[0] = {0, 0}, {1, 0} ..
		std::vector<D2D_POINT_2U> frames;
		int tick;			//	�ִϸ��̼� ���� �ӵ�
		int invokeIndex;	//	���� �ִٸ� �ش� �ִϸ��̼� �ε����� ���ư��� ����
	};

public:
	Renderer(std::string name);	//	�̹����� �̹� �ִٸ� �̸����� ����´�

	//	���� ��ġ�� ���� �־� �̹����� �ε��Ѵ�
	Renderer(std::string name, std::wstring fileName, UINT fx, UINT fy);
	virtual ~Renderer();

	void Update(int state);
	void Render();

	//	frames = �ִϸ��̼� ��, length = �迭 ũ��, tick = �ִϸ��̼� �ӵ�
	//	isSetAnimation = ������ �� �� �ִϸ��̼����� ������ �� �ΰ�?
	//	invokeIndex =  frames �ִϸ��̼��� ������ index ������ �ִϸ��̼��� ����
	void AddAnimation(D2D_POINT_2U frames[], int length, int tick,
		bool isSetAnimation = false, int invokeIndex = -1);

	//	�ش� �ε����� �ִϸ��̼� ���� ����
	void SetAnimation(int state);

	//	�������� �ִ� ���(�߷��� ������ ���ϴ� ���)
	//	�������� �ִϸ��̼� ���� �ε���
	// void SetDownAnimation(int index);

	//	������� ���� ���� ����
	//	�ּ� ���� �޾ƾ� �ȿ� �ִ� ���빰�� �ٲ� �� �����Ƿ� �����ͷ� ����´�
	void SetIndexPointer(int* pStatus);

private:
	BaseTexture* m_Texture;
	D2D1_SIZE_F m_Size;

	int m_AnimDownIndex;	//SetDownAnimation Index �־��� ��
	
	Frame m_CurrentFrame;	//	���� �������� �ִϸ��̼� ������
	int m_CurrentStatus;	//	���� ���� �ε���
	int m_CurrentFrameTime;	//	���� �ִϸ��̼� ���� �ð� (tick)
	int m_CurrentFrameIndex;	//	���� �ִϸ��̼� ���� ����

	int* m_AnimIndexPointer;	//	���� ���� �� �ش� �ּ� ���� ���¸� �־��� ����

public:
	std::vector<Frame> AnimFrame;	//	�ִϸ��̼� ��

	float Opacity;	//	����
	bool isReverse;	//	�¿� ���� Ȯ�� ����
	
	D2D_SIZE_F GetSize() { return m_Size; } // ���� �̹��� ������ ��ȯ
};

