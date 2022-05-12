#include "stdafx.h"
#include "BossMonster.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BossBullet.h"
#include "KeyMgr.h"
CBossMonster::CBossMonster()
	:m_eCurState(DOWN), m_ePreState(END)
{
}


CBossMonster::~CBossMonster()
{
	Release();
}

void CBossMonster::Initialize(void)
{
	m_tInfo.fX = 650.f;
	m_tInfo.fY = 400.f;

	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_fSpeed = 5.f;
	m_fDiagonal = 10.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss.bmp", L"Boss");

}

int CBossMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	

	Monster_Dir();
	Motion_Change();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBossMonster::Late_Update(void)
{
	Move_Frame();
}

void CBossMonster::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX * 0.5f,// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY * 0.5f,
		(int)m_tInfo.fCX* 0.5f,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY* 0.5f,
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상

}

void CBossMonster::Release(void)
{
}

void CBossMonster::Motion_Change(void)
{

	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case RU:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		case RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case LD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case LU:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 8;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case FLY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 9;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case LAND:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 10;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case POSE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion =11;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CBossMonster::Monster_Dir(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//플레이어와의 각도에 따라서 시선이 달라짐

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	float fWidth = m_pTarget->Get_Info().fX - (m_tInfo.fX + iScrollX);
	float fHeight = m_pTarget->Get_Info().fY - (m_tInfo.fX + iScrollY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	

	float	fRadian = acosf(fWidth / fDiagonal);

	m_fAngle = fRadian * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	// 각도 완벽
	if (25 <= m_fAngle &&  m_fAngle < 90)
	{

		m_eCurState = RU; 

	}
	else if ((90 <= m_fAngle &&  m_fAngle < 130))
	{
		m_eCurState = LU;

	}
	else if ((130 <= m_fAngle &&  m_fAngle < 165))
	{
		m_eCurState = LEFT;

	}
	else if ((-145 <= m_fAngle &&  m_fAngle < -90))
	{
		m_eCurState = LD;

	}
	else if ((-90 <= m_fAngle &&  m_fAngle < -40))
	{
		m_eCurState = DOWN;

	}
	else if ((-40<= m_fAngle &&  m_fAngle < 5))
	{
		m_eCurState = RD;

	}
	else if ((5 <= m_fAngle &&  m_fAngle < 25))
	{
		m_eCurState = RIGHT; 

	}


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<BossBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
	}
}
