#include "stdafx.h"
#include "Potion.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
CPotion::CPotion()
{
}


CPotion::~CPotion()
{
	Release();
}

void CPotion::Initialize(void)
{
	m_tInfo.fX = 2700.f;
	m_tInfo.fY = 1730.f;
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 22.f;

	m_eRender = RENDER_ITEM;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Potion.bmp", L"Potion");
}

int CPotion::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPotion::Late_Update(void)
{
}

void CPotion::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Potion");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top  + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX*0.5f,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY*0.5f,
		(int)m_tInfo.fCX *0.5f,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY *0.5f ,
		RGB(255, 0, 255));			// 제
}

void CPotion::Release(void)
{
}

void CPotion::OnCollision(void) // 플레이어와 충돌
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	if (m_pTarget)
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			static_cast<CPlayer*>(m_pTarget)->Set_HpPlus(15);
			CSoundMgr::Get_Instance()->PlaySoundW(L"Bubbler_Drink_01.wav", SOUND_EFFECT, 1.f);

			m_bDead = true;

		}
	}
}

void CPotion::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}

bool CPotion::Get_DeadEffect(void)
{
	return false;
}
