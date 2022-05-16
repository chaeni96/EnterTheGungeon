#pragma once
#include "Obj.h"
#include "Bullet.h"

class CPlayer : public CObj
{
public:
	enum STATE  { IDLE, WALK, ROLL, DEAD, HIT, GHOST, END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int		Update(void) override;
	virtual	void	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual		void	OnCollision(void)	override;
	bool Get_DeadEffect() { return m_bDeadEffect; }
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;

public :
	bool		Check_Roll(void) { return m_bRoll; }
	STATE  Get_State(void) { return m_eCurState; }
	void   Set_CollisionCheck(void) { m_CollisionCheck = false; }

private:
	void		Mouse_Sight(void); // 마우스 위치에 따라서 플레이어의 시선방향 움직임
	void		Key_Input(void);
	void		OffSet(void);
	void		Motion_Change(void);
	void		Hit(void);

private:
	float					m_fDiagonal;
	DWORD					m_delayTime;
	
	STATE					m_ePreState;
	STATE					m_eCurState;
	bool					m_bDeadEffect;
	bool					m_bHitEffect;
	bool					m_CollisionCheck;
	bool					m_bStretch = true;
	bool					m_bRoll; // 구르는 상태 확인
	bool					m_bGhost;
	int iCount;
	POINT	pt{};

};
