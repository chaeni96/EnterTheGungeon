#pragma once
#include "Obj.h"
class CMonster : public CObj
{
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
	virtual		bool	Get_DeadEffect(void);
private:
	POINT			m_tPoint[3];		// аб ╩С╢э, ©Л ╩С╢э, аб го╢э

};

