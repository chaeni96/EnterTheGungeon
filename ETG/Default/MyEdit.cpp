#include "stdafx.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{

	CTileMgr::Get_Instance()->Initialize();
}

void CMyEdit::Update(void)
{
	CTileMgr::Get_Instance()->Update();
	Key_Input();

}

void CMyEdit::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back/MapEdit.bmp", L"MapEdit");

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MapEdit");
	BitBlt(hDC, iScrollX, iScrollY, 2400, 1400, hGroundMemDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
}

void CMyEdit::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 0);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		CTileMgr::Get_Instance()->Save_Tile();


	
}
