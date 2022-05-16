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
	m_tInfo.fX = 720.f;
	m_tInfo.fY = 580.f;
	m_tInfo.fCX = 285.f;
	m_tInfo.fCY = 188.f;

	m_eRender = RENDER_UI;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Inventory1.bmp", L"Inventory");


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
		int(m_tInfo.fCX -70.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY -70.f),
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

void CInventory::OnCollision(void)
{
}

void CInventory::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}

bool CInventory::Get_DeadEffect(void)
{
	return false;
}
