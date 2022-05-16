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

	GetCursorPos(&pt);	// 현재 마우스의 위치 좌표를 얻어오는 함수
	ScreenToClient(g_hWnd, &pt);	// 전체 스크린영역에서 생성한 클라이언트(창) 좌표로 변환

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;
	
	Update_Rect();
	ShowCursor(false);		// 마우스 커서를 출력하지 않겠다.

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	

}

void CMouse::Render(HDC hDC)
{


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cursor");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left ),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top ),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX * 0.5f,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY * 0.5f,
		(int)m_tInfo.fCX * 0.5f,				// 복사할 비트맵의 가로, 세로 길이
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

