#pragma once
#include "Obj.h"
class CMonster : public CObj
{
public:
	enum STATE {MONSTER_UP, MONSTER_RIGHT, MONSTER_DOWN, MONSTER_LEFT, MONSTER_HIT, MONSTER_DEAD, MONSTER_END};
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual		void	OnCollision(void)	override;
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;
	virtual		bool	Get_DeadEffect(void);

private:
	void		Motion_Change(void);
	void		Monster_Dir(void);

private:
	STATE		m_eCurState;
	STATE		m_ePreState;
	bool		m_bDeadEffect;

};

