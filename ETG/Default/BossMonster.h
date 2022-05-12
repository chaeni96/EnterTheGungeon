#pragma once
#include "Obj.h"
class CBossMonster :
	public CObj
{
public:
	enum STATE {RU, RIGHT, RD, DOWN, LD, LEFT, LU, HIT, DEAD, FLY, LAND, POSE, END };
public:
	CBossMonster();
	virtual ~CBossMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Motion_Change(void);
	void		Monster_Dir(void);


private:
	STATE m_ePreState;
	STATE m_eCurState;
	float			m_fDiagonal;
	POINT			m_tPosin;
};

