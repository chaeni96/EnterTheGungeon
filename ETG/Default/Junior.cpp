#include "stdafx.h"
#include "Junior.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "HostBullet.h"
#include "SoundMgr.h"

CJunior::CJunior()
	:m_eCurState(IDLE), m_ePreState(END)
{
}


CJunior::~CJunior()
{
}

void CJunior::Initialize(void)
{
	m_tInfo.fCX = 72.f;
	m_tInfo.fCY = 45.f;

	m_fSpeed = 5.f;
	m_iHp = 10;
	m_fDiagonal = 5.f;
	m_eRender = RENDER_GAMEOBJECT;
	m_DelayTime = GetTickCount();
	m_bDeadEffect = false;
	m_SoundTime = GetTickCount();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Pet/junior.bmp", L"junior");

	m_fDiagonal = 5.f;
}

int CJunior::Update(void)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget)
	{

		float		fWidth = m_pTarget->Get_Info().fX - (m_tInfo.fX);
		float		fHeight = m_pTarget->Get_Info().fY - (m_tInfo.fY);

		float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
		float		fRadian = acosf(fWidth / fDiagonal);


		if (m_tInfo.fY < m_pTarget->Get_Info().fY)
			fRadian *= -1.f;

		m_fAngle = fRadian * 180.f / PI;

		if (fDiagonal > 100)
		{
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);

			if (GetAsyncKeyState('A') || GetAsyncKeyState('W') || GetAsyncKeyState('D') || GetAsyncKeyState('S'))
			{
				m_eCurState = ATTACK;

				if (m_DelayTime + 4000 < GetTickCount())
				{

					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CHostBullet>::Create(m_tInfo.fX + 30.f, m_tInfo.fY, DIR_RIGHT));
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CHostBullet>::Create(m_tInfo.fX -30.f, m_tInfo.fY, DIR_LEFT));
					//총쏘는 함수
					m_DelayTime = GetTickCount();
				}
			}
			
			
		}		
		}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CJunior::Late_Update(void)
{

	switch ((m_eCurState))
	{
		
	case IDLE:
		if (m_SoundTime + 1000 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"junior.mp3", SOUND_EFFECT, 1.f);
			m_SoundTime = GetTickCount();
		}
		break;

	default:
		break;

	}
	Motion_Change();

	if (Move_Frame() == true)
	{
		switch ((m_eCurState))
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;

			break;

		case ATTACK:
		
			m_tFrame.iFrameStart = 5;
			break;
		default:
			break;

		}
	}
}

void CJunior::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"junior");

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

void CJunior::Release(void)
{
}

void CJunior::OnCollision(void)
{
}

void CJunior::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
	switch (_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= _fX;
		break;
	case DIR_UP:
		m_tInfo.fY -= _fY;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += _fX;
		break;
	case DIR_DOWN:
		m_tInfo.fY += _fY;
		break;
	case DIR_END:
		break;
	default:
		break;
	}
}

bool CJunior::Get_DeadEffect(void)
{
	return false;
}

void CJunior::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}

}

void CJunior::Player_Dir(void)
{
}
