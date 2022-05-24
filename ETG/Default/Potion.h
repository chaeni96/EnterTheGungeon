#pragma once
#include "Obj.h"
class CPotion :
	public CObj
{
public:
	CPotion();
	virtual ~CPotion();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;
	void   Set_CollisionCheck(void) { m_bCollisionCheck = false; }

	virtual		void	OnCollision(void)	override;
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;
	virtual		bool	Get_DeadEffect(void) override;
};

