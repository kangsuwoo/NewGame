#pragma once
#include "Transform.h"

class Renderer : public Transform
{
	//	Frame ?
	//	애니메이션 프레임을 가지고 있는 구조체
	struct Frame {
		//	애니메이션 인덱스를 넣는다
		//	Ex) frames[0] = {0, 0}, {1, 0} ..
		std::vector<D2D_POINT_2U> frames;
		int tick;			//	애니메이션 실행 속도
		int invokeIndex;	//	값이 있다면 해당 애니메이션 인덱스로 돌아가는 변수
	};

public:
	Renderer(std::string name);	//	이미지가 이미 있다면 이름으로 갖고온다

	//	파일 위치를 직접 넣어 이미지를 로드한다
	Renderer(std::string name, std::wstring fileName, UINT fx, UINT fy);
	virtual ~Renderer();

	void Update(int state);
	void Render();

	//	frames = 애니메이션 통, length = 배열 크기, tick = 애니메이션 속도
	//	isSetAnimation = 시작할 때 이 애니메이션으로 시작할 것 인가?
	//	invokeIndex =  frames 애니메이션이 끝나면 index 값으로 애니메이션을 실행
	void AddAnimation(D2D_POINT_2U frames[], int length, int tick,
		bool isSetAnimation = false, int invokeIndex = -1);

	//	해당 인덱스로 애니메이션 강제 실행
	void SetAnimation(int state);

	//	떨어지고 있는 경우(중력이 밑으로 향하는 경우)
	//	떨어지는 애니메이션 셋팅 인덱스
	// void SetDownAnimation(int index);

	//	사용중인 상태 변수 셋팅
	//	주소 값을 받아야 안에 있는 내용물을 바꿀 수 있으므로 포인터로 갖고온다
	void SetIndexPointer(int* pStatus);

private:
	BaseTexture* m_Texture;
	D2D1_SIZE_F m_Size;

	int m_AnimDownIndex;	//SetDownAnimation Index 넣어줄 값
	
	Frame m_CurrentFrame;	//	현재 실행중인 애니메이션 프레임
	int m_CurrentStatus;	//	현재 상태 인덱스
	int m_CurrentFrameTime;	//	현재 애니메이션 진행 시간 (tick)
	int m_CurrentFrameIndex;	//	현재 애니메이션 진행 상태

	int* m_AnimIndexPointer;	//	상태 변경 시 해당 주소 값에 상태를 넣어줄 변수

public:
	std::vector<Frame> AnimFrame;	//	애니메이션 통

	float Opacity;	//	투명도
	bool isReverse;	//	좌우 반전 확인 변수
	
	D2D_SIZE_F GetSize() { return m_Size; } // 원본 이미지 사이즈 반환
};

