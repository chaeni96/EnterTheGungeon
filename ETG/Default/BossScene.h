#pragma once
#include "Obj.h"
class CBossScene :
	public CObj
{
public:
	enum STATE { START, END };

public:
	CBossScene();
	~CBossScene();
public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;
	virtual		void	OnCollision(void)	override;
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;
	virtual		bool	Get_DeadEffect(void) override;
	void   Set_CollisionCheck(void) { m_bCollisionCheck = false; }

private:
	void		Motion_Change(void);

private:
	STATE		m_eCurState;
	STATE		m_ePreState;
	DWORD		m_DeleteTime;
};

