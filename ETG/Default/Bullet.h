#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	enum STATE { NOMAL, BOOM, BULLET_END };

public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual		void	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual		void	OnCollision(void)	override;
	bool Get_DeadEffect() { return m_bDeadEffect; }
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;
	void   Set_CollisionCheck(void) { m_bCollisionCheck = false; }

private:
	void		Motion_Change(void);

private:
	STATE	m_eCurState;
	STATE   m_ePreState;
};

