#include "stdafx.h"
#include "Monster2.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "BossBullet.h"
#include "AbstractFactory.h"
#include "Potion.h"
#include "SoundMgr.h"
CMonster2::CMonster2()
	:m_eCurState(STATE_END), m_ePreState(STATE_END), m_ecurPattern(NONE)
{
}


CMonster2::~CMonster2()
{
}

void CMonster2::Initialize(void)
{
	m_tInfo.fCX = 144.f;
	m_tInfo.fCY = 128.f;
	m_fSpeed = 0.8f;
	m_iHp = 8;
	m_fDiagonal = 12.f;
	m_eRender = RENDER_GAMEOBJECT;
	m_DelayTime = GetTickCount();
	m_bDeadEffect = false;
	m_eCurState = IDLE_DOWN;
	m_SoundTime = GetTickCount();
	m_pTime = GetTickCount();
	m_bCollisionCheck = false;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster2/Monster2.bmp", L"Monster2");
}

int CMonster2::Update(void)
{
	if (m_bDeadEffect)
	{
		m_eCurState = DEAD_ALL;
		
			if (m_bDead)
			{
				random_device random;
				mt19937 rd(random());
				uniform_int_distribution<int> range(1, 2);

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
			m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
			
			if (m_pTarget)
			{
				float		fWidth = fabs(m_pTarget->Get_Info().fX) - fabs(m_tInfo.fX);
				float		fHeight = ( m_pTarget->Get_Info().fY )- (m_tInfo.fY );

				float		fDiagonal =sqrtf((fWidth * fWidth) + (fHeight * fHeight));
				float		fRadian = acosf(fWidth / fDiagonal);

				m_fAngle = fRadian * 180.f / PI;
				
				if (m_tInfo.fY < m_pTarget->Get_Info().fY)
					m_fAngle *= -1.f;

			
						if ((fDiagonal) < 400.f)
						{
							m_tInfo.fX += m_fSpeed* cosf(m_fAngle * PI / 180.f);
							m_tInfo.fY -= m_fSpeed* sinf(m_fAngle * PI / 180.f);

							switch (m_ecurPattern)
							{
							case CMonster2::SPLIT:
								

								if (m_DelayTime + 1000 < GetTickCount())
								{
									Split();

									if (m_pTime + 1000 < GetTickCount())
									{
										AttackBullet();
										m_pTime = GetTickCount();
									}
									m_DelayTime = GetTickCount();
									m_ecurPattern = NONE;
								}
								break;
							case CMonster2::SMOG:
								if (m_DelayTime + 2000 < GetTickCount())
								{
									Smog();
									CSoundMgr::Get_Instance()->PlaySoundW(L"gunknight_shockwave_01.wav", SOUND_EFFECT, 1.f);

									m_DelayTime = GetTickCount();
									m_ecurPattern = MOVE;
								
								}
								break;
							case CMonster2::MOVE:
								if (m_DelayTime + 1000 < GetTickCount())
								{
									Monster_Dir();

									MoveToPlayer();
									m_DelayTime = GetTickCount();
									m_ecurPattern = NONE;
								}
								break;
							case CMonster2::NONE:
								if (m_DelayTime + 2000 < GetTickCount())
								{
									RandomPattern();
									m_DelayTime = GetTickCount();
								}
								break;
						
								}
						
						}
						else if(m_fDiagonal >= 400.f)
						
						{

							switch (m_eDir)
							{
							case DIR_LEFT:
								m_tInfo.fX += m_fSpeed;
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



	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster2::Late_Update(void)
{


	Motion_Change();
	if (Move_Frame() == true)
	{
		switch ((m_eCurState))
		{
		case HIT_ALL:
			Monster_Dir();
			break;
		case DEAD_ALL:
			m_bDead = true;
			break;
		case IDLE_UP:
		case IDLE_DOWN:
		case IDLE_LEFT:
		case IDLE_RIGHT:
			Monster_Dir();

			if (m_pTarget)
			{
				dynamic_cast<CPlayer*>(m_pTarget)->Set_PlayerCollisionCheck();
			}

			m_tFrame.iFrameStart = 0;
			break;
		case ATTACK_UP:
		case ATTACK_DOWN:
		case ATTACK_LEFT:
		case ATTACK_RIGHT:
			Monster_Dir();
			
			if (m_pTarget)
			{
				dynamic_cast<CPlayer*>(m_pTarget)->Set_PlayerCollisionCheck();
			}
			break;

		case SMOG_LEFT:
		case SMOG_RIGHT:
			if (m_pTarget)
			{
				dynamic_cast<CPlayer*>(m_pTarget)->Set_PlayerCollisionCheck();
			}
			break;
		default:
			break;

		}
	}


}

void CMonster2::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Monster2");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX * 0.5f,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY* 0.5f,
		(int)m_tInfo.fCX* 0.5f,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY * 0.5f,
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상

}

void CMonster2::Release(void)
{
}

void CMonster2::OnCollision(void)
{
	if (!m_bCollisionCheck)
	{
		Hit();

		m_bCollisionCheck = true;

		if (m_iHp <= 0)
		{
			m_bDeadEffect = true;
			CSoundMgr::Get_Instance()->PlaySoundW(L"gunnut_dead.wav", SOUND_EFFECT, 1.f);

		}
	}

	
}

void CMonster2::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
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

bool CMonster2::Get_DeadEffect(void)
{
	return false;
}

void CMonster2::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		case IDLE_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case IDLE_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case IDLE_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK_RIGHT:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_DOWN:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_LEFT:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD_ALL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 8;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case SMOG_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 9;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case SMOG_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 10;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case HIT_ALL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 11;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CMonster2::Monster_Dir(void)
{

	if (m_pTarget != nullptr)
	{
	
		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX )); // 밑변
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY )); // 높이
		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	
		float	fRadian = acosf(fWidth / fDiagonal); // 라디안 각도

		m_fAngle = fRadian * 180.f / PI; // 각도
		
		if (m_pTarget->Get_Info().fY > (m_tInfo.fY ))  //  cos 0도에서 180도 밖에 표현이 안되기때문에
			m_fAngle *= -1.f;


		if (25 <= m_fAngle &&  m_fAngle < 130)
		{
			m_eCurState = IDLE_UP;

		}
		else if ((130 <= m_fAngle &&  m_fAngle < 145))
		{
			m_eCurState = IDLE_LEFT;

		}
		else if ((-145 <= m_fAngle &&  m_fAngle < -95))
		{
			m_eCurState = IDLE_LEFT;

		}
		else if ((-95 <= m_fAngle &&  m_fAngle < -40))
		{
			m_eCurState = IDLE_DOWN;

		}
		else if ((-40 <= m_fAngle &&  m_fAngle < 5))
		{
			m_eCurState = IDLE_RIGHT;

		}
		else if ((5 <= m_fAngle &&  m_fAngle < 25))
		{
			m_eCurState = IDLE_RIGHT;

		}


	}

}

void CMonster2::Hit()
{
	m_iHp -= 1;
	m_eCurState = HIT_ALL;
	CSoundMgr::Get_Instance()->PlaySoundW(L"gunnut_hurt.wav", SOUND_EFFECT, 0.5f);

}



void CMonster2::Split()
{

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this); // 플레이어 객체 가져오기	

	if (m_pTarget != nullptr)
	{

		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX)); // 밑변
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY)); // 높이
		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	
		float	fRadian = acosf(fWidth / fDiagonal); // 라디안 각도

		m_fAngle = fRadian * 180.f / PI; // 각도

		if (m_pTarget->Get_Info().fY > (m_tInfo.fY))  //  cos 0도에서 180도 밖에 표현이 안되기때문에
			m_fAngle *= -1.f;
		
		if (25 <= m_fAngle &&  m_fAngle < 130)
		{
			m_eCurState = ATTACK_UP;

			
		

		}
		else if ((130 <= m_fAngle &&  m_fAngle < 145))
		{
			m_eCurState = ATTACK_LEFT;
			
		}
		else if ((-145 <= m_fAngle &&  m_fAngle < -95))
		{
			m_eCurState = ATTACK_LEFT;
			
		}
		else if ((-95 <= m_fAngle &&  m_fAngle < -40))
		{
			m_eCurState = ATTACK_DOWN;
		
		}
		else if ((-40 <= m_fAngle &&  m_fAngle < 5))
		{
			m_eCurState = ATTACK_RIGHT;
		
		}
		else if ((5 <= m_fAngle &&  m_fAngle < 25))
		{
			m_eCurState = ATTACK_RIGHT;
			
		}

	}
}

