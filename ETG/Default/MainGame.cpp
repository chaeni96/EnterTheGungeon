#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	m_iFPS = 0;
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	CSoundMgr::Get_Instance()->Initialize(); 
	CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
}

void CMainGame::Update(void)
{
	
	CSceneMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();

}

void CMainGame::Late_Update(void)
{

	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	if (SC_LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	
	CSceneMgr::Get_Instance()->Render(hMemDC);

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

}

void CMainGame::Release(void)
{
	CSoundMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);	
}


