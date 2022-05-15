#include "stdafx.h"
#include "Gun.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"
CGun::CGun()
{
}

CGun::~CGun()
{
	Release();
}

void CGun::Initialize(void)
{	
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 1.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GundeadGun/Gun_LD.bmp", L"Gun_LD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GundeadGun/Gun_Left.bmp", L"Gun_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GundeadGun/Gun_Right.bmp", L"Gun_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GundeadGun/Gun_LU.bmp", L"Gun_LU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GundeadGun/Gun_RD.bmp", L"Gun_RD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GundeadGun/Gun_RU.bmp", L"Gun_RU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GundeadGun/Gun_Left_UP.bmp", L"Gun_Left_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GundeadGun/Gun_Right_UP.bmp", L"Gun_Right_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GundeadGun/Gun_Left_Down.bmp", L"Gun_Left_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GundeadGun/Gun_Right_Down.bmp", L"Gun_Right_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Weapon/Plg.bmp", L"Plg");

	m_fDiagonal = 15.f;
}

int CGun::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	//업데이트문에서 마우스 좌표가지고 와서 작을 경우에 프라임키 left주고 아닐경우에 right주기 
	Mouse_Sight();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CGun::Late_Update(void)
{
	if (m_pTarget == nullptr)
	{
		m_bDead = true;
	}
}

void CGun::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX ,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY ,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY ,
		RGB(255, 0, 255));			// 제거하고자 하는 색상/ 제거하고자 하는 색상


}

void CGun::Release(void)
{
}

void CGun::OnCollision(void)
{
}

bool CGun::Get_DeadEffect(void)
{
	return false;
}


void CGun::Mouse_Sight(void)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget != nullptr)
	{

		m_tInfo.fY = m_pTarget->Get_Info().fY + 11.f;
		m_tInfo.fX = m_pTarget->Get_Info().fX;
		GetCursorPos(&pt);	// 현재 마우스의 위치 좌표를 얻어오는 함수
		ScreenToClient(g_hWnd, &pt);	// 전체 스크린영역에서 생성한 클라이언트(창) 좌표로 변환


		float fWidth = (pt.x - (m_tInfo.fX + iScrollX)); //밑변  // 스크롤 넘어갔을때 문제 발생
		float fHeight = (pt.y - (m_tInfo.fY + iScrollY)); // 높이

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); //빗변	

		float	fRadian = acosf(fWidth / fDiagonal);	//두점 사이의 각도

		if (pt.y > (m_tInfo.fY + iScrollY))
			fRadian *= -1.f;

		m_fAngle = fRadian * 180.f / PI; //디그리 각도


		if (pt.x > m_tInfo.fX + iScrollX)
		{
			m_tInfo.fX += 16.f;

			if (25 <= m_fAngle &&  m_fAngle < 60)
			{
				m_pFrameKey = L"Gun_RU";
			}
			else if ((60 <= m_fAngle &&  m_fAngle < 88))
			{
				m_pFrameKey = L"Gun_Right_UP";

			}
			else if ((-5 <= m_fAngle &&  m_fAngle < 25))
			{
				m_pFrameKey = L"Gun_Right";

			}
			else if ((-20 <= m_fAngle &&  m_fAngle < -5))
			{
				m_pFrameKey = L"Gun_RD";
			}
			else if ((-60 <= m_fAngle &&  m_fAngle < -20))
			{
				m_pFrameKey = L"Gun_Right_Down";

			}
		}

		else if (pt.x < m_tInfo.fX + iScrollX)
		{
			m_tInfo.fX -= 16.f;
			if ((91 <= m_fAngle &&  m_fAngle < 115))
			{
				m_pFrameKey = L"Gun_Left_UP";

			}
			else if ((115 <= m_fAngle &&  m_fAngle < 150))
			{
				m_pFrameKey = L"Gun_LU";

			}
			else if ((150 <= m_fAngle &&  m_fAngle < 183))
			{
				m_pFrameKey = L"Gun_Left";

			}
			else if ((-120 <= m_fAngle &&  m_fAngle < -100))
			{
				m_pFrameKey = L"Gun_LD";

			}
			else if ((-100 <= m_fAngle &&  m_fAngle < -70))
			{
				m_pFrameKey = L"Gun_Left_Down";
			}
		}
		else
			m_pFrameKey = L"Plg";

		m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
		m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));

		if ((CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)))
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));

		}

	}

}
