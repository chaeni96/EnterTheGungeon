#pragma once
#include "Obj.h"
class CComando :
	public CObj
{
public:
	CComando();
	virtual ~CComando();

public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;

public:
	void		Mouse_Sight(void);

private:

	POINT			m_tPoint[3];
	POINT			pt{};
	float			m_fDiagonal;
	POINT			m_tPosin;
	DWORD			m_dwTime;
};
