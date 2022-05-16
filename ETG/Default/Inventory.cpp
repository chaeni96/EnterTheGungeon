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

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left ),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top ),
		int(m_tInfo.fCX -70.f),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY -70.f),
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
