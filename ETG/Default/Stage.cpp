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
#include "KeyMgr.h"
#include "HpBar.h"
#include "Inventory.h"
#include "SoundMgr.h"
#include "Monster2.h"
#include "Potion.h"

float	g_fSoundStage = .5f;

CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	// ���⼭ ������� �÷��̾��� ������ �޾ƿ;��ϴµ� ��� �޾ƿ���...
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CMouse>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_HP, CAbstractFactory<CHpBar>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_INVEN, CAbstractFactory<CInventory>::Create());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CPotion>::Create());

	//��ǥ �޾ƿͼ� �ֱ� �̻����� ��쿡��

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back/mapSuccess.bmp", L"mapSuccess");

	//CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile(); // Ÿ�� 
	
	//Ÿ�� �Ŵ��� ��������� �ּҰ� �Ѱ��ֱ�
	CObjMgr::Get_Instance()->Set_Vector(CTileMgr::Get_Instance()->Get_Tile());
	CSoundMgr::Get_Instance()->PlaySoundW(L"GUNGEONDOWN.mp3", SOUND_EFFECT, 0.3f);

}



void CStage::Update(void)
{

	//CTileMgr::Get_Instance()->Update();

	CObjMgr::Get_Instance()->Update();	

}

void CStage::Late_Update(void)
{
	//CTileMgr::Get_Instance()->Late_Update();

	CObjMgr::Get_Instance()->Late_Update();

}

void CStage::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//�Ϲ� ���϶��� ����ŷ �ϵ���

	random_device random;
	mt19937 rd(random());
	uniform_int_distribution<int> range(0, 12);
	iTemp = range(rd);


	
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		
		if (iTemp == 5)
		{
			iScrollX -= 10;
			iScrollY += 10;

		}
	}

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"mapSuccess");
	BitBlt(hDC, iScrollX, iScrollY, 3600, 2100, hGroundMemDC, 0, 0, SRCCOPY);

	
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
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER1_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_HP);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_INVEN);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);



}
