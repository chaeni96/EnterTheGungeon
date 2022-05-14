#include "stdafx.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 21.f;
	m_tInfo.fCY = 19.f;

	m_fSpeed = 7.f;
	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Normal.bmp", L"Normal");

}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	
}

void CBullet::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Normal");

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
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상

} 

void CBullet::Release(void)
{
	
}

void CBullet::OnCollision(void)
{

		m_bDead = true;
	
	
}
