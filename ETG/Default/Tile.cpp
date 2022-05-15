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



	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		m_tRect.left + iScrollX,	// 2,3 ���� :  ������� ��ġ X, Y
		m_tRect.top + iScrollY,
		TILECX,				// 4,5 ���� : ������� ����, ���� ����
		TILECY,
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		TILECX * m_iDrawID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		TILECX,				// ������ ��Ʈ���� ����, ���� ����
		TILECY,
		RGB(255, 0, 255));			// �����ϰ��� �ϴ� ����/ �����ϰ��� �ϴ� ����



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
