#include "stdafx.h"
#include "BossMonster.h"
#include "BossBomb.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BossBullet.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
CBossMonster::CBossMonster()
	:m_eCurState(DOWN), m_ePreState(END), currentState(NONE)
{
}


CBossMonster::~CBossMonster()
{
	Release();
}

void CBossMonster::Initialize(void)
{
	m_tInfo.fX = 980.f;
	m_tInfo.fY = 690.f;
	m_iHp = 15;
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;
	iCount = 0;
	iTempX = 0;
	iTempY = 10;
	m_fSpeed = 5.f;
	m_fDiagonal = 70.f;
	m_bDeadEffect = false;
	m_bCollisionCheck = false;
	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss.bmp", L"Boss");
	m_DelayTime = GetTickCount();

	m_dwTime = GetTickCount();
	CSoundMgr::Get_Instance()->PlaySoundW(L"Gull_Outro_01.wav", SOUND_EFFECT, 0.5f);

}

int CBossMonster::Update(void)
{

	if (m_bDeadEffect)
	{
		m_eCurState = DEAD;

		if (m_bDead)
			return OBJ_DEAD;
	}
	else {

		if (m_eCurState != FLY && m_eCurState != POSE)
		{
			Monster_Dir();
		}

		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
		// 원래 랜덤인데 시연회때는 랜덤으로 X
			switch (currentState)
			{
			case LAUNCH1:
				if (m_dwTime + 500 < GetTickCount())
				{
					PatternNormalShot();
					m_dwTime = GetTickCount();
					currentState = NONE;
				}
				break;
			case LAUNCH2:
				if (m_dwTime + 500 < GetTickCount())
				{
					PatternWideShot();
					m_dwTime = GetTickCount();
					currentState = NONE;
				}
				break;

			case LAUNCH3:
				if (m_dwTime + 200 < GetTickCount())
				{
					if (iCount < 5)
					{
						PatternContinueShot();
						m_dwTime = GetTickCount();
						++iCount;
					}
					else
					{
						currentState = NONE;
						iCount = 0;
					}
				}
				
				break;

			case MOVE:

				if (m_dwTime + 600 < GetTickCount())
				{
					m_eCurState = FLY;
					CSoundMgr::Get_Instance()->PlaySoundW(L"Gull_Lift_01.wav", SOUND_EFFECT, 0.5f);

					if (PatternMoveToUp())
					{
						currentState = BOMB;
					}
					m_dwTime = GetTickCount();
				}
				break;

			case BOMB:

				if (m_dwTime + 400 < GetTickCount())
				{
						if (iCount < 20)
						{
							PatternBomb();
							m_dwTime = GetTickCount();
							++iCount;
						}
						else
						{
							currentState = RETURN;
							iCount = 0;
					
						}
					}				
				break;

			case RETURN:
				m_eCurState = LAND;

				if (m_dwTime + 600 < GetTickCount())
				{
					if (PatternMoveToOri())
					{
						m_eCurState = POSE;
						currentState = LAUNCH1;
						CSoundMgr::Get_Instance()->PlaySoundW(L"Gull_Flap_01.wav", SOUND_EFFECT, 0.5f);

					}
					
					m_dwTime = GetTickCount();

				}
				break;

			case NONE:

				if (m_dwTime + 2000 < GetTickCount())
				{
					RandomPattern();
					m_dwTime = GetTickCount();
				}
				break;
		
			}
		}
	
	Update_Rect();
	return OBJ_NOEVENT;
}



void CBossMonster::Late_Update(void)
{

	Motion_Change();
	if (Move_Frame() == true)
	{
		switch ((m_eCurState))
		{
		case HIT:
			break;
		case FLY :
			m_tFrame.iFrameStart = 0;
			break;
		case LAND:
			m_tFrame.iFrameStart = 0;
			break;
		case DEAD:
				m_bDead = true;
			
				CSceneMgr::Get_Instance()->Scene_Change(SC_ENDING);
			

			break;
		case POSE:
			m_eCurState = DOWN;
			Monster_Dir();
			break;
		default:
			break;

		}

	
	}



}

void CBossMonster::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX) + 50.f ,				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY) + 50.f,
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX * 0.5f,// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY * 0.5f,
		(int)m_tInfo.fCX* 0.5f,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY * 0.5f,
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상

}

void CBossMonster::Release(void)
{

}



void CBossMonster::Motion_Change(void)
{

	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case RU:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		case RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RD:
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

		case LD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case LU:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case FLY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 8;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case LAND:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 9;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case POSE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion =10;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 11;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CBossMonster::Monster_Dir(void)
{
	//플레이어와의 각도에 따라서 시선이 달라짐

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this); // 플레이어 객체 가져오기	

	if (m_pTarget != nullptr)
	{
		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX)); // 밑변
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY)); // 높이

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	

		float	fRadian = acosf(fWidth / fDiagonal); // 라디안 각도

		m_fAngle = fRadian * 180.f / PI; // 각도

		if (m_pTarget->Get_Info().fY > m_tInfo.fY )  //  cos 0도에서 180도 밖에 표현이 안되기때문에
			m_fAngle *= -1.f;


		if (25 <= m_fAngle &&  m_fAngle < 90)
		{
			m_eCurState = RU;

		}
		else if ((90 <= m_fAngle &&  m_fAngle < 130))
		{
			m_eCurState = LU;

		}
		else if ((130 <= m_fAngle &&  m_fAngle < 165))
		{
			m_eCurState = LEFT;

		}
		else if ((-145 <= m_fAngle &&  m_fAngle < -90))
		{
			m_eCurState = LD;

		}
		else if ((-90 <= m_fAngle &&  m_fAngle < -40))
		{
			m_eCurState = DOWN;

		}
		else if ((-40 <= m_fAngle &&  m_fAngle < 5))
		{
			m_eCurState = RD;

		}
		else if ((5 <= m_fAngle &&  m_fAngle < 25))
		{
			m_eCurState = RIGHT;

		}


	}
	
}

