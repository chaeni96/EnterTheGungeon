#include "stdafx.h"
#include "BossBomb.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CBossBomb::CBossBomb()
	:m_eCurState(IDLE), m_ePreState(END)
{
}


CBossBomb::~CBossBomb()
{
}

void CBossBomb::Initialize(void)
{

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 65.f;
	m_bDeadEffect = false;
	m_fSpeed = 7.f;
	m_bDeadEffect = false;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BossBomb.bmp", L"BossBomb");
}

int CBossBomb::Update(void)
{
	if (m_bDeadEffect)
	{
		m_eCurState = DEAD;

		if (m_bDead)
			return OBJ_DEAD;

	}
	else
	{
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBossBomb::Late_Update(void)
{
	
		if (m_tInfo.fY >  600)
		{	
			m_bDeadEffect = true;
		}

		Motion_Change();

		if (Move_Frame() == true)
		{

			switch (m_eCurState)
			{
			case IDLE:
				m_tFrame.iFrameStart = 0;
				break;
			
			case DEAD:
				m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

				if (m_pTarget)
				{
					dynamic_cast<CPlayer*>(m_pTarget)->Set_CollisionCheck();
				}

				m_bDead = true;
				break;
		
			default:
				break;
			}

		}


	

		
	// �÷��̾� ���� �޾ƿͼ� Y �Ѿ�� �����ϵ��� �Ѵ�
	
}

void CBossBomb::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossBomb");

	if (m_eCurState != DEAD)
	{
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
	else
	{
		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX + 50),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY +50),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
}

void CBossBomb::Release(void)
{
}

void CBossBomb::OnCollision(void)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget) {

		if (dynamic_cast<CPlayer*>(m_pTarget)->Get_State() != 2)
		{
			m_bDeadEffect = true;
		}
	}
}

void CBossBomb::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
	
		}

		m_ePreState = m_eCurState;
	}
}