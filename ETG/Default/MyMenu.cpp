#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");

	CObj*		pButton = CAbstractFactory<CMyButton>::Create(200.f, 400.f);
	pButton->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

	pButton = CAbstractFactory<CMyButton>::Create(400.f, 400.f);
	pButton->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

	pButton = CAbstractFactory<CMyButton>::Create(600.f, 400.f);
	pButton->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

}

void CMyMenu::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
}
