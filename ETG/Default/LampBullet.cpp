#include "stdafx.h"
#include "LampBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "ObjMgr.h"


CLampBullet::CLampBullet()
	:m_eCurState(NOMAL), m_ePreState(BULLET_END)

{
}


CLampBullet::~CLampBullet()
{
}

void CLampBullet::Initialize(void)
{
	m_tInfo.fCX = 110.f;
	m_tInfo.fCY = 110.f;
	m_bDeadEffect = false;
	m_fSpeed = 3.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Left_Bullet.bmp", L"Left_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Right_Bullet.bmp", L"Right_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Lamp_Effect.bmp", L"Lamp_Effect");

}

int CLampBullet::Update(void)
{
	if (m_bDeadEffect)
	{
		m_fSpeed = 0.f;
		m_pFrameKey = L"Lamp_Effect";
		m_eCurState = BOOM;

		if (m_bDead)
			return OBJ_DEAD;

	}
	else
	{
		m_pTarget = m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
		GetCursorPos(&pt);	// 현재 마우스의 위치 좌표를 얻어오는 함수
		ScreenToClient(g_hWnd, &pt);
		if (m_pTarget)
		{
			int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

			if (pt.x >= m_pTarget->Get_Info().fX + iScrollX)
			{
				m_pFrameKey = L"Right_Bullet";
			}
			else if(pt.x < m_pTarget->Get_Info().fX + +iScrollX)
			{
				m_pFrameKey = L"Left_Bullet";

			}
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
		}
	}
	

	Update_Rect();
	return OBJ_NOEVENT;
}

void CLampBullet::Late_Update(void)
{
	Motion_Change();

	if (Move_Frame() == true)
	{

		switch (m_eCurState)
		{
		case NOMAL:

			m_tFrame.iFrameStart = 5;
			break;

		case BOOM:
			m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

			if (m_pTarget)
			{
				dynamic_cast<CPlayer*>(m_pTarget)->Set_CollisionCheck();
			}

			m_bDead = true;
			break;

		default:
			break;
		}

	}
}

void CLampBullet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (m_eCurState != BOOM)
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX* 0.5f,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY* 0.5f,
			(int)m_tInfo.fCX* 0.5f,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY* 0.5f,
			RGB(255, 0, 255));
	}
	else
	{

		m_tInfo.fCX = 116.f;
		m_tInfo.fCY = 136.f;

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
}

void CLampBullet::Release(void)
{
}

void CLampBullet::OnCollision(void)
{

	m_bDeadEffect = true;
	
}

void CLampBullet::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{

	switch (_eDir)
	{
	case DIR_LEFT:
	case DIR_UP:
	case DIR_RIGHT:
	case DIR_DOWN:
		m_bDeadEffect = true;
		break;
	case DIR_END:
		break;
	default:
		break;
	}
}

void CLampBullet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case NOMAL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			break;

		case BOOM:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}
