#include "stdafx.h"
#include "ScrollMgr.h"



CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}
void CScrollMgr::Scroll_Lock(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCX - 3600 > m_fScrollX)
		m_fScrollX = WINCX - 3600;

	if (WINCY - 2100 > m_fScrollY)
		m_fScrollY = WINCY - 2100;
}