#pragma once
#include "Obj.h"
class CHost :
	public CObj
{
public: 
	enum STATE{IDLE, ATTACK_DOWN, ATTACK_RD, ATTACK_RIGHT, HIT, FAINT, DEAD, END};
public:
	CHost();
	virtual ~CHost();


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
	void		Hit();
	void		Attack();

private:
	STATE		m_eCurState;
	STATE		m_ePreState;
	bool		m_bDeadEffect;

	float			m_fDiagonal;
	POINT			m_tPosin;
	DWORD			m_pTime;
	DWORD			m_DelayTime;
};

