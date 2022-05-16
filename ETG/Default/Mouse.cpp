#include "stdafx.h"
#include "Mouse.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 26.f;
	m_tInfo.fCY = 26.f;

	m_eRender = RENDER_UI;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Cursor/Cursor.bmp", L"Cursor");


}

int CMouse::Update(void)
{

	POINT	pt{};

	GetCursorPos(&pt);	// ���� ���콺�� ��ġ ��ǥ�� ������ �Լ�
	ScreenToClient(g_hWnd, &pt);	// ��ü ��ũ���������� ������ Ŭ���̾�Ʈ(â) ��ǥ�� ��ȯ

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;
	
	Update_Rect();
	ShowCursor(false);		// ���콺 Ŀ���� ������� �ʰڴ�.

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	

}

void CMouse::Render(HDC hDC)
{


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cursor");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left ),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top ),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX * 0.5f,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY * 0.5f,
		(int)m_tInfo.fCX * 0.5f,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY * 0.5f,
		RGB(255, 0, 255));
}

void CMouse::Release(void)
{
	
}

void CMouse::OnCollision(void)
{
}

bool CMouse::Get_DeadEffect(void)
{
	return false;
}

void CMouse::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}

