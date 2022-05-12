#pragma once

#include "Include.h"
#include "Obj.h"
class CUi
{
public:
	CUi();
	virtual ~CUi();

public:
	virtual void	Initialize(void) PURE;
	virtual int	Update(void) PURE;
	virtual void	Late_Update(void) PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release(void) PURE;
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }
	const RENDERID	Get_RenderID(void) const { return m_eRender; }

	bool		Get_Dead() { return m_bDead; }

protected:
	void		Update_Rect(void);
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;

	bool		m_bDead;
	CObj* m_pTarget;
	RENDERID	m_eRender;

};

