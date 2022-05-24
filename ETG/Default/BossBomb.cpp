#include "stdafx.h"
#include "BossBomb.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SoundMgr.h"
CBossBomb::CBossBomb()
	:m_eCurState(IDLE), m_ePreState(END)
{
}


CBossBomb::~CBossBomb()
{
}

void CBossBomb::Initialize(void)
{

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 65.f;
	m_bDeadEffect = false;
	m_fSpeed = 7.f;
	m_bDeadEffect = false;
	m_SoundTime = GetTickCount();

	m_eRender = RENDER_GAMEOBJECT;
	CSoundMgr::Get_Instance()->PlaySoundW(L"beehive_shot_03_002.wav", SOUND_EFFECT, 0.5f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BossBomb.bmp", L"BossBomb");
}

int CBossBomb::Update(void)
{
	if (m_bDeadEffect)
	{

		m_eCurState = DEAD;

		if (m_bDead)
			return OBJ_DEAD;

	}
	else
	{
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBossBomb::Late_Update(void)
{


	switch (m_eCurState)
	{
	
	case DEAD:
		if (m_SoundTime + 2000 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"dragun_explode_01.wav", SOUND_EFFECT, 1.f);
			m_SoundTime = GetTickCount();
		}

		break;

	default:
		break;
	}

	
		if (m_tInfo.fY >  900)
		{	
			m_bDeadEffect = true;
		}

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


	

		
	// 플레이어 정보 받아와서 Y 넘어갈때 삭제하도록 한다
	
}

void CBossBomb::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossBomb");

	if (m_eCurState != DEAD)
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX + 20.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY + 20.f),
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
			int(m_tInfo.fCX + 100.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY +100.f),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
}

void CBossBomb::Release(void)
{

}

void CBossBomb::OnCollision(void)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget) {

		if (dynamic_cast<CPlayer*>(m_pTarget)->Get_State() != 2)
		{
			m_bDeadEffect = true;

		}
	}
}

void CBossBomb::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}



void CBossBomb::Motion_Change(void)
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
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
	
		}

		m_ePreState = m_eCurState;
	}
}