void CBossMonster::RandomPattern()
{

	random_device random;
	mt19937 rd(random());
	uniform_int_distribution<int> range(1,4);

	currentState = (PATTERN)range(rd);


}

bool CBossMonster::PatternMoveToUp()
{
	m_tInfo.fY -= 80.f;

	if (m_tInfo.fY < -100)
	{
		//미사일 쏘기 플레이어 정보 받아와서 보스보다 왼쪽에 있을때는 왼쪽 영역에 폭탄 투하, 오른쪽에 있을때는 오른쪽 영역에 폭탄 투하 일정 좌표에 플레이어의 실시간 y 좌표보다 커지면 삭제 이거는 미사일의 late_update에서 

		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		if (m_pTarget)
		{

		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX + iScrollX));
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY + iScrollY));

		float	fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight)); //빗변	

		float	fRadian = acosf(fWidth / fDiagonal);


		if (m_pTarget->Get_Info().fY > (m_tInfo.fY + iScrollY))
			fRadian *= -1.f;

		m_fAngle = fRadian * 180.f / PI;

		m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
		m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<BossBullet>::Create(m_tPosin.x, m_tPosin.y, m_fAngle));

		return true;
		}
	}
	return false;
	
				

		
	
	
}

void CBossMonster::PatternBomb()
{

	random_device random;
	mt19937 rd(random());
	uniform_int_distribution<int> range(450, 1520);

	random_device random2;
	mt19937 rd2(random2());
	uniform_int_distribution<int> range2(-150, -10);

	iTempX = (float)range(rd);
	iTempY = (float)range2(rd2);

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_pTarget != nullptr)
	{
		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX + iScrollX));
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY + iScrollY));

		float	fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight)); //빗변	

		float	fRadian = acosf(fWidth / fDiagonal);


		if (m_pTarget->Get_Info().fY > (m_tInfo.fY + iScrollY))
			fRadian *= -1.f;

		m_fAngle = fRadian * 180.f / PI;

		m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
		m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));


		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CBossBomb>::Create(iTempX, iTempY, m_fAngle));
		

	}
}

bool CBossMonster::PatternMoveToOri()
{
	if (m_tInfo.fY == 690.f)
	{
		return true;
	}
	m_tInfo.fY += 80.f;
	return false;
}


void CBossMonster::PatternWideShot()
{
	int degree = 0;

	while (degree < 360)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<BossBullet>::Create(m_tInfo.fX, m_tInfo.fY, degree));
		degree += 45;
	}
}

void CBossMonster::PatternContinueShot()
{

		if (m_pTarget != nullptr)
		{
			int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

			float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX ));
			float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY ));

			float	fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight)); //빗변	

			float	fRadian = acosf(fWidth / fDiagonal);

			m_fAngle = fRadian * 180.f / PI;

			if (m_pTarget->Get_Info().fY > (m_tInfo.fY ))
				m_fAngle *= -1.f;


			m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
			m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));
			
			
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<BossBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
			
			
	}
	
}

void CBossMonster::PatternNormalShot()
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_pTarget != nullptr)
	{
		m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX ));
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY ));

		float	fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight)); //빗변	

		float	fRadian = acosf(fWidth / fDiagonal);
		m_fAngle = fRadian * 180.f / PI;

		if (m_pTarget->Get_Info().fY > (m_tInfo.fY ))
			m_fAngle *= -1.f;


		m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
		m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<BossBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));

	}

}



void CBossMonster::OnCollision(void)
{

		m_eCurState = HIT;

	if (!m_bCollisionCheck)
	{
	
		m_iHp -= 1;
		CSoundMgr::Get_Instance()->PlaySoundW(L"Boss_hurt.wav", SOUND_EFFECT, 0.5f);

		m_bCollisionCheck = true;
	}

	 if (m_iHp <= 0)
	{
		m_bDeadEffect = true;
		CSoundMgr::Get_Instance()->PlaySoundW(L"Gull_Death_01.wav", SOUND_EFFECT, 0.5f);

	}
	//hp의따라서 행동 만약에 hp가 0 보다 클때는 타격 이펙트를 true로 하고 아닐[때는 die 함수를 쓴다
}

void CBossMonster::OnCollision(DIRECTION _eDir, const float & _fX, const float & _fY)
{
}


bool CBossMonster::Get_DeadEffect(void)
{
	return false;
}
