#include "stdafx.h"
#include "Shark.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "SharkBullet.h"
#include "SoundMgr.h"
CShark::CShark()
{
}


CShark::~CShark()
{
}

void CShark::Initialize(void)
{
	m_tInfo.fCX = 29.f;
	m_tInfo.fCY = 29.f;

	m_fSpeed = 1.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Weapon/Shark/Shark.bmp", L"Shark");

	m_fDiagonal = 28.f;
}

int CShark::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	//������Ʈ������ ���콺 ��ǥ������ �ͼ� ���� ��쿡 ������Ű left�ְ� �ƴҰ�쿡 right�ֱ� 
	Mouse_Sight();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CShark::Late_Update(void)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
	if (m_pTarget)
	{

		if (static_cast<CPlayer*>(m_pTarget)->Get_State() == 5)
		{
			m_bDead = true;
		}
	}
}

void CShark::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Shark");

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

void CShark::Release(void)
{
}

void CShark::OnCollision(void)
{
}

bool CShark::Get_DeadEffect(void)
{
	return false;
}

void CShark::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}

void CShark::Mouse_Sight(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget != nullptr)
	{

		m_tInfo.fY = m_pTarget->Get_Info().fY + 25.f + 10.f;
		m_tInfo.fX = m_pTarget->Get_Info().fX + 20.f;
		GetCursorPos(&pt);	// ���� ���콺�� ��ġ ��ǥ�� ������ �Լ�
		ScreenToClient(g_hWnd, &pt);	// ��ü ��ũ���������� ������ Ŭ���̾�Ʈ(â) ��ǥ�� ��ȯ


		float fWidth = (pt.x - (m_tInfo.fX + iScrollX)); //�غ�  // ��ũ�� �Ѿ���� ���� �߻�
		float fHeight = (pt.y - (m_tInfo.fY + iScrollY)); // ����

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //����	

		float	fRadian = acosf(fWidth / fDiagonal);	//���� ������ ����

		if (pt.y > (m_tInfo.fY + iScrollY))
			fRadian *= -1.f;

		m_fAngle = fRadian * 180.f / PI; //��׸� ����


		if (pt.x > m_tInfo.fX + iScrollX)
		{
			m_tInfo.fX += 16.f;

			if (25 <= m_fAngle &&  m_fAngle < 60)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 0;

			}
			else if ((60 <= m_fAngle &&  m_fAngle < 88))
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameEnd = 1;

			}
			else if ((-5 <= m_fAngle &&  m_fAngle < 25))
			{
				m_tFrame.iFrameStart = 2;
				m_tFrame.iFrameEnd = 2;

			}
			else if ((-20 <= m_fAngle &&  m_fAngle < -5))
			{
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameEnd = 3;

			}
			else if ((-60 <= m_fAngle &&  m_fAngle < -20))
			{
				m_tFrame.iFrameStart = 4;
				m_tFrame.iFrameEnd = 4;


			}
		}

		else if (pt.x < m_tInfo.fX + iScrollX)
		{
			m_tInfo.fX -= 16.f;
			if ((91 <= m_fAngle &&  m_fAngle < 115))
			{
				m_tFrame.iFrameStart = 9;
				m_tFrame.iFrameEnd = 9;
			}
			else if ((115 <= m_fAngle &&  m_fAngle < 150))
			{
				m_tFrame.iFrameStart = 8;
				m_tFrame.iFrameEnd = 8;
			}
			else if ((150 <= m_fAngle &&  m_fAngle < 183))
			{
				m_tFrame.iFrameStart = 7;
				m_tFrame.iFrameEnd = 7;
			}
			else if ((-120 <= m_fAngle &&  m_fAngle < -100))
			{
				m_tFrame.iFrameStart = 6;
				m_tFrame.iFrameEnd = 6;
			}
			else if ((-100 <= m_fAngle &&  m_fAngle < -70))
			{
				m_tFrame.iFrameStart = 5;
				m_tFrame.iFrameEnd = 5;
			}
		}
		else
			m_pFrameKey = L"Plg";

		m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
		m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

		if ((CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)))
		{
		
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CSharkBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
			CSoundMgr::Get_Instance()->PlaySoundW(L"tank_shot_01_001.wav", SOUND_EFFECT, 10.f);

		}

	}

}
