#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iDrawID = 0;
	m_iOption = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"Tile");
}

int CTile::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	

	Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update(void)
{
	
}

void CTile::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile");



	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		m_tRect.left + iScrollX,	// 2,3 인자 :  복사받을 위치 X, Y
		m_tRect.top + iScrollY,
		TILECX,				// 4,5 인자 : 복사받을 가로, 세로 길이
		TILECY,
		hMemDC,							// 비트맵을 가지고 있는 DC
		TILECX * m_iDrawID,								// 비트맵 출력 시작 좌표, X,Y
		0,
		TILECX,				// 복사할 비트맵의 가로, 세로 길이
		TILECY,
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상



}

void CTile::Release(void)
{
	
}

void CTile::OnCollision(void)
{
}

bool CTile::Get_DeadEffect(void)
{
	return false;
}
