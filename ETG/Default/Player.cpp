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
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_fSpeed = 5.f;

	m_fDiagonal = 100.f;

	m_bJump = false;
	m_fJumpPower = 15.f;
	m_fJumpTime = 0.f;

	m_eRender = RENDER_GAMEOBJECT;

	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/maja2.bmp", L"Player");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LU.bmp", L"Player_LU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RU.bmp", L"Player_RU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LD.bmp", L"Player_LD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RD.bmp", L"Player_RD");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Stretch.bmp", L"Stretch");

	m_pFrameKey = L"Player_DOWN";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	//CSoundMgr::Get_Instance()->PlaySoundW(L"Success.wav", SOUND_EFFECT, g_fSound);

}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	Key_Input();
	Jumping();
	OffSet();

	

	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	Motion_Change();
	Move_Frame();


#ifdef _DEBUG

	//system("cls");
	cout << "플레이어 좌표 : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;


#endif // _DEBUG
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	HDC		hStretchDC = CBmpMgr::Get_Instance()->Find_Image(L"Stretch");

	
	/*BitBlt(hDC,							// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top), 
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY), 
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 7, 8인자 : 비트맵을 출력할 시작 좌표, X,Y
		0, 
		SRCCOPY);*/						// 출력효과, 그대로 복사 출력

	if (m_bStretch)
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));			// 제거하고자 하는 색상
	}

	else
	{
		StretchBlt(hStretchDC,		// 출력할 이미지 핸들
					0,				// 복사 받을 이미지 시작 좌표(Left, Top 좌표)
					0, 
					m_tInfo.fCX,	// 출력할 이미지 가로 세로 사이즈	
					m_tInfo.fCY, 
					hMemDC,			// 반전해서 출력하고자 하는 텍스처 이미지
					m_tFrame.iFrameStart * (int)m_tInfo.fCX + m_tInfo.fCX,	// 가져올 이미지의 시작점 x,y좌표							// 비트맵 출력 시작 좌표, X,Y
					m_tFrame.iMotion * (int)m_tInfo.fCY,
					-m_tInfo.fCX, // 복사할 비트맵의 가로, 세로 길이
					m_tInfo.fCY, 
					SRCCOPY);

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
					int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
					int(m_tRect.top + iScrollY),
					int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
					int(m_tInfo.fCY),
					hStretchDC,							// 비트맵을 가지고 있는 DC
					0,								// 비트맵 출력 시작 좌표, X,Y
					0,
					(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
					(int)m_tInfo.fCY,
					RGB(0, 0, 0));
	}
				
}
void CPlayer::Release(void)
{
	
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = L"Player_RIGHT";
		m_eCurState = WALK;
		m_bStretch = false;
	}

	else if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_RIGHT";
		m_eCurState = WALK;
		m_bStretch = true;
	}

	else if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_UP";
		m_eCurState = WALK;

	}

	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_pFrameKey = L"Player_DOWN";
		m_eCurState = WALK;
	}

	else if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		//m_bJump = true;

		CSoundMgr::Get_Instance()->PlaySound(L"Success.wav", SOUND_EFFECT, g_fSound);

		return;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_F3))
	{
		g_fSound -= 0.1f;

		if (g_fSound < 0.f)
			g_fSound = 0.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);		
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_F2))
	{
		g_fSound += 0.1f;

		if (g_fSound > 1.f)
			g_fSound = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);

	}

	else
		m_eCurState = IDLE;

}

void CPlayer::Jumping(void)
{
	float		fY = 0.f;

	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.2f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}
}

void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int		iItvX = 300;
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

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}
