#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
{
}


CShield::~CShield()
{
	Release();
}

void CShield::Initialize(void)
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 5.f;		// 공전 속도
	m_fDistance = 100.f;
}

int CShield::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	m_fAngle += m_fSpeed;

	m_tInfo.fX = m_pTarget->Get_Info().fX + m_fDistance * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY = m_pTarget->Get_Info().fY - m_fDistance * sinf((m_fAngle * PI) / 180.f);
	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CShield::Late_Update(void)
{
	// 쿨타임 종료, 쉴드와 무언가가 충돌했을 때
	// 개수 제한
}

void CShield::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release(void)
{

}
