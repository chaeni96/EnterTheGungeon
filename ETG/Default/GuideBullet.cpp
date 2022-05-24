#include "stdafx.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "BossMonster.h"
#include "Player.h"
#include "SoundMgr.h"
CGuideBullet::CGuideBullet()
{
}


CGuideBullet::~CGuideBullet()
{
	Release();}


void CGuideBullet::Initialize(void)
{
	m_tInfo.fCX = 28.f;
	m_tInfo.fCY = 27.f;

	m_fSpeed = 7.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Guide.bmp", L"Guide");
	CSoundMgr::Get_Instance()->PlaySoundW(L"Comando.wav", SOUND_EFFECT, 20.f);

}

int CGuideBullet::Update(void)
{
	if (m_bDead)
	{
		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_BOSS, this);

		if (m_pTarget)
		{
			m_pTarget->Set_CollisionCheck();
		}
		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, this);

		if (m_pTarget)
		{
			m_pTarget->Set_CollisionCheck();
		}

		return OBJ_DEAD;
	}


	//�÷��̾��� ��ġ�� ���� m_pTarget �ٲ��ֱ�
	if (m_tInfo.fX < 1680 && m_tInfo.fY < 1170)
	{
		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_BOSS, this);
	}
	else
	{
		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, this);

	}

	if (m_pTarget)
	{
		float		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
		float		fRadian = acosf(fWidth / fDiagonal);

		m_fAngle = fRadian * 180.f / PI;

		if (m_tInfo.fY < m_pTarget->Get_Info().fY)
			m_fAngle *= -1.f;
	}
	m_fSpeed += 0.1f;

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CGuideBullet::Late_Update(void)
{
	
}

void CGuideBullet::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Guide");

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
		RGB(255, 0, 255));			// �����ϰ��� �ϴ� ����/ �����ϰ��� �ϴ� ����
}

void CGuideBullet::Release(void)
{
	
}

void CGuideBullet::OnCollision(void)
{
	m_bDead = true;
}

void CGuideBullet::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
	switch (_eDir)
	{
	case DIR_LEFT:
	case DIR_UP:
	case DIR_RIGHT:
	case DIR_DOWN:
		m_bDead = true;
		break;
	case DIR_END:
		break;
	default:
		break;
	}
}

