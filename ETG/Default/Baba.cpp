#include "stdafx.h"
#include "Baba.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CBaba::CBaba()
	:m_eCurState(IDLE), m_ePreState(END)
{
}


CBaba::~CBaba()
{
}

void CBaba::Initialize(void)
{
	m_tInfo.fCX = 46.f;
	m_tInfo.fCY = 46.f;
	
	m_fSpeed = 5.f;
	m_iHp = 10;
	m_fDiagonal = 5.f;
	m_eRender = RENDER_GAMEOBJECT;
	m_bDeadEffect = false;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Pet/baba.bmp", L"baba");

	m_fDiagonal = 5.f;

}

int CBaba::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	//플레이어 위치 받아오기 

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
	if(m_pTarget)
	{
		float		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY; //각도 라디안은 0도에서 180이고 무조건 몬스터 클래스에서는 자기자신을 기준으로 값을 구하는거니깐 몬스터 좌표기준으로 각 구하기

		float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		float		fRadian = acosf(fWidth / fDiagonal);

		m_fAngle = (fRadian * 180.f) / PI;

		if (m_pTarget->Get_Info().fY > m_tInfo.fY) //sin으로 들어가는 값을 구하기 위해서,180도가 넘었음
			m_fAngle *= -1.f;


		
	}

	if (GetAsyncKeyState('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		
		m_eCurState = LEFT;

	}
	else if (GetAsyncKeyState('D'))
	{
		m_tInfo.fX += m_fSpeed;
			m_eCurState = RIGHT;
		

	}
	else if (GetAsyncKeyState('W'))
	{
		m_tInfo.fY -= m_fSpeed;
			m_eCurState = UP;
	

	}
	else if (GetAsyncKeyState('S'))
	{
		m_tInfo.fY += m_fSpeed;
		
			m_eCurState = DOWN;
		
	}
	else
	{
		m_eCurState = IDLE;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBaba::Late_Update(void)
{
	Motion_Change();

	if (Move_Frame() == true)
	{
		switch ((m_eCurState))
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;

			break;
	
		case UP:
		case DOWN:
		case RIGHT:
		case LEFT:
			m_tFrame.iFrameStart = 0;
			break;
		default:
			break;

		}
	}
}

void CBaba::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"baba");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX - 10.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY - 10.f),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CBaba::Release(void)
{
}

void CBaba::OnCollision(void)
{
}

void CBaba::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}

bool CBaba::Get_DeadEffect(void)
{
	return false;
}

void CBaba::Motion_Change(void)
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

		case UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case LEFT:
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

void CBaba::Player_Dir(void)
{
	//key input으로 motionChange
}
