#include "stdafx.h"
#include "Ending.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
CEnding::CEnding()
	:m_eCurState(START), m_ePreState(END)

{
}


CEnding::~CEnding()
{
	Release();

}

void CEnding::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ending/Ending.bmp", L"Ending");
	CSoundMgr::Get_Instance()->PlaySoundW(L"Opening_Ending.mp3", SOUND_EFFECT, 1.5f);

}

void CEnding::Update(void)
{

}

void CEnding::Late_Update(void)
{
	
	Motion_Change();
	Move_Frame();
}

void CEnding::Render(HDC hDC)
{

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, m_tFrame.iFrameStart *WINCX, m_tFrame.iMotion *WINCY, SRCCOPY);
}

void CEnding::Release(void)
{
}

void CEnding::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();

		m_ePreState = m_eCurState;
	}
}
