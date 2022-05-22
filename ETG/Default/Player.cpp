#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "Mouse.h"
#include "Gun.h"
#include "Comando.h"
#include "BossMonster.h"
#include "Monster.h"
#include "Monster2.h"
#include "SceneMgr.h"
float	g_fSound = 10.f;

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
	m_tInfo.fX = 2822.f;
	m_tInfo.fY = 1720.f;

	m_tInfo.fCX = 40.f; // 20 * 25
	m_tInfo.fCY = 50.f;

	m_fSpeed = 5.f;
	m_iLife = 3;
	m_fDiagonal = 100.f;
	m_bDeadEffect = false;
	m_bRoll = false;
	m_bHitEffect = false;
	m_bGhost = false;
	m_CollisionCheck = false;
	m_bBossCheck = false;
	m_bMonster1Check = false;
	m_bMonster2Check = false;
	m_iHp = 50;
	m_pFrameKey = L"Player_RIGHT";
	m_eRender = RENDER_GAMEOBJECT;
	m_delayTime = GetTickCount();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LU.bmp", L"Player_LU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RU.bmp", L"Player_RU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LD.bmp", L"Player_LD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RD.bmp", L"Player_RD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Ghost.bmp", L"Player_Ghost");

	//CSoundMgr::Get_Instance()->PlaySoundW(L"Success.wav", SOUND_EFFECT, g_fSound);

}

int CPlayer::Update(void)
{
	if (m_bDeadEffect)
	{
		m_eCurState = DEAD;
		if (m_bGhost)
		{
			m_pFrameKey = L"Player_Ghost";
			m_eCurState = GHOST;

			if (m_bDead)
				return OBJ_DEAD;

		}
	}
	else
	{
		if (m_eCurState != HIT)
		{
		
		Mouse_Sight();
	}
		Key_Input();

		OffSet();
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_tInfo.fX == 2822.f && m_tInfo.fY == 1720.f)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('Q'))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_HIDDEN);

		}
	}
	if (m_tInfo.fX ==  1670 && m_tInfo.fY < 850)
	{
		if (m_delayTime + 4000 < GetTickCount())
		{
			if (!m_bBossCheck)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBossMonster>::Create());
				m_bBossCheck = true;
			}
			m_delayTime = GetTickCount();
		}

	}

	if (m_tInfo.fX < 2350 && m_tInfo.fY > 1300)
	{
		if (m_delayTime + 3000 < GetTickCount())
		{
			if (!m_bMonster1Check)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(1450.f, 1450.f, DIR_DOWN)); // +,+
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(1700.f, 1870.f, DIR_UP)); // -
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(1410.f, 1830.f, DIR_RIGHT)); //  +
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(1925.f, 1380.f, DIR_LEFT)); // -,-
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(1600.f, 1350.f, DIR_RIGHT)); // +, -
				//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(1930.f, 1930.f, DIR_RIGHT)); // +, -
				//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(1930.f, 1930.f, DIR_UP)); // +, -


				m_bMonster1Check = true;
			}
			m_delayTime = GetTickCount();
		}

	}

	if (m_tInfo.fX > 2250 && m_tInfo.fY == 1190)
	{
		if (m_delayTime + 2000 < GetTickCount())
		{
			if (!m_bMonster2Check)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster2>::Create(2177.f, 460.f, DIR_RIGHT)); // +,+
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster2>::Create(2177.f, 460.f, DIR_DOWN)); // +,+
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster2>::Create(2384.f, 760.f, DIR_UP)); // -
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster2>::Create(3044.f, 762.f, DIR_LEFT)); //  +

				m_bMonster2Check = true;
			}
			m_delayTime = GetTickCount();
		}

	}
	Motion_Change();

	if (Move_Frame() == true)
	{

		switch (m_eCurState)
		{
		case IDLE :
			m_tFrame.iFrameStart = 0;
			break;
		case HIT:
			m_bHitEffect = true;
			break;
		case WALK:
			m_tFrame.iFrameStart = 0;
			break;
		case ROLL:
			break;
		case DEAD:
			m_bGhost = true;
			break;
		case GHOST:
			m_bDead = true;
			break;

		default:
			break;
		}
		Mouse_Sight();

	}

	
	

}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();



	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX + 40.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY + 51.f),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX ,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY ,
		((int)m_tInfo.fCX ),				// 복사할 비트맵의 가로, 세로 길이
		((int)m_tInfo.fCY),
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상

				
}
void CPlayer::Release(void)
{


}



