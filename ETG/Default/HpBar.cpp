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

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX + 55.f),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY + 20.f),
		hMemDC2,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + 26.f),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_fGague ),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY +20.f),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// �����ϰ��� �ϴ� ����/ �����ϰ��� �ϴ� ����
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
