#include "stdafx.h"
#include "BossBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SoundMgr.h"

BossBullet::BossBullet()
	:m_eCurState(IDLE), m_ePreState(END)


{
}


BossBullet::~BossBullet()
{
}

void BossBullet::Initialize(void)
{

	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 47.f;
	m_fSpeed = 8.f;
	m_eRender = RENDER_GAMEOBJECT;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BossBullet.bmp", L"BossBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Host_bullet.bmp", L"Host_bullet");

	m_pFrameKey = L"BossBullet";
	CSoundMgr::Get_Instance()->PlaySoundW(L"burninghand_shot_01.wav", SOUND_EFFECT, 1.f);

}

int BossBullet::Update(void)
{
	if (m_bDeadEffect)
	{
		m_eCurState = DEAD;

		if (m_bDead)
			return OBJ_DEAD;

	}
	else
	{

		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);

	}

	
	Update_Rect();

	return OBJ_NOEVENT;
}

void BossBullet::Late_Update(void)
{
	Motion_Change();

	if (Move_Frame() == true)
	{

		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			break;

		case DEAD:
			m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

			if (m_pTarget)
			{
				dynamic_cast<CPlayer*>(m_pTarget)->Set_PlayerCollisionCheck();
			}

			m_bDead = true;
			break;

		default:
			break;
		}

	}
}

void BossBullet::Render(HDC hDC)
{


	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	if (m_eCurState != DEAD)
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX ),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY ),
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
			int(m_tInfo.fCX + 40.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY + 40.f),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}

	
}

void BossBullet::Release(void)
{

}

void BossBullet::OnCollision(void)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget) {

		if (dynamic_cast<CPlayer*>(m_pTarget)->Get_State() != 2)
		{
			m_bDeadEffect = true;
		}
	}
}

void BossBullet::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
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

void BossBullet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}



