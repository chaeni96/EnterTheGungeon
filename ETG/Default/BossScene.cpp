#include "stdafx.h"
#include "BossScene.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "BossMonster.h"
#include "AbstractFactory.h"
CBossScene::CBossScene()
	:m_eCurState(START), m_ePreState(END)
{
}


CBossScene::~CBossScene()
{
	Release();

}

void CBossScene::Initialize(void)
{
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;

	CSoundMgr::Get_Instance()->PlaySoundW(L"boss_start.wav", SOUND_MONSTER, 10.f);


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossScene.bmp", L"BossScene");
	m_eRender = RENDER_SCENE;
	m_DeleteTime = GetTickCount();
}

int CBossScene::Update(void)
{
	if (m_bDead)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBossMonster>::Create());

		return OBJ_DEAD;
	}


	return OBJ_NOEVENT;
}

void CBossScene::Late_Update(void)
{
	Motion_Change();

	if (Move_Frame() == true)
	{

		switch (m_eCurState)
		{
		case START:

			m_bDead = true;
			break;


		default:
			break;
		}

	}
}

void CBossScene::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossScene");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, m_tFrame.iFrameStart *WINCX, m_tFrame.iMotion *WINCY, SRCCOPY);
}

void CBossScene::Release(void)
{
}

void CBossScene::OnCollision(void)
{
}

void CBossScene::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}

bool CBossScene::Get_DeadEffect(void)
{
	return false;
}

void CBossScene::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 300;
		m_tFrame.dwTime = GetTickCount();

		m_ePreState = m_eCurState;
	}
}