void CPlayer::Mouse_Sight(void)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	//마우스 실시간 좌표 받아오기

	GetCursorPos(&pt);	// 현재 마우스의 위치 좌표를 얻어오는 함수
	ScreenToClient(g_hWnd, &pt);	// 전체 스크린영역에서 생성한 클라이언트(창) 좌표로 변환

	// 플레이어의 중점과 마우스의 각도 구하기

	float fWidth = (pt.x - (m_tInfo.fX + iScrollX)); //밑변  // 스크롤 넘어갔을때 문제 발생
	float fHeight = (pt.y  - (m_tInfo.fY + iScrollY)); // 높이

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	
															
	float	fRadian = acosf(fWidth / fDiagonal);	//두점 사이의 각도

	if (pt.y > (m_tInfo.fY + iScrollY))
		fRadian *= -1.f;
	
	m_fAngle = fRadian * 180.f / PI; //디그리 각도

	if (25 <= m_fAngle &&  m_fAngle < 60)
	{
		m_pFrameKey = L"Player_RU";
		m_eCurState = IDLE;

	}
	else if ((60 <= m_fAngle &&  m_fAngle < 115))
	{
		m_pFrameKey = L"Player_UP";
		m_eCurState = IDLE;

	}
	else if ((115 <= m_fAngle &&  m_fAngle < 150))
	{
		m_pFrameKey = L"Player_LU";
		m_eCurState = IDLE;

	}
	else if ((150 <= m_fAngle &&  m_fAngle < 183))
	{
		m_pFrameKey = L"Player_LEFT";
		m_eCurState = IDLE;

	}
	else if ((-120 <= m_fAngle &&  m_fAngle < -100))
	{
		m_pFrameKey = L"Player_LEFT";
		m_eCurState = IDLE;


	}
	else if ((-100 <= m_fAngle &&  m_fAngle < -40))
	{
		m_pFrameKey = L"Player_DOWN";
		m_eCurState = IDLE;

	}
	else if ((-40 <= m_fAngle &&  m_fAngle < 25))
	{
		m_pFrameKey = L"Player_RIGHT";	
		m_eCurState = IDLE;

	}
	
	else {
		m_eCurState = IDLE;
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		m_eCurState = ROLL;
	}


}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	
		if (GetAsyncKeyState('A'))
		{
			m_tInfo.fX -= m_fSpeed;
			if (!m_bHitEffect)
			{
				m_eCurState = WALK;
			}
		}
		else if (GetAsyncKeyState('D'))
		{
			m_tInfo.fX += m_fSpeed;
			if (!m_bHitEffect)
			{
				m_eCurState = WALK;
			}

		}
		else if (GetAsyncKeyState('W'))
		{
			m_tInfo.fY -= m_fSpeed;
			if (!m_bHitEffect)
			{
				m_eCurState = WALK;
			}

		}
		else if (GetAsyncKeyState('S'))
		{
			m_tInfo.fY += m_fSpeed;
			if (!m_bHitEffect)
			{
				m_eCurState = WALK;
			}
		}
		
		//함수하나 만들기
		
		//컨트롤 눌렀을때 무기변환하도록 하고 처음 생성시에 무조건 기본 총 만들게 한다 그다음에 컨트롤 눌렀을때 생성한것가지고 와서 타입 비교
		if (GetAsyncKeyState(0x31)) // 1번눌렀을때 일반 총
		{
			CObjMgr::Get_Instance()->Weapon_Change(TYPE_WEAPON_GUN);
			m_eCurState = WALK;

		}
		
		else if (GetAsyncKeyState(0x32)) // 2번 눌렀을때 코만도
		{
			CObjMgr::Get_Instance()->Weapon_Change(TYPE_WEAPON_COMANDO);
			m_eCurState = WALK;

		}
		else if (GetAsyncKeyState(0x33)) // 3번 눌렀을때 램프
		{
			CObjMgr::Get_Instance()->Weapon_Change(TYPE_WEAPON_LAMP);
			m_eCurState = WALK;

		}
		else if (GetAsyncKeyState(0x34)) // 4번 눌렀을때 램프
		{
			CObjMgr::Get_Instance()->Weapon_Change(TYPE_WEAPON_SHARK);
			m_eCurState = WALK;

		}

		//2번 눌렀을때 코만도 생성해야하는데 WEAPON이 비었을때? 그리고 코만도를 생성했을때는 일반총을 삭제해줘야한다
		
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			m_eCurState = ROLL;
		}



}


void CPlayer::Hit(void)
{
	m_eCurState = HIT;
	m_bHitEffect = true;

	if (!m_CollisionCheck)
	{
		m_iHp -= 1;
		m_CollisionCheck = true;
	}
}

void CPlayer::OnCollision(void)
{
	if (m_eCurState != ROLL)
	{
		Hit();

		if (m_iHp <= 0)
		{
			m_bDeadEffect = true;
		}

	}
	
}

//타일 충돌
void CPlayer::OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY)
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



void CPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int		iItvX = 100;
	int		iItvY = 50;

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
		case GHOST:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

