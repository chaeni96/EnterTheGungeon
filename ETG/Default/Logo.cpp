#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	// MCIWndCreate : mci(멀티미디어 장치를 재생하고 리소스 파일을 기록하기 위한 인터페이스), 오디오 및 비디오 주변 장치를 제어하는 장치
	// : 멀티미디어를 재생하기 위한 윈도우창을 생성하는 함수

	// 1인자 : 부모의 윈도우 핸들, 2인자 : mci윈도우 인스턴스 핸들
	// 3인자 : 창 스타일 WS_CHILD : 자식 창의 형태, WS_VISIBLE : 그 즉시 화면 갱신 MCIWNDF_NOPLAYBA : 플레이 바를 만들지 않겠다.
	// 4인자 : 파일 경로
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Video/Wildlife.wmv");

	// MoveWindow : 동영상을 재생할 크기를 설정, 설정하지 않을 경우 동영상의 원래 크기대로 출력
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);


	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
}

void CLogo::Update(void)
{
	
}

void CLogo::Late_Update(void)
{
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo) ||		
		CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);

		return;
	}
}

void CLogo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release(void)
{
	MCIWndClose(m_hVideo);
}
