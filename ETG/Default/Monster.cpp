#include "stdafx.h"
#include "Monster.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "MonsterBullet.h"
#include "Potion.h"
CMonster::CMonster()
	:m_eCurState(MONSTER_DOWN), m_ePreState(MONSTER_END)
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;
	m_fSpeed = 0.4f;
	m_iHp = 3;
	m_fDiagonal = 2.f;
	m_iRandom = 0;
	m_eRender = RENDER_GAMEOBJECT;
	m_DelayTime = GetTickCount();
	m_bDeadEffect = false;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster1/Monster1.bmp", L"Monster1");
}

int CMonster::Update(void)
{
	if (m_bDeadEffect)
	{
		m_eCurState = MONSTER_DEAD;

		if (m_bDead)
		{
			random_device random;
			mt19937 rd(random());
			uniform_int_distribution<int> range(1, 3);

			m_iRandom = range(rd);

			if (m_iRandom == 1)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CPotion>::Create(m_tInfo.fX, m_tInfo.fY));
			}

			return OBJ_DEAD;
		}


	}
	else
	{

		if (m_eCurState != MONSTER_HIT)
		{
			m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

			if (m_pTarget)
			{

				float		fWidth = m_pTarget->Get_Info().fX - (m_tInfo.fX );
				float		fHeight = m_pTarget->Get_Info().fY - (m_tInfo.fY );

				float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
				float		fRadian = acosf(fWidth / fDiagonal);


				if (m_tInfo.fY < m_pTarget->Get_Info().fY )
					fRadian *= -1.f;

				m_fAngle = fRadian * 180.f / PI;

				if (fDiagonal < 500)
				{
					if (m_DelayTime + 1500 < GetTickCount())
					{
						Attack();
						m_DelayTime = GetTickCount();
					}

					if (fDiagonal < 250.f)
					{
						m_tInfo.fX += 1 * cosf(m_fAngle * PI / 180.f);
						m_tInfo.fY -= 1 * sinf(m_fAngle * PI / 180.f);
					}
					
					}

			
		}
			switch (m_eDir)
			{
			case DIR_LEFT:
				m_tInfo.fX -= m_fSpeed;
				m_tInfo.fY += m_fSpeed;
				break;
			case DIR_RIGHT:
				m_tInfo.fX += m_fSpeed;
				m_tInfo.fY -= m_fSpeed;
				break;
			case DIR_UP:
				m_tInfo.fX -= m_fSpeed;
				m_tInfo.fY += m_fSpeed;
				break;
			case DIR_DOWN:
				m_tInfo.fX += m_fSpeed;
				m_tInfo.fY += m_fSpeed;
				break;
			default:
				break;
			}

		}
		
	
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{

	Motion_Change();
	if (Move_Frame() == true)
	{
		switch ((m_eCurState))
		{
		case MONSTER_HIT:
			Monster_Dir();

			break;
		case MONSTER_DEAD:
			m_bDead = true;
			break;
		case MONSTER_UP:
		case MONSTER_DOWN:
		case MONSTER_LEFT:
		case MONSTER_RIGHT:
			Monster_Dir();

			if (m_pTarget)
			{
				dynamic_cast<CPlayer*>(m_pTarget)->Set_CollisionCheck();
			}

			m_tFrame.iFrameStart = 0;
			break;

		default:
			break;

		}


	}

}

void CMonster::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Monster1");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX ),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY ),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX *0.5f,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY*0.5f,
		(int)m_tInfo.fCX*0.5f,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY*0.5f,
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상

}


void CMonster::Release(void)
{
	
}

bool CMonster::Get_DeadEffect(void)
{
	return false;
}

void CMonster::Motion_Change(void)
{

	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case MONSTER_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		case MONSTER_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTER_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTER_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTER_HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 300;
			m_tFrame.dwTime = GetTickCount();
			break;

		case MONSTER_DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}

void CMonster::Monster_Dir(void)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this); // 플레이어 객체 가져오기	

	if (m_pTarget != nullptr)
	{
		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX )); // 밑변
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY)); // 높이
		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	
		float	fRadian = acosf(fWidth / fDiagonal); // 라디안 각도
		if (m_pTarget->Get_Info().fY > m_tInfo.fY)  //  cos 0도에서 180도 밖에 표현이 안되기때문에
			fRadian *= -1.f;

		m_fAngle = fRadian * 180.f / PI; // 각도

		if (25 <= m_fAngle &&  m_fAngle < 130)
		{
			m_eCurState = MONSTER_UP;

		}
		else if ((130 <= m_fAngle &&  m_fAngle < 165))
		{
			m_eCurState = MONSTER_LEFT;

		}
		else if ((-145 <= m_fAngle &&  m_fAngle < -90))
		{
			m_eCurState = MONSTER_LEFT;

		}
		else if ((-90 <= m_fAngle &&  m_fAngle < -40))
		{
			m_eCurState = MONSTER_DOWN;

		}
		else if ((-40 <= m_fAngle &&  m_fAngle < 5))
		{
			m_eCurState = MONSTER_RIGHT;

		}
		else if ((5 <= m_fAngle &&  m_fAngle < 25))
		{
			m_eCurState = MONSTER_RIGHT;

		}

	
	}

}

void CMonster::Hit()
{
	m_iHp -= 1;
	m_eCurState = MONSTER_HIT;
}

void CMonster::Attack()
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_pTarget != nullptr)
	{
		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX ));
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY));

		float	fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight)); //빗변	

		float	fRadian = acosf(fWidth / fDiagonal);
		
		m_fAngle = fRadian * 180.f / PI;

		if (m_pTarget->Get_Info().fY > (m_tInfo.fY))
			m_fAngle *= -1.f;


		m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
		m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CMonsterBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));

	}
}


void CMonster::OnCollision(void)
{
	Hit();

	if (m_iHp <= 0)
	{
		m_bDeadEffect = true;

	}
}

void CMonster::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
	switch (_eDir)
	{
	case DIR_LEFT:
	case DIR_RIGHT:
	case DIR_UP:
	case DIR_DOWN:
		m_fSpeed *= -1;
		break;
	default:
		break;
	}
}
