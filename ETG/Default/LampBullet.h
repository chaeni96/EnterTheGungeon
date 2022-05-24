#pragma once
#include "Obj.h"

class CLampBullet:
	public CObj
{
public:
	enum STATE { NOMAL, BOOM, BULLET_END };

public:
	CLampBullet();
	~CLampBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual	void OnCollision(void)	override;
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;
	void   Set_CollisionCheck(void) { m_bCollisionCheck = false; }

public:
	bool Get_DeadEffect() { return m_bDeadEffect; }
private:
	void		Motion_Change(void);


private:
	POINT			pt{};

	STATE	m_eCurState;
	STATE   m_ePreState;
};

