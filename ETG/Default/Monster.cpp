#include "stdafx.h"
#include "Monster.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	m_tInfo.fX = 200.f;
	m_tInfo.fY = 200.f;

	m_fSpeed = 5.f;

	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Plg.bmp", L"Rotation");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Reset.bmp", L"Reset");
	
	m_pFrameKey = L"Monster";	
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	float	fDiagonal = sqrtf((m_tInfo.fCX / 2.f) * (m_tInfo.fCX / 2.f) + (m_tInfo.fCY / 2.f)  * (m_tInfo.fCY / 2.f));

	// 좌 상단

	m_tPoint[0].x = long(fDiagonal * cosf((m_fAngle + 135.f) * PI / 180.f) + (m_tInfo.fCX / 2.f));
	m_tPoint[0].y = long(fDiagonal * -sinf((m_fAngle + 135.f) * PI / 180.f) + (m_tInfo.fCY / 2.f));

	// 우 상단

	m_tPoint[1].x = long(fDiagonal * cosf((m_fAngle + 45.f) * PI / 180.f) + (m_tInfo.fCX / 2.f));
	m_tPoint[1].y = long(fDiagonal * -sinf((m_fAngle + 45.f) * PI / 180.f) + (m_tInfo.fCY / 2.f));

	// 좌 하단

	m_tPoint[2].x = long(fDiagonal * cosf((m_fAngle + 225.f) * PI / 180.f) + (m_tInfo.fCX / 2.f));
	m_tPoint[2].y = long(fDiagonal * -sinf((m_fAngle + 225.f) * PI / 180.f) + (m_tInfo.fCY / 2.f));
		
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		m_fAngle += 5.f;

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		m_fAngle -= 5.f;

}

void CMonster::Render(HDC hDC)
{
	HDC		hRotationDC = CBmpMgr::Get_Instance()->Find_Image(L"Rotation");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	HDC		hResetDC = CBmpMgr::Get_Instance()->Find_Image(L"Reset");
	
	PlgBlt(hRotationDC,			// 회전 시킬 이미지를 어디에 그릴 것인지 설정
			m_tPoint,			// 그림을 그릴 사각형의 좌표 포인트 변수 3개, 배열의 이름을 전달(배열의 순서는 좌 상단, 우 상단, 좌 하단)
			hMemDC,				// 어디에 있는 이미지에 회전을 적용할 것인가
			0,					//그림을 그릴 이미지 X, Y 시작 좌표
			0, 
			(int)m_tInfo.fCX,	// 그릴 이미지의 가로, 세로 길이
			(int)m_tInfo.fCY,
			NULL, 
			NULL, 
			NULL);

	GdiTransparentBlt(hDC, 					
		int(m_tRect.left),	
		int(m_tRect.top),
		int(m_tInfo.fCX),				
		int(m_tInfo.fCY),
		hRotationDC,
		0,
		0,
		(int)m_tInfo.fCX,		
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	


	BitBlt(hRotationDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hResetDC, 0, 0, SRCCOPY);


}

void CMonster::Release(void)
{
	
}
