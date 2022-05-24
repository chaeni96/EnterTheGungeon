#include "stdafx.h"
#include "HostBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SoundMgr.h"
CHostBullet::CHostBullet()

{
}

CHostBullet::~CHostBullet()
{
}

void CHostBullet::Initialize(void)
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 17.f;
	m_bDeadEffect = false;
	m_fSpeed = 7.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Host_bullet.bmp", L"Host_bullet");
	CSoundMgr::Get_Instance()->PlaySoundW(L"host_shot.wav", SOUND_EFFECT, 0.5f);

}

int CHostBullet::Update(void)
{
	if (m_bDead)
	{
		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

		if (m_pTarget)
		{
			dynamic_cast<CPlayer*>(m_pTarget)->Set_PlayerCollisionCheck();
		}

		return OBJ_DEAD;
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_eDir == DIR_RIGHT)
	{
		m_tInfo.fX += m_fSpeed;
	}
	else if (m_eDir == DIR_LEFT)
	{
		m_tInfo.fX -= m_fSpeed;
	}
	else
	{

		m_tInfo.fX +=  m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -=  m_fSpeed * sinf(m_fAngle * PI / 180.f);

	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CHostBullet::Late_Update(void)
{
	Update_Rect();
	if (m_tRect.left <= 2411.f || m_tRect.right >= 3218.f || m_tRect.bottom >= 1926.f || m_tRect.top <= 1284.f)
	{
		if (m_eDir != DIR_LEFT && m_eDir != DIR_RIGHT)
		{
			m_bDead = true;
		}
	}
}

void CHostBullet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Host_bullet");

	if (m_eDir == DIR_LEFT || m_eDir == DIR_RIGHT)
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX - 5.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY - 5.f),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	else
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX + 10.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY + 10.f),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
}

void CHostBullet::Release(void)
{
}

void CHostBullet::OnCollision(void)
{
	if (m_pTarget) {
		if (m_eDir != DIR_LEFT && m_eDir != DIR_RIGHT)
		{
			if (dynamic_cast<CPlayer*>(m_pTarget)->Get_State() != 2)
			{
				m_bDead = true;
			}

		}
		else
			m_bDead = true;

	}
}

void CHostBullet::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
	switch (_eDir)
	{
	case DIR_LEFT:
	case DIR_UP:
	case DIR_RIGHT:
	case DIR_DOWN:
		m_bDead = true;
		break;
	case DIR_END:
		break;
	default:
		break;
	}
}


