#pragma once
#include "Obj.h"
class CJunior :
	public CObj
{
public:
	enum STATE { IDLE, ATTACK, END };
public:
	CJunior();
	~CJunior();


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
	void		Player_Dir(void);
private:
	float  m_fDiagonal;
	STATE		m_eCurState;
	STATE		m_ePreState;
	DWORD		m_DelayTime;
};

