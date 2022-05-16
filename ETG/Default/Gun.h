#pragma once
#include "Obj.h"

class CGun :
	public CObj
{
public:
	CGun();
	virtual ~CGun();

public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;
	virtual		void	OnCollision(void)	override;
	virtual		bool	Get_DeadEffect(void);
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;
public :
	void		Mouse_Sight(void);

private:

	POINT			m_tPoint[3];
	POINT			pt{};
	float			m_fDiagonal;
	POINT			m_tPosin;
};

