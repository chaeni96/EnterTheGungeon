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

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left ),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top ),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// �����ϰ��� �ϴ� ����/ �����ϰ��� �ϴ� ����
}

void CInventory::Release(void)
{
}
