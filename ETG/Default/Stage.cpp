#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Monster.h"
#include "Mouse.h"
#include "Gun.h"
#include "Comando.h"
#include "BossMonster.h"

CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	// ¿©±â¼­ ¸¸µé¾îÁØ ÇÃ·¹ÀÌ¾îÀÇ Á¤º¸¸¦ ¹Þ¾Æ¿Í¾ßÇÏ´Âµ¥ ¾î¶»°Ô ¹Þ¾Æ¿ÃÁö...
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_WEAPON, CAbstractFactory<CGun>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CMouse>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(200.f, 200.f));

	//ï¿½ï¿½Ç¥ ï¿½Þ¾Æ¿Í¼ï¿½ ï¿½Ö±ï¿½ ï¿½Ì»ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ì¿¡ï¿½ï¿½
	CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBossMonster>::Create());

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back/mapSuccess.bmp", L"mapSuccess");

	CTileMgr::Get_Instance()->Load_Tile();

}	



void CStage::Update(void)
{
	CObjMgr::Get_Instance()->Update();	
	CTileMgr::Get_Instance()->Update();

}

void CStage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

}

void CStage::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		iScrollX -= 10;
		iScrollY += 10;
	}

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Map");
	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"mapSuccess");
	BitBlt(hDC, iScrollX, iScrollY, 2400, 1400, hGroundMemDC, 0, 0, SRCCOPY);

	//CTileMgr::Get_Instance()->Render(hDC);

	//CLineMgr::Get_Instance()->Render(hMemDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BOSS);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_WEAPON);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);	
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER_BULLET);

}