void CMonster2::Smog()
{

	if (m_pTarget != nullptr)
	{

		if (m_pTarget->Get_Info().fX > (m_tInfo.fX))  //  cos 0도에서 180도 밖에 표현이 안되기때문에
			m_eCurState = SMOG_RIGHT;

		else
			m_eCurState = SMOG_LEFT;

	}
}

void CMonster2::RandomPattern()
{
	random_device random;
	mt19937 rd(random());
	uniform_int_distribution<int> range(1, 2);

	m_ecurPattern = (PATTERN)range(rd);
}

void CMonster2::MoveToPlayer(void)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget != nullptr)
	{
		m_tInfo.fX = m_pTarget->Get_Info().fX + 10.f;
		m_tInfo.fY = m_pTarget->Get_Info().fY;
		

		if (m_pTime + 1000 < GetTickCount())
		{
			m_eCurState = ATTACK_LEFT;
			m_pTime = GetTickCount();
		}

	}
}

void CMonster2::AttackBullet(void)
{

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this); // 플레이어 객체 가져오기	

	if (m_pTarget != nullptr)
	{

		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX)); // 밑변
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY)); // 높이
		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	
		float	fRadian = acosf(fWidth / fDiagonal); // 라디안 각도

		m_fAngle = fRadian * 180.f / PI; // 각도

		if (m_pTarget->Get_Info().fY > (m_tInfo.fY))  //  cos 0도에서 180도 밖에 표현이 안되기때문에
			m_fAngle *= -1.f;
		m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
		m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<BossBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));

		CSoundMgr::Get_Instance()->PlaySoundW(L"gunnut_swing_01.wav", SOUND_EFFECT, 1.f);

	}
}