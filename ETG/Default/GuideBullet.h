#pragma once
#include "Obj.h"
class CGuideBullet :
	public CObj
{
public:
	CGuideBullet();
	virtual ~CGuideBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual		void	OnCollision(void)	override;
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;
	bool Get_DeadEffect() { return m_bDeadEffect; }
	void   Set_CollisionCheck(void) { m_bCollisionCheck = false; }

};

