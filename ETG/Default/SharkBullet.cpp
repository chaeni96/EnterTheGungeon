#include "stdafx.h"
#include "SharkBullet.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "BossMonster.h"
#include "SoundMgr.h"
CSharkBullet::CSharkBullet()
	: m_eCurState(NOMAL), m_ePreState(BULLET_END)

{
}


CSharkBullet::~CSharkBullet()
{
}

void CSharkBullet::Initialize(void)
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 16.f;

	m_bDeadEffect = false;
	m_fSpeed = 3.f;
	m_bCheckTile = false;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Left_Shark.bmp", L"Left_Shark");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Right_Shark.bmp", L"Right_Shark");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Left_SharkEffect.bmp", L"Left_SharkEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Right_SharkEffect.bmp", L"Right_SharkEffect");

	CSoundMgr::Get_Instance()->PlaySoundW(L"sharkgun_shot_0.mp3", SOUND_EFFECT, 14.f);

	m_SoundDelay = GetTickCount();
}

int CSharkBullet::Update(void)
{
	if (m_bDeadEffect)
	{
		if (m_bCheckTile)
		{
			return OBJ_DEAD; 
		}
			m_fSpeed = 0.f;
			if (m_pFrameKey == L"Right_Shark")
			{
				m_pFrameKey = L"Right_SharkEffect";
				CSoundMgr::Get_Instance()->PlaySoundW(L"sharkgun_eat_01.wav", SOUND_EFFECT, 10.f);

				m_tInfo.fX += 10.f;
			}
			else if (m_pFrameKey == L"Left_Shark")
			{
				m_pFrameKey = L"Left_SharkEffect";
				CSoundMgr::Get_Instance()->PlaySoundW(L"sharkgun_eat_01.wav", SOUND_EFFECT, 10.f);

				m_tInfo.fX -= 10.f;
			}
			
			m_eCurState = BOOM;


			if (m_bDead)
			
			{

				m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_BOSS, this);

				if (m_pTarget)
				{
					dynamic_cast<CBossMonster*>(m_pTarget)->Set_CollisionCheck();
				}

				return OBJ_DEAD;

		}
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
				m_pFrameKey = L"Right_Shark";


			}
			else if (pt.x < m_pTarget->Get_Info().fX + +iScrollX)
			{
				m_pFrameKey = L"Left_Shark";


			}
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
		}
	}


	Update_Rect();
	return OBJ_NOEVENT;
}

void CSharkBullet::Late_Update(void)
{

	Motion_Change();

	if (Move_Frame() == true)
	{

		switch (m_eCurState)
		{
		case NOMAL:
		
			m_tFrame.iFrameStart = 0;
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

void CSharkBullet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (m_eCurState != BOOM)
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX + 15.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY + 15.f),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	else
	{

		m_tInfo.fCX = 112.f;
		m_tInfo.fCY = 95.f;

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX + 90.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY + 90.f),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
}

void CSharkBullet::Release(void)
{
}

void CSharkBullet::OnCollision(void)
{
	m_bDeadEffect = true;

}

void CSharkBullet::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{

	switch (_eDir)
	{
	case DIR_LEFT:
	case DIR_UP:
	case DIR_RIGHT:
	case DIR_DOWN:
		m_bCheckTile = true;
		m_bDeadEffect = true;
		break;
	case DIR_END:
		break;
	default:
		break;
	}
}

void CSharkBullet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case NOMAL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			break;

		case BOOM:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}
