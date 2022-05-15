#include "stdafx.h"
#include "BossBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"

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
	m_fSpeed = 8.f;
	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BossBullet.bmp", L"BossBullet");

}

int BossBullet::Update(void)
{
	if (m_bDead)
	{
		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

		if (m_pTarget)
		{
			dynamic_cast<CPlayer*>(m_pTarget)->Set_CollisionCheck();
		}

		return OBJ_DEAD;
	}


	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	
	Update_Rect();

	return OBJ_NOEVENT;
}

void BossBullet::Late_Update(void)
{
	if (m_tRect.left < 100 || m_tRect.right > 1100 || m_tRect.top < 100 || m_tRect.bottom > 750 )
	{

		m_bDead = true;
	}
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

void BossBullet::OnCollision(void)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget) {

		if (dynamic_cast<CPlayer*>(m_pTarget)->Get_State() != 2)
		{
			m_bDead = true;
		}
	}
}


