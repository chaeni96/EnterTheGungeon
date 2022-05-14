#include "stdafx.h"
#include "BossMonster.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BossBullet.h"
#include "KeyMgr.h"
CBossMonster::CBossMonster()
	:m_eCurState(DOWN), m_ePreState(END)
{
}


CBossMonster::~CBossMonster()
{
	Release();
}

void CBossMonster::Initialize(void)
{
	m_tInfo.fX = 650.f;
	m_tInfo.fY = 400.f;

	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_iHp = 10;
	m_fSpeed = 5.f;
	m_fDiagonal = 70.f;
	m_bDeadEffect = false;
	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss.bmp", L"Boss");
	
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	currentState = None;
	behaviorState = Exit;
	m_dwTime = GetTickCount();

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
		BehaviorUpdate();
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
			break;
		case DEAD:
			m_bDead = true;
			break;
		default:
			break;

		}

		Monster_Dir();

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
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX * 0.5f,// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY * 0.5f,
		(int)m_tInfo.fCX* 0.5f,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY* 0.5f,
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
			m_tFrame.dwSpeed = 250;
			m_tFrame.dwTime = GetTickCount();
			break;

		case FLY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 8;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case LAND:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 9;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case POSE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion =10;
			m_tFrame.dwSpeed = 200;
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
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//플레이어와의 각도에 따라서 시선이 달라짐

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this); // 플레이어 객체 가져오기	

	if (m_pTarget != nullptr)
	{
		float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX + iScrollX)); // 밑변
		float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fX + iScrollY)); // 높이

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	

		float	fRadian = acosf(fWidth / fDiagonal); // 라디안 각도


		if (m_tInfo.fY < m_pTarget->Get_Info().fY)  //  cos 0도에서 180도 밖에 표현이 안되기때문에
			fRadian *= -1.f;

		m_fAngle = fRadian * 180.f / PI; // 각도

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
	srand(unsigned(time(nullptr)));

	currentState = PATTERN((rand() % None));
}

bool CBossMonster::TargetMove()
{
	return false;
}

void CBossMonster::BehaviorUpdate()
{
	switch (behaviorState)
	{
	case Enter:
		BehaviorEnter();
		break;

	case Execute:
		BehaviorExecute();
		break;

	case Exit:
		BehaviorExit();
		break;
	}
}

void CBossMonster::BehaviorEnter()
{
	if (!m_pTarget)
		return;

	behaviorState = Execute;
}

void CBossMonster::BehaviorExecute()
{
	switch (currentState)
	{

	case LAUNCH1:
		if (m_dwTime + 1000 < GetTickCount())
		{
			PatternNormalShot();
			m_dwTime = GetTickCount();
		}
		break;
	case LAUNCH2:
	
		if (m_dwTime + 1000 < GetTickCount())
		{
			PatternWideShot();
			m_dwTime = GetTickCount();
		}
		break;
	case LAUNCH3:
	
		if (m_dwTime + 100 < GetTickCount())
		{
			PatternContinueShot();
			m_dwTime = GetTickCount();
			
		}
		break;
	}

	behaviorState = Exit;

}

void CBossMonster::BehaviorExit()
{
	switch (currentState)
	{
		case LAUNCH1:
		case LAUNCH2:
		case LAUNCH3 :
			RandomPattern();
			currentState = None;
			break;

		case None:
			RandomPattern();
			break;
}

behaviorState = Enter;
}

void CBossMonster::PatternWideShot()
{
	int degree = 0;

	while (degree < 360)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<BossBullet>::Create(m_tInfo.fX, m_tInfo.fY, degree));
		degree += 30;
	}
}

void CBossMonster::PatternContinueShot()
{
	for (int i = 0; i < 2; ++i)
	{
			int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


			float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX + iScrollX));
			float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY + iScrollY));

			float	fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight)); //빗변	

			float	fRadian = acosf(fWidth / fDiagonal);


			if (m_pTarget->Get_Info().fY > (m_tInfo.fY + iScrollY))
				fRadian *= -1.f;

			m_fAngle = fRadian * 180.f / PI;

			m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
			m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<BossBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));

	}
	
}

void CBossMonster::PatternNormalShot()
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	float fWidth = (m_pTarget->Get_Info().fX - (m_tInfo.fX + iScrollX));
	float fHeight = (m_pTarget->Get_Info().fY - (m_tInfo.fY + iScrollY));

	float	fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight)); //빗변	

	float	fRadian = acosf(fWidth / fDiagonal);


	if (m_pTarget->Get_Info().fY > (m_tInfo.fY + iScrollY))
		fRadian *= -1.f;

	m_fAngle = fRadian * 180.f / PI;


	m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
	m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<BossBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));

	

}

void CBossMonster::PatternMoveToPlayer()
{
	m_eCurState = FLY;
}

void CBossMonster::Hit()
{
	m_iHp -= 1;
	m_eCurState = HIT;
}


void CBossMonster::OnCollision(void)
{
	Hit();

	 if (m_iHp <= 0)
	{
		m_bDeadEffect = true;

	}
	//hp의따라서 행동 만약에 hp가 0 보다 클때는 타격 이펙트를 true로 하고 아닐[때는 die 함수를 쓴다
}