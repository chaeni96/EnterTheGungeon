#include "stdafx.h"
#include "BossBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

BossBullet::BossBullet()
{
}


BossBullet::~BossBullet()
{
}

void BossBullet::Initialize(void)
{

	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 47.f;
	m_fDiagonal = 10.f;
	m_fSpeed = 6.f;
	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BossBullet.bmp", L"BossBullet");

}

int BossBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	//�÷��̾��� ������ ���缭 �ϴ°�

	//�÷��̾�� ������ ���ؿ���
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	m_tInfo.fX += 10.f;
	m_tInfo.fY -= 10.f;

	Update_Rect();

	return OBJ_NOEVENT;
}

void BossBullet::Late_Update(void)
{
}

void BossBullet::Render(HDC hDC)
{


	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossBullet");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void BossBullet::Release(void)
{
}
