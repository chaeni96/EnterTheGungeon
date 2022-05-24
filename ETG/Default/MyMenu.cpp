#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "Player.h"
CMyMenu::CMyMenu()
	:m_eCurState(START), m_ePreState(END)
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	m_DelayTime = GetTickCount();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Opening.bmp", L"Opening");

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());	// 플레이어 생성

	CObj*		pButton = CAbstractFactory<CMyButton>::Create(120.f, 420.f);
	pButton->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

	
	pButton = CAbstractFactory<CMyButton>::Create(120.f, 500.f);
	pButton->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);


}

void CMyMenu::Update(void)
{


	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::Late_Update(void)
{
	Motion_Change();

	Move_Frame();
	
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Opening");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, m_tFrame.iFrameStart *WINCX, m_tFrame.iMotion *WINCY, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
	CSoundMgr::Get_Instance()->StopAll();
}

void CMyMenu::Motion_Change(void)
{

	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 150;
		m_tFrame.dwTime = GetTickCount();

		m_ePreState = m_eCurState;
	}
}


