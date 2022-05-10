#include "stdafx.h"
#include "Monster.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	m_tInfo.fX = 200.f;
	m_tInfo.fY = 200.f;

	m_fSpeed = 5.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");

	m_pFrameKey = L"Monster";
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					
		int(m_tRect.left + iScrollX),	
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				
		int(m_tInfo.fCY),
		hMemDC,							
		0,
		0,
		(int)m_tInfo.fCX,		
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	
}

void CMonster::Release(void)
{
	
}
