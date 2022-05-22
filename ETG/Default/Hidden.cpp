#include "stdafx.h"
#include "Hidden.h"
#include "Player.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "HpBar.h"
#include "Inventory.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Host.h"
CHidden::CHidden()
{
}


CHidden::~CHidden()
{
}

void CHidden::Initialize(void)
{

	if (!CObjMgr::Get_Instance()->Get_Player_Info())
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::Create(700.f, 280.f);

		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
		CObjMgr::Get_Instance()->Set_Player(pPlayer);


	}
	else
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(700.f, 280.f));


	CObjMgr::Get_Instance()->Add_Object(OBJ_HP, CAbstractFactory<CHpBar>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_INVEN, CAbstractFactory<CInventory>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CHost>::Create());

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back/Hidden_Stage.bmp", L"Hidden_Stage");

}

void CHidden::Update(void)
{
	CObjMgr::Get_Instance()->Update();

}

void CHidden::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

}

void CHidden::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Hidden_Stage");
	BitBlt(hDC, iScrollX, iScrollY, 900, 1200, hGroundMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

}

void CHidden::Release(void)
{
	// ³ªÁß¿¡
}
