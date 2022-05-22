#include "stdafx.h"
#include "Host.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Baba.h"
#include "HostBullet.h"
#include "Junior.h"
CHost::CHost()
	: m_eCurState(IDLE), m_ePreState(END)

{
}


CHost::~CHost()
{
}

void CHost::Initialize(void)
{
	m_tInfo.fCX = 126.f;
	m_tInfo.fCY = 104.f;
	m_tInfo.fX = 350.f;
	m_tInfo.fY = 480.f;
	m_fSpeed = 0.8f;
	m_iHp = 25;
	m_fDiagonal = 12.f;
	m_eRender = RENDER_GAMEOBJECT;
	m_bDeadEffect = false;
	m_pTime = GetTickCount();
	m_DelayTime = GetTickCount();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/host.bmp", L"host");

}

int CHost::Update(void)
{
	if (m_bDeadEffect)
	{
		m_eCurState = DEAD;

		if (m_bDead)
		{
			m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this); // 플레이어 객체 가져오기	

			if (m_pTarget)
			{

				CObjMgr::Get_Instance()->Add_Object(OBJ_PET, CAbstractFactory<CJunior>::Create(350.f, 480.f));
			}

			//펫생성
			return OBJ_DEAD;
		}
	}
	else
	{
		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this); // 플레이어 객체 가져오기	


	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CHost::Late_Update(void)
{
	Motion_Change();
	if (Move_Frame() == true)
	{
		switch ((m_eCurState))
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;

			break;
		case HIT:
		{
			if (m_pTime + 500 < GetTickCount())
			{
				Attack();
				m_pTime = GetTickCount();
				int degree = 200;

				while (degree < 360)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CHostBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY, degree));
					degree += 10;

				}
			}

			
			

			break;
		}
		case DEAD:
			m_bDead = true;
			break;
		case FAINT:
			m_tFrame.iFrameStart = 0;
			break;
	
		case ATTACK_DOWN:
		case ATTACK_RD:
		case ATTACK_RIGHT:
			Attack();
			m_tFrame.iFrameStart = 0;
			break;
		default:
			break;

		}
	}
}

void CHost::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"host");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX ),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX * 0.5f,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY* 0.5f,
		(int)m_tInfo.fCX* 0.5f,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY* 0.5f,
		RGB(255, 0, 255));
}

void CHost::Release(void)
{
}

void CHost::OnCollision(void)
{
	Hit();
	if ( 0< m_iHp && m_iHp <= 5)
	{
		m_eCurState = FAINT;
		//뚱바 생성
		if (m_iHp == 5)
		{
			if ( GetTickCount() - m_DelayTime > 3000)
			{

			CObjMgr::Get_Instance()->Add_Object(OBJ_PET, CAbstractFactory<CBaba>::Create(m_pTarget->Get_Info().fX - 35.f, m_pTarget->Get_Info().fY + 80.f));
			m_DelayTime = GetTickCount();
			}
		}

	}

	else if (m_iHp <= 0)
	{
		m_bDeadEffect = true;

	}

}

void CHost::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}

bool CHost::Get_DeadEffect(void)
{
	return false;
}

void CHost::Motion_Change(void)
{

	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();

			break;

		case ATTACK_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK_RD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case FAINT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		
		}

		m_ePreState = m_eCurState;
	}
}

void CHost::Monster_Dir(void)
{
}

void CHost::Hit()
{
	m_iHp -= 1;
	m_eCurState = HIT;
}

void CHost::Attack()
{


	if (m_pTarget != nullptr)
	{
		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX)); // 밑변
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY)); // 높이

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	

		float	fRadian = acosf(fWidth / fDiagonal); // 라디안 각도

		m_fAngle = fRadian * 180.f / PI; // 각도

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)  //  cos 0도에서 180도 밖에 표현이 안되기때문에
			m_fAngle *= -1.f;


		 if ((-90 <= m_fAngle &&  m_fAngle < -45))
		{
			m_eCurState = ATTACK_DOWN;

		}
		else if ((-45 <= m_fAngle &&  m_fAngle <-10 ))
		{
			m_eCurState = ATTACK_RD;

		}
		else if ((-10 <= m_fAngle &&  m_fAngle < 30))
		{
			m_eCurState = ATTACK_RIGHT;

		}
		 
		 // 총알 생성
		
		 m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
		 m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

		
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CHostBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
		
	}

}
