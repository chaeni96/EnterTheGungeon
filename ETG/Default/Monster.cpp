#include "stdafx.h"
#include "Monster.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"


CMonster::CMonster()
	:m_eCurState(MONSTER_DOWN), m_ePreState(MONSTER_END)
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_tInfo.fX = 1000.f;
	m_tInfo.fY = 1000.f;

	m_fSpeed = 3.f;

	m_eRender = RENDER_GAMEOBJECT;

	m_bDeadEffect = false;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster1/Monster1.bmp", L"Monster1");
}

int CMonster::Update(void)
{
	if (m_bDeadEffect)
	{
		m_eCurState = MONSTER_DEAD;

		if (m_bDead)
			return OBJ_DEAD;
	}
	else
	{
		//공격함수
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY += m_fSpeed;
	}
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{

	Motion_Change();
	if (Move_Frame() == true)
	{
		switch ((m_eCurState))
		{
		case MONSTER_HIT:
			Monster_Dir();
			break;
		case MONSTER_DEAD:
			m_bDead = true;
			break;

		case MONSTER_UP:
		case MONSTER_DOWN:
		case MONSTER_LEFT:
		case MONSTER_RIGHT:
			m_tFrame.iFrameStart = 0;
			break;

		default:
			break;

		}


	}

}

void CMonster::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Monster1");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX + 25.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY + 25.f),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상

}


void CMonster::Release(void)
{
	
}

void CMonster::OnCollision(void)
{
	m_bDead = true;
}

void CMonster::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}



bool CMonster::Get_DeadEffect(void)
{
	return false;
}

void CMonster::Motion_Change(void)
{

	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case MONSTER_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		case MONSTER_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTER_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTER_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTER_HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTER_DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}

void CMonster::Monster_Dir(void)
{
}
