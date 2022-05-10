#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "Mouse.h"

float	g_fSound = 1.f;

CPlayer::CPlayer()
	: m_eCurState(IDLE), m_ePreState(END)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = 500.F;

	m_tInfo.fCX = 80.f; // 20 * 25
	m_tInfo.fCY = 100.f;

	m_fSpeed = 5.f;

	m_fDiagonal = 100.f;

	m_bJump = false;
	m_bRoll = false;
	m_fJumpPower = 15.f;
	m_fJumpTime = 0.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LU.bmp", L"Player_LU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RU.bmp", L"Player_RU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LD.bmp", L"Player_LD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RD.bmp", L"Player_RD");
	//CSoundMgr::Get_Instance()->PlaySoundW(L"Success.wav", SOUND_EFFECT, g_fSound);

}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Mouse_Sight();
	Key_Input();
	OffSet();
	Dodge_Roll();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	Motion_Change();
	Move_Frame();


#ifdef _DEBUG

	//system("cls");
	//cout << "�÷��̾� ��ǥ : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;


#endif // _DEBUG
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX * 0.5f,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY * 0.5f,
		(int)m_tInfo.fCX * 0.5f,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY * 0.5f,
		RGB(255, 0, 255));			// �����ϰ��� �ϴ� ����/ �����ϰ��� �ϴ� ����

				
}
void CPlayer::Release(void)
{
	
}

void CPlayer::Mouse_Sight(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	//���콺 �ǽð� ��ǥ �޾ƿ���

	GetCursorPos(&pt);	// ���� ���콺�� ��ġ ��ǥ�� ������ �Լ�
	ScreenToClient(g_hWnd, &pt);	// ��ü ��ũ���������� ������ Ŭ���̾�Ʈ(â) ��ǥ�� ��ȯ

	// �÷��̾��� ������ ���콺�� ���� ���ϱ�

	float fWidth = (pt.x - (m_tInfo.fX + iScrollX)); //�غ�  // ��ũ�� �Ѿ���� ���� �߻�
	float fHeight = (pt.y  - (m_tInfo.fY + iScrollY)); // ����

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //����	
															
	float	fRadian = acosf(fWidth / fDiagonal);	//���� ������ ����

	if (pt.y > (m_tInfo.fY + iScrollY))
		fRadian *= -1.f;

	m_fAngle = fRadian * 180.f / PI; //��׸� ����

	if (25 <= m_fAngle &&  m_fAngle < 70)
	{
		m_pFrameKey = L"Player_RU";

	}
	else if ((70 <= m_fAngle &&  m_fAngle < 110))
	{
		m_pFrameKey = L"Player_UP";

	}
	else if ((110 <= m_fAngle &&  m_fAngle < 170))
	{
		m_pFrameKey = L"Player_LU";

	}
	else if ((170 <= m_fAngle &&  m_fAngle < 260))
	{
		m_pFrameKey = L"Player_LEFT";
	
	}
	else if ((-90 <= m_fAngle &&  m_fAngle < -40))
	{
		m_pFrameKey = L"Player_DOWN";

	}
	else if ((-40 <= m_fAngle &&  m_fAngle < 25))
	{
		m_pFrameKey = L"Player_RIGHT";	

	}

}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	if (GetAsyncKeyState('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eCurState = WALK;

	
	}

	else if (GetAsyncKeyState('D'))
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurState = WALK;

	
	}

	else if (GetAsyncKeyState('W'))
	{
		m_tInfo.fY -= m_fSpeed;
		m_eCurState = WALK;
	

	}

	else if (GetAsyncKeyState('S'))
	{
		m_tInfo.fY += m_fSpeed;
		m_eCurState = WALK;
	
	
	}
	else
		m_eCurState = IDLE;

}

void CPlayer::Dodge_Roll(void)
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_eCurState = ROLL;
		// ������ ���� ���� �ϳ� �����ϰ� �� �����϶��� ���� �Ѿ˰� �浹ó�� X
		m_bRoll = true;
	}

}


void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int		iItvX = 100;
	int		iItvY = 200;

	if (iOffSetX - iItvX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX + iItvX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	
	if (iOffSetY - iItvY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetY + iItvY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ROLL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 90;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

