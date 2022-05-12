#include "stdafx.h"
#include "Inventory.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CInventory::CInventory()
{
}

CInventory::~CInventory()
{
	Release();
}

void CInventory::Initialize(void)
{
	m_tInfo.fX = 500.f;
	m_tInfo.fX = 500.f;
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 130.f;

	m_eRender = RENDER_UI;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Inventory.bmp", L"Inventory");


}

int CInventory::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CInventory::Late_Update(void)
{
}

void CInventory::Render(HDC hDC)
{


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Inventory");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left ),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top ),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상
}

void CInventory::Release(void)
{
}
