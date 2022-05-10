#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "Mouse.h"

float	g_fSound = 1.f;

CPlayer::CPlayer()
	: m_eCurState(IDLE), m_ePreState(END)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = 500.F;

	m_tInfo.fCX = 80.f; // 20 * 25
	m_tInfo.fCY = 100.f;

	m_fSpeed = 5.f;

	m_fDiagonal = 100.f;

	m_bJump = false;
	m_bRoll = false;
	m_fJumpPower = 15.f;
	m_fJumpTime = 0.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LU.bmp", L"Player_LU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RU.bmp", L"Player_RU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LD.bmp", L"Player_LD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RD.bmp", L"Player_RD");
	//CSoundMgr::Get_Instance()->PlaySoundW(L"Success.wav", SOUND_EFFECT, g_fSound);

}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Mouse_Sight();
	Key_Input();
	OffSet();
	Dodge_Roll();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	Motion_Change();
	Move_Frame();


#ifdef _DEBUG

	//system("cls");
	//cout << "플레이어 좌표 : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;


#endif // _DEBUG
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX * 0.5f,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY * 0.5f,
		(int)m_tInfo.fCX * 0.5f,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY * 0.5f,
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상

				
}
void CPlayer::Release(void)
{
	
}

void CPlayer::Mouse_Sight(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	//마우스 실시간 좌표 받아오기

	GetCursorPos(&pt);	// 현재 마우스의 위치 좌표를 얻어오는 함수
	ScreenToClient(g_hWnd, &pt);	// 전체 스크린영역에서 생성한 클라이언트(창) 좌표로 변환

	// 플레이어의 중점과 마우스의 각도 구하기

	float fWidth = (pt.x - (m_tInfo.fX + iScrollX)); //밑변  // 스크롤 넘어갔을때 문제 발생
	float fHeight = (pt.y  - (m_tInfo.fY + iScrollY)); // 높이

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	
															
	float	fRadian = acosf(fWidth / fDiagonal);	//두점 사이의 각도

	if (pt.y > (m_tInfo.fY + iScrollY))
		fRadian *= -1.f;

	m_fAngle = fRadian * 180.f / PI; //디그리 각도

	if (25 <= m_fAngle &&  m_fAngle < 70)
	{
		m_pFrameKey = L"Player_RU";

	}
	else if ((70 <= m_fAngle &&  m_fAngle < 110))
	{
		m_pFrameKey = L"Player_UP";

	}
	else if ((110 <= m_fAngle &&  m_fAngle < 170))
	{
		m_pFrameKey = L"Player_LU";

	}
	else if ((170 <= m_fAngle &&  m_fAngle < 260))
	{
		m_pFrameKey = L"Player_LEFT";
	
	}
	else if ((-90 <= m_fAngle &&  m_fAngle < -40))
	{
		m_pFrameKey = L"Player_DOWN";

	}
	else if ((-40 <= m_fAngle &&  m_fAngle < 25))
	{
		m_pFrameKey = L"Player_RIGHT";	

	}

}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	if (GetAsyncKeyState('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eCurState = WALK;

	
	}

	else if (GetAsyncKeyState('D'))
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurState = WALK;

	
	}

	else if (GetAsyncKeyState('W'))
	{
		m_tInfo.fY -= m_fSpeed;
		m_eCurState = WALK;
	

	}

	else if (GetAsyncKeyState('S'))
	{
		m_tInfo.fY += m_fSpeed;
		m_eCurState = WALK;
	
	
	}
	else
		m_eCurState = IDLE;

}

void CPlayer::Dodge_Roll(void)
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_eCurState = ROLL;
		// 구르기 상태 변수 하나 선언하고 그 상태일때는 몬스터 총알과 충돌처리 X
		m_bRoll = true;
	}

}


void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int		iItvX = 100;
	int		iItvY = 200;

	if (iOffSetX - iItvX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX + iItvX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	
	if (iOffSetY - iItvY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetY + iItvY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ROLL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 90;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

