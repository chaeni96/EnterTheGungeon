#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_fAngle(0.f)
	, m_pFrameKey(nullptr), m_eType(TYPE_END), m_iHp(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left   = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top    = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
 	m_tRect.right  = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

bool CObj::Move_Frame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;

			return true;  // 한바퀴 다 돌았을때 true 반환
		}
	}

	return false;
}
