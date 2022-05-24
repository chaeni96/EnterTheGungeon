#include "stdafx.h"
#include "Baba.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
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
	CSoundMgr::Get_Instance()->PlaySoundW(L"baba.wav", SOUND_EFFECT, 5.f);

}

int CBaba::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	//�÷��̾� ��ġ �޾ƿ��� 

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
	if(m_pTarget)
	{
		float		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY; //���� ������ 0������ 180�̰� ������ ���� Ŭ���������� �ڱ��ڽ��� �������� ���� ���ϴ°Ŵϱ� ���� ��ǥ�������� �� ���ϱ�

		float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		float		fRadian = acosf(fWidth / fDiagonal);


		if (m_tInfo.fY < m_pTarget->Get_Info().fY)
			fRadian *= -1.f;

		m_fAngle = fRadian * 180.f / PI;

		if (fDiagonal > 110)
		{

			m_tInfo.fX += 4.f * cosf(m_fAngle * PI / 180.f);
			m_tInfo.fY -= 4.f * sinf(m_fAngle * PI / 180.f);

			if (GetAsyncKeyState('A'))
			{

				m_eCurState = LEFT;

			}
			else if (GetAsyncKeyState('D'))
			{
				m_eCurState = RIGHT;


			}
			else if (GetAsyncKeyState('W'))
			{
				m_eCurState = UP;


			}
			else if (GetAsyncKeyState('S'))
			{

				m_eCurState = DOWN;

			}
			else
			{
				m_eCurState = IDLE;
			}
		}

		
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

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX - 10.f),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY - 10.f),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
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
	switch (_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= _fX;
		break;
	case DIR_UP:
		m_tInfo.fY -= _fY;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += _fX;
		break;
	case DIR_DOWN:
		m_tInfo.fY += _fY;
		break;
	case DIR_END:
		break;
	default:
		break;
	}
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
	//key input���� motionChange
}
