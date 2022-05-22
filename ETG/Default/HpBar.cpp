#include "stdafx.h"
#include "HpBar.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CHpBar::CHpBar()
{
}

CHpBar::~CHpBar()
{
	Release();
}

void CHpBar::Initialize(void)
{
	m_tInfo.fX = 150.f;
	m_tInfo.fY = 50.f;
	m_tInfo.fCX = 208.f;
	m_tInfo.fCY = 24.f;

	m_eRender = RENDER_UI;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HpEmpty.bmp", L"HpEmpty");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HpFull.bmp", L"HpFull");


}

int CHpBar::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CHpBar::Late_Update(void)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget)
	{
		float iHp = (float)m_pTarget->Get_Hp();

		m_fGague = m_tInfo.fCX*(iHp / 50);
	}
}

void CHpBar::Render(HDC hDC)
{


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"HpFull");
	HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"HpEmpty");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX + 55.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY + 20.f),
		hMemDC2,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + 26.f),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_fGague ),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY +20.f),
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,// 비트맵 출력 시작 좌표, X,Y
		0,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상
}

void CHpBar::Release(void)
{
}

void CHpBar::OnCollision(void)
{
}

void CHpBar::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}

bool CHpBar::Get_DeadEffect(void)
{
	return false;
}
